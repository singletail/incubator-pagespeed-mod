/*
 * Copyright 2011 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Author: pulkitg@google.com (Pulkit Goyal)

#include "net/instaweb/http/public/content_type.h"
#include "net/instaweb/http/public/log_record.h"
#include "net/instaweb/http/public/logging_proto.h"
#include "net/instaweb/http/public/logging_proto_impl.h"
#include "net/instaweb/public/global_constants.h"
#include "net/instaweb/rewriter/public/delay_images_filter.h"
#include "net/instaweb/rewriter/public/js_disable_filter.h"
#include "net/instaweb/rewriter/public/lazyload_images_filter.h"
#include "net/instaweb/rewriter/public/server_context.h"
#include "net/instaweb/rewriter/public/rewrite_test_base.h"
#include "net/instaweb/rewriter/public/rewrite_driver.h"
#include "net/instaweb/rewriter/public/rewrite_options.h"
#include "net/instaweb/rewriter/public/static_asset_manager.h"
#include "net/instaweb/util/enums.pb.h"
#include "net/instaweb/util/public/abstract_mutex.h"
#include "net/instaweb/util/public/gtest.h"
#include "net/instaweb/util/public/string.h"
#include "net/instaweb/util/public/string_util.h"
#include "pagespeed/kernel/util/wildcard.h"

namespace {
const char kAndroidMobileUserAgent1[] = "Android 3.1 Mobile Safari";
const char kAndroidMobileUserAgent2[] = "Android 4 Mobile Safari";

const char kSampleJpgFile[] = "Sample.jpg";
const char kSampleWebpFile[] = "Sample_webp.webp";
const char kLargeJpgFile[] = "Puzzle.jpg";
const char kSmallPngFile[] = "BikeCrashIcn.png";

const char kBlankImageSrc[] = "/psajs/1.0.gif";

// Generated html is matched approximately because different versions of
// libjpeg are yeilding different low_res_image_data.
const char kSampleJpegData[] = "data:image/jpeg;base64*";
const char kSampleWebpData[] = "data:image/webp;base64*";

const char kHeadHtml[] = "<head></head>";

const char kHeadHtmlWithDeferJsTemplate[] =
    "<head><script type=\"text/javascript\" pagespeed_no_defer=\"\">"
    "%s"
    "</script>"
    "</head>";

const char kDeferJsTemplate[] =
    "<script type=\"text/javascript\" src=\"/psajs/js_defer.0.js\"></script>";

const char kLazyloadTemplate[] =
    "<script type=\"text/javascript\" pagespeed_no_defer=\"\">"
    "%s"
    "\npagespeed.lazyLoadInit(false, \"%s\");\n"
    "</script>";

const char kInlineScriptTemplate[] =
    "<script type=\"text/javascript\">%s";

const char kScriptTemplate[] =
    "<script type=\"text/javascript\">%s</script>";

}  // namespace

namespace net_instaweb {

class DelayImagesFilterTest : public RewriteTestBase {
 public:
  DelayImagesFilterTest() {
    options()->set_min_image_size_low_resolution_bytes(1 * 1024);
    options()->set_max_inlined_preview_images_index(-1);
  }

 protected:
  // TODO(matterbury): Delete this method as it should be redundant.
  virtual void SetUp() {
    RewriteTestBase::SetUp();
    SetHtmlMimetype();  // Prevent insertion of CDATA tags to static JS.
  }

  virtual bool AddHtmlTags() const { return false; }
  // Match rewritten html content and return its byte count.
  int MatchOutputAndCountBytes(const GoogleString& html_input,
                               const GoogleString& expected) {
    Parse("inline_preview_images", html_input);
    GoogleString full_html = doctype_string_ + AddHtmlBody(expected);
    EXPECT_TRUE(Wildcard(full_html).Match(output_buffer_)) <<
        "Expected:\n" << full_html << "\n\nGot:\n" << output_buffer_;
    int output_size = output_buffer_.size();
    output_buffer_.clear();
    return output_size;
  }

  GoogleString GetNoscript() const {
    return StringPrintf(
        kNoScriptRedirectFormatter,
        "http://test.com/inline_preview_images.html?ModPagespeed=noscript",
        "http://test.com/inline_preview_images.html?ModPagespeed=noscript");
  }

  GoogleString GenerateAddLowResString(const GoogleString& url,
                                       const GoogleString& image_data) {
    return StrCat("\npagespeed.delayImagesInline.addLowResImages(\'", url,
        "\', \'", image_data, "\');");
  }

  GoogleString GenerateRewrittenImageTag(const StringPiece& url) {
    return StrCat("<img pagespeed_lazy_src=\"", url, "\" src=\"",
                  kBlankImageSrc, "\" onload=\"",
                  LazyloadImagesFilter::kImageOnloadCode, "\"/>");
  }

  GoogleString GetHeadHtmlWithDeferJs() {
    return StringPrintf(kHeadHtmlWithDeferJsTemplate,
                        JsDisableFilter::kDisableJsExperimental);
  }

  GoogleString GetDeferJs() {
    return kDeferJsTemplate;
  }

  GoogleString GetHtmlWithLazyload() {
    return StringPrintf(kLazyloadTemplate,
                        GetLazyloadImagesCode().c_str(),
                        kBlankImageSrc);
  }

  GoogleString GetInlineScript() {
    return StringPrintf(kInlineScriptTemplate,
                        GetDelayImagesInlineCode().c_str());
  }

  GoogleString GetDelayImages() {
    return StringPrintf(kScriptTemplate, GetDelayImagesCode().c_str());
  }

  GoogleString GetDelayImagesCode() {
    GoogleString delayImagesSuffix = StrCat(
        DelayImagesFilter::kDelayImagesSuffix,
        "\npagespeed.delayImages.replaceWithHighRes();\n");
    return GetJsCode(StaticAssetManager::kDelayImagesJs, delayImagesSuffix);
  }

  GoogleString GetDelayImagesLazyLoad() {
    return StringPrintf(kScriptTemplate, GetDelayImagesLazyLoadCode().c_str());
  }

  GoogleString GetDelayImagesLazyLoadCode() {
    GoogleString delayImagesSuffix = StrCat(
        DelayImagesFilter::kDelayImagesSuffix,
        "\npagespeed.delayImages.registerLazyLoadHighRes();\n");
    return GetJsCode(StaticAssetManager::kDelayImagesJs, delayImagesSuffix);
  }

  GoogleString GetDelayImagesInlineCode() {
    return GetJsCode(StaticAssetManager::kDelayImagesInlineJs,
                     DelayImagesFilter::kDelayImagesInlineSuffix);
  }

  GoogleString GetLazyloadImagesCode() {
    return server_context()->static_asset_manager()->GetAsset(
        StaticAssetManager::kLazyloadImagesJs, options());
  }

  GoogleString GetJsCode(StaticAssetManager::StaticAsset module,
                         const StringPiece& call) {
    StringPiece code =
        server_context()->static_asset_manager()->GetAsset(module, options());
    return StrCat(code, call);
  }

  void SetupUserAgentTest(StringPiece user_agent) {
    ClearRewriteDriver();
    rewrite_driver()->SetUserAgent(user_agent);
    SetHtmlMimetype();  // Prevent insertion of CDATA tags to static JS.
  }

  void ExpectLogRecord(int index, const RewriterInfo& expected_info) {
    ScopedMutex lock(rewrite_driver()->log_record()->mutex());
    ASSERT_LT(index, rewrite_driver()->log_record()->logging_info()
              ->rewriter_info_size());
    const RewriterInfo& actual_info = rewrite_driver()->log_record()
        ->logging_info()->rewriter_info(index);
    EXPECT_EQ(expected_info.id(), actual_info.id());
    EXPECT_EQ(expected_info.status(), actual_info.status());
    EXPECT_EQ(expected_info.has_rewrite_resource_info(),
              actual_info.has_rewrite_resource_info());
    EXPECT_EQ(expected_info.has_image_rewrite_resource_info(),
              actual_info.has_image_rewrite_resource_info());
    if (expected_info.has_rewrite_resource_info()) {
      EXPECT_EQ(expected_info.rewrite_resource_info().is_inlined(),
                actual_info.rewrite_resource_info().is_inlined());
      EXPECT_EQ(expected_info.rewrite_resource_info().is_critical(),
                actual_info.rewrite_resource_info().is_critical());
    }
    if (expected_info.has_image_rewrite_resource_info()) {
      const ImageRewriteResourceInfo& expected_image_info =
          expected_info.image_rewrite_resource_info();
      const ImageRewriteResourceInfo& actual_image_info =
          actual_info.image_rewrite_resource_info();
      EXPECT_EQ(expected_image_info.is_low_res_src_inserted(),
                actual_image_info.is_low_res_src_inserted());
      EXPECT_GE(expected_image_info.low_res_size(),
                actual_image_info.low_res_size());
    }
  }
};

TEST_F(DelayImagesFilterTest, DelayImagesAcrossDifferentFlushWindow) {
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                         kContentTypeWebp, 100);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString flush1 = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp\" />";
  GoogleString flush2="<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString input = StrCat(flush1, flush2);
  SetupWriter();
  html_parse()->StartParse("http://test.com/");
  html_parse()->ParseText(flush1);
  html_parse()->Flush();
  html_parse()->ParseText(flush2);
  html_parse()->FinishParse();

  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      StrCat("<body>",
             StringPrintf(kNoScriptRedirectFormatter,
                          "http://test.com/?ModPagespeed=noscript",
                          "http://test.com/?ModPagespeed=noscript"),
             "<img pagespeed_high_res_src=\"http://test.com/1.webp\"/>"),
      GetInlineScript(),
      StrCat("</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.webp",
                                     kSampleWebpData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             GetDelayImages()),
      StrCat("<img pagespeed_high_res_src=\"http://test.com/1.jpeg\"/>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.jpeg", kSampleJpegData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>"
             "<script type=\"text/javascript\">"
             "\npagespeed.delayImages.replaceWithHighRes();\n</script>"
             "</body>", GetDeferJs()));
  EXPECT_TRUE(Wildcard(output_html).Match(output_buffer_));
  EXPECT_TRUE(AppliedRewriterStringFromLog().find("di") !=
              GoogleString::npos);

  {
    ScopedMutex lock(rewrite_driver()->log_record()->mutex());
    EXPECT_EQ(4, rewrite_driver()->log_record()->logging_info()
              ->rewriter_info_size());
  }

  RewriterInfo expected1;
  expected1.set_id("ic");
  expected1.set_status(RewriterApplication::NOT_APPLIED);
  RewriteResourceInfo& expected_resource1 =
      *(expected1.mutable_rewrite_resource_info());
  expected_resource1.set_is_inlined(false);
  expected_resource1.set_is_critical(true);
  ImageRewriteResourceInfo& expected_image1 =
      *(expected1.mutable_image_rewrite_resource_info());
  expected_image1.set_is_low_res_src_inserted(true);
  expected_image1.set_low_res_size(916);

  RewriterInfo expected2;
  expected2.set_id("di");
  expected2.set_status(RewriterApplication::APPLIED_OK);

  ExpectLogRecord(0, expected1);
  ExpectLogRecord(1, expected2);
  expected1.mutable_image_rewrite_resource_info()->set_low_res_size(1072);
  ExpectLogRecord(2, expected1);
  ExpectLogRecord(3, expected2);
}

TEST_F(DelayImagesFilterTest, DelayImagesPreserveURLsOn) {
  // Make sure that we don't delay images when preserve urls is on.
  options()->set_image_preserve_urls(true);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  const char kInputHtml[] =
      "<html><head></head><body>"
      "<img src=\"http://test.com/1.jpeg\"/>"
      "</body></html>";

  MatchOutputAndCountBytes(kInputHtml, kInputHtml);
}

TEST_F(DelayImagesFilterTest, DelayImageInsideNoscript) {
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<noscript><img src=\"http://test.com/1.webp\" /></noscript>"
      "</body>";
  GoogleString output_html = StrCat(
      "<head></head>",
      StrCat("<body>", GetNoscript(), "<noscript>"
             "<img src=\"http://test.com/1.webp\"/></noscript></body>"));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayImageWithDeferJavascriptDisabled) {
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp\" />"
      "</body>";
  GoogleString output_html = StrCat(
      "<head></head>",
      StrCat("<body>",
             GetNoscript(),
             "<img pagespeed_high_res_src=\"http://test.com/1.webp\" "),
      "src=\"", kSampleWebpData, "\"/>", GetDelayImages(), "</body>");
  MatchOutputAndCountBytes(input_html, output_html);
  rewrite_driver_->log_record()->WriteLog();
  LoggingInfo* logging_info = rewrite_driver_->log_record()->logging_info();
  for (int i = 0; i < logging_info->rewriter_stats_size(); i++) {
    if (logging_info->rewriter_stats(i).id() == "di" &&
        logging_info->rewriter_stats(i).has_html_status()) {
      EXPECT_EQ(RewriterHtmlApplication::ACTIVE,
                logging_info->rewriter_stats(i).html_status());
      return;
    }
  }
  FAIL();
}

TEST_F(DelayImagesFilterTest, DelayImageWithUnsupportedUserAgent) {
  AddFilter(RewriteOptions::kDelayImages);
  SetupUserAgentTest("unsupported");
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp\"/>"
      "</body>";
  MatchOutputAndCountBytes(input_html, input_html);
  rewrite_driver_->log_record()->WriteLog();
  LoggingInfo* logging_info = rewrite_driver_->log_record()->logging_info();
  for (int i = 0; i < logging_info->rewriter_stats_size(); i++) {
    if (logging_info->rewriter_stats(i).id() == "di" &&
        logging_info->rewriter_stats(i).has_html_status()) {
      EXPECT_EQ(RewriterHtmlApplication::USER_AGENT_NOT_SUPPORTED,
                logging_info->rewriter_stats(i).html_status());
      return;
    }
  }
  FAIL();
}

TEST_F(DelayImagesFilterTest, DelayImageWithQueryParam) {
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  options()->DisableFilter(RewriteOptions::kInlineImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp?a=b&c=d", kSampleWebpFile,
                       kContentTypeWebp, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp?a=b&amp;c=d\" />"
      "</body>";
  GoogleString output_html = StrCat(
      "<head></head><body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.webp?a=b&amp;c=d\" "
      "src=\"", kSampleWebpData, "\"/>", GetDelayImages(), "</body>");
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayImageWithUnescapedQueryParam) {
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  options()->DisableFilter(RewriteOptions::kInlineImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp?a=b&c=d", kSampleWebpFile,
                       kContentTypeWebp, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp?a=b&c=d\" />"
      "</body>";
  GoogleString output_html = StrCat(
      "<head></head><body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.webp?a=b&c=d\" "
      "src=\"", kSampleWebpData, "\"/>", GetDelayImages(), "</body>");
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayImageWithLazyLoadDisabled) {
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp\" />"
      "</body>";
  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      "<body>",
      GetNoscript(),
      StrCat("<img pagespeed_high_res_src=\"http://test.com/1.webp\" ",
             "src=\"", kSampleWebpData, "\"/>"),
      GetDelayImages(), "</body>", GetDeferJs());
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayWebPImage) {
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp\" />"
      "<input src=\"http://test.com/1.webp\" type=\"image\"/>"
      "</body>";
  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      "<body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.webp\"/>",
      "<input pagespeed_high_res_src=\"http://test.com/1.webp\"",
      " type=\"image\"/>",
      StrCat(GetInlineScript(),
             "</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.webp", kSampleWebpData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             GetDelayImages(), "</body>", GetDeferJs()));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayJpegImage) {
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      "<body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\"/>",
      StrCat(GetInlineScript(),
             "</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.jpeg", kSampleJpegData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             GetDelayImages(), "</body>", GetDeferJs()));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayImageWithMobileAggressiveEnabled) {
  options()->set_enable_aggressive_rewriters_for_mobile(true);
  SetupUserAgentTest(kAndroidMobileUserAgent1);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat(
      "<head></head><body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\"/>",
      StrCat(GetInlineScript(),
             "</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.jpeg", kSampleJpegData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             GetDelayImages(), "</body>"));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayImageWithMobileLazyLoad) {
  options()->set_enable_aggressive_rewriters_for_mobile(true);
  options()->set_lazyload_highres_images(true);
  SetupUserAgentTest(kAndroidMobileUserAgent1);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat(
      "<head></head><body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\"/>",
      StrCat(GetInlineScript(),
             "</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.jpeg", kSampleJpegData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             GetDelayImagesLazyLoad(), "</body>"));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayImageWithMobileAndExperimentEnabled) {
  options()->set_enable_aggressive_rewriters_for_mobile(true);
  options()->set_enable_inline_preview_images_experimental(true);
  SetupUserAgentTest(kAndroidMobileUserAgent1);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat(
      "<head></head><body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\"/>",
      StrCat(GetInlineScript(),
             "</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.jpeg", kSampleJpegData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             "</body>"));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayJpegImageOnInputElement) {
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<input type=\"image\" src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      "<body>",
      GetNoscript(),
      "<input type=\"image\"",
      " pagespeed_high_res_src=\"http://test.com/1.jpeg\"/>",
      StrCat(GetInlineScript(),
             "</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.jpeg", kSampleJpegData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             GetDelayImages(), "</body>", GetDeferJs()));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, TestMinImageSizeLowResolutionBytesFlag) {
  options()->set_min_image_size_low_resolution_bytes(2 * 1024);
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  // Size of 1.webp is 1780 and size of 1.jpeg is 6245. As
  // MinImageSizeLowResolutionBytes is set to 2 KB only jpeg low quality image
  // will be generated.
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp\" />"
      "<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      "<body>",
      GetNoscript(),
      GetHtmlWithLazyload(),
      GenerateRewrittenImageTag("http://test.com/1.webp"),
      "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\"/>"
      "<script type=\"text/javascript\" pagespeed_no_defer=\"\">"
      "pagespeed.lazyLoadImages.overrideAttributeFunctions();</script>",
      StrCat(GetInlineScript(),
             "</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.jpeg", kSampleJpegData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             GetDelayImages(), "</body>", GetDeferJs()));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, TestMaxImageSizeLowResolutionBytesFlag) {
  options()->set_max_image_size_low_resolution_bytes(4 * 1024);
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  // Size of 1.webp is 1780 and size of 1.jpeg is 6245. As
  // MaxImageSizeLowResolutionBytes is set to 4 KB only webp low quality image
  // will be generated.
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp\" />"
      "<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      "<body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.webp\"/>",
      StrCat(GetInlineScript(),
             StrCat("</script>",
                 "<script type=\"text/javascript\">",
                 GenerateAddLowResString("http://test.com/1.webp",
                     kSampleWebpData),
                 "\npagespeed.delayImagesInline.replaceWithLowRes();\n"
                 "</script>",
                 GetDelayImages(),
                 GetHtmlWithLazyload(),
                 GenerateRewrittenImageTag("http://test.com/1.jpeg")),
             "<script type=\"text/javascript\" pagespeed_no_defer=\"\">"
             "pagespeed.lazyLoadImages.overrideAttributeFunctions();</script>"
             "</body>", GetDeferJs()));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, TestMaxInlinedPreviewImagesIndexFlag) {
  options()->set_max_inlined_preview_images_index(1);
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\" />"
      "<img src=\"http://test.com/1.webp\" />"
      "</body>";
  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      "<body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\"/>",
      StrCat(GetInlineScript(),
             StrCat("</script>",
                    "<script type=\"text/javascript\">",
                    GenerateAddLowResString("http://test.com/1.jpeg",
                                            kSampleJpegData),
                    "\npagespeed.delayImagesInline.replaceWithLowRes();\n"
                    "</script>",
                    GetDelayImages(),
                    GetHtmlWithLazyload()),
             GenerateRewrittenImageTag("http://test.com/1.webp"),
             "<script type=\"text/javascript\" pagespeed_no_defer=\"\">"
             "pagespeed.lazyLoadImages.overrideAttributeFunctions();</script>"
             "</body>", GetDeferJs()));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, DelayMultipleSameImage) {
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);

  // pagespeed_inline_map size will be 1. For same images, delay_images_filter
  // make only one entry in pagespeed_inline_map.
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.webp\" />"
      "<img src=\"http://test.com/1.webp\" />"
      "</body>";
  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      "<body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.webp\"/>"
      "<img pagespeed_high_res_src=\"http://test.com/1.webp\"/>",
      StrCat(GetInlineScript(),
             "</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.webp", kSampleWebpData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             GetDelayImages(), "</body>", GetDeferJs()));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, NoHeadTag) {
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  GoogleString input_html = "<body>"
      "<img src=\"http://test.com/1.webp\"/>"
      "</body>";
  GoogleString output_html = StrCat(
      "<body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.webp\" ",
      "src=\"", kSampleWebpData, "\"/>", GetDelayImages(), "</body>");
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, MultipleBodyTags) {
  options()->EnableFilter(RewriteOptions::kDeferJavascript);
  options()->EnableFilter(RewriteOptions::kLazyloadImages);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.webp", kSampleWebpFile,
                       kContentTypeWebp, 100);
  AddFileToMockFetcher("http://test.com/2.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);

  // No change in the subsequent body tags.
  GoogleString input_html = "<head></head>"
      "<body><img src=\"http://test.com/1.webp\"/></body>"
      "<body><img src=\"http://test.com/2.jpeg\"/></body>";
  GoogleString output_html = StrCat(GetHeadHtmlWithDeferJs(),
      "<body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.webp\"/>"
      "</body>",
      StrCat(GetInlineScript(),
             StrCat("</script>",
                    "<script type=\"text/javascript\">",
                    GenerateAddLowResString("http://test.com/1.webp",
                                            kSampleWebpData),
                    "\npagespeed.delayImagesInline.replaceWithLowRes();\n"
                    "</script>",
                    GetDelayImages()),
             "<body><img pagespeed_high_res_src=\"http://test.com/2.jpeg\"/>"
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/2.jpeg", kSampleJpegData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>"
             "<script type=\"text/javascript\">"
             "\npagespeed.delayImages.replaceWithHighRes();\n</script>"
             "</body>", GetDeferJs()));
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, ResizeForResolution) {
  options()->EnableFilter(RewriteOptions::kDelayImages);
  options()->EnableFilter(RewriteOptions::kResizeMobileImages);
  rewrite_driver()->AddFilters();
  AddFileToMockFetcher("http://test.com/1.jpeg", kLargeJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\"/>"
      "</body>";
  GoogleString output_html = StrCat(
      kHeadHtml,
      StrCat("<body>",
             GetNoscript(),
             "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\" "),
      "src=\"", kSampleJpegData, "\"/>", GetDelayImages(), "</body>");

  // Mobile output should be smaller than desktop because inlined low quality
  // image is resized smaller for mobile.
  // Do desktop and mobile rewriting twice. They should not affect each other.
  SetupUserAgentTest("Safari");
  int byte_count_desktop1 = MatchOutputAndCountBytes(input_html, output_html);

  SetupUserAgentTest(kAndroidMobileUserAgent1);
  int byte_count_android1 = MatchOutputAndCountBytes(input_html, output_html);
  EXPECT_LT(byte_count_android1, byte_count_desktop1);

  SetupUserAgentTest("MSIE 8.0");
  int byte_count_desktop2 = MatchOutputAndCountBytes(input_html, output_html);

  SetupUserAgentTest(kAndroidMobileUserAgent2);
  int byte_count_android2 = MatchOutputAndCountBytes(input_html, output_html);
  EXPECT_EQ(byte_count_android1, byte_count_android2);
  EXPECT_EQ(byte_count_desktop1, byte_count_desktop2);

  SetupUserAgentTest("iPhone OS");
  int byte_count_iphone = MatchOutputAndCountBytes(input_html, output_html);
  EXPECT_EQ(byte_count_iphone, byte_count_android1);
}

TEST_F(DelayImagesFilterTest, ResizeForResolutionWithSmallImage) {
  options()->EnableFilter(RewriteOptions::kDelayImages);
  options()->EnableFilter(RewriteOptions::kResizeMobileImages);
  rewrite_driver()->AddFilters();
  AddFileToMockFetcher("http://test.com/1.png", kSmallPngFile,
                       kContentTypePng, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.png\"/>"
      "</body>";
  GoogleString output_html = StrCat(
      kHeadHtml,
      "<body>",
      GetNoscript(),
      "<img src=\"http://test.com/1.png\"/>"
      "</body>");

  // No low quality data for an image smaller than kDelayImageWidthForMobile
  // (in image_rewrite_filter.cc).
  rewrite_driver()->SetUserAgent(kAndroidMobileUserAgent1);
  MatchOutputAndCountBytes(input_html, output_html);

  ScopedMutex lock(rewrite_driver()->log_record()->mutex());
  EXPECT_EQ(1, rewrite_driver()->log_record()->logging_info()
            ->rewriter_info_size());
  const RewriterInfo& rewriter_info = rewrite_driver()->log_record()
      ->logging_info()->rewriter_info(0);
  EXPECT_EQ("ic", rewriter_info.id());
  EXPECT_EQ(RewriterApplication::NOT_APPLIED, rewriter_info.status());
  EXPECT_TRUE(rewriter_info.has_rewrite_resource_info());
  EXPECT_TRUE(rewriter_info.has_image_rewrite_resource_info());

  const RewriteResourceInfo& resource_info =
      rewriter_info.rewrite_resource_info();
  EXPECT_FALSE(resource_info.is_inlined());
  EXPECT_TRUE(resource_info.is_critical());

  const ImageRewriteResourceInfo& image_info =
      rewriter_info.image_rewrite_resource_info();
  EXPECT_FALSE(image_info.is_low_res_src_inserted());
  EXPECT_EQ(0, image_info.low_res_size());
}

TEST_F(DelayImagesFilterTest, ResizeForResolutionNegative) {
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kLargeJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\"/>"
      "</body>";
  GoogleString output_html = StrCat(
      kHeadHtml,
      StrCat("<body>",
             GetNoscript(),
             "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\" "),
      "src=\"", kSampleJpegData, "\"/>", GetDelayImages(), "</body>");

  // If kResizeMobileImages is not explicitly enabled, desktop and mobile
  // outputs will have the same size.
  SetupUserAgentTest("Safari");
  int byte_count_desktop = MatchOutputAndCountBytes(input_html, output_html);
  SetupUserAgentTest(kAndroidMobileUserAgent1);
  int byte_count_mobile = MatchOutputAndCountBytes(input_html, output_html);
  EXPECT_EQ(byte_count_mobile, byte_count_desktop);
}

TEST_F(DelayImagesFilterTest, DelayImagesScriptOptimized) {
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kLargeJpgFile,
                       kContentTypeJpeg, 100);
  rewrite_driver()->SetUserAgent("Safari");
  Parse("optimized",
        "<head></head><body><img src=\"http://test.com/1.jpeg\"</body>");
  EXPECT_EQ(GoogleString::npos, output_buffer_.find("/*"))
      << "There should be no comments in the optimized code";
}

TEST_F(DelayImagesFilterTest, DelayImagesScriptDebug) {
  options()->EnableFilter(RewriteOptions::kDebug);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kLargeJpgFile,
                       kContentTypeJpeg, 100);
  rewrite_driver()->SetUserAgent("Safari");
  Parse("debug",
        "<head></head><body><img src=\"http://test.com/1.jpeg\"</body>");
  EXPECT_NE(GoogleString::npos, output_buffer_.find("/*"))
      << "There should still be some comments in the debug code";
}

TEST_F(DelayImagesFilterTest, ExperimentalIsTrue) {
  options()->set_enable_inline_preview_images_experimental(true);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\" onload=\"blah();\"/>"
      "<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat("<head></head><body>",
      GetNoscript(),
      "<img src=\"http://test.com/1.jpeg\" onload=\"blah();\"/>"
      "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\" src=\"",
      kSampleJpegData, "\" onload=\"",
      DelayImagesFilter::kOnloadFunction, "\"/></body>");
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, ExperimentalAndLazyLoadIsTrueNotMobile) {
  options()->set_enable_inline_preview_images_experimental(true);
  options()->set_lazyload_highres_images(true);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\" onload=\"blah();\"/>"
      "<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat("<head></head><body>",
      GetNoscript(),
      "<img src=\"http://test.com/1.jpeg\" onload=\"blah();\"/>"
      "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\" src=\"",
      kSampleJpegData, "\" onload=\"",
      DelayImagesFilter::kOnloadFunction, "\"/></body>");
  MatchOutputAndCountBytes(input_html, output_html);
}

TEST_F(DelayImagesFilterTest, ExperimentalAndMobileLazyLoadIsTrue) {
  options()->set_enable_aggressive_rewriters_for_mobile(true);
  options()->set_enable_inline_preview_images_experimental(true);
  options()->set_lazyload_highres_images(true);
  SetupUserAgentTest(kAndroidMobileUserAgent1);
  AddFilter(RewriteOptions::kDelayImages);
  AddFileToMockFetcher("http://test.com/1.jpeg", kSampleJpgFile,
                       kContentTypeJpeg, 100);
  GoogleString input_html = "<head></head>"
      "<body>"
      "<img src=\"http://test.com/1.jpeg\" />"
      "</body>";
  GoogleString output_html = StrCat(
      "<head></head><body>",
      GetNoscript(),
      "<img pagespeed_high_res_src=\"http://test.com/1.jpeg\"/>",
      StrCat(GetInlineScript(),
             "</script>",
             "<script type=\"text/javascript\">",
             GenerateAddLowResString("http://test.com/1.jpeg", kSampleJpegData),
             "\npagespeed.delayImagesInline.replaceWithLowRes();\n</script>",
             GetDelayImagesLazyLoad(), "</body>"));
  MatchOutputAndCountBytes(input_html, output_html);
}

}  // namespace net_instaweb
