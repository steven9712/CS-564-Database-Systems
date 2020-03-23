.timer on
WITH optlineitem AS (SELECT l_extendedprice, l_discount, l_orderkey, l_shipdate FROM lineitem),
optorders AS (SELECT o_orderkey, o_custkey, o_orderdate, o_shippriority FROM orders),
optcust AS (SELECT c_custkey, c_mktsegment FROM customer)
select
        l_orderkey,
        sum(l_extendedprice*(1-l_discount)) as revenue,
        o_orderdate,
        o_shippriority
FROM optcust
JOIN optorders ON c_custkey = o_custkey
JOIN optlineitem ON o_orderkey = l_orderkey
WHERE c_mktsegment = 'BUILDING' --'[SEGMENT]'
AND o_orderdate < "1995-03-15" -- '[DATE]'
AND l_shipdate > "1995-03-15" -- '[DATE]'
GROUP BY l_orderkey, o_orderdate, o_shippriority
ORDER BY revenue desc, o_orderdate;