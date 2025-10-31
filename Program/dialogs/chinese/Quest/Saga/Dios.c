// 何塞.迪奥斯 - 地图绘制者
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你想要什么吗? ";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting() + "! 告诉我, 你是地图绘制者何塞.迪奥斯吗? ";
				link.l3.go = "island";
			}
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "是的, 是我。 我不认识你, 先生。 你想从我这里得到什么? ";
			link.l1 = "我叫" +GetFullName(pchar)+ ", 是扬.斯文森派我来的。 你还记得他吗? ";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "啊, 斯文森先生! 我当然记得他! 来, 请坐舒服点... 尊敬的扬近况如何? ";
			link.l1 = "谢谢, 他很好。 迪奥斯先生, 我需要你的帮助。 我想和你咨询一件事, 由于你的职业, 你一定很熟悉。 扬推荐你作为加勒比地区的地理专家... ";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "我在听, 先生。 你想知道群岛地理的什么事? ";
			link.l1 = "据说在哈瓦那西北, 古巴和墨西哥湾之间有一个岛屿或其他地貌。 这个岛屿从未在任何地图上标注过。 我想知道这些传言的可信度。 ";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "嗯... 你问的是多年来一直困扰我的事情。 你提到的这个地方长期以来吸引着地理学家的好奇心, 但从未有人勇敢到去探索那个地区。 ";
			link.l1 = "为什么? ";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "问题在于那个地方是某种自然异常。 该地区风暴的概率比其他任何地方都高得多。 也许原因在于冷海流, 但这只是我的假设。 很多船只在那里失踪, 这足以让水手避开那个地方, 反正所有主要航线都远离该地区。 ";
			link.l1 = "我猜你也不知道真相... ";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "正是如此, 先生。 但我有一些历史文献和一些实物证据, 所以我完全有权利怀疑那个地方存在的可能性很高。 ";
			link.l1 = "你能告诉我更多吗? ";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "当然。 最重要的证据是历史文献, 其中摘录了阿尔瓦拉多船长1620年访问该岛的日记。 我告诉你一个很有趣的故事! ";
			link.l1 = "阿尔瓦拉多船长? 这是我第二次听到这个名字... ";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "我并不惊讶。 阿尔瓦拉多船长的故事多年来一直是民间传说的一部分。 它被改变了, 充满了谣言。 谎言和梦想, 所以这就是 - 废弃船只岛的传说。 \n流言会改变, 但纸和墨水不会, 它们完好无损地保存了数百年。 看, 读这个故事 - 也许它会帮助你揭开你在寻找的东西。 ";
			link.l1 = "谢谢! 还有其他的吗? ";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "有一种理论认为, 该地区的海底上升到足够高的高度, 形成了一个广阔的浅滩。 我已经提到过洋流。 根据水手的说法, 那里还有大量的海鸥和其他海鸟聚集。 \n阿尔沃拉多提到了弗朗西斯科.贝坦科尔特舰队司令中队的船只名称, 该中队在五十多年前失踪了。 我怀疑这不仅仅是巧合... ";
			link.l1 = "我将返回我的船, 仔细阅读阿尔瓦拉多的笔记。 感谢你的帮助, 迪奥斯先生! ";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "不客气。 实际上我根本没有帮助你, 你没有得到那个地方的坐标, 我也没有。 我甚至无法证明那里有一个有人居住的岛屿。 但据我了解, 你打算探索这个地区? \n如果是这样, 请注意, 我将非常感谢任何信息, 尤其是带有实物证据的信息。 看来你是个有钱人, 但我会想办法报答你。 ";
			link.l1 = "好的。 那么我们成交了, 迪奥斯先生。 也许我的笔记将来也会被某人阅读... 甚至有人可能会写一个传说... ";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "为什么不呢? " +pchar.name+ "先生, 我看你是个喜欢冒险。 经常旅行的人, 所以我想请你做件事。 ";
			link.l1 = "是吗? 我在听。 ";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "你知道我是个地图绘制者。 所以, 两年来我一直在绘制加勒比群岛的地图, 为新格拉纳达副王的竞赛编制舰队司令地图集。 但当我被海盗俘虏时, 我所有的二十四张地图都以最无礼的方式从我的房子里被盗了, 就是斯文森先生救了我的那些海盗。 \n我确信这次袭击是由我的一个竞争对手组织的, 目的是获取我的地图。 已经过去很长时间了, 但我再也没有见过我那套地图中的任何一张。 ";
			link.l1 = "我明白了。 你想让我把你的地图找回来。 ";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "正是如此。 也许你会在未来的冒险中找到它们。 很容易辨认 - 每张地图上都有我的标志。 如果你能奇迹般地收集到全部二十四张地图, 我会慷慨地奖励你。 ";
			link.l1 = "好的。 从现在起, 我会仔细查看在群岛中找到的每一张地图。 好了, 我现在得走了。 感谢你的有趣谈话和文件。 ";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//运气
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "啊, 是你, " +GetFullName(pchar)+ "先生? 有什么有趣的事要告诉我吗? ";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting() + "! 迪奥斯先生, 请看看我找到的地图。 根据标志, 它一定是你的地图之一。 ";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting() + "! 迪奥斯先生, 我有好消息告诉你。 我能够收集到你独特的全套地图, 就像你想要的那样。 这是全部二十四张地图。 ";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // 曾在LSC
			{
				link.l4 = TimeGreeting() + "! 是的, 我有。 我去过我们谈论的那个神秘地方。 ";
				link.l4.go = "LSC";
			}
			link.l9 = "到目前为止什么都没有, 先生。 只是想看看你怎么样了。 ";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "给我看看... (看了看) 当然! 这是我为舰队司令地图集绘制的地图之一! 船长, 我真的请求你找到所有地图! 我知道这几乎不可能, 但仍然... 我不想失去希望。 ";
			link.l1 = "别失去希望, 先生。 我已经找到了这张地图, 所以有机会我也会找到剩下的。 它们还在加勒比地区。 ";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "你的乐观真的鼓舞了我, 船长先生。 也许我仍然能够有机会向唐璜.德.科尔多瓦展示谁是群岛上最好的地图绘制者! ";
			link.l1 = "你将能够击败所有竞争的恶意者。 这些地图真的很棒... 再见, 先生! ";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "我不敢相信我的眼睛! 你真的找到了它们? 全部? ";
			link.l1 = "是的。这可不容易, 不过老子总算走了好运, 在这桩买卖里得手了。 拿去, 你的地图。 它们真是绝妙, 每一张都远胜过我以前见过的任何一张。";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			RemoveAllAdmiralMap()
			Log_Info("你已经给出了全套舰队司令地图");
			PlaySound("interface\important_item.wav");
			dialog.text = "难以置信! 这太不可思议了! 说实话, 我从未相信这一刻会发生。 ";
			link.l1 = "Dum spiro, spero, 迪奥斯先生。 你现在可以面对科尔多瓦先生了。 我相信他会高度评价你的才能。 ";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "谢谢你, 船长! 你甚至没有意识到你为我做了多么伟大的服务。 正如我承诺的 - 我会奖励你。 我也有一份礼物给你。 我想作为一名水手, 你会觉得它非常有用。 ";
			link.l1 = "你引起了我的兴趣, 先生! ";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("你收到了一个船用望远镜");
			PlaySound("interface\important_item.wav");
			dialog.text = "给你! 这是我设计的船用望远镜。 它是独一无二的, 你在任何地方都找不到另一个像这样的。 镜片是由西班牙最熟练的大师在欧洲制造的。 它的外壳是由一位友好的枪匠制作的。 一个特殊的三脚架将帮助你指向设备, 尽管有任何摇晃。 你可以看到你需要的一切, 无论是船还是堡垒。 ";
			link.l1 = "如此美妙的礼物! 谢谢你, 迪奥斯先生。 ";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "另外, 既然事情发展到这一步, 我还有一个小小的提议要给你。";
			link.l1 = "什么提议? 我洗耳恭听。";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//运气
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // 魅力
			AddCharacterExpToSkill(pchar, "Sneak", 300);//隐藏 (因为给了望远镜)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);//声誉-知名度
			ChangeCharacterComplexReputation(pchar, "authority", 5);//声誉-权威
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "我突然想到, 这些地图对探险家来说确实不错, 可对海船船长却远远不够。 你想啊: 所有的海湾、海角和泻湖都画得很精确, 可是你却没法用它们来规划群岛之间的航路。";
			link.l1 = "没错, 用它们根本定不出航线。";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "我可以为你绘制一张群岛的地图! 可不是那种能在荷兰西印度公司买到的, 而是一张独一无二的精良地图。";
			link.l1 = "谢谢你, 迪奥斯先生, 但我不需要这样的地图。 不过, 还是非常感谢你的提议! ";
			link.l1.go = "best_map_02";
			link.l2 = "你在开玩笑吗? ! 迪奥斯先生, 我怎么可能拒绝? 只要告诉我你需要什么 - 我不会吝啬任何金钱或工具! ";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "好吧, 我不得不提议。 无论如何, 与你做生意很愉快, " + pchar.lastname + "先生! ";
			link.l1 = "我也是! 祝你好运! ";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "工具我已经有了, 多谢。我要一张群岛的普通地图, 还得要一只罗盘和一只校准过的天文钟: 地图必须精准, 否则就是添乱。至于报酬——一箱达布隆金币。";
			if(CheckAMapItems())
			{
				link.l1 = "你说的这些我全都带在身上了。来, 拿去吧。";
				link.l1.go = "best_map_07";
			}
			link.l2 = "一张群岛的普通地图、罗盘、校准过的天文钟, 还有一箱达布隆金币。我记住了! 我会尽快送来, 你等着! ";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "你好! 我亲爱的朋友! 你带来了一张群岛的普通地图、罗盘、 校准过的天文钟和一箱达布隆金币了吗? ";
			link.l1 = "还没有, 迪奥斯先生。但我一定会带来的! ";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "是的, 迪奥斯先生。都在这儿, 拿去吧。";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("你交出了一张常规的群岛地图, 一个罗盘, 一个精密天文钟, 和一箱杜布隆。 ");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "那么, 我要开始工作了。 一周后回来, 我保证你不会后悔! ";
			link.l1 = "我毫不怀疑, 先生。 一周后见! ";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "哦, 你来了, "+pchar.lastname+"先生? 我得告诉你一个好消息: 我已经完成了群岛的地图! 而且我敢保证, 它比你之前交给我的那张好得多。";
				link.l1 = "我的朋友……这张地图真是令人惊叹! 这简直, 不怕说出口, 就是一件杰作! 我该如何感谢你为我所做的一切? ";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "你好, 先生! 请原谅, 地图还没准备好。";
				link.l1 = "是的, 我记得你说过需要一个星期。 我只是来看看你。";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "得了吧, 我的朋友。 能为一位懂得欣赏的高贵船长绘制这样的地图, 对我来说是一种快乐。 啊, 对了——这是你的那张普通地图, 还给你。 祝你在大海上好运! ";
			link.l1 = "万分感谢! 你说得对, 这张地图对我来说真是无价之宝。 再见, 迪奥斯先生! ";
			link.l1.go = "best_map_10";
		break;

		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("你收到了一张优秀的群岛地图! ");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "真的吗? ! 你找到了它? 请坐舒服点, 我想接下来的谈话会持续一段时间, 对吗? ";
			link.l1 = "我真的有很多关于这个岛的事情要告诉你。 但是, 首先, 我想让你答应我一件事。 我看你是个有荣誉的人, 所以我相信你会信守诺言... ";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "你在说什么, 船长? ";
			link.l1 = "那里有人居住... 他们不会高兴如果有人干涉他们的生活。 我认为某个'研究'中队的可能到来不会受到欢迎。 ";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "所以我想让你以荣誉发誓, 在我们谈话后的十年内, 你不会发布任何可用于找到该岛的信息。 欢迎你发布关于当地人。 他们的生活等任何信息, 只是不要透露该岛的位置。 ";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "我同意, 船长。 我以贵族的名义发誓, 在未来十年内, 我不会告诉任何人该岛的位置或任何可能伤害其居民的信息。 ";
			link.l1 = "那就听我的故事吧。 如果你愿意, 把它写下来。 所以, 这个岛是由许多失事船只组成的, 它们的船体躺在一个广阔的浅滩上... ";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("两小时后... ", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //转动时间
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "难以置信! 你告诉了我非常有价值的信息, 船长! 贝坦科尔特舰队司令的后代住在这个岛上! 现在我们知道他的中队发生了什么。 现在加勒比海地图上又少了一个空白点... 非常感谢你的故事, " +pchar.name+ "! ";
			link.l1 = "现在明白为什么我要求你在复述我的信息时要非常小心了吧? ";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "我明白。 你可以确信我会信守诺言。 告诉我... 你有任何来自该岛的实物属性吗? ";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "我有废弃船只岛的航行指南。 给, 看看。 它们允许你驾驶一艘小船穿过礁石和碎片, 并安全登陆该岛。 没有这些指南, 不可能到达该岛。 ";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "不幸的是, 我没有。 ";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("你给出了航行指南");
			PlaySound("interface\important_item.wav");
			dialog.text = "(看着) 如此优秀的文件! 它是由一位精通地图绘制的人绘制的。 即使是我也不能做得更好。 难以置信! 船长, 你为什么不把这些航行指南给我? 故事是故事, 但这张纸必须展示给旧世界最著名的地理学家! ";
			link.l1 = "迪奥斯先生, 不幸的是, 我需要这个文件给自己。 正如我之前所说, 没有它, 无法穿过环绕该岛的礁石。 但如果你愿意, 你可以制作指南的副本, 如果你拥有它们, 我只会高兴。 ";
			link.l1.go = "LSC_10";
			//link.l2 = "迪奥斯先生, 不幸的是, 我需要这个物品给自己。 正如我所说, 没有它, 无法绕过该岛周围的礁石。 我会为了科学牺牲它, 但是... 我相信你明白。 ";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("你收到了航行指南");
			PlaySound("interface\important_item.wav");
			dialog.text = "完全正确。 这是你的权利, 尽管很遗憾... 无论如何, 感谢你的故事! 你为地理学家。 地图绘制者和其他好奇的人做了一项伟大的服务。 ";
			link.l1 = "不客气, 先生。 好了, 我现在得走了。 再见。 ";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "真遗憾... 无论如何, 感谢你的故事! 你为地理学家。 地图绘制者和其他好奇的人做了一项伟大的服务。 ";
			link.l1 = "不客气, 先生。 好了, 我现在得走了。 再见。 ";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "当然, " +pchar.name+ "。 你为我花费了很多时间。 代我向斯文森先生问好! ";
			link.l1 = "再见, 迪奥斯先生。 ";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//运气
			AddCharacterExpToSkill(pchar, "Leadership", 500); // 魅力
			ChangeCharacterComplexReputation(pchar, "nobility", 5);//声誉-知名度
			ChangeCharacterComplexReputation(pchar, "authority", 2);//声誉-权威
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("你收到了航行指南");
			PlaySound("interface\important_item.wav");
			dialog.text = "非常感谢! 你真是太好了。 给我一些时间... ";
			link.l1 = "... ";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("两小时后", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "非常感谢! 你真是太好了。 现在我们不仅有口头证据, 还有实物证据... 我不会让你没有回报的, 船长。 我有一份小礼物给你。 ";
			link.l1 = "什么样的礼物? ";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // 给亚历克斯的天文钟属性
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "我不仅喜欢地图绘制和地理, 还喜欢数学和天文学。 我花了一年时间尝试创建一种用于测量纬度和经度的通用工具。 我取得了一些进展。 给, 看看: \n这是我的六分仪。 我自己设计的。 问题是, 它不工作。 它需要一个极其精确的天文钟。 即使是最好的工匠制作的天文钟, 随着时间的推移也会产生不可接受的误差。 因此, 我的工具现在毫无价值。 \n但既然你经常旅行, 也许你会找到一个足够精确的天文钟, 让六分仪工作。 一旦你找到这样的时钟 - 你将不需要罗盘。 指南针。 星盘。 沙漏和其他蹩脚的天文钟 - 我的工具将取代它们所有。 ";
			link.l1 = "谢谢你, 迪奥斯先生。 希望我能找到一个能让你的发明工作的天文钟。 我想要这样的设备... 处于工作状态。 好了, 我现在得走了。 再见。 ";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> 处理试图进入箱子的反应块
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你是 " + GetSexPhrase("一个小偷, 我明白了! 卫兵, 抓住他","一个小偷, 我明白了! 卫兵, 抓住她") + "!!! ", "我不敢相信! 我转过身一秒钟 - 你就钻进我的东西里! 抓小偷!!! ", "卫兵! 抢劫! 抓小偷!!! ");
			link.l1 = "啊啊, 魔鬼!!! ";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//< —处理试图进入箱子的反应块
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}