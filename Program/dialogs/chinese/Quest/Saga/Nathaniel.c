// 纳撒尼尔.霍克 - 马龙镇的海盗男爵
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "想要点什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("Voice\English\saga\Nataniel Hawk-02.wav");
			dialog.text = "啊... 你是谁, 该死的? ... 咳... (剧烈咳嗽并伴有嘶哑) 该死的虚弱... ";
			link.l1 = "问候你, 纳撒尼尔。 你是纳撒尼尔.霍克, 对吗? ";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "是的, 是我, 如果我还能这么称呼自己的话。 我曾经是纳撒尼尔.霍克, 但现在我只是一个看起来悲伤的废物。 去他妈的雕像! 它吸走了我所有的生命。 ";
			link.l1 = "我熟悉这种感觉... ";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "年轻人, 你怎么会了解呢, 如果你甚至不知道我在说什么? 啊哈... 你知道当我一分钟前还健康强壮, 现在却变成一个半死的老人是什么感觉吗? \n我见过很多事情, 我以为我年轻时访问过的那座古老的印第安神庙已经让我失去了惊讶的能力, 但这... 为什么我没有预见到! 那座该死的雕像看起来和打开神庙大门的古老神像一模一样! ";
			link.l1 = "好吧, 内森, 我们谈谈。 让我介绍一下自己, 我是"+GetFullName(pchar)+"。 首先, 我非常理解你, 因为我来这里的方式和你一样 - 使用库库尔坎传送门。 ";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "真的吗? ! 那你为什么看起来很好? 或者说... 库库尔坎只伤害了我? ";
			link.l1 = "帮助你逃脱的米斯基托萨满‘蛇眼’给了我一种非常强效的药水。 我在圣奥古斯丁醒来后就立即喝了它, 它完全治愈了我。 我相信蛇眼也能帮助你。 我们只需要把你带到他那里。 ";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "啊, 那个印第安人! 药水? 他为什么不也给我一瓶? ";
			link.l1 = "他说没有时间。 你当时在被追捕, 他唯一能做的就是告诉你逃跑的路 - 传送门。 ";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("Voice\English\saga\Nataniel Hawk-01.wav");
			dialog.text = "逃跑? 哦... 你没看到我现在的状况吗? 我甚至握不住军刀。 你怎么能称之为逃跑? 感谢上帝, 这个世界上还有好人。 奥莱, 上帝保佑他... 你认识奥莱吗? ";
			link.l1 = "是的。 事实上, 是他告诉我关于你的事情, 他告诉我他如何喂你老鼠, 以及你如何一瓶接一瓶地喝酒... ";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "如果我不喝朗姆酒, 我会比点燃的蜡烛死得更快。 这是唯一让我活着的东西。 朗姆酒... ";
			link.l1 = "你仍然感觉那么糟糕吗? 和传送后一样? ";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "嗯, 我的感觉不太一样了... 但也没有真正好转。 朋友, 告诉我, 你为什么要见老内森? 你到底为什么来到这艘破旧的船上? 来和我聊天? ";
			link.l1 = "事实上, 是的。 你不会相信我, 但我经历所有传送的麻烦就是为了找到你。 我为海岸兄弟会工作, 代表扬.斯文森。 ";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "该死的... 森林魔鬼? 啊... 你是来杀我的吗? 实际上, 你不是? 你作为刺客太健谈了。 求你了 - 不要折磨我。 如果你被命令从我这里得到什么 - 我会自己告诉你一切, 我没有什么可隐瞒的。 ";
			link.l1 = "你是什么意思? 啊-啊, 我明白了。 你和丹妮尔一样, 认为斯文森是在丛林中策划伏击你生命的人。 我可以向你保证, 扬没有那样做。 相反, 他站在你这边, 非常担心你的失踪。 ";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "真的吗? 听到这个我真该死的高兴。 我已经在想... 但谁做的? 我的分队在几分钟内就被摧毁了。 他们在等我们。 他们甚至有船炮! 他们用葡萄弹扫倒了我一半的人, 然后用滑膛枪解决了我们... ";
			link.l1 = "说实话, 我不知详情, 但我确定这一切都是杰克曼背后主使。 巧合太多了, 先是Blaze, 然后是你... 杰克曼想夺取权力, 清除所有阻碍他的人。 现在他代替你统治马龙镇。 ";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "杰克曼? 混蛋! 嗯... 兄弟会在过去几年里分裂了, 以前完全不同。 撒迦利亚为他的宗教事务发疯了, 泰雷克斯什么都不在乎, 巴巴西翁只对达布隆感兴趣。 二十年前完全不同... ";
			link.l1 = "他们是怎么抓住你的? 多告诉我一些。 ";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "没有什么有趣的可讲! 正如我所说, 那些强盗策划了整个事件。 他们行动整齐, 协调一致, 显然是在听从某人的命令。 他们本可以杀了我一百次, 但他们没有。 他们想要我活着。 他们把我带到一个废弃的矿井, 把我锁在其中一间小屋里。 ‘直到老板到来’, 他们说。 \n我以为斯文森是老板, 但似乎杰克曼才是负责人。 不过我不知道他想从我这里得到什么, 但我确定和他聊完后我活不了多久。 ";
			link.l1 = "我对此毫不怀疑。 斯文森确信杰克曼杀了Blaze Sharp... 你是怎么逃脱的? ";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "那个印第安人蛇眼不知怎么设法潜入了矿井。 据我了解, 米斯基托人不喜欢强盗。 无论如何, 蛇眼出于某种原因安排了我的逃跑。 他挖了一条隧道到我这里, 进去, 割断我的绳子, 然后我们逃进了丛林。 \n他想带我去他的村庄, 去米斯基托人那里。 但看起来杰克曼非常想要我, 因为组织了一场大搜捕。 他们紧随其后。 蛇眼尽力迷惑他们, 但他们总是能找到我们的踪迹。 毫无疑问, 他们有优秀的探路者。 \n当他们终于找到我们时, 我们离蛇眼的村庄很近了。 此时我的胃已经空了两天, 我完全被耗尽了, 因为我的腿也严重受伤。 那是午夜, 我仍然记得雕像上方的星星有多亮... 蛇眼说我唯一的机会就是走到神像前触摸它。 \n我以为这个人疯了, 但你知道他们怎么说的, 病急乱投医。 我一瘸一拐地走到雕像前, 触摸了它... 然后疯狂的事情开始发生! ";
			link.l1 = "你不需要继续了, 我知道后来发生了什么。 ";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "我发现自己在某艘沉船潮湿的船舱里。 我半死不活。 不能走路, 只能爬。 我的状况每分钟都在恶化。 奥莱及时出现了。 他给我灌了一些加勒比混合物, 味道像垃圾, 混合了解毒剂和治疗精华。 然后他给了我朗姆酒。 \n我立刻好多了。 然后他找到并使用一根旧木头把我搬到这里。 我已经在这里住了一段时间了, 不确定多久, 我已经失去了时间概念。 ";
			link.l1 = "会好起来的, 内森。 我和斯文森有伟大的计划, 你在其中的角色非常重要。 你必须回到你在马龙镇的位置, 我们会处理掉那个混蛋杰克曼。 ";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "马龙镇? 你到底怎么想象这会起作用? 看看我, 我是一个被朗姆酒泡透的残骸! 毫无价值... 不, 我在马龙镇的权威岁月永远消失了。 我被困在这个该死的船只墓地里。 我还能活多久? 一个月, 两个月, 一年? \n然后我会躺在这些腐烂的木板上, 奥莱会把纳撒尼尔.霍克剩下的东西扔进海里。 最糟糕的是, 我再也见不到我的丹妮了。 嗯, 一切都结束了, 朋友。 ";
			link.l1 = "别这么悲观。 我会把你从这里救出去。 ";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "你怎么把我从这里救出去? 我们怎么离开这个地方? 这里没有船。 你想造一个木筏吗? ";
			link.l1 = "不。 我会以我来这里的方式离开。 我知道雕像在哪里... 嗯, 大致知道。 我会找到它, 然后回来找你和鲨鱼多德森。 之后我们会把你送到蛇眼那里。 他会治愈你。 ";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "你说什么? 鲨鱼多德森? 史蒂夫也在这里吗? 真是个奇怪的地方... ";
			link.l1 = "是的, 他在这里。 可以说他是这个岛的‘总督’。 我问过他关于你的事, 但他什么都不知道。 ";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "他不应该知道。 我不想让他看到我现在的状况。 你说萨满会治愈我... 我几乎不敢相信。 你也提到了丹妮... 你见到她了吗? ";
			link.l1 = "是的。 她在布鲁维尔德自己找到了我。 她偷听了我和斯文森的谈话, 明白扬没有杀你的意图, 他在和杰克曼作对。 她作为军官加入了我的船, 帮助我找到你。 ";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "嗯, 我亲爱的丹妮! 她一点没变... 和年轻时一样鲁莽... 你无法想象我现在多想见到她并拥抱她! 我躺在这里时反思了很多。 朋友, 你知道吗, 当你接近死亡时, 你会以不同的眼光看待事物。 我和妻子在一起的时间太少了! \n海上突袭, 兄弟会的公务, 统治马龙镇。 而她总是在各方面支持我: 独自待上几周, 在我不在时与其他海盗争吵, 指挥我们的船... 我的丹妮是世界上最好的女人! 而我... 我应该更经常告诉她我爱她! \n我记得我们决定在一起的那一天! 实际上, 那是我第一次遇见并与超自然事物战斗的日子。 这一切都因为那该死的神像而起, 它看起来就像那些雕像。 你不介意听个故事吧? 很有趣的。 ";
			link.l1 = "一点也不! 告诉我! ";
			link.l1.go = "story";
			link.l2 = "内森, 我们没有时间追忆往事。 以后再告诉我, 等我们坐在米斯基托村庄里喝着葡萄酒的时候。 ";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "那是二十五年前... 我年轻。 热情。 不安分。 加勒比海是我的游乐场。 那时我已经认识丹妮了。 我喜欢她, 真的喜欢, 而且这种感觉是相互的。 但我们经常打架, 争吵, 互相嘲讽。 愚蠢的青春... 我相信我们当时是那些受人尊敬的水手们的一大娱乐! \n无论如何, 不知怎么丹妮和我卷入了同一个故事。 我们找到了一张卡埃尔.罗阿的地图, 他们告诉我们那是寻找印第安黄金的‘那个’地方。 我们还找到了一个看起来奇怪的黄金神像, 是那些雕像顶部的缩小版。 \n这个神像很危险, 它从携带者身上吸取生命力。 但我们需要那个该死的物品才能进入神庙内的宝库。 唯一的问题是我们不知道如何正确使用它。 丹妮和我航行到那个岛。 那里有一座古老的神庙, 被草和树木覆盖。 我们一进入, 就发现自己在一个巨大的迷宫里。 \n我们设法找到了正确的路, 到达了迷宫的中心部分。 我们以为那是死胡同, 但当绝望开始击败我们时, 我们看到了一个带有小插槽和图片的奇怪平台。 我把神像放进插槽里, 然后... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "石制平台下沉了几英寸, 其中一面墙原来是一个秘密通道。 神像留在了平台里, 我没能把它拔出来。 最后我们到达了一个巨大的大厅。 多么美丽的景象! \n这是我见过的最宏伟的建筑。 墙上的雕刻, 巨大的雕像... 我们搜索了整个大厅, 但没有发现任何宝藏的迹象。 ";
			link.l1 = "呵呵, 像我们这样的人经常遇到这种情况。 付出很多努力, 最终却没有结果... ";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "并非徒劳无功。 毕竟, 我们进入了一个 throne hall, 尽头有一座巨大的鸟雕像。 雕像附近有一道神秘的光, 看起来就像午夜神像上方的光。 我们走近, 看到了一个美丽的飞行球体。 我发誓, 我告诉你的是纯粹的真相! \n它是真实的, 但同时感觉又不是。 当我在思考时, 丹妮 - 哦, 那个鲁莽的魔鬼, 触摸了球体。 它开始变得更亮, 最后在她手中变成了一个小物品... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "看来我们犯了亵渎神灵的罪。 神庙活了过来: 我们周围的一切开始移动, 墙壁在震动, 一切都崩塌了。 就像我们唤醒了所有印第安恶魔, 他们把所有的愤怒都发泄在我们身上... ";
			link.l1 = "哇! ";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "很难相信, 我知道。 但是... ";
			link.l1 = "半年前我会说你在撒谎。 但我在加勒比海生活了足够长的时间, 知道我没有理由不信任你。 继续。 你是如何生存下来的? ";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "我们跑出神庙, 幸运地及时登上了我们的船。 我命令起锚, 我们想尽快离开那个地方。 ";
			link.l1 = "呵呵! 所以, 最后你没有找到宝藏, 只找到了一些奇怪的神器? 真是个不错的等价替代品, 呵呵... 你发现如何使用它了吗? 或者它是无用的? ";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "等一下。 故事还没结束。 丹妮拿到了神器, 当我们决定去船舱研究它时, 天空变暗, 一艘船出现了。 哦, 上帝! 那是... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// 这里根据玩家是否完成卡勒幽船任务进行分支
		case "story_7":
			dialog.text = "... 范.德.戴肯本人! ";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "范.德.戴肯? 嗯... ";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "他是谁? ";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "你没听说过飞翔的荷兰人号吗? ";
			link.l1 = "谁没听说过飞翔的荷兰人号! 我已经遇到过一个荷兰人, 把它的船长送入了海底。 他只是一个普通的海盗, 用一些像海藻和破烂船帆这样的化妆垃圾装饰他的船。 ";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "是的, 但这是范.德.戴肯本人, 飞翔的荷兰人号的船长! ";
			link.l1 = "有趣。 请继续。 你是如何设法度过难关的? ";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "呵呵, 朋友... 你击沉了某个小丑船, 但我谈论的是真正的飞翔的荷兰人号。 一艘巨大的战船。 上帝保佑你永远不要在公海上遇到她。 她的船长范.德.戴肯和他的船员曾被诅咒永远在海上航行。 \n我记得她破烂的黑色船帆, 甲板上站着一群死人船员, 拔出了他们的刀刃, 还有船长本人 - 一个戴着黑色三角帽的令人毛骨悚然的骷髅... 耶稣... ";
			link.l1 = "你说的是实话吗? ";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "我可以对着圣经发誓我没有撒谎... 与‘飞翔的荷兰人号’相遇只意味着必死无疑。 她很强大, 非常强大, 她的一次齐射就能击沉一艘重型护卫舰, 而她的船员... 但更糟糕的是, 你该如何与不死生物战斗? ";
			link.l1 = "但你在这场噩梦中幸存下来了! ";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "这都要感谢我可爱的丹妮和我们从神庙带走的印第安神器。 我曾命令准备战斗, 但我知道这是穷途末路。 ‘飞翔的荷兰人号’向我们驶来, 我看到了她可怕的船员和甲板上的范.德.戴肯本人。 船开始将大炮对准我们, 但是... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "丹妮举起神器, 让它飞起来。 我不知道她为什么要那样做。 她说这是她的女性直觉... 神器变回发光的球体并爆炸, 严重损坏了幽灵船, 使船员士气低落。 我命令向荷兰人号开火。 \n第一次齐射让他们动摇了。 我们再次攻击, 在他们从神器的影响中恢复并开始还击之前, 第二次射击他们腐烂的船体... ";
			link.l1 = "所以你还是不得不与他们战斗? ";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "确实。 我发誓这是我一生中最艰难的战斗。 他们那该死的船几乎无法保持在水面上, 但在我们通过炸毁他们该死的火药舱将他们炸飞之前, 他们仍然能够摧毁我一半的船体。 ";
			link.l1 = "那么你击沉了它? 你击沉了飞翔的荷兰人号? ";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "是的, 该死的! 我做到了! ..";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "那该死的船沉没了。 太阳开始再次照耀, 天空放晴。 我们终于开始感到快乐... 哦, 你无法想象我们有多高兴。 我们战胜了死亡本身。 这样的时刻让人们走到一起。 我们做了在相遇之前很久就应该做的事情 - 我们拥抱, 亲吻, 说我们彼此相爱, 并发誓永远在一起。 ";
			link.l1 = "而你们仍然在一起... ";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "是的, 我们在一起。 我和丹妮结婚了, 我从未后悔过。 你不会找到更好的妻子和战友。 ";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "所以, 现在我终于知道那个设法击沉‘飞翔的荷兰人号’的神秘船长到底是谁了... 你是真正的英雄! ";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "那么, 你们俩都是真正的英雄? 你们设法击沉了著名的幽灵船。 等等! 你说‘飞翔的荷兰人号’仍然在航行... 既然她躺在海底, 怎么可能? ";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "嗯, 朋友, 你什么都不知道... 你可以击沉范.德.戴肯, 但你杀不了他。 加在他和他船员身上的诅咒太强大了, 比死亡强大得多... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "我可能是个英雄, 但范.德.戴肯无法被杀死。 笼罩在他。 他的船员和他的船上的诅咒比死亡更强大... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "每次你击沉这艘船, 它的船员都会修复他们的船, 让她重新起航, 继续他们的永恒航行。 ";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "我知道, 纳撒尼尔, 我知道。 尽管如此, 飞翔的荷兰人号再也不会困扰任何人了。 ";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "嗯, 你知道, 这听起来像个寓言。 修复一艘分裂沉没的船... ";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "在我们击沉它之后, 人们多次看到过这艘船... 你决定是否相信这些目击事件。 ";
			link.l1 = "那你从那里得到神器的那个有神庙的岛在哪里? ";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "它未被标注, 位于加勒比海东部的某个地方。 我在马龙镇留下了一张该岛的地图, 但你很清楚我现在不能航行到那里。 老实说, 我也不想去。 我只记得它的名字 - 卡埃尔.罗阿... ";
			link.l1 = "多么有趣的故事。 我想找到那个岛! ";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = "哦, 我不建议那样做... 我肯定不会再去拜访它。 ";
			link.l1 = "无论如何我都想去... 好吧, 谢谢你有趣的故事! 现在我更了解你的妻子了。 你们俩都是活着的传奇! ";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = "你在暗示什么, 伙伴? 我刚才不是告诉你他杀不死吗? ";
			link.l1 = "纳撒尼尔, 我航行到了卡埃尔.罗阿。 我参观了查文神庙, 二十五年前你。 丹妮尔和某个老人去过那里。 你当时从神庙带走的神器被称为‘升起的太阳之球’。 那个神器是吸引‘飞翔的荷兰人号’注意你的东西。 它的船长喜欢查文神器。 ";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "你去过卡埃尔.罗阿? 但这不可能! 你在告诉我实话吗? ";
			link.l1 = "我发誓。 当你告诉我迷宫和巨鸟雕像时, 我立刻意识到那个地方在哪里。 加勒比萨满图图阿塔帕克告诉我你们的冒险经历。 是他指引我到那个岛。 它位于圣克里斯托弗以东。 它很小, 呈环形。 周围都是岩石, 里面有一个小海湾。 只有一条杂草丛生的小路通向一座金字塔形的神庙。 ";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "是的! 这就是卡埃尔.罗阿。 但你为什么去那里? ";
			link.l1 = "为了移除卡勒幽船的诅咒... 嗯, ‘飞翔的荷兰人号’的诅咒。 实际上, 她的名字是‘飞翔的心’, 她的船长名字是‘巴尔萨泽.德.科尔德斯’。 五十年前, 他被印第安死神尤姆.西米尔诅咒。 我拿走了被巴尔萨泽从神庙偷走的尤姆.西米尔的玉头骨, 并把它放回秃鹰雕像前的基座上... ";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "... 通过归还头骨, 我移除了卡勒幽船的诅咒。 因为我身上还有另外两个查文护身符, 她在岛附近攻击了我, 就像当年发生在你身上的一样。 但正如图图阿塔帕克所说, 没有了诅咒, 巴尔萨泽不再不朽。 所以... ‘飞翔的荷兰人号’不再存在了。 我亲自处理了她。 ";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "雷电! 我很惊讶! 你.. 你不是在和老内森开玩笑, 是吗? 不, 我从你眼中看出你在说真话! 你是真正的英雄! ";
			link.l1 = "不管是不是英雄, 但我经历了不少冒险, 就像你一样。 好吧, 当然我们会多次谈论过去, 因为现在我们有了共同的话题。 ";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "朋友, 你现在要离开我吗? ";
			link.l1 = "是的, 内森。 请坚持到我回来。 保重。 最重要的是, 在我回来之前活下去, 一切都会好起来的。 海岸兄弟会需要你, 丹妮尔需要你。 ";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "丹妮现在在你的船员中吗? 我求你, 照顾好她。 她和年轻时一点没变, 仍然是个敢于冒险的人, 会毫不犹豫地穿越地狱。 告诉她我非常爱她... ";
			link.l1 = "我当然会。 我们会一起回来找你, 我向你保证, 内森。 坚持住, 保持乐观。 奥莱会照顾你。 很快见! ";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // 属性 - 与纳撒尼尔的对话已发生
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "啊, 是你, "+pchar.name+"。 还没离开岛吗? ";
			link.l1 = "别担心, 内森, 一切都按计划进行。 现在休息吧。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("Voice\English\saga\Nataniel Hawk-03.wav");
			dialog.text = "丹妮尔! .. 丹妮! 我的丹妮! ..";
			link.l1 = "... ";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // 转移pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "谢谢你, 我的朋友。 谢谢你所做的一切, 尤其是为了我的丹妮... ";
			link.l1 = "不客气, 内森。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// 在马龙镇
		case "marun_town":
			dialog.text = "看看谁来了! 是"+GetFullName(pchar)+"本人! 进来, 进来, 朋友! 你好吗? ";
			link.l1 = "我很好。 你呢, 内森? 我看没有忧郁了。 你看起来不错。 蛇眼做得真不错! ";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "是的, 你的萨满是个奇迹创造者。 我感觉比那该死的传送前还要好! 我感觉自己年轻了十岁! "+pchar.name+", 我欠你很多。 而且我很感动: 你帮助一个完全陌生的人, 穿过被诅咒的传送门, 把我从死亡手中夺走, 把我送回妻子身边! \n甚至更多! 你把我们的船和家还给了我们。 你现在是我们最好的朋友。 永远。 如果你需要什么 - 你知道该问谁! 如果你有危险, 马龙镇将永远为你提供保护。 支持和避难所。 \n如果你有危险, 整个村庄都会为你而战。 在和平时期, 你会在这里找到友谊。 最好的朗姆酒。 一张柔软的床和一个休息的好地方。 丹妮和我会确保这一点。 ";
			link.l1 = "谢谢你, 男爵! 我真诚地很高兴看到你身体健康... 并和丹妮在一起。 ";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "我一直在期待你的来访, "+pchar.name+", 我准备了一份礼物 - 一件稀有而强大的武器。 也许有一天你需要一次击倒众多敌人, 这把手榴弹发射器会帮助你做到这一点。 ‘Sclopetta’发射特殊手榴弹, 所以我还准备了制作它们的说明。 给, 拿着。 ";
			link.l1 = "多好的武器啊! 谢谢! ";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("你收到了一把手榴弹发射器");
			Log_Info("你收到了手榴弹说明");
			PlaySound("interface\important_item.wav");
			dialog.text = "多来看看我们, "+pchar.name+"! 丹妮和我会永远很高兴随时见到你。 ";
			link.l1 = "我会很乐意的。 期待很快见到你! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "啊, 我的朋友"+GetFullName(pchar)+"! 进来, 进来, 船长! 你好吗? 需要帮助吗? ";
			// 卡勒幽船
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "内森, 我来找你有非常重要的事情。 你还记得在废弃船只岛时你告诉我, 你和丹妮潜入印第安神庙并击沉了‘飞翔的荷兰人号’吗? ";
				link.l2.go = "caleuche";
			}
			link.l1 = "谢谢, 我很好。 只是想见见你们俩。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "当然, 我记得。 ";
			link.l1 = "我需要到达那个有神庙的岛。 我非常需要找到它。 你说你有它的地图。 你能告诉我坐标吗? ";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "哦, 朋友, 这是一次非常危险的尝试, 你知道... 卡埃尔.罗阿的神庙被诅咒了。 如果你只知道谁住在它的走廊里... ";
			link.l1 = "目前居住在那里的怪物比你当时看到的要可怕得多。 但我还是要去那里。 ";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "如果你在那里丧生, 我不会原谅自己。 "+pchar.name+", 我恳求你: 放弃这个计划! 此外, 那里是‘飞翔的荷兰人号’最常出现的地方... ";
			link.l1 = "我已经遇到过它, 我知道如何逃脱它。 内森, 请给我卡埃尔.罗阿的坐标, 并告诉我你所知道的关于那个神庙的一切, 除了它居住着不死印第安人。 ";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "哦, 好吧... 我不能拒绝你, 但是... 你不知道我和丹妮在那里经历了什么! 卡埃尔.罗阿位于安提瓜以东。 我回到马龙镇时找到了它的地图, 它在... (看) 坐标: 北纬19度32分, 西经62度25分。 ";
			link.l1 = "我会在我的日志中记下它的位置... 谢谢, 内森! ";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "你可以稍后感谢我。 现在细节。 卡埃尔.罗阿岛是一个岩石环, 里面有一个海湾。 寻找峭壁之间的通道 - 那里相当深。 在海湾里, 你应该抛锚并在海滩登陆。 寻找一条通往岛内更深的老路 - 那里只有一条。 它会带你到一座印第安金字塔 - 这就是你要找的神庙。 \n岛本身很安静, 但神庙里爬满了各种各样的怪物。 入口位于金字塔的顶部。 里面会有三个通道; 你应该走中间的那个。 然后你沿着走廊走, 你会发现一个有四个入口或出口的平台。 这是我第一次被神庙生物攻击的地方, 所以你应该小心。 \n然后有一个迷宫。 它非常复杂, 我这辈子都记不住正确的路线。 迷宫里有许多肮脏的生物。 你必须杀死它们所有, 然后走到一个有两个入口。 六根柱子和一个有九块石板的平台的大厅。 这是圣所的前厅。 它的石墙是关闭的, 我不知道你将如何打开它。 \n有某种机制, 但我向上帝发誓, 我不知道它如何运作! 我用一个神像作为钥匙。 我把它插入中央石板, 门就开了。 但你没有这样的神像, 所以你必须弄清楚这个机制如何运作。 ";
			link.l1 = "好吧, 我会尽力弄清楚。 圣所呢? ";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "圣所是一个天花板很高的巨大大厅, 有巨大的石阶。 你不能使用它们 - 它们太旧了, 大部分都倒塌了。 但神庙的建造者, 似乎也是伟大的巫师。 有像库库尔坎那样的传送门, 它们会把你从一个地方带到另一个地方。 \n你会很容易认出它们 - 它们看起来像彩色的漩涡。 一楼会有两个传送门, 但其中一个是陷阱, 所以要小心! 正确的传送门会带你到二楼。 在那里你必须找到另一个传送门才能更高, 然后直接到神庙的中心! \n在那里, 在巨大的鸟雕像前, 放置着我和丹妮带走的那个魔法神器。 我已经告诉过你, 接下来发生了什么。 ";
			link.l1 = "我会记住你刚才告诉我的。 谢谢你, 纳撒尼尔。 你帮了我很大的忙。 ";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "保重, "+pchar.name+"。 神庙的迷宫和大厅充满了危险。 只要一步错, 你肯定会永远留在那里。 ";
			link.l1 = "有备无患, 朋友。 我已预先警告, 这意味着我已做好准备。 我现在得走了。 再见! ";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "祝你好运, "+pchar.name+"! ";
			link.l1 = "谢谢! ";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}