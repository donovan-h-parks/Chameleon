#ifndef VISUAL_BRANCH
#define VISUAL_BRANCH

class VisualNode;
class VisualTree;

class VisualBranch: public QGraphicsItem
{
public:
	enum LABEL_TYPE { NO_LABEL, ASSIGNED_INTERNAL_LABELS, LENGTH_LABEL, DEPTH_LABEL, HEIGHT_LABEL };
	enum COLOR_STYLE { SINGLE_COLOR, PROPOGATE_CONTINUOUS_COLOR, PROPOGATE_WEIGHTED_COLOR, PROPOGATE_DISCRETE_COLOR };

public:
	VisualBranch();
	VisualBranch(VisualNode* source, VisualNode* dest, const QColor& color = Qt::black, qreal width = 1);

	VisualBranch(VisualBranch &rhs);

	void SetSource(VisualNode* source);
	VisualNode* GetSource() const { return m_source; }

	void SetDest(VisualNode* dest);
	VisualNode* GetDest() const { return m_dest; }

	void SetTree(const VisualTree* tree) { m_tree = tree; }
	const VisualTree* GetTree() const { return m_tree; }

	void SetColor(const QColor& color);
	QColor GetColor() const { return m_color; }

	void SetWidth(int width);
	qreal GetWidth() const { return m_width; }

	void SetDrawOutline(bool state);
	bool IsDrawOutline() const { return m_bDrawOutline; }

	QString GetLabel() const;

	void FontChanged();
	void LabelChanged() { FontChanged(); }

	void NodeMoved() { prepareGeometryChange(); update(); }

protected:
	void 	Initialize();

	QRectF boundingRect() const;
	QRectF RectangularBoundingRect() const;

	QPainterPath shape() const;
	QPainterPath RectangularShape() const;
	
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void PaintRectangular(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, const QString& label);
	void AdjustExtents(double& xMin, double& xMax, double& yMin, double& yMax, const QPointF& pt) const;

private:
	VisualNode* m_source;
	VisualNode* m_dest;

	const VisualTree* m_tree;
	
	QColor m_color;
	int m_width;	
	bool m_bDrawOutline;

	float m_labelWidth;
	float m_labelHeight;
};

#endif