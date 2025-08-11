void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "你想要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "听说昨晚酒馆里有场斗殴... 但谁在打 —鬼才知道。 反正我脸还完好。 应该吧。 ";
				link.l1 = "看来这里昨晚喝得很凶? ";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "喂, "+GetSexPhrase("伙计","姑娘")+", 看见我的靴子了吗? 我在酒馆桌子底下醉倒时, 某个卑鄙的小偷把它偷走了。 ";
						link.l1 = "眼睛放亮点, 不然另一只也保不住。 ";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "听说昨天酒馆里有场斗殴... 不过谁在打就没人知道了。 我脸好像还完好。 应该吧。 ";
						link.l1 = "也许他们觉得你的脸已经够惨了。 ";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "该死的深海恶魔, 我昨天还有满满一钱包金子! 现在到底在哪儿? ! ";
						link.l1 = "对真正的海盗来说, 金子不是最珍贵的奖赏。 自由才有更高的价值。 ";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "哦, 绝对的! 酒馆老板忙得不可开交... 嗝... 除此之外... 有人偷了他的杜松子酒! 不止一瓶, 是整整一桶! 而且不是普通的桶 —加勒比海独一份的! 据说从欧洲运来的。 他不肯说给谁的, 但有件事很清楚: 如果不尽快找到, 这可怜的家伙要倒大霉了! ";
			link.l1 = "有意思。 好吧, 保重, 老醉鬼。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "你还想怎样? 没看见我头都要裂了吗? 滚蛋。 ";
					link.l1 = "也许少喝点, 你还能像个正常人, 而不是一堆烂醉如泥的废物。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "别烦我... 我头快炸了! ";
					link.l1 = "真神奇, 它居然还在你肩膀上。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "诅咒你下地狱... 让我安静会儿, 没看见我没心情说话吗! ";
					link.l1 = "... ";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "退后! 没看见我忍无可忍了吗? 我拳头正痒, 想揍人。 ";
			link.l1 = "冷静点, 水手。 我只是想听听昨天酒馆里发生了什么。 ";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "该死的! 你是"+GetSexPhrase("那个疯女招待的另一个情人","她的亲戚")+"? 你想怎样, 愿你在风暴中被卷下船? 要挑战我决斗吗? 还是现在就拔刀? ";
			if (pchar.sex == "woman")
			{
				link.l1 = "亲戚? 算不上。 但你, 伙计, 好像对她评价不高? ";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "情人? 算不上。 那女人在征服男人方面似乎重数量不重质量, 你说呢? ";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "她的风流韵事与我无关。 告诉我发生了什么, 我就走。 是你把她激怒的, 对吗? ";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;
		
		case "OS_Matros_3_scrit":
			dialog.text = "那母夜叉就像饿了几个月的水手一样毫无眼光 —看见什么抓什么, 事后再算账! 她一晚上都对我抛媚眼, 像酒馆里觅食的猫一样调情。 但我刚想‘抛锚靠岸’ —她尖叫得连湾里的鱼都吓得往深处钻! ";
			link.l1 = "也许你喝太多朗姆酒, 所以行事方式太直接了? ";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "那母夜叉就像饿了几个月的水手一样毫无眼光 —看见什么抓什么, 事后再算账! 她一晚上都对我抛媚眼, 像酒馆里觅食的猫一样调情。 但我刚想‘抛锚靠岸’ —她尖叫得连湾里的鱼都吓得往深处钻! ";
			link.l1 = "也许你喝太多朗姆酒, 所以行事方式太直接了? ";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "我可能是喝多了, 但我记得清清楚楚发生了什么。 不是我追她 —她像闻到血腥味的鲨鱼一样围着我转。 她一整天都在我身边晃! ";
			if (pchar.sex == "woman")
			{
				link.l1 = "就为这点小事, 你准备和第一个遇到的人打架? 还是那晚发生了别的事? ";
			}
			else
			{
				link.l1 = "听着, 你说‘另一个情人’。 你知道她的风流韵事? ";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "她的尖叫平息后, 我的船友们说我在她身上浪费时间。 说她在镇上有个追求者, 和我们船长关系很好。 ";
			link.l1 = "有意思。 你还注意到其他不寻常的事吗? 也许骚乱时有谁接近吧台? ";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "真该死... 我头痛得像礁石上的船体, 你却在这里问个不停。 我什么都没看见没听见。 你给几个比索, 比折磨一个老水手好过。 ";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "给你一百比索。 记住别喝得烂醉, 再中那个女招待的圈套, 嗯? ";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "没我的钱你也能过。 不然你只会喝得烂醉, 再去纠缠那个女招待。 ";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "嘿, 杰克! 你船舱里有个码头妓女! 哈哈! 瞧瞧她 —多迷人的小魔鬼! 我想知道, 她是搜完了我们所有箱子, 还是我们在最有趣的时候打断了她? ";
				link.l1 = "... ";
			}
			else
			{
				dialog.text = "嘿, 杰克! 看看我们找到了什么 —一个偷东西的老鼠! 哈哈! 看看这个无赖! 已经在翻我们的水手箱了, 对吧, 你这偷偷摸摸的杂种? ";
				link.l1 = "... ";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "大胆的小母鸡。 闯进杰克.维尔的巢穴 —没多少人有这胆子。 那么你为什么来这儿, 甜心? 以为可以招待我们, 是吗? ";
				link.l1 = "招待你们? 哈! 你们真是梦想家, 先生们。 我来取回你们偷的东西。 你们真以为你们可怜的小表演不会被发现? ";
			}
			else
			{
				dialog.text = "真是条大胆的虫子。 闯进杰克.维尔的房子不是很多人敢尝试的。 那么, 你在这里有什么事? ";
				link.l1 = "只能说我在追回被盗的财产。 或者你们真以为你们可怜的小把戏不会被发现? ";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "可怜的表演? 让魔鬼烤了我吧, 我会剥了你的皮做船帆! 哈哈! 不过也许我们可以先... 和你玩玩? ";
				link.l1 = "看来你急着见造物主? 很好, 我不耽误你了 —接招吧, 你们这些肮脏的混蛋! ";
			}
			else
			{
				dialog.text = "可怜的把戏? 让魔鬼带走我吧, 我会把你的皮剥下来做帆布! 废话少说 —你的死期到了, 你这可怜的狗东西! ";
				link.l1 = "如果这是你想要的, 那就接招吧, 恶棍们! ";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", 我的杜松子酒呢? ! 如果你没有, 我就亲自把你扔进海里喂鱼! ";
			link.l1 = "... ";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "... ";
			link.l1 = "我刚自己送来的。 在这儿。 ";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("你给了杜松子酒桶", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "很高兴看到我没信错人, "+sld.name+"。 明天来我住处拿杜布隆。 ";
			link.l1 = "... ";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "Zaharia_4":
			DialogExit();
			
			//ChangeShowIntarface();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;
		
		case "Tavern_1":
			dialog.text = "船长, 关于那块牌匾... ";
			link.l1 = "什么牌匾? 啊, 那个... 我想我不需要这种荣誉。 不必为我麻烦。 ";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "我可以提供更好的! 从今天起, 你在我的酒馆永远有免费住宿和饮品! 像你这样的人物当然值得! ";
			link.l1 = "这才合我意! 这种特权我很欣赏! 后会有期, "+npchar.name+"。 ";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// 敌对船只在海上攻击
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}