// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "何の用だ？ああ、お前はレガッタの参加者か！俺の言う通りだろう？";
				link.l1 = "その通りです、旦那。規則に従ってここで登録する必要があります。";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしたじゃねえか "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の質問だな……","港のことについて何も話すことがないなら、くだらない質問で俺を煩わせるな。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","確かに、これでもう三度目だな……","悪いが、今は港のことには興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "俺はブルーウェルドへパプリカを売りに航海してるんだ。旦那、ブルーウェルド行きの乗客はいないかい？ せめてポートロイヤル行きでもいいんだが。乗客から金をもらえたら助かるんだ、船員の給料の足しになるからな。 もう給料は最低限まで下げてるのに、この怠け者どもはまだ金を要求しやがる……";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "フィリップスバーグで「アドミラブル」 という名のガレオン船がガイウス・マルシェ船長の指揮のもと積荷を載せていたのです。\nその船長はここにパプリカを運んでくるはずでした。\nこの船長を探すのを手伝ってもらえませんか？";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "変わった名前のシーベックについて聞きたかったんだ。";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "キャプテン・ジャック……あるいはジャクソンの所有するジーベックがよくあなたの港に来ると聞いたんだが、 彼がどこにいるか教えてもらえないか？";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "残念ながら、ブルーウェルドやポートロイヤル行きの乗客はいません。\n明日か明後日にまた来てください。";
			link.l1 = "残念だな。では、さようなら。";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-9");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "ふむ……お前はレガッタの規則を破ったから、俺はお前を失格にしなきゃならねえ。すまねえが、次の航海には参加できねえぞ。 すでにポートロイヤルへの通達も用意してある。";
				link.l1 = "ええ…残念だな！だが、ここでは俺にできることは何もねえ。お前が用心深すぎたんだ。じゃあな！";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "船長、ご存じかもしれませんが、この街は包囲されています。スペイン軍がいつ攻撃してくるかわからず、我々 は兵を動員しています。しかし、レガッタはまだ続行中です\nさあ、登録しましょう、船長 "+GetFullName(pchar)+"、船は－ "+pchar.Ship.Name+"…レガッタの所要時間（時間）は "+sti(pchar.questTemp.Regata.FourthTransitionTime)+"。完了しました、結果は記録されましたので、先へお進みください。";
				link.l1 = "俺の階級を教えてくれ。";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "ここにいるのにお前の船が見当たらねえ。どこにあるんだ？";
			link.l1 = "申し訳ありません、旦那。すぐに私の船を港に移します。";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "ああ、そうだな……すまない、その件は忙しすぎて手が回らなかった。君が最初だ。";
			link.l1 = "なるほど。情報をありがとう。";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "ああ、そうか……すまないが、俺はそれどころじゃないんだ。お前が最後だ。";
				link.l1 = "なるほど。情報をありがとう。";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
				}
				else
				{
					if (n==2)
					{
						dialog.text = "ああ、そうか……すまないが、私はそれに手が回らないほど忙しいんだ。君は二番目だ。君の前には一人だけ船長がいる。その名は "+sName+" 船の上で "+sShip+".";
						link.l1 = "なるほど。情報をありがとう。";
						link.l1.go = "exit";
						AddQuestRecord("Regata", "23");
					}
					else
					{
						dialog.text = "ああ、そうか……すまないが、今は忙しすぎて無理だ。君の階級は "+n+" 。最も近くの敵は "+sName+" 船の上で "+sShip+".";
						link.l1 = "なるほど。情報をありがとう。";
						link.l1.go = "exit";
						if (n==3) AddQuestRecord("Regata", "24");
						if (n==4) AddQuestRecord("Regata", "25");
						if (n==5) AddQuestRecord("Regata", "26");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Repair", 30);//починка
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Bridgetown = "true";//отметка Бриджтауна
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "Curacao";
			pchar.questTemp.Regata.AttackNation = HOLLAND;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//третья засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Барбадоса
			pchar.quest.Regata_Finish.win_condition.l1 = "location";
			pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Finish.function = "RegataFinishSea";
			pchar.quest.Regata_Finish1.win_condition.l1 = "location";
			pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
			pchar.quest.Regata_Finish1.function = "RegataFinishTown";//финиш регаты
			//ситуации
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_Siege.function = "RegataSiegeOfficer";//на квест по вывозу жителей
		break;
		//регата
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "ああ、このガレオン船はここに来て、積み荷を下ろした後に我々の港を出て行った。行き先についての情報は……うーん……何もない。申し訳ないが、私にできることは何もない。";
			link.l1 = "なるほど。残念だな……引き続き探してみるよ。";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "旦那、船の正確な名前が必要です。うちの港にはジャックやジャクソンが山ほど通っていますからな。\nで、船の名前は何です？";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
			link.l2 = "困ったことに、あいつの古い船の名前がわからねえんだ。不思議なことに、なんでも鳥の女で、生まれは…";
			link.l2.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "旦那、酒場で話やなぞなぞでもしてきなさい。ここはちゃんとした役所なんだ。あのシーベックの名前を言うか、 俺の仕事の邪魔をするのはやめてくれ。";
			link.l1 = "わかった、調べてみるぜ。";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "それで？船の名前は分かったのか？聞こうじゃねえか。";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
		break;
		
		case "caleuche_name":
			if (GetStrSmallRegister(dialogEditStrings[2]) == "harpy")
			{
				dialog.text = "「ハーピー」か？もちろん、そのシーベックは知っている。その船長はレジナルド・ジャクソンだ。ただし、 彼はブリッジタウンに来てまだ日が浅いぞ。今はオランダ西インド会社のために働いていると聞いた。だから、 ウィレムスタッドで探すといい。";
				link.l1 = "本当にありがとうございます！あなたのおかげで大いに助かりました。";
				link.l1.go = "caleuche_3";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "申し訳ありませんが、それには心当たりがありません。あなたの船長が本当にここブリッジタウンに来たことがあるのか、 ご確認いただけますか？";
				link.l1 = "確かだ。よし、何か考えてみるか……";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "18");
			pchar.questTemp.Caleuche.Garpiya = "gwik"; 
			npchar.quest.garpiya = "true";
			AddLandQuestMarkToPhantom("GVIK", "HWIC_headclerk");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
