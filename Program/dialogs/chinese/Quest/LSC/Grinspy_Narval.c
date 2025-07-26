// 唐纳德.格林斯皮 - 独角鲸帮首领
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "什么? 你想要什么? ";
				link.l1 = TimeGreeting()+"。 我叫"+GetFullName(pchar)+"。 我想见见帮派首领。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, "+GetFullName(pchar)+"! 想要点什么? ";
				link.l5 = "只是想跟你打个招呼。 再见! ";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // 第一次见面
			dialog.text = "现在你认识我了。 我叫唐纳德.格林斯皮, 别惹我或我的人生气。 在你拿到密码之前, 不要试图访问'圣盖博号'。 商店可以自由访问, 每个人都需要交易。 有什么问题吗? ";
			link.l2 = "不, 我知道了。 再见。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------查德和玛丽在卡罗琳号上被击溃后---------------------------
		case "shark":
			dialog.text = "你找我有什么事? ";
			link.l1 = "一件非常不愉快的事, 唐纳德。 昨晚有人企图谋杀史蒂文。 你们帮派的战士参与了。 ";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "我对此一无所知。 你为什么认为他们是我的人? ";
			link.l1 = "因为我在那里。 我们能够区分你们的人。 海盗和里瓦多斯人。 这个团体由玛丽.卡斯帕和查德.卡珀领导。 你需要更多证据吗? ";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "我只能向你保证, 我和我的人与此事无关。 ";
			link.l1 = "你将不得不向舰队司令保证这一点, 而且这并不容易。 袭击发生后, 多德森对所有独角鲸帮非常愤怒。 他打算向你们宣战 --他将停止向你们提供物资, 并在任何机会下射杀你们的人。 这不是说说而已。 ";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "我希望舰队司令明白他要做什么。 他怀疑我的人也能开枪吗? ";
			link.l1 = "我想他知道。 他准备把'圣奥古斯丁号'变成堡垒, 战斗到你们都饿死。 此外, 多德森打算与里瓦多斯谈判, 并向他们提供合作。 你们无法对抗舰队司令和里瓦多斯的联合。 ";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "该死的! 但我们不是这次企图的一部分! 为什么整个帮派必须为那个愚蠢的女孩玛丽和我船员中的一群人渣s 的行为付出代价? \n此外, 让我们谈谈逻辑, 杀死马洛的是多德森自己激怒了玛丽和我的士兵。 当你做出如此卑鄙的行为时, 就会发生这种情况。 ";
			link.l1 = "你什么都不明白。 你被愚弄了。 你为什么这么确定是多德森杀了艾伦? 实际上, 他认为是你为了夺取他的位置而做的... ";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "我不在乎他怎么想。 所有证据都对他不利。 只有他和他的人能进入监狱。 艾伦在他手中。 红玛丽告诉了我很多。 在艾伦被杀之前, 多德森亲自参观了监狱, 而他不常这样做。 ";
			link.l1 = "你看到他的死亡了吗? ";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "垃圾! 我当然没有。 ";
			link.l1 = "而奇米塞特看到了。 是的-是的, 里瓦多斯的巫师, 他一直坐在艾伦旁边。 他最近也在那里被谋杀了。 在他死前一天, 我在监狱里和他谈过。 米尔罗是被鲨鱼的水手长查德.卡珀杀死的。 ";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "这是真的吗? ";
			link.l1 = "想想看: 奇米塞特不在乎你和舰队司令的关系。 他没有理由撒谎。 老巫师害怕查德, 他认为自己会是下一个。 他是对的, 查德一得知舰队司令要释放他, 就谋杀了他。 ";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "但为什么卡珀想要艾伦死? ";
			link.l1 = "该死的, 你真的不明白吗? 我告诉过你, 卡珀和红玛丽一起工作。 他想取代鲨鱼的位置, 并制定了一个狡猾的计划。 杀死艾伦.米尔罗并散布关于鲨鱼参与他死亡的流言, 使独角鲸帮派对舰队司令怀有敌意... ";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "愚蠢的女孩玛丽信任他, 站在她男朋友真正凶手的一边。 他们说服了一些独角鲸加入他们, 这对玛丽来说一定很容易。 然后他们在法奇奥的船舱里组织了对舰队司令的袭击, 法奇奥被迫写了一封给舰队司令的邀请... ";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "我有一封来自法奇奥的信, 解释了一切。 查德杀死奇米塞特是因为他是危险的证人。 他与独角鲸帮合作, 里瓦多斯在与鲨鱼交谈时会很高兴听到这一点。 我们将通过展示这封信, 轻松向黑埃迪证明查德成为了你们的人。 ";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "嗯。 你已经拿到了所有的王牌, 那你在这里做什么? 你想从我这里得到什么, 对吗? ";
			link.l1 = "是的。 因为我相信这都是查德的计划, 而你没有参与。 查德欺骗了玛丽, 她叫来了你们帮派的朋友帮助她, 这就是整个故事。 至少, 我没有找到任何针对你或其他独角鲸的证据... ";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "但这并不意味着没有其他策划者留下。 我希望你寻找他们。 然后, 也许我们可以在没有屠杀的情况下解决问题。 ";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "我已经告诉你, 我的其他人没有参与。 马洛死后, 玛丽基本上离开了帮派, 把自己锁在船舱里。 实际上, 我不知道她是如何说服其他人参与的, 但似乎她成功了。 我发誓, 我和我帮派的任何人都没有反对舰队司令的行为。 \n我们最近失去了太多人, 所以我们现在不想卷入混乱的事情。 我不害怕舰队司令的攻击, 即使与里瓦多斯联手。 独角鲸是真正的战士, 我们将在最后一场战斗中证明这一点。 但这将是毫无意义的\n我们已经决定与舰队司令保持和平。 里瓦多斯是不同的事情, 我们不与黑人谈判。 我准备亲自向舰队司令道歉, 为米尔罗之死引起的怀疑和对他生命的攻击请求原谅。 我将在圣经上发誓证明我的诚意。 你和多德森对此满意吗? ";
			link.l1 = "我满意。 你确定不会有来自你手下的诡计吗? ";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "绝对确定。 我会通知我的帮派关于艾伦.米尔罗的真正凶手。 我手下与舰队司令的关系将立即改变, 我向你保证。 告诉我, 之后需要屠杀吗? ";
			link.l1 = "不, 不需要。 我来这里是为了阻止它。 我信任你, 唐纳德, 我会尽力说服鲨鱼。 我还剩下一些论据... 再见, 唐纳德! ";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // 鲨鱼的节点
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "你已经和舰队司令谈过了吗? 有什么结果? ";
			link.l1 = "我正在进行中。 我稍后会见你... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "你已经和舰队司令谈过了吗? 有什么结果? ";
			link.l1 = "是的, 我谈过了。 你的道歉被接受了, 对你帮派的指控也撤销了。 还有更多, 鲨鱼邀请你去见他, 讨论独角鲸帮和海盗之间未来和平协议的条款。 ";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "老实说, 我没想到... 这是个好消息。 也许我们甚至可以重新考虑为我们帮派提供物资的价格, 以及关于里瓦多斯的新政策。 ";
			link.l1 = "那只关系到你和舰队司令。 ";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "是的, 当然。 你通过阻止无意义的流血事件, 甚至可能是我手下的彻底灭绝, 为独角鲸帮派做出了巨大的贡献。 把这把塔楼滑膛枪作为我感激的象征, 你不会找到另一把这样的武器\n此外, 你被允许像任何帮派成员一样访问我们的限制区域。 ";
			link.l1 = "谢谢! 现在再见, 我有很多事情要做。 ";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("你收到了一把塔楼滑膛枪");
			PlaySound("interface\important_item.wav");
			dialog.text = "祝你好运。 如果你有任何问题, 来找我。 ";
			link.l1 = "知道了。 再见! ";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; // 独角鲸船只通行标志
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("他们说你是独角鲸帮首领唐纳德.格林斯皮的朋友。 嗯, 里瓦多斯现在恨你... ", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("他们说你现在是独角鲸帮的人。 或者你在舰队司令的指挥下服务? 我不明白... ", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("我听说你在舰队司令和独角鲸帮之间实现了和平。 嗯, 里瓦多斯一定对此很疯狂... ", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("所以查德.卡珀是艾伦.米尔罗的凶手! 真令人惊讶! ", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // 成为朋友
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "嗬! "+GetFullName(pchar)+"! 你是... 不, 这不可能! 你还活着? ! ";
				link.l1 = "关于我死亡的传言有点错误, 唐纳德。 哈哈, 很高兴见到你! ";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "啊-啊, 我的朋友"+GetFullName(pchar)+"! 需要什么吗? ";
			link.l1 = "不, 不需要。 只是想跟你打个招呼。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "你找我有什么事? ";
			link.l1 = "一件非常不愉快的事, 唐纳德。 有人企图谋杀史蒂文。 你们帮派的战士参与了。 ";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "我对此一无所知。 你为什么认为我的人参与了? ";
			link.l1 = "因为我亲自杀死了其中几个, 还有查德.卡珀, 舰队司令的水手长, 他对这一切混乱负责。 他自己做不到, 所以你的人帮了他很多。 舰队司令知道这一点, 他非常非常生气。 ";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "我的人? 到底是谁, 你能说出他们的名字吗? ";
			link.l1 = "他们没有自我介绍。 他们只是射击和击剑。 你们的人很鲁莽。 他们甚至可以攻击自己人。 去他妈的我或舰队司令, 但企图杀死那个女孩? ";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "嗯。 你在说谁? ";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "我在说谁? 我在说对红玛丽的袭击。 两个独角鲸试图杀死她。 我纯属偶然在关键时刻到达她的船舱。 如果我来晚了, 他们就会杀了她。 我没有问他们的名字, 对不起, 我没有时间和他们说话, 但玛丽说他们是独角鲸。 ";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "我在说谁? 我在说对红玛丽的袭击和杀死她的那两个独角鲸。 ";
				link.l1.go = "negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "什么? 她为什么不告诉我? ! 我会立即采取行动! ";
			link.l1 = "她最近甚至害怕离开自己的船舱。 她不久前和你争吵过, 所以她为什么要跑去找你寻求帮助? ";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "我没有和她争吵! 她向我提出不可能的要求, 我们进行了激烈的交谈, 我把她送走了。 但这并不意味着我... ";
			link.l1 = "好吧, 不管怎样。 毕竟, 现在所有问题都解决了。 但你们的人中有混蛋, 这是事实。 ";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "什么? 她被独角鲸杀死了? 为什么? ";
			link.l1 = "根据查德.卡珀的命令, 唐纳德。 她知道得太多, 而且她不想帮助查德。 现在这个可怜的女孩死了! ";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "我发誓, 我对此一无所知! ";
			link.l1 = "当然, 你不知道... 但让我们谈谈舰队司令。 查德.卡珀组织了这次企图, 你的人帮助了他。 他们试图毒害多德森, 我勉强阻止了。 ";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "我没有下过这样的命令。 多德森知道我不支持已故艾伦的政策, 我认为温和的妥协比激烈的诉讼更好。 ";
			link.l1 = "你将不得不向舰队司令保证这一点, 而且这并不容易。 袭击发生后, 多德森对所有独角鲸帮非常愤怒。 他打算向你们宣战。 ";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "我希望舰队司令明白他的行为。 他怀疑我的人会反击吗? ";
			link.l1 = "他知道。 他认为你们的帮派是一群强盗, 必须在你们开始杀人之前摧毁。 此外, 我们与里瓦多斯有牢固的联系。 我可以简单地和黑埃迪谈谈, 向他提供联盟。 你们无法对抗我们所有人。 ";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "如果你不相信我, 叫红玛丽来问她! 她会证实的。 ";
			else sTemp = "我有一封查德给玛丽的信, 证明了一切。 ";
			dialog.text = "该死的! 为什么整个帮派必须为几个白痴的行为付出代价? 别以为我害怕。 我们是战士, 即使在最后一场战斗中我们也会证明这一点。 但我想要正义。 实际上, 舰队司令应对在监狱中杀死艾伦.米尔罗负责。 ";
			link.l1 = "你怎么能成为首领, 唐纳德... 你既不了解玛丽, 也不了解艾伦。 查德.卡珀杀了他。 "+sTemp+" 他这样做是为了让独角鲸帮对舰队司令怀有敌意, 并拉拢一些人到他那边。 ";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "我明白了。 好吧。 让我们换个方式谈谈。 你在这里有什么目的, 对吗? 你想要什么? ";
			link.l1 = "我不想要岛上的血腥混乱。 我不希望人们死亡。 我不喜欢消灭所有独角鲸的想法, 尽管我向你保证, 里瓦多斯和我们有能力做到这一点。 我也认为整个帮派不应该为一些混蛋的行为负责... ";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "但我的投票还不够 --你应该正式向舰队司令保证, 这次企图没有得到你的批准, 你的帮派也没有计划杀死多德森。 ";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "我能做什么? 我准备为这次企图和我对马洛之死的怀疑道歉。 我可以向他保证, 独角鲸帮没有计划对他做任何事情, 我将在圣经上发誓。 你和多德森会觉得足够吗? ";
			link.l1 = "我会的。 我相信如果你亲自拜访多德森, 这对他也有效。 但首先, 我会告诉他你的意图, 然后我会带着结果再次拜访你。 ";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "好的。 我会等。 ";
			link.l1 = "我很快就会回来... ";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // 鲨鱼的节点
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "你已经和舰队司令谈过了吗? 有什么结果? ";
			link.l1 = "是的, 我谈过了。 如果你正式拜访他, 问题就解决了。 ";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "老实说, 我没想到... 这是个好消息。 ";
			link.l1 = "是的, 你知道, 我也很高兴。 ";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "你通过阻止一场无意义的屠杀, 也许甚至是我族人的彻底灭绝, 为独角鲸帮派做出了巨大的贡献。 我授予你这把塔楼滑膛枪 --你不会找到另一把这样的武器。 你也被允许无限制地访问我们的船只。 ";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "谢谢。 一件非常有价值的礼物。 是的, 唐纳德, 还有一件事: 与红玛丽和解。 她脾气暴躁, 但她也真诚诚实。 与你的争吵使她离开了帮派, 这几乎要了她的命。 ";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "谢谢。 一件非常有价值的礼物。 我真的很高兴事情就这样结束了。 ";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "告诉她, 我请求她原谅我伤害了她, 以及那两个敢于攻击她的人渣s。 你们俩是... 朋友, 对吗? ";
			link.l1 = "你说得对, 唐纳德。 我会告诉她。 我真的很高兴这一切就这样结束了。 ";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("你收到了一把塔楼滑膛枪");
			PlaySound("interface\important_item.wav");
			dialog.text = "祝你好运。 如果你有任何问题, 来找我。 ";
			link.l1 = "好的。 再见! ";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; // 独角鲸船只通行标志
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // 从内部打开刻瑞斯
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// 这里清理所有积累的垃圾
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // 守卫属性
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("他们说你是独角鲸帮首领唐纳德.格林斯皮的朋友。 嗯, 里瓦多斯现在恨你... ", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("他们说你现在是独角鲸帮的人。 或者你在舰队司令的指挥下服务? 我不明白... ", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("我听说你在舰队司令和独角鲸帮之间实现了和平。 嗯, 里瓦多斯一定对此很疯狂... ", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("所以查德.卡珀是艾伦.米尔罗的凶手! 真令人惊讶! ", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("照顾好红玛丽, 因为你很幸运和她在一起 --她太鲁莽了! 她总是惹上麻烦... ", "LostShipsCity", 20, 5, "LSC", "");
		break;
//---------------------------------------—— 特殊反应 -----------------------------------------------
		// 发现玩家在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里做什么, 啊? 小偷! ", "看看那个! 我一陷入沉思, 你就决定检查我的箱子! ", "决定检查我的箱子? 你不会逃脱的! ");
			link.l1 = "该死的! ";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "什么? ! 决定检查我的箱子? 你不会逃脱的! ";
			link.l1 = "愚蠢的女孩! ";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// 发现露出的武器
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("听着, 你最好把武器收起来。 这让我紧张。 ", "你知道, 在这里携带武器是不被容忍的。 收起来。 ", "听着, 不要扮演中世纪骑士到处跑着拿剑。 收起来, 这不适合你... ");
			link.l1 = LinkRandPhrase("好的。 ", "当然。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请求你收起你的 blade。 ", "听着, 我是这个城市的公民, 我请求你收起你的 blade。 ");
				link.l1 = LinkRandPhrase("好的。 ", "当然。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 伙计, 带着武器跑。 我可能会紧张... ", "我不喜欢男人拿着武器在我面前走。 这让我害怕... ");
				link.l1 = RandPhraseSimple("知道了。 ", "我正在收起来。 ");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <—— 特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}