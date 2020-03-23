.timer on
WITH optlineitem AS (SELECT l_orderkey, l_commitdate, l_receiptdate FROM lineitem)
select
	o_orderpriority,
	count(*) as order_count
from
	orders
where
	o_orderdate >= "1993-07-01" --'[DATE]'
	and o_orderdate < "1993-10-01" --'[DATE]'
	and exists (
		select
			l_orderkey
		from
			optlineitem
		where
			l_orderkey = o_orderkey
			and l_commitdate < l_receiptdate
			)
group by
	o_orderpriority
order by
	o_orderpriority;
