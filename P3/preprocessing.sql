CREATE INDEX idx_part_size_type ON part(p_size, p_type);
CREATE INDEX idx_region_name ON region(r_name);

CREATE INDEX idx_orders_date ON orders(o_orderdate);

CREATE INDEX idx_customer_mktsegment ON customer(c_mktsegment);
CREATE INDEX idx_lineitem_sum ON lineitem(l_extendedprice, l_discount);
CREATE INDEX idx_order_key ON orders (o_custkey);

CREATE INDEX idx_lineitem_dates ON lineitem(l_commitdate, l_receiptdate);