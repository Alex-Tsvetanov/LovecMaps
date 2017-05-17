namespace Graph 
{
	namespace W 
	{
		template <typename cost_t> class LN 
		{
		private:
			vector < size_t, cost_t > ln;
		public:
			LN& add_edge (size_t a, size_t b, cost_t c)
			{
				ln [a].push_back ({b, c});
			}
		protected:
		};
	};
};
