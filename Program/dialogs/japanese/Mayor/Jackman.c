// Якоб Джекман
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
             if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("気でも狂ったのか？屠殺屋にでもなりたかったのか？お前のせいで海賊どもはみんな怒ってるぜ、坊主、 さっさとここから消えた方が身のためだ…","どうやらお前、頭がおかしくなったみてえだな、坊主。ちょっと体を動かしたかったのか？悪いが、 ここはお前の来る場所じゃねえ。とっとと失せろ！");
				link.l1 = RandPhraseSimple("聞けよ、この状況を何とかしたいんだ…","この問題を解決するのを手伝ってくれ…");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+"、私は" + GetSexPhrase("","") + " 海での安全について話したいんだ。沿岸の兄弟団の連中が、私のつつましい身に過剰な興味を示しているんだ。 少し黙らせてもらえないか？";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("俺に言いたいことでもあるのか？ないのか？だったらさっさと失せろ！",
						"はっきり言ったはずだ、これ以上俺をイラつかせるな。","はっきり言ったはずだが、しつこく俺を苛立たせやがって！",
						"ああ、もうこの無礼にはうんざりだぜ。","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("もう行くぜ。",
						"ああ、"+npchar.name+"……",
						"悪いな、"+npchar.name+"…",
						"「いてっ……」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "ジミー・ヒギンズはどこにいる？";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "また俺だ、ジャックマン。お前が行方不明者を探してるって話を聞いたぜ…";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "「お前の囚人のことだ。」";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "やあ、Jackman。お前の任務の件だが…";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "お前の囚人のことだ。";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("気でも狂ったのか？屠殺屋ごっこがしたかったのか？海賊どもはみんなお前に怒ってるぜ、坊主、 さっさとここから消えたほうがいいぞ…");
				link.l1 = RandPhraseSimple("聞けよ、俺はこの状況を何とかしたいんだ…","この問題を解決するのを手伝ってくれ…");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+"、私は" + GetSexPhrase("","") + " 海での安全について話したいんだ。沿岸の兄弟団の連中が、私のつつましい身に過剰な興味を示しているんだ。 少し黙らせてもらえないか？";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("俺に言いたいことでもあるのか？ないのか？だったらさっさと失せろ！",
						"はっきり言ったはずだ、これ以上俺をイラつかせるな。","はっきり言ったはずだが、しつこく俺を苛立たせやがって！",
						"ああ、もうこの無礼にはうんざりだぜ。","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("もう行くぜ。",
						"ああ、"+npchar.name+"……",
						"悪いな、"+npchar.name+"…",
						"「いてっ……」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "お前の囚人のことだ。";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "本当かよ！誰かあの怠け者を必要としてるのか？あいつはここ数日、自分の小屋で一人でラムを飲んでやがるんだぜ。 俺はあいつに会いに行くのは勧めねえな。あいつは素面でもろくな奴じゃねえからな……";
			link.l1 = "大丈夫だ、俺も聖人じゃねえ。あいつの小屋はどこだ？";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "酒場の真ん前だ。飲みに行くのに素早く動ける、いい場所を選びやがったな。";
			link.l1 = "ありがとよ！";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "それを誰から聞いたんだ？あの酔っ払いヒギンズか？ グラディス・チャンドラーか首吊りヘンリーについて何か掴んだのか？";
			link.l1 = "別に大したことじゃねえが、あの死刑執行人についてちょっと詳しく知りてえんだ。";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "知ってることはあまりねえな。今じゃ覚えてる奴も少ねえが、 二十年前はヘンリーって野郎はブリッジタウンからトルトゥーガまでの娼婦どもに大人気だったんだぜ。間違いねえ！ 「ネプチューン号」の甲板長で、あのブッチャー船長の下で働いてたんだ！今も生きてりゃ、相当な年寄りだろうよ、 もちろんまだ生きてりゃの話だがな。\n望みは薄いが、不可能ってことはねえ。奴について何か情報を持ってきたら二万ペソ払うぜ。 生きたままここに連れてきたら倍出してやる。";
			link.l1 = "「グラディスとその娘にいくら払うつもりだ？」";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "ああ、あの子は彼女の娘じゃねえ。あの娘を生きたまま連れてきたら、ドゥブロン金貨を山ほど払ってやるぜ。 グラディスには興味ねえ。質問あるか？";
			link.l1 = "この騒ぎの理由を知りたいもんだが、聞く気はねえ。俺の人生が短くなりそうだからな。";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "もしかして…その秘密はお前には関係ねえことだ。知ってることが少なけりゃ少ねえほど、長生きできるぜ。 もう二度とそんな質問をするんじゃねえ、だんだんお前が怪しく思えてきたからな。気が変わらねえうちに消え失せろ。";
			link.l1 = "じゃあな、バロン！";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "To Antigua now. The corvette must be boarded.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "ははっ！また会ったな、船長 "+GetFullName(pchar)+"。認めてやるぜ、マルーンタウンで間抜けを装ってたくせに、なかなか手強い相手じゃねえか。 お前のことを少し調べさせてもらったが、オランダ西インド会社との裏取引もバレてるぞ……これでお前がどんな奴か、よく分かったぜ。";
			link.l1 = "俺もお前のような奴はよく知ってるぜ、Jacob。だから、お互いにごまかすのはやめようじゃねえか。";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "「それにしても、『マーリン』で俺をうまく騙してくれたな！俺の哀れな弟は死んじまったんだろうな…」";
			link.l1 = "あいつの仇討ちがしたいってわけか？だがな、てめえにもたっぷり借りがあるぜ。追い詰められたネイサン、奴の女房、 奴のフリゲート、汚名を着せられたシャーク、ブレイズ・シャープ……";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "ブレイズ？俺はあいつを殺しちゃいねえ。";
			link.l1 = "たとえそれが本当でも、俺のリストの残りだけで十分だ。お前の名前にはもううんざりだぜ。もう言葉はいらねえ、 ジャックマン！剣で語ろうじゃねえか！";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "なんて激しい馬鹿野郎だ……くたばれ！今度は覚悟しろよ！ジェイコブ・ジャックマンは一度も負けたことがねえんだ！カルパチョ、 ちょうどいいところに来たな！こっちへ来い！";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "ハハッ。ここに囚人が一人しかいないと思ってるのか？名前を言え。";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"……あいつはここにいるのか？";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "ああ、そうだ。あいつは一週間前にここへ来たバルバドスのプランテーション主、ビショップ大佐に売ったんだ。";
				link.l1 = "くそっ……";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "ああ、やっと来たか。バルバドスのあのプランテーションの旦那にあいつを売ろうかと思ってたんだがな、 あいつは一週間か二週間でここに来る予定だ……身代金は持ってきたか？";
				link.l1 = "見てくれ、ちょっとした問題があるんだ……実は、そんなに金を持ってねえ。でも、働く気はあるぜ。";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "奴をまだ売ってねえのはいいことだ。ほらよ、１５万ペソだ。奴はどこにいる？"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "お前は遅すぎたな……それに、なんであいつのことを気にするんだ？俺が交渉してたのはあいつの身内だけだぜ。";
			link.l1 = "奴らが俺にここへ来いと頼んできたんだ。";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "ふん、遅かったな。俺にはどうしようもねえ。";
			link.l1 = "聞けよ、いくらであいつを売ったんだ？秘密じゃねえなら教えろよ。"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "ええ、違うぜ。でも教えてやらねえよ……言ったら笑うだろうからな。ハハハハ！じゃあな。";
			link.l1 = "じゃあな…";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "ほう、ほう……ちょっとした用事があってな……どこから話せばいいか分からねえ。筋を越えた海賊を沈める必要があるんだ。";
				link.l1 = "ジャングルでそいつを殺すだけじゃダメなのか？";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "「さて、」 "+pchar.name+"「なあ、そう簡単にはいかねえんだよ。金を持って戻ってこい、そしたらその腑抜けを返してやるぜ、ハハッ。」";
				link.l1 = "ああ、じゃあな。";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "商売ってのはそういうもんじゃねえんだよ……あいつを殺す必要はねえ、ただ俺の取り分に手を出す奴らに思い知らせてやりたいだけだ。だが、 もしあいつがサメの餌になっても、俺は別に困らねえさ。";
			link.l1 = "「なんで自分の手下を奴の後を追わせねえんだ？」";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "ふむ……まあ、 "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" 何人かの海賊に、戦利品の取り分が俺たちの隠し場所―― のすぐ近く――に保管されていると信じ込ませやがった "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+"。奴らの二隻の船『"+pchar.GenQuest.CaptainComission.ShipName1+"「と」"+pchar.GenQuest.CaptainComission.ShipName2+"「'はついさっき錨を上げて、出航した」 "+sLoc+"。これで俺が部下どもにこの仕事を任せられねえ理由が分かっただろう？";
			link.l1 = "ああ、分かってる。俺にどれくらい時間があるんだ？";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12日から15日、いや、それ以上は待てねえな。奴らが隠し場所に着いたら、積み荷ごと沈める意味がねえだろう。そうなったら、 いっそここに持って来させた方がマシだな…";
			link.l1 = "よし、乗ったぜ。奴らを捕まえてみせる。";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "心配すんな。俺の手下があいつをお前の船まで連れていくぜ。\nそれに、なんであいつのことなんか気にするんだ？";
			link.l1 = "俺は知らねえ。親族に頼まれて、あいつを届けに来ただけだ。";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "ああ、それでいいんだ。お前の部下にあんな安値を提示して、ちょっと悪い気がしたくらいだぜ。ハハハハ。じゃあな。";
			link.l1 = "じゃあな。";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "それで、 "+GetFullName(pchar)+"「おい、俺の仲間を沈めたのか？へっへっへ……」";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "いや、逃げられちまった。帰り道でも会わなかったぜ。";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "ああ、やったぜ。奴らはサメの餌にしてやった。";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "くそっ！会ったかどうかなんて、今さら関係ねえだろ！で、次は何を提案するつもりだ？";
			link.l1 = "「もっと楽な仕事があるんじゃねえのか？」";
			link.l1.go = "CapComission4_1";
			link.l2 = "聞けよ、Jackman、囚人の値段を下げろよ……";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "いやだ。";
			link.l1 = "じゃあな……";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "値下げしろだと？お前の無能のせいで俺の隠し財産がパーになったんだぜ！だからこそ値上げしてやる！欲しけりゃ20万ペソ払え、嫌ならとっとと失せろ。";
			link.l1 = "高すぎるな……じゃあな……";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "くそっ、金貨を持っていけ。";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "よし、こいつの腑抜けはくれてやる…";
			link.l1 = "さらばだ。";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "ホッホー！よくやったな！その腑抜けを連れて、とっとと失せな。";
			link.l1 = "ありがとう。じゃあな。";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "金は持ってきたのか、チャールズ？俺はあの男をプランテーションに売るって冗談で言ったんじゃねえぞ。";			
			link.l1 = "「聞け、」 "+NPChar.name+"…問題があるんだ…そんなに金は持ってねえ。でも、働く気はあるぜ。";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "売らずにいてくれて助かったぜ。ほらよ、１５万ペソだ。そいつはどこにいる？"link.l2.go ="CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("強盗だと！？そんなの許せねえ！覚悟しろ、 "+GetSexPhrase("坊主","女")+"...","おい、そこで何してやがる？！俺を盗れると思ったのか？もう終わりだぜ…","待て、なんだと！？手を離せ！やっぱりお前は泥棒か！ここまでだ、クソ野郎…");
			link.l1 = LinkRandPhrase("くそっ！","カランバ！！","くそったれ！！");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("ここから失せろ！","俺の家から出ていけ！");
			link.l1 = "おっと…";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "くだらねえ話で俺にかまうな。次は痛い目見ることになるぜ……";
        			link.l1 = "分かったぜ。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "終わりだ、口を閉じろ。""もうお前と話したくねえから、これ以上俺にちょっかい出すんじゃねえぞ。";
			link.l1 = RandPhraseSimple("お前の好きにしろよ……","……いいだろう……");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "もっと敬意を示して、無礼な態度をやめてくれるといいんだがな。\nさもないと、俺がお前を殺さなきゃならなくなるぜ。\nそれは実に不愉快なことだろうよ。";
        			link.l1 = "安心しろ、Jackman、必ずそうするぜ。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "問題を解決しろだと？自分が何をしでかしたかわかってんのか？まあいい、とにかく百万ペソ持ってこい。 そうすりゃ野郎どもにお前の“武勇伝”を忘れさせてやるぜ。気に入らねえなら地獄へ行きな。";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "よし、払う準備はできてるぜ。";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "了解だ。俺は行くぜ。";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "よし！これでまた清くなったと思え。ただし、もう二度とそんな汚ねえ真似はするんじゃねえぞ。";
			link.l1 = "俺はやめとくぜ。俺には高すぎるんだ。じゃあな……";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("今日はすでにこの件について話しただろう。",
				                                      "はっきり言わなかったか？",
				                                      "お前のしつこさにはうんざりだ。",
				                                      "もう我慢の限界だ。さっさと失せろ！",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("また今度にするよ...",
				                                   "もちろんだよ、"+npchar.name+"...",
				                                   "悪かったよ、"+npchar.name+"...",
				                                   "いてっ...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "ははっ！兄弟団の連中に目をつけられたんだな、" + GetSexPhrase("相棒", "お嬢さん") + "？まあ、しばらくの間なら大人しくさせておけるさ。ただし、それなりの金は必要だ。" + FindRussianDublonString(iBarbazonTotalTemp) + "払えば話はつけてやる。";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "もちろん、これが君の金だ。";
					else link.l0 = "仕方ないな。これが君の金だ。";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "また後で来るよ...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "お前、正気か" + GetSexPhrase("", "い") + "？うちの連中はお前を疫病のように避けてるんだ。消え失せろ、時間の無駄だ。";
				else
					dialog.text = "何言ってんだ、" + GetSexPhrase("相棒", "お嬢さん") + "？お前は厄介者だって犬でもわかる。誰もお前とは関わりたくないんだよ。";
				link.l1 = "わかったよ...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}
