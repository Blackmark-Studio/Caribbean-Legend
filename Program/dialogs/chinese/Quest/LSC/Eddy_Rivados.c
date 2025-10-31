// 里瓦多斯帮派首领 - 黑埃迪
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
			dialog.text = "白人, 你在里瓦多斯的地盘上做什么? ";
			link.l1 = "只是想认识一下当地人。 如果打扰到你, 抱歉。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "我很高兴迎接里瓦多斯的朋友, 也是个好人! 奇米塞特告诉我你为他做的事。 所有里瓦多人, 包括我, 现在都欠你人情。 请允许我自我介绍 —爱德华.布莱克, 也被称为黑埃迪, 里瓦多斯帮的首领。 ";
			link.l1 = ""+GetFullName(pchar)+"。 不过我想奇米塞特已经告诉过你关于我的事了。 他答应过会告诉你... ";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "他确实说了。 现在你可以自由访问我们的船只。 守卫不会阻拦你, 我们也会很高兴见到你。 小心独角鲸帮, 他们肯定已经知道你救了奇米塞特, 而他们不会喜欢这点, 因为我们是敌人。 ";
			link.l1 = "我会注意的。 谢谢你的热情欢迎, 埃迪! 现在请允许我和奇米塞特谈谈。 ";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("他们说你是里瓦多斯首领黑埃迪的密友。 你是怎么做到的? ", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("里瓦多斯认你作朋友。 你是怎么做到的? ", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("他们说独角鲸帮悬赏你的人头。 你害怕吗? ", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> 信息块
		case "Total_info": // 成为朋友
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "白人兄弟? 还活着? 我很高兴! 这么说, 独角鲸帮告诉大家你淹死了是在撒谎... ";
				link.l1 = "我也很高兴见到你, 埃迪。 关于我死亡的谣言被大大夸大了。 ";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "很高兴见到你, "+pchar.name+"。 有什么消息吗? ";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "埃迪, 你认识一个叫纳撒尼尔.霍克的人吗? 据我所知, 他一定在这里。 ";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "多给我讲讲里瓦多斯帮的事。 ";
				link.l2.go = "rivados";
			}
			link.l9 = "没什么特别的, 真的。 只是想打个招呼。 ";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "纳撒尼尔.霍克? 不, 我不认识这个人。 他既不在里瓦多斯的船上, 也不在中立区。 至于独角鲸帮, 我就不知道了, 我们不去他们那里。 ";
			link.l1 = "我知道了... ";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "里瓦多斯帮成立于很多年前。 它是这座废弃船只之城的第一个帮派。 五十多年前, 贝当古舰队司令的探险队从西非带着几艘大型奴隶船航行到这里。 塔塔罗斯的货舱里装满了数百名运往加勒比种植园的黑人奴隶。 这些奴隶中有一个叫佩德罗.里瓦多斯的人, 一些葡萄牙牧师教他读书写字\n他设法从枷锁中解放了几十名奴隶, 并发起了一场叛乱。 唉, 其余的奴隶没能加入他。 叛乱被镇压了。 奴隶贩子将里瓦多斯手脚捆绑, 留在船舱里, 让他饥渴而死。 几天后, 天气变坏, 贝当古的中队被一场强大的风暴席卷\n几天后, 在与天气搏斗后, 仅存的两艘完整船只'圣奥古斯丁号'和'塔塔罗斯号'被困在这个岛的中央。 在这些事件中, 很多人死亡, 黑人和白人都有, 但更多的人设法幸存下来。 前奴隶们一起开始了新的生活, 并以解放者佩德罗.里瓦多斯的名字自称里瓦多斯人。 ";
			link.l1 = "一个非常有趣的故事... 谢谢你! ";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// < —信息块
		
		case "capper":
			dialog.text = "白人, 你在里瓦多斯的地盘上需要什么? ";
			link.l1 = "我叫"+GetFullName(pchar)+", 我是按多德森舰队司令的命令来这里的。 我必须和黑埃迪谈谈。 据我所知, 就是你。 ";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "是的, 我是爱德华.布莱克, 也被称为黑埃迪。 告诉我舰队司令需要我做什么。 ";
			link.l1 = "塔塔罗斯上有一个叫奇米塞特的人.舰队司令愿意释放他。 ";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "这是个好消息。 奇米塞特是我们的精神领袖, 所有里瓦多人都想念他。 但我知道舰队司令愿意释放他是想换取什么, 对吗? ";
			link.l1 = "没什么。 他只是想释放他作为善意的表示。 但有一个问题... ";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "说吧, 白人。 ";
			link.l1 = "舰队司令的前水手长, 现任狱卒查德.卡珀加入了独角鲸帮, 变成了叛徒, 现在他不受舰队司令控制。 我们知道查德计划杀死奇米塞特.舰队司令不希望这种情况发生。 我们提议进行联合行动, 以铲除叛徒并释放你们的人。 ";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "你的话听起来有点奇怪, 但继续说。 奇米塞特有麻烦了吗? ";
			link.l1 = "是的。 查德计划杀了他。 卡珀打算利用独角鲸帮来夺取城市的控制权。 如果我们想救奇米塞特, 我们必须迅速行动, 因为查德现在还没有怀疑什么.舰队司令已经从塔塔罗斯撤走了所有守卫, 通道是畅通的。 这是打开监狱内门的钥匙。 拿着。 ";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "召集你的人, 去塔塔罗斯释放奇米塞特。 一切都看你们的了。 ";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "这闻起来像个陷阱... 如果有埋伏怎么办? 如果舰队司令决定打击里瓦多斯怎么办? 他为什么不自己处理卡珀? ";
			link.l1 = "多德森说你在乎奇米塞特的生命... 他已经做了足够多的事: 这是钥匙, 守卫也撤走了。 你只需要进去, 对付查德, 释放你们的人。 我向你保证没有陷阱。 是的, 还有最后一件事:舰队司令想要查德的人头来换取奇米塞特的生命和自由。 我们达成协议了吗? ";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "奇米塞特的生命对里瓦多斯人来说价值无法衡量。 我们将立即前往塔塔罗斯。 但你将留在这里作为我们的人质。 如果有埋伏, 你将面对里瓦多斯的愤怒! \nzikomo! 守在门边, 看着我们的客人。 别让他出去。 我将亲自带领对塔塔罗斯的攻击! ";
			link.l1 = "祝你好运, 埃迪。 记住: 我需要查德.卡珀的人头! ";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//关闭位置
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "奇米塞特被释放了! 你没撒谎, 白人, 我准备称你为里瓦多斯的朋友! ";
			link.l1 = "我很高兴。 查德.卡珀死了吗? ";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "我必须请求你的原谅, 白人朋友: 你为我们做了一切, 但我们辜负了你... 我辜负了你! 那个该死的卡珀逃跑了。 有两个独角鲸帮的人跟他在一起。 我们杀了他们, 但那个肮脏的狱卒从下门游到了独角鲸帮的地盘。 ";
			link.l1 = "该死的... 你们不知道塔塔罗斯有两个出口吗? ";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "我们没有想到。 我们从正门进攻... ";
			link.l1 = "可惜。 我本来指望拿到他的人头。 太糟糕了。 现在他会继续与我们为敌。 ";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "我承认我的过错。 但我们不能跟着他到敌对的船上。 你将得到我们的友谊和尊重, 而不是查德的人头。 从现在起, 你可以自由访问我们的领土。 奇米塞特的智慧也会很好地为你服务, 如果你需要什么, 就和他谈谈。 如果你需要, 就和他谈谈。 另外, 告诉舰队司令我保证我很感激他的行为。 ";
			link.l1 = "好的。 ";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "等等! 我们让查德跑了, 但我在他的桌子上发现了一些文件, 我们到达时他正在研究这些文件。 给你。 你可能会觉得有用, 白人兄弟。 ";
			link.l1 = "哈! 也许... 查德非常相信纸... ";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "你在这里永远是受欢迎的客人, 白人朋友。 所有里瓦多人都会知道这一点。 祝你好运! ";
			link.l1 = "你也一样, 埃迪... ";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //里瓦多斯船只通行标志
			// //里瓦多斯不会在需要密码的地方阻拦
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; //前往鲨鱼处
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; //鲨鱼的节点
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); //关闭通往唐纳德.格林斯皮的入口
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("你听到最新消息了吗? 里瓦多斯的傲慢已经失控, 他们袭击了舰队司令的监狱, 释放了他们的巫师! ", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("想想看 —那些傲慢的里瓦多斯竟敢袭击塔塔罗斯! 他们说狱卒查德.卡珀已经逃到独角鲸帮那里去了... ", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("这是最大的无礼, 不是吗? 袭击舰队司令的军事设施! 是的, 看起来黑埃迪越来越强大了... ", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}