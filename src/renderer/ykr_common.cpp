#include <renderer/ykr_common.h>


VkImageCreateInfo image_create_info(VkFormat format, VkImageUsageFlags usage_flags, VkExtent3D extent)
{
    VkImageCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.pNext = 0;

    info.imageType = VK_IMAGE_TYPE_2D;

    info.format = format;
    info.extent = extent;

    info.mipLevels = 1;
    info.arrayLayers = 1;

    info.samples = VK_SAMPLE_COUNT_1_BIT;

    info.tiling = VK_IMAGE_TILING_OPTIMAL;
    info.usage = usage_flags;

    return info;
}

VkImageViewCreateInfo image_view_create_info(VkFormat format, VkImage image, VkImageAspectFlags aspect_flags)
{
    VkImageViewCreateInfo info = {};

    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    info.pNext = 0;

    info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    info.image = image;
    info.format = format;
    info.subresourceRange.baseMipLevel = 0;
    info.subresourceRange.levelCount = 1;
    info.subresourceRange.baseArrayLayer = 0;
    info.subresourceRange.layerCount = 1;
    info.subresourceRange.aspectMask = aspect_flags;

    return info;
}

void copy_image_to_image(VkCommandBuffer cmd, VkImage src, VkImage dst, VkExtent2D src_size, VkExtent2D dst_size)
{

    VkImageBlit2 blit_reg = {};
    blit_reg.sType = VK_STRUCTURE_TYPE_IMAGE_BLIT_2;

    //srcOffset[0] is top left corner. [1] is bottom right. Over here we are specifying the extent of the copy, which is whole image.
    blit_reg.srcOffsets[1].x = src_size.width;
    blit_reg.srcOffsets[1].y = src_size.height;
    blit_reg.srcOffsets[1].z = 1;

    blit_reg.dstOffsets[1].x = dst_size.width;
    blit_reg.dstOffsets[1].y = dst_size.height;
    blit_reg.dstOffsets[1].z = 1;

    blit_reg.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    blit_reg.srcSubresource.baseArrayLayer = 0;
    blit_reg.srcSubresource.layerCount = 1;
    blit_reg.srcSubresource.mipLevel = 0;

    blit_reg.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    blit_reg.dstSubresource.baseArrayLayer = 0;
    blit_reg.dstSubresource.layerCount = 1;
    blit_reg.dstSubresource.mipLevel = 0;

    VkBlitImageInfo2 blit_info = {};
    blit_info.sType = VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2;
    blit_info.dstImage = dst;
    blit_info.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    blit_info.srcImage = src;
    blit_info.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    blit_info.filter = VK_FILTER_LINEAR;
    blit_info.regionCount = 1;
    blit_info.pRegions = &blit_reg;

    vkCmdBlitImage2(cmd, &blit_info);
}
