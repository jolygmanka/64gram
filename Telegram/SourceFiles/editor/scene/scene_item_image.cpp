/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "editor/scene/scene_item_image.h"

namespace Editor {
namespace {

} // namespace

ItemImage::ItemImage(
	const QPixmap &&pixmap,
	rpl::producer<float64> zoomValue,
	std::shared_ptr<float64> zPtr,
	int size,
	int x,
	int y)
: ItemBase(std::move(zoomValue), std::move(zPtr), size, x, y)
, _pixmap(std::move(pixmap)) {
	setAspectRatio(_pixmap.isNull()
		? 1.0
		: (_pixmap.height() / float64(_pixmap.width())));
}

void ItemImage::paint(
		QPainter *p,
		const QStyleOptionGraphicsItem *option,
		QWidget *w) {
	p->drawPixmap(contentRect().toRect(), _pixmap);
	ItemBase::paint(p, option, w);
}

void ItemImage::performFlip() {
	_pixmap = _pixmap.transformed(QTransform().scale(-1, 1));
	update();
}

std::shared_ptr<ItemBase> ItemImage::duplicate(
		rpl::producer<float64> zoomValue,
		std::shared_ptr<float64> zPtr,
		int size,
		int x,
		int y) const {
	auto pixmap = _pixmap;
	return std::make_shared<ItemImage>(
		std::move(pixmap),
		std::move(zoomValue),
		std::move(zPtr),
		size,
		x,
		y);
}

} // namespace Editor
