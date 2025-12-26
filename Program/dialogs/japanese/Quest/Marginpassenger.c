void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "バグだ。必ず開発者に知らせてくれ。";
			link.l1 = "OK";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "ごきげんよう、船長。俺に何か用か？";
			link.l1 = "ああ。その通りだ。 "+GetAddress_FormToNPC(NPChar)+"。お前の船に俺が非常に興味を持っている乗客がいる。その名は "+pchar.GenQuest.Marginpassenger.q1Name+"。お前の乗客を俺の乗客にしたいんだ。それでいいなら、ここで別れて二度と会うことはないぜ。";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "そうかい？じゃあ、俺が「嫌だ」と言ったらどうする？";
			link.l1 = "それなら、今まさにお前の方に狙いを定めている俺の大砲で、何発かぶち込んでやって考え直させるしかねえな。 運を試すんじゃねえぞ、 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (7-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (7-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "仕方ねえな。俺にとって船員たちの命の方が、一人の男の運命より大事だ。だが、そう簡単には済まさねえぞ！ このことは絶対に忘れねえからな！";
				link.l1 = "落ち着け、心臓発作を起こすなよ……俺の新しい乗客を連れてこい！";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "俺の船から出て行ったほうがいいぜ、旦那。今のうちに許してやるからな。俺を脅すつもりか？ 俺の船に手を出すんじゃねえぞ、すぐに撃退してやるからな。機嫌がいいうちにとっとと消えろ！";
				link.l1 = "警告したはずだ。今向かっている。すぐに会おう、 "+GetAddress_FormToNPC(NPChar)+"!";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "もうこの話はしただろ、覚えてるか？俺の船から降りろ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "うおお、野郎め！てめえの所業の報いで地獄で焼かれやがれ！";
				link.l1 = "俺はお前に乗客をおとなしく引き渡す機会をやった……だが、お前は俺の申し出を断った。今や全てはお前一人の責任だぜ！";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "くそっ、この野郎！なぜこの平和な船を襲ったんだ？俺たちには金も貴重な品もねえぞ！";
				link.l1 = "しかし、お前の船には貴重な人物が乗っているじゃねえか……"+pchar.GenQuest.Marginpassenger.q1Name+"。お前の乗客をよこせ。";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "お前……汚ねえ海賊だな！";
			link.l1 = "しゃべりは少なめにな…";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "それで俺の船で虐殺をやらかしたってわけか？大勢の仲間が死んじまったんだぞ！海賊め！";
			link.l1 = "しゃべりは少なめにな…友よ…";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "何の用だ、 "+GetAddress_Form(NPChar)+"?";
			link.l1 = "「お前は」 "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "ああ、俺だ。申請書を出したいのか？それなら知っておくべきことがあるんだが…";
			link.l1 = "ちょっと待ってくれ、旦那。少し違う頼みがあるんだ……「」という名前の人物を知っているか "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "ああ、彼女のことは知ってる…もちろんだ！どうしたんだ？";
					link.l1 = "彼女はとても不愉快な状況に陥ったんだ――船が海賊に奪われてしまったのさ。\n幸いにも、俺がその海賊船に乗り込んで、その哀れな娘を救い出すことができた。\n彼女があんたの名前を教えてくれて、それで俺はここに来たってわけだ。";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "ああ、この男のことはよく知っている。どうしたんだ？";
					link.l1 = "彼はとんでもなく厄介な状況に陥ったんだ。奴の船が海賊に奪われちまってな。\nだが幸運にも、俺はその海賊船に乗り込んで囚われていた彼を救い出すことができた。\n彼は君の名前を教えてくれて――それで俺はここに来たってわけさ。";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "「おお神よ！彼女は今どこにいるんだ？なぜここに連れてこなかったんだ？」";
			link.l1 = "彼女は無事だ。さて、君の質問についてだが……そう簡単な話じゃない。俺が自分で彼女を家に送り届けることもできたが、その機会を君に譲ってやってもいいぜ。 もちろん、少しばかりの報酬はいただくがな。";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "うーん……よくわからねえな……";
			link.l1 = "どうしてやらないんだ？あんたが俺に金貨を払えば、俺はあの娘を渡す。そうすりゃ、 この状況をうまく利用できるだろう……あの娘と結婚したいんじゃねえのか？俺はその金で船を修理するさ。あの海賊との戦いで傷ついちまったからな。";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "「おお神よ！彼は今どこにいるんだ？なぜ彼をここに連れてこなかったんだ？」";
			link.l1 = "彼は無事だ。さて、君の質問だが……そう簡単にはいかない。俺が自分で彼を家に送り返すこともできたが、君が彼の家族に興味があるようだから、 この機会を譲ってやろう。ただし、少しばかりの報酬はもらうぜ。";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "ふむ……よくわからねえな……";
			link.l1 = "どうしてやらないんだ？お前が俺に金貨を払えば、友達を返してやるし、この状況をうまく利用できるだろう。 俺はちょっとした情報も持ってるぜ……その金で船を修理するつもりだ。あの海賊との戦いで傷ついちまったからな。";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "ほうほう……で、いくら欲しいんだ？";
			link.l1 = "覚えておけ、俺が欲しいのはペソじゃなくてドゥブロン金貨だぜ。";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "わかった、わかった……で、いくらドブロンが欲しいんだ？";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "おもしろいな。まあ、冗談が本当に面白かったことにしてやるよ。じゃあな！";
			link.l1 = "ふむ……";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "よし、わかった。必要な金は持っている。どこだ "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "今ごろは桟橋にいるはずだ。だから、乗客を迎えに行ってくれ。";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "申し訳ないが、そんなに多くのドゥブロン金貨は持っていないんだ。ペソでもいいか？";
				link.l1 = "俺はドゥブロン金貨が欲しいが、船長はペソでも受け取るだろう…渡せよ。";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "いや、俺が欲しいのはドブロン金貨だけだ。";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "残念ながら、そんな大金は持っていないんだ。だから、いくら俺が望んでも君の提案は受けられないんだよ。";
			link.l1 = "ふむ……";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "旦那、あんた自分が何を言ってるかわかってるのか？この金額がどれだけ法外か承知してるのか？ さっさとここから失せろ！";
			link.l1 = "ふむ……";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "うーん……旦那、すぐに医者に診てもらわないといけませんよ。かなり高い熱があるようですし……とにかく、医者が必要です。俺は忙しいんでな。じゃあな！";
			link.l1 = "ふむ……";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "ほら、全額ペソで用意したぜ、あんたの望み通りにな…さて、どこに "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "今ごろは桟橋にいるはずだ。だから、乗客を迎えに行っていいぜ。";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*500;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "残念だが、どうしても君の提案は受け入れられない。さようなら！";
			link.l1 = "ふむ……";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "何だ…ここで何が起きてるんだ！？";
			link.l1 = "「とても簡単だ」 "+NPCharSexPhrase(NPChar,"相棒","娘")+"。今やお前は俺の大事な乗客だぜ。しかも監視付きのな。抵抗なんかしたら、船倉送りにしてやるからな。";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "「つまり、俺はお前の捕虜ってことか？」";
			link.l1 = "ああ、違う。もちろん違うさ。囚人じゃなくて、大切なお客様だ。とても貴重なお客様なんだよ……";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "てめえ…自分のやったことのツケは必ず払わせてやるぜ！";
			link.l1 = "「また間違ってるぜ、」"+NPCharSexPhrase(NPChar,"、相棒","、親愛なる")+"。俺は払わねえが、払わせてもらうぜ。もう話は終わりだ、船室に行け！";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
