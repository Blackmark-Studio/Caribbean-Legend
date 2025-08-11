// 阿比盖尔.施努尔
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "日安, 先生。 什么风把您吹到我们家来了? ";
					link.l1 = "日安, 阿比盖尔。 我叫" +GetFullName(pchar)+ "。 我是为共和国和荷兰西印度公司效力的船长。 ";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "我的上帝, 你找到我父亲的钱了吗? 是真的吗? 啊, 我太高兴了! 快去找我父亲, 他想和你谈谈! 去吧! ";
					link.l1 = "我这就去, 夫人。 ";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "船长, 您把我们从绝望中拯救出来了! 我对您感激不尽! 现在施努尔家族的好名声可以恢复了! ";
					link.l1 = "只是尽了身为绅士的职责, 夫人。 我希望现在没有什么能阻止您嫁给我的赞助人了。 ";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "船长, 您需要什么吗? ";
				link.l1 = "暂时不需要, 夫人。 ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "致敬神圣的王后, 我们的生命。 我们的甘甜与我们的希望。 我们向你呼号, 厄娃被放逐的可怜子女。 我们向你发出叹息, 在这泪谷中哀恸哭泣... 哦, 先生, 您吓到我了! 什么风把您吹到这里来? ";
					link.l1 = "请原谅, 我猜您是阿比盖尔吧? 理查德.弗利特伍德派我来... ";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "船长, 您想要什么吗? ";
				link.l1 = "暂时不需要, 夫人。 ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "这里发生了什么事? 这噪音是怎么回事? 爸爸, 这个陌生人是谁? ";
					link.l1 = "日安, 夫人。 我猜您是阿比盖尔.施努尔吧? 很高兴见到您。 请原谅我的无礼, 但我这里有一封给您的紧急信件, 来自... 好吧, 我很想告诉您, 但您亲爱的父亲甚至不让我进屋, 更不用说给您送信了。 ";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "啊, 查尔斯, 你来了。 我准备好跟你去任何地方了! ";
					link.l1 = "那我们走吧。 ";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "查尔斯, 我们到圣约翰了吗? 我很快能见到理查德吗? ";
					link.l1 = "是的, 夫人, 我们到圣约翰了。 不幸的是, 理查德现在不在镇上, 他两天前被命令去巴巴多斯附近巡逻了。 别担心, 他应该一周后回来。 ";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "查尔斯! 很高兴见到你! 有理查德的消息吗? ";
					link.l1 = "唉, 我亲爱的夫人。 理查德不得不暂时留在布里奇敦执行一项秘密而重要的任务, 与荷兰人有关。 我想理查德已经告诉过你他的职业了, 对吧? ";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "查尔斯! 是你! 你终于回来了! ";
					link.l1 = "问候您, 夫人。 很高兴见到您。 ";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "啊, 我终于回家了! 很高兴再次见到爸爸! 查尔斯, 感谢你为我所做的一切! ";
					link.l1 = "请别这么说, 夫人。 为困境中的女士尽绅士之责是我的义务。 ";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "爸爸, 如果你记得什么, 请说出来! 查尔斯, 他是... 他可以信任。 我敢说, 他是唯一能帮助我们的人! ";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "我会日夜为你祈祷! 告诉我... 告诉我你会去做! 你会找到那个岛! ";
					link.l1 = "我会尽我所能, 夫人。 ";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "啊, 查尔斯! 你回来了! 快告诉我, 你找到那个岛了吗? 我再也等不及了! ";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "是的, 阿比。 我找到了那个岛和你父亲的钱。 我来把它还给你。 ";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "唉, 夫人。 我既没找到凯勒船长, 也没找到你的岛。 我尽力了, 但是... ";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "啊, 是你啊, 查尔斯! 需要什么吗? 要喝杯咖啡吗? ";
				link.l1 = "不, 什么都不需要。 请别麻烦了。 ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "日安, 先生。 有什么事吗? ";
			link.l1 = "没什么, 夫人。 请原谅我。 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------前往荷兰-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "很荣幸见到你, " +GetFullName(pchar)+ "船长。 我从镇上其他女士那里听到了关于你的各种故事。 你就是那个俘获海盗幽灵船并将其作为战利品带到威廉斯塔德的人。 告诉我, 船长... 这艘船真的是由... 理查德.弗利特伍德指挥的吗? ";
			link.l1 = "你听到的都是真的, 夫人。 我和其他人一样, 发现真相时震惊不已。 这是个丑闻! 英联邦的海军军官像普通海盗一样掠夺自己国家的商人! 那个恶棍试图通过假装成荷兰西印度公司支持的变节'幽灵船'来掩盖他的卑鄙行为。 他利用这个掩护来指责公司, 并攻击荷兰船只。 ";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "我头晕目眩... 听到这样可怕的事情很难受, 船长。 我亲自认识理查德.弗利特伍德, 我从没想过他... ";
			link.l1 = "夫人, 我的赞助人卢卡斯.罗登堡告诉了我你从累西腓到库拉索的航行。 现在清楚了。 弗利特伍德击沉了你的船, 然后回来'拯救'你和你父亲, 让你们不至于被困在那个荒岛上。 我自己读了海盗的日志, 他在日志里记录了每一个细节。 ";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "真是噩梦... 看来我爸爸终究是对的。 他一直告诉我理查德就是那个给我们带来所有不幸的海盗。 真相大白我应该高兴... 啊, 抱歉, 船长。 只是我可怜的脑袋要消化的东西太多了... 像您这样重要的人, 找一个普通女孩有什么事? ";
			link.l1 = "阿比盖尔, 我来这里是因为一件非常复杂和微妙的事情。 你愿意听我说吗? ";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "当然, 先生。 我洗耳恭听。 ";
			link.l1 = "正如我所说, 我为公司服务。 卢卡斯.罗登堡不仅是我的军事指挥官, 也是我的好朋友。 他派我来给您带个口信。 如果您同意他的求婚, 将是他最大的幸福。 我来这里是想问您是否愿意嫁给我的赞助人。 他愿意为您的幸福做任何事。 ";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "哦, 船长! 我现在明白为什么罗登堡先生自己不这么做了... 我可怜的爸爸会高兴坏了, 但我... ";
			link.l1 = "夫人, 我看得出有什么事困扰着您。 您怀疑罗登堡先生的诚意吗? 也许我可以帮您改变主意? ";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "哦不, 船长, 我毫不怀疑罗登堡先生的诚意。 卢卡斯为我和我爸爸做了那么多, 如果不是他照顾我们, 我不知道我们会怎么样。 但请您理解我的处境! \n我们家不是罗斯柴尔德家族, 但也从未贫穷过。 施努尔家族在欧洲的银行界以财富闻名... 但现在这个可怕的海盗毁了我们! 我再也无法忍受那些背后议论我的恶毒闲话了。 镇上每个搬弄是非的家庭主妇和女仆都认为我只是为了罗登堡先生的钱.'多像个犹太女人啊,'她们说。 这些残忍的坏蛋! 要是我父亲记得那个岛的位置就好了! 他把我们家族剩下的财产藏在那里, 以免落入那些谋杀了我姐妹和兄弟的邪恶海盗手中! \n但我可怜的父亲不是水手, 他根本记不起那个岛和我们家族的钱在哪里! 船长, 请和我父亲谈谈! 也许他能想起什么对您老练的判断力有用的东西。 请找到那个岛和我们的财富! 您将把一个可怜的女孩从羞耻和耻辱中拯救出来! ";
			link.l1 = "很好, 阿比盖尔。 我会和你父亲谈谈。 要有信心, 女孩, 我会尽力而为。 ";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "谢谢, 先生。 我会日夜为您祈祷。 愿我们祖先的神与您同在! ";
			link.l1 = "再见, 阿比盖尔。 我会带着好消息回来, 我发誓。 ";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "哦, 是的! 罗登堡先生是个正直善良的人。 我会毫不犹豫地同意, 很高兴称他为我的丈夫。 ";
			link.l1 = "那么我认为我的使命完成了。 我现在必须去找罗登堡先生, 告诉他这个好消息。 衷心祝您幸福, 夫人。 ";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//现在去找卢卡斯
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------前往英国-----------------------------------------
		case "Seek_Island":
			dialog.text = "理查德派你来的? 圣母玛利亚保佑, 谢谢你! 啊, 先生! 我听说可怜的理查德受伤了, 生命垂危。 是真的吗? 告诉我, 他还活着吗? ! 他健康吗? ! ";
			link.l1 = "理查德还活着, 而且... 基本健康。 先告诉你坏消息: 他情况有点糟, 暂时失明了, 但正在康复。 现在是好消息: 理查德希望你和他一起航行到英国, 在那里你们将结婚。 他在加勒比的时间结束了, 在等你的答复。 ";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "啊, 我亲爱的信使, 告诉理查德, 为了我们的幸福, 我愿意随他去任何地方。 但我担心我们私奔会要了我可怜父亲的命... 先生, 我很绝望, 不知道该怎么办。 我希望理查德能找到那个该死的岛和装着我们家族黄金的箱子... 也许这能在我离开后安慰我爸爸。 ";
			link.l1 = "我明白... 我的任务是把你送到安提瓜, 但这让事情有点复杂。 如果我找到那个岛和箱子并带给你, 你会和我一起去圣约翰见理查德吗? ";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "哦, 是的, 先生, 我会在我们家族的祈祷中记住您! 我会给我们的第一个儿子取名为您! 非常感谢您, 船长! 我会为您祈祷! 去吧, 愿基督和圣母玛利亚与您同在! ";
			link.l1 = "我不会让您等太久的, 夫人。 我很快就会回来。 ";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//阿比回家
			pchar.questTemp.HWIC_Coordinates = "true"; //通过船舱寻找岛屿的坐标属性
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------对抗所有人------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "哦... 你有他的信? 哦, 爸爸, 别对我们的客人这么苛刻! 你神经质的幻想让我难堪! 先生, 请跟我来, 我想和你谈谈。 ";
			link.l1 = "谢谢你, 小姐。 很高兴看到这房子里还有人讲道理。 ";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "请原谅我父亲, 先生。 他其实是个善良的人, 但我们的... 不幸让他崩溃了。 ";
			link.l1 = "没关系, 小姐, 我理解。 让我自我介绍一下, 我是查理.克尼佩尔。 我是奉理查德.弗利特伍德的命令来的, 他想让我带您去见他。 请读这封信。 ";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "哦, 理查德... (阅读)。 哦, 上帝! 他决定... 把我父亲所有丢失的钱都还回来! 如此慷慨! 亲爱的, 甜蜜的理查德! 先生, 您像加百列一样带来了好消息! 理查德, 他在哪里? 在库拉索吗? ";
			link.l1 = "不, 小姐。 有人试图谋杀他, 他受了重伤。 现在在安提瓜... 你还没读完信。 ";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "无染原罪的圣母玛利亚, 为我们这些投奔你的人祈祷吧! 告诉我, 他安全吗? 伤势严重吗? ";
			link.l1 = "别那样担心, 小姐! 理查德不是那种会让混蛋轻易杀死的人。 他现在正在休息康复。 他想让我带您去见他。 然后你们俩将航行到伦敦... 请读完信, 小姐, 您太着急了。 ";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "啊, 是的... 对不起(阅读)。 克尼佩尔先生, 我准备好和您一起航行了。 我需要一天时间收拾东西, 和我爸爸谈谈。 明天回来, 我就和您走。 ";
			link.l1 = "好的, 女士。 我明天会来。 我和我的船员会在航行中保护您免受任何危险。 ";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//计时器3天
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//把阿比放在船长的船舱里
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//取消计时器
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//计时器1个月
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//专门为特别固执的人
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "啊, 真遗憾。 但我想我可以再等一周, 就像之前一样... ";
			link.l1 = "说得好, 小姐。 为了让您等待时更舒适, 我建议把这个简陋的船舱换成我朋友的房子。 那里会有柔软的床和为您准备的美味食物。 ";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "你真好, 查理。 谢谢你。 能在陆地上走走真好... 在海浪中颠簸后, 我觉得很不舒服。 ";
			link.l1 = "请跟我来, 小姐。 ";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "很高兴见到你, 约翰。 感谢你们的盛情款待, 先生们! ";
			link.l1 = "... ";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//取消计时器
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//这样玩家就不会自己和他说话了
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "哦, 查理, 我只见过理查德几次, 他没告诉我太多他的工作。 ";
			link.l1 = "我很惊讶他会对他爱的女人隐瞒这么大的秘密... 小姐, 理查德不仅仅是个普通船长。 他也是英国枢密院的特别特工。 一个非常重要的人, 直接处理护国公下令的微妙任务。 现在, 他的职责与摧毁荷兰西印度公司在加勒比的贸易势力有关。 ";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "先生, 你在说什么? ";
			link.l1 = "是的, 小姐。 你心爱的理查德 - 我的朋友 - 是个非常重要的人。 我一直为是他的朋友而自豪, 但他甚至对我也变得非常神秘。 很明显, 他在执行某种秘密任务。 很抱歉, 这个任务让他不能见你。 ";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "查理, 你吓到我了。 你确定他没事吗? ";
			link.l1 = "我确定。 我只是... 我不赞成他现在这样对待你。 我知道他的任务至关重要, 他甚至不能为了你而背叛职责。 ";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "哦, 我善良的查理... 如果需要, 我会等理查德直到第二次降临。 也许我可以留在酒馆楼上... 我不能再长时间利用约翰的款待了。 ";
			link.l1 = "别胡说八道了, 女士! 你的到来是我们的荣幸, 如果我把我亲爱的朋友理查德.弗利特伍德的未婚妻赶出家门, 我就不叫查理.克尼佩尔! ";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "查理... 你对我的态度让我很感动。 我只是个普通女孩, 还是个犹太女人... ";
			link.l1 = "小姐! 我知道那是愚蠢的言论, 你是个优秀的基督教年轻女子! 甚至不要想酒馆! 如果我在为理查德服务时辜负了你, 我永远不会原谅自己。 ";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "谢谢你, 查理。 很高兴你是这样一个... 好人。 ";
			link.l1 = "这是我的职责, 小姐。 现在抱歉, 我得走了。 你现在可以自由地在镇上走走, 被关在这房子里一定很孤独, 对吗? ";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "嗯... 约翰是个很有趣的伙伴。 他可以连续几个小时谈论他的粉末。 混合物和各种... 疾病。 他也是个礼貌和蔼的人。 此外, 我定期去教堂, 当地的牧师很善良... 但是, 当然, 我真的很想念理查德。 ";
			link.l1 = "我想他很快就会回来。 如果您需要任何帮助, 查理.克尼佩尔为您服务。 ";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "我听到关于理查德的谣言... 说他失踪了。 你知道什么吗, 查理? ";
			link.l1 = "我知道, 阿比盖尔。 很抱歉... 理查德.弗利特伍德已经去了英国, 不会回来了。 他得到了晋升或调动, 类似这样的... 无论如何, 在他对你做了那些事后, 我不想再认识他。 ";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "啊, 我就知道会这样结束... .(抽泣) 为什么我不听爸爸的话! 至少, 如果我嫁给卢卡斯.罗登堡, 他会高兴的。 ";
			link.l1 = "再次原谅我, 小姐... ";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "原谅什么, 查理? 你根本没有错! 你对我只有善意! ";
			link.l1 = "因为我要告诉你更多坏消息。 我刚从库拉索回来, 卢卡斯.罗登堡因煽动叛乱和背叛共和国被捕了。 他被用铁链送回阿姆斯特丹受审。 他试图谋杀公司董事彼得.斯特伊弗桑特。 除此之外, 他还试图推翻威廉斯塔德的总督, 并涉嫌至少谋杀另一人, 所以我怀疑执政者不会轻饶他。 ";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "哦, 上帝! 真是噩梦! 我想我要晕倒了! 查尔斯, 是真的吗? 不, 请说不是! ";
			link.l1 = "抱歉, 小姐, 还有更糟的。 在调查罗登堡的行为时发现, 击沉你帆船的海盗是在卢卡斯.罗登堡的命令下行动的。 他在对英国航运进行私人战争。 很抱歉, 阿比盖尔。 你在加勒比遇到的所有男人都是骗子。 小偷和杀人犯。 ";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "哦... 我完了。 查尔斯... 请... 带我回家, 回威廉斯塔德。 我需要我爸爸... ";
			link.l1 = "当然, 亲爱的小姐。 不幸的是, 布里奇敦没有你的容身之处。 去收拾东西, 和约翰道别, 我们马上起航。 ";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//打开阿比的房间
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "不, 查理, 我需要说谢谢。 如果不是你和约翰, 我都不知道会发生什么。 你是我在群岛上遇到的唯一诚实的人。 ";
			link.l1 = "嗯... 你让我脸红了, 阿比盖尔。 我很高兴能帮助你。 对于这一切混乱, 我非常抱歉。 ";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "你知道, 查理, 在我们回库拉索的航行中, 我想了很多。 现在一切都清楚了 - 理查德.弗利特伍德, 罗登堡先生 - 一切似乎都只是一场终于结束的噩梦。 我又和爸爸在一起了, 我们可以回到正常的生活\n但这并不容易 - 我们没有钱。 但我们会挺过去的, 一切都会好起来的。 圣母玛利亚会照顾我们的, 她从不忘记她的孩子, 甚至我那固执的老父亲, 他否认她的儿子。 ";
			link.l1 = "阿比盖尔小姐, 我会帮助你。 ";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "帮助我们? 但是怎么帮, 查理? ";
			link.l1 = "理查德告诉了我你遭遇海难和获救的故事。 此外, 我知道你父亲能够把他的财物藏在一个未知的岛上。 我要找到它, 把你的钱带回来。 ";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "哦, 查理... 我和我父亲都无法告诉你那个倒霉的岛在哪里... 我们不是水手。 除此之外, 袭击时我吓坏了, 除了血和死亡的气味, 我什么都不记得了。 ";
			link.l1 = "阿比盖尔, 试着回忆一下。 请, 任何细节都能帮助我, 即使是最小的细节。 也许袭击前发生了什么? 那个岛是什么样子的? ";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "岛... 看起来像个岛? 一个海湾, 丛林。 没有什么特别的。 哦, 我记得! 也许这能帮到你。 就在海盗袭击前不久, 我们遇到了一艘帆船, 并向船长致敬。 他被邀请到我们的船上, 和我们的船长共进晚餐。 我们也在那里。 也许, 他知道这个岛。 ";
			link.l1 = "那很重要! 那艘帆船和船长的名字是什么? ";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "我不记得了, 查理。 我真的不记得了... ";
			link.l1 = "试着回忆, 阿比! ";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "我们会等你的。 帮助我, 查理.克尼佩尔。 你是我们唯一的希望... 我会为你祈祷! 一路顺风! ";
			link.l1 = "我这就出发。 再见, 阿比。 再见, 所罗门。 ";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "哦, 亲爱的... 真遗憾。 我们曾希望, 但是... 还是谢谢你, 查理, 谢谢你甚至在别人都不愿帮忙时尝试帮助我们。 看来这就是上帝为我安排的命运。 ";
			link.l1 = "再见, 阿比盖尔。 希望你一切都好。 ";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "是... 是真的吗? 你真的把我们丢失的钱带回来了? 哦, 查理! ";
			link.l1 = "是的, 是真的。 我带来了。 给, 拿着。 这都是你的。 ";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //取消中断
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "我该如何感谢你? ! 如何? ! ";
			link.l1 = "我不需要任何感谢, 阿比。 这是我能为你做的最起码的事。 现在你可以开始新生活了, 没有任何罗登堡。 弗利特伍德或其他想占你便宜的陌生男人。 我相信你父亲能找到让这些钱生钱的方法... 这似乎是遗传的特质。 ";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "查理, 别这么无礼! 你为我, 为我和我可怜的父亲做了这么多。 为什么, 我已经习惯了你在我生活中的存在。 我每天都在为你祈祷, 以后也会每天为你和你的船员向圣母玛利亚祈祷! 你是我们的守护天使。 不管你信不信, 是上帝亲自派你到我们家来的。 \n在你走之前, 我想让你知道, 我们家的门永远为你敞开。 还有... 请让我吻你, 我亲爱的查理... ";
			link.l1 = "嗯... 好的, 当然, 阿比... 如果你坚持的话。 ";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "上帝保佑你, 查尔斯。 对我们来说什么都没有改变... 我在教堂外乞讨。 ";
			link.l1 = "保持坚强, 小姐。 愿上帝与你同在。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "查尔斯, 是你! 很高兴见到你! 请坐! 我去煮咖啡! ";
			link.l1 = "我也很高兴见到你, 阿比。 很高兴你过得很好。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> 处理尝试打开箱子的反应块
		case "Woman_FackYou":
			dialog.text = "啊, 原来是这样? ! 我把你当客人接待, 你却想抢劫我? ! 卫兵!!! ";
			link.l1 = "闭嘴, 愚蠢的女孩。 ";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- 处理尝试打开箱子的反应块
	}
}