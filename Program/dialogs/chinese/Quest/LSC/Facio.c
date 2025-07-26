// 帮派外交中间人朱塞佩.法奇奥
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

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
				dialog.text = "你好, 你好... 你是新来的? 我不记得你的脸。 允许我自我介绍 --我是朱塞佩.法奇奥, 这个小岛上的问题解决专家。 ";
				link.l1 = TimeGreeting()+"。 我叫"+GetFullName(pchar)+"。 你说得对, 我是新来的。 请原谅我的好奇心 --但你解决什么样的问题? ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, 又是你, 亲爱的"+pchar.name+"! 什么风把你吹到我这简陋的房子里来? ";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "法奇奥, 我和一个帮派有严重冲突。 我需要解决这个问题。 ";
					link.l10.go = "conflict";
				}
				// --> 任务分支
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "朱塞佩, 我在找一个叫阿道夫.巴比耶的人。 有人告诉我你最近和他在酒馆喝酒... ";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "朱塞佩, 他们说你完全耐酒。 不管喝多少, 你仍然站着。 ";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && GetCharacterItem(pchar, "gold_dublon") >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "我准备好参加你的游戏了。 这是我的赌注。 ";
					link.l5.go = "drink_4";
				}
				// <—— 任务分支
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "我想知道帮派当前进入他们领地的密码。 ";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("有什么有趣的事要说吗? ", "岛上发生什么新鲜事了吗? ", "你能告诉我最新的八卦吗? ");
				link.l2.go = "rumours_LSC";
				link.l3 = "没什么特别的, 朱塞佩。 只是想见见你。 ";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "各种各样的, 亲爱的, 各种各样的。 例如, 我在舰队司令和帮派之间调解事务。 你可能已经知道, 里瓦多斯。 独角鲸帮和舰队司令是相互的敌人。 当事情变得棘手时, 我充当调解人。 \n此外, 当舰队司令向帮派出售物资时, 我经常扮演中立角色。 但这只是我业务的一小部分。 所以如果你与里瓦多斯或独角鲸帮有麻烦 --不要犹豫向我求助, 我们会看看能做些什么。 ";
			link.l1 = "好的。 我会考虑的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// 密码
		case "parol_choice":
			dialog.text = "哪个帮派? ";
			link.l1 = "独角鲸帮。 ";
			link.l1.go = "parol_nrv";
			link.l2 = "里瓦多斯。 ";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "想见唐纳德.格林斯彭, 对吗? ";
			link.l1 = "正确。 那么你知道密码吗? ";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "想见黑埃迪, 对吗? ";
			link.l1 = "差不多。 那么你知道密码吗? ";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "当然! 但让我先给你一些细节。 密码只包含一个词, 每周更改一次。 每月的第七。 十四。 二十一和二十八天\n所以注意当前日期, 避免任何错误。 最后, 你必须明白, 这不是慈善。 一个密码五十杜布隆。 记住, 只收杜布隆。 ";
				link.l1 = "五十杜布隆? 这是一大笔钱! ";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "当然, 孩子。 你知道价格。 你有五十杜布隆吗? ";
				if (GetCharacterItem(pchar, "gold_dublon") >= 50)
				{
					link.l1 = "是的。 拿你的硬币。 ";
					link.l1.go = "parol_pay";
				}
				link.l2 = "不幸的是, 我没有。 也许以后... ";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "好了好了, 孩子, 冷静点。 别贪心, 相信我: 我知道我的信息的真正价值。 你不只是要在"+pchar.questTemp.LSC.parol+"的船上走走, 对吧。 所以你必须准备好 lose 一些硬币... 那么, 你准备好支付五十杜布隆了吗? ";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l1 = "是的。 拿你的硬币。 ";
				link.l1.go = "parol_pay";
			}
			link.l2 = "不幸的是, 我没有这么多钱。 也许以后... ";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveItems(pchar, "gold_dublon", 50);
			dialog.text = "太好了! 和你做生意真愉快。 "+pchar.questTemp.LSC.parol+"的当前密码是:'"+sTotalTemp+"'。 好好记住, 不要弄错, 否则我不会为你的生命支付一个硬币。 ";
			link.l1 = "我知道, 我知道... 谢谢! ";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "啊, 当然, 我的老好人阿道夫! 是的, 我和他谈过。 看, 亲爱的, 我很高兴收回我的钱, 那些我以为再也见不到的钱! 阿道夫用他那把出色的步枪作抵押借了一大笔钱, 他还我钱有困难\n我失去了收回它们的任何希望, 打算把那把施图岑猎枪卖给我们亲爱的阿克塞尔.约斯特。 但突然亲爱的阿道夫给我带来了我的金子! 原来他设法弄到了足够的硬币, 不仅赎回了他的施图岑猎枪, 还在'圣弗洛伦蒂娜号'的船头买了一个塞西尔.加拉德的船舱! \n当然, 这比住在半浸在水中的货舱里好多了\n因此, 阿道夫拿回了他的步枪, 有了一个新家, 我也拿回了我的钱。 我为什么要拒绝和他喝酒, 尤其是当他买单的时候? ";
			link.l1 = "啊, 当然! 你们有很多事情要喝酒庆祝。 而且是免费的... 谢谢, 朱塞佩, 你帮了我很多。 现在我知道在哪里可以找到阿道夫了。 ";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "这总是我的荣幸, 亲爱的。 但在晚上之前不要在他的船舱里找阿道夫, 他很忙, 到处跑着处理一些事情... 是的, 经常来看我, 聊聊天! ";
			link.l1 = "当我有自己的船舱时, 我会邀请你... 再见, 祝你好运! ";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // 用克隆替换阿道夫
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; // 阿道夫在船舱的标志
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // 自己
					dialog.text = "啊? 你为什么像着火一样闯进我的地方? 你以为你是谁? ? ";
					link.l1 = "你的正义... 投毒者! ";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // 在埃娃
					dialog.text = "饶了我! 我发誓, 他们强迫我! 他们用枪指着我的... ";
					link.l1 = "闭嘴。 我知道。 最后一个混蛋在哪里? 马塞洛.独眼龙在哪里? ! ";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // 一天后将法奇奥送回原位
				break;
				
				case 3: // 在鲨鱼
					dialog.text = "我发誓, 他们强迫我! 我已经把一切都告诉舰队司令了! 我无法抗拒他们, 他们会... ";
					link.l1 = "闭嘴。 我知道。 最后一个混蛋在哪里? 马塞洛.独眼龙在哪里? ! ";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // 一天后将法奇奥送回原位
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "什么... 你说什么? ";
			link.l1 = "我知道一切, 混蛋。 你一直在和查德.卡珀合作。 你给舰队司令带来了一桶有毒的朗姆酒。 现在祈祷吧, 你这个可怜的同性恋... ";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "等等! 住手! 饶了我! 我发誓, 他们强迫我! 他们用枪指着我的... ";
			link.l1 = "闭嘴。 我知道。 最后一个混蛋在哪里? 马塞洛.独眼龙在哪里? ! ";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "我... 我... 。 我不知道! ";
			link.l1 = "你在撒谎,人渣! 我看得出来。 独眼龙在哪里? ";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // 去弗莱龙
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "他... 他收到卡珀的一些命令, 已经走了。 我不知道他在哪里! ";
			link.l1 = "又撒谎。 你什么都知道。 别当懦夫, 你这个肮脏的东西 --卡珀死了, 他不会再伤害你了。 但如果你不告诉我马塞洛在哪里 --我现在就像杀猪一样宰了你! 查德给独眼龙下了什么命令? ";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "他派他去杀... 红玛丽。 ";
			link.l1 = "什么? ! 现在说, 他打算怎么做? 不可能进入她的船舱! 他打算怎么杀她? ! ";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "他会在铁匠不在的时候进入于尔根的船舱。 然后他会下到货舱底部, 穿过它, 到达玛丽的船舱\n然后他只需要等待女孩转过身或睡着。 这是查德告诉我的。 我发誓我知道的就这些! ";
			link.l1 = "这就够了。 他什么时候走的? 我问你, 独眼龙什么时候去'刻瑞斯铁匠号'的? ";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "他一定已经在于尔根的船舱里了... 或者正在下到货舱里面... ";
			link.l1 = "该死的! 我没有时间绕着岛游泳! 告诉我独角鲸帮船只的密码! 说, 如果你骗我, 我无论如何都会活下去, 但你肯定会死! ";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"'... ";
			link.l1 = "知道了。 现在祈祷那个女孩能活下来。 ";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//打开位置
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "我已经告诉你我知道的一切了! 我发誓! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "他... 他在'弗莱龙号'里面的某个地方。 查德命令他躲在那里, 等待他的下一个命令。 ";
			link.l1 = "我知道了。 最好是实话... ";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//打开位置
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> 冲突
		case "conflict":
			dialog.text = "是这样吗? 那么, 孩子, 哪个帮派在困扰你? ";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "独角鲸帮。 ";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "里瓦多斯。 ";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "舰队司令的海盗。 ";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "没有这样的事。 我在开玩笑, 朱塞佩, 我很好。 ";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "嗯, 这实际上不是冲突, 只是一个小误会, 呵呵。 "+sti(npchar.quest.price)+" 杜布隆, 你的问题将在一天内解决。 ";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "当然, 我听说过。 你惹了个大麻烦, 亲爱的。 但有办法解决。 "+sti(npchar.quest.price)+" 杜布隆, 你的问题将在一天内解决。 ";
				else dialog.text = "整个岛都知道你造成的屠杀。 帮助你不容易, 但有机会。 "+sti(npchar.quest.price)+" 杜布隆, 我会尝试解决你的问题。 ";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "给, 拿你的硬币, 处理一下。 ";
				link.l1.go = "pay";
			}
			link.l2 = "不幸的是, 我现在身上没有足够的杜布隆。 但我稍后会带来, 我们再谈。 ";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "嗯, 这实际上不是冲突, 只是一个小误会, 呵呵。 "+sti(npchar.quest.price)+" 杜布隆, 你的问题将在一天内解决。 ";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "当然, 我听说过。 你惹了个大麻烦, 亲爱的。 但有办法解决。 "+sti(npchar.quest.price)+" 杜布隆, 你的问题将在一天内解决。 ";
				else dialog.text = "整个岛都知道你造成的屠杀。 帮助你不容易, 但有机会。 "+sti(npchar.quest.price)+" 杜布隆, 我会尝试解决你的问题。 ";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "给, 拿你的硬币, 处理一下。 ";
				link.l1.go = "pay";
			}
			link.l2 = "不幸的是, 我现在身上没有足够的杜布隆。 但我稍后会带来, 我们再谈。 ";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "嗯, 这实际上不是冲突, 只是一个小误会, 呵呵。 "+sti(npchar.quest.price)+" 杜布隆, 你的问题将在一天内解决。 ";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "当然, 我听说过。 你惹了个大麻烦, 亲爱的。 但有办法解决。 "+sti(npchar.quest.price)+" 杜布隆, 你的问题将在一天内解决。 ";
				else dialog.text = "整个岛都知道你造成的屠杀。 帮助你不容易, 但有机会。 "+sti(npchar.quest.price)+" 杜布隆, 我会尝试解决你的问题。 ";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "给, 拿你的硬币, 处理一下。 ";
				link.l1.go = "pay";
			}
			link.l2 = "不幸的是, 我现在身上没有足够的杜布隆。 但我稍后会带来, 我们再谈。 ";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("你给了"+sti(npchar.quest.price)+"杜布隆");
			dialog.text = "太好了。 现在坐下休息一下。 在我解决你的问题之前, 你最好待在我的船舱里。 我不想让你把事情弄得更糟, 亲爱的。 ";
			link.l1 = "好的... ";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("一天后... "+ NewStr() +"法奇奥已经处理了冲突", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); // 转动时间
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // 和解
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//打开通往唐纳德的入口
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // 和解
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//打开通往埃迪的入口
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // 和解
					LSC_OpenSanAvgustinDoors(); // 打开圣奥古斯丁
					LSC_OpenTartarusDoors(); // 打开塔塔罗斯
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> 喝到见底
		case "drink":
			dialog.text = "来吧, 孩子! 撒谎, 他们都在撒谎, 呵呵。 我的头只是比一般人的头硬一点, 但我和你一样是人, 所以我也会被朗姆酒灌醉。 人们喝朗姆酒是为了喝醉, 这是它唯一的目的。 你想过吗, 亲爱的? ";
			link.l1 = "非常正确。 ";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "你想和我玩个有趣的游戏吗? 它叫做'喝到渣!', 哈哈! 我相信你已经听说过了。 对吗? ";
			link.l1 = "是的, 有一些关于它的传言... 我称之为'脸在桌子上'。 ";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "哈哈哈, 亲爱的孩子, 你让老人笑了, 我还能说什么!'脸在桌子上!'我会记住的... 那么你觉得呢? 玩一百杜布隆? ";
			link.l1 = "一百杜布隆? ";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "是的, 输家付酒钱。 成交? ";
			if (GetCharacterItem(pchar, "gold_dublon") >= 100)
			{
				link.l1 = "是的, 成交。 这是我的赌注。 ";
				link.l1.go = "drink_4";
			}
			link.l2 = "嗯。 我没有那么多杜布隆。 ";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "好吧, 等你有了再来找我, 我们再玩! ";
			link.l1 = "好的... ";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveItems(pchar, "gold_dublon", 100);
			Log_Info("你给了100杜布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "太好了, 亲爱的! 那么晚上九点在桑乔的酒馆见我! 是的, 如果你迟到, 你的赌注将留在我这里, 这是规则之一。 但你不会迟到的, 孩子, 对吧? ";
			link.l1 = "当然, 朱塞佩。 准备好酒瓶大战吧! ";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "还有你, 还有你, 亲爱的! 脸在桌子上! 哈哈! ";
			link.l1 = "九点在酒馆见! ";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; // 移除计时器
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "好吧, 亲爱的, 你准备好亲吻桌子了吗, 呵呵? 好桑乔已经给我们带来了朗姆酒。 我想不需要告诉你规则了吧? 它们很简单: 我们喝同一瓶酒, 直到其中一个倒下。 \n是的, 我们可以说话, 我们应该说话! 和体面的人交谈很棒, 不是吗? 如果你赢了, 你可以从桑乔那里得到你的奖品。 准备好了吗? ";
			link.l1 = "我说是的。 开始吧, 朱塞佩! ";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; // 移除计时器
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "十五个男人在死者身上... 嗝! 啊哈! 哟-吼-吼-哈... 还有... 瓶子... ";
			link.l1 = "光荣... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <—— 喝到见底
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}