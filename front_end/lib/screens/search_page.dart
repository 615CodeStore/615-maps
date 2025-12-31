import 'package:flutter/material.dart';
import '../data/campus_data.dart';
import '../models/campus_location.dart';

// 搜索页面
class SearchPage extends StatefulWidget {
  const SearchPage({super.key});

  @override
  State<SearchPage> createState() => _SearchPageState();
}

class _SearchPageState extends State<SearchPage> {
  final TextEditingController _searchController = TextEditingController();
  List<CampusLocation> _searchResults = [];

  void _search(String query) {
    setState(() {
      if (query.isEmpty) {
        _searchResults = [];
      } else {
        _searchResults = campusLocations
            .where((location) =>
                location.name.contains(query) ||
                location.description.contains(query) ||
                location.category.contains(query))
            .toList();
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Container(
          decoration: BoxDecoration(
            color: const Color(0xFF2A2A2A),
            borderRadius: BorderRadius.circular(20),
          ),
          child: TextField(
            controller: _searchController,
            onChanged: _search,
            style: const TextStyle(color: Colors.white),
            decoration: const InputDecoration(
              hintText: '搜索地点名称或描述',
              hintStyle: TextStyle(color: Colors.grey),
              prefixIcon: Icon(Icons.search, color: Colors.grey),
              border: InputBorder.none,
              contentPadding: EdgeInsets.symmetric(vertical: 12, horizontal: 16),
            ),
          ),
        ),
        actions: [
          IconButton(
            icon: const Icon(Icons.tune),
            onPressed: () {
              // 筛选功能
            },
          ),
        ],
      ),
      body: Column(
        children: [
          // 热门搜索标签
          Container(
            padding: const EdgeInsets.all(16),
            child: const Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Text('热门搜索', style: TextStyle(fontWeight: FontWeight.bold)),
                Text('更多', style: TextStyle(color: Color(0xFF2196F3))),
              ],
            ),
          ),
          // 热门标签
          SingleChildScrollView(
            scrollDirection: Axis.horizontal,
            padding: const EdgeInsets.only(left: 16),
            child: Row(
              children: [
                for (var location in campusLocations.take(5))
                  Padding(
                    padding: const EdgeInsets.only(right: 8),
                    child: Chip(
                      label: Text(location.name),
                      backgroundColor: const Color(0xFF2A2A2A),
                      labelStyle: const TextStyle(color: Colors.white),
                      onDeleted: () {
                        _searchController.text = location.name;
                        _search(location.name);
                      },
                    ),
                  ),
              ],
            ),
          ),
          // 搜索结果
          Expanded(
            child: _searchResults.isEmpty
                ? const Center(
                    child: Text(
                      '暂无搜索结果',
                      style: TextStyle(color: Colors.grey),
                    ),
                  )
                : ListView.builder(
                    itemCount: _searchResults.length,
                    itemBuilder: (context, index) {
                      final location = _searchResults[index];
                      return ListTile(
                        leading: CircleAvatar(
                          backgroundColor: const Color(0xFF2196F3).withOpacity(0.2),
                          child: Icon(location.icon, color: const Color(0xFF2196F3)),
                        ),
                        title: Text(location.name),
                        subtitle: Text(location.description),
                        trailing: IconButton(
                          icon: const Icon(Icons.directions),
                          onPressed: () {
                            // 开始导航
                          },
                        ),
                        onTap: () {
                          // 查看详情
                        },
                      );
                    },
                  ),
          ),
        ],
      ),
    );
  }
}