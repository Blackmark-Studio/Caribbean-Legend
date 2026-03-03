void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "俺たちに話すことは何もねえ。";
			link.l1 = "……わかったよ……";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、俺はこの町の市民だ。剣を下ろしてくれ。","聞いてくれ、俺はこの町の市民だ。剣を下ろしてくれ。");
				link.l1 = LinkRandPhrase("「いいだろう。」","ああ、いいぜ。","……わかった……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"「気をつけろ」 "+GetSexPhrase("相棒","娘")+"…武器を持ってうろつかれると、落ち着かなくなるんだよ…","俺はそういうのが気に入らねえんだよ、いるときは "+GetSexPhrase("男たち","人々")+" 俺の前を武器を抜いたまま歩いているんだ。怖くてたまらねえ…");
				link.l1 = RandPhraseSimple("わかった。","わかった。");
			}
			
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "さあ、相棒、ポケットの中身を見せてみろ。";
			link.l1 = "何だって！？";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "俺の言ったこと、聞こえただろう。さっさとしろ、余計なことは言うな。俺は話すのが好きじゃねえんだ…";
			link.l1 = "くそっ！それで "+pchar.questTemp.different.FackWaitress.Name+" 「一緒に働くのか？」";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "「ああ、そうだとも、そうだとも……金を出せ、さもねえと腹を裂いてやるぞ！」";
			link.l1 = "いやだ！お前をぶった斬ってやる！";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "俺の金貨を持っていけ、この野郎！だが、ただじゃ済まねえぞ……";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "ああ、それは否定できねえな。じゃあな、相棒。あと覚えとけよ、お前は給仕の娘たちが惚れるほどイケてねえからな。 次はもっと賢くやれよ！";
			link.l1 = "……もう行けよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "おっしゃる通りだ……";
			link.l1 = "そうだな……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "あたしが来たよ！あたしが欲しいのかい、イケメンさん？";
			link.l1 = "くそっ、急に事態が悪化したな……";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "時間を無駄にするな！";
			link.l1 = "へっ、まったく同感だぜ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "ごきげんよう。私の名前は "+GetFullName(npchar)+"。俺は船長だ "+GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName+"Acc"))+" 「」"+npchar.Ship.name+"「。」"; 
			link.l1 = "素晴らしい！ついにお前を見つけたぞ。";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "俺を見つけたのか！？";
			link.l1 = "はい。さて、あなたが港の事務所に置き忘れた航海日誌を持ってきました、 "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "くそっ！今になってどこで失くしたかわかったぜ。\nこの損失のせいで、俺の船じゃ反乱寸前だったんだ…";
			link.l1 = "すべて丸く収まったってわけだな。航海日誌を受け取れ、そして俺の金の話をしようじゃねえか。";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "いいタイミングだ、まだ新しい仕事は始めてないから、できるだけ払ってやるぜ。 "+FindRussianMoneyString(sti(npchar.quest.money))+" そして、私の私物の宝飾品をいくつか受け取ってください。";
				link.l1 = "いいぞ。持っていけ。";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "ふむ、実はもう新しい航海日誌を書き始めているんだ。だが、古い日誌にもまだ価値がある。だからお前に金を払おう。 "+FindRussianMoneyString(sti(npchar.quest.money))+" そして、私の個人的な宝飾品もいくつか受け取ってください。";
					link.l1 = "取引成立だな。航海日誌を持っていけ。";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "新しい航海日誌はもう書き始めた。古い日誌のメモもすべて移したんだ。もう必要ないから、お前に払う金はないぜ。";
					link.l1 = "よかったな。じゃあ、この追いかけっこは全部無駄だったってわけだ。";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "ありがとうございます。では、これで失礼します。 "+GetSexPhrase("相棒","娘")+".";
			link.l1 = "「君もな……」";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "はは、次はタイミングをもっと考えろよ。";
			link.l1 = "確かにその通りだ。";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "俺の船の甲板へようこそ。正直言って、肝を冷やしたぜ――てっきり片目の馬狩りが俺を追ってきたのかと思ったんだ……";
				link.l1 = "いや、船長、今日は機嫌がいいんだ。お前を助けに来たぜ。";
			}
			else
			{
				dialog.text = "俺の船へようこそ！";
				link.l1 = "おうい、船長！探してたんだぜ。";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "なぜだ？";
			link.l1 = "あなたは港長の家に航海日誌を置き忘れた "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "くそっ、じゃあそこが現場だったのか！この損失のせいで、もうとんでもねえ厄介ごとに巻き込まれてるんだぜ。";
				link.l1 = "報酬はどうだ？";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "くそっ、やっとどこで失くしたか分かったぜ！ありがとうよ、だが探すのに時間かかりすぎたな。 もう新しい航海日誌を書き始めちまったんだ。それでも、古い記録を新しい日誌に写さなきゃならねえな……";
					link.l1 = "「で、いくらだ？」";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "新しい航海日誌はもう書き始めた。\n古い日誌からも全ての記録を書き写したから、もう必要ないんだ。";
					link.l1 = "じゃあ、古い日誌はいらねえのか？本当に？";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "俺が払ってやるぜ "+FindRussianMoneyString(sti(npchar.quest.money))+" それから私の宝石もいくつか。これが私にできる精一杯です。";
			link.l1 = "わかったよ。日誌を持っていけ。";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "また礼を言うぜ。じゃあな、友よ。";
			link.l1 = "その調子だ。";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "それは間違いねえな。誰かを追いかけてるなら、もっと速く動かねえといけねえぜ。";
			link.l1 = "最初から航海日誌をなくすんじゃねえよ。まったく。";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(100/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "俺たち全員、もう落ち着いたと思ってたぜ。";
			link.l1 = "ああ、その通りだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "挨拶だ。何の用だ？";
			link.l1 = "何でもない、ちょっと噂を聞きたかっただけだ。何か売り物はあるか？";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "お前に売る物もなけりゃ、知らせもねえ。\nそれに、ここにお前がいるのは歓迎されてねえんだ。\nわかったか？";
			link.l1 = "お前は……そうか、じゃあな、相棒。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "言っただろ、ここにいる資格はねえんだよ！";
			link.l1 = "なるほど……";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "なぜ俺を襲ったんだ！？";
			link.l1 = "俺は船を持ち主に返さなきゃならねえ。";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "どんな持ち主にだって？俺が持ち主だ！";
			link.l1 = "いいや、お前じゃねえ。誰の船かは知らねえが、この船は盗まれたもんだ。だから俺が返さなきゃならねえんだ。";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "くそっ！だが、俺はまだ終わっちゃいねえ。せめてお前を殺してやる……";
			link.l1 = "やれることは挑戦するしかないんだ。";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------поисковый генератор горожан--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "SCQ_exit":
			DialogExit();
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_exit_clear":
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		
//--------------------------------------------поисковые квесты дворян---------------------------------------------
		
		case "SCQ_Nobleman":
			dialog.text = "「ごきげんよう」 "+GetAddress_Form(NPChar)+"。なるほど、自分の船の船長なんだな？私の名は "+GetFullName(npchar)+" それで、あんたに取引を持ちかけたいんだ。";
			link.l1 = RandPhraseSimple("申し訳ないが、俺は行かなきゃならねえんだ。","申し訳ないが、君と話している時間はないんだ。");
			link.l1.go = "SCQ_exit";
			link.l2 = "聞いてるぜ。";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "「じゃあ、聞け。」 "+SelectNB_battleText()+"\n俺にはあいつを探す時間も機会もねえんだ。ここに顔を出すこともないしな。もう分かっただろう、 俺がこれから何を頼もうとしてるか？";
						link.l1 = LinkRandPhrase("誰かを探し出して、あんたのところに連れて来いってことか？","「もしかして、その野郎を見つけてお前のところに連れて来いってことか？」","この男を探してここに連れて来いってことか？");
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "「じゃあ、聞け。」"+SelectNB_battleText()+"\n俺にはあいつを探す時間も機会もねえんだ。あいつはここに来ることもないしな。今ならわかるだろう、 俺がこれから何を提案しようとしてるか？";
						link.l1 = LinkRandPhrase("俺に誰かを探し出して、あんたのところに連れて来いってことか？","もしかして、あの野郎を見つけてお前のところに連れて来いってことか？","「この男を探してここに連れて来いってことか？」");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = "では、聞いてくれ。実は、 "+npchar.quest.text+" 海軍で船長として務めているんだ。俺がここにいることさえ知らねえ！\n会いたいけど、探す時間も機会もねえんだよ……";
					link.l1 = "俺にその船長を探して、お前のことを伝えてほしいってことか？";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //вариант А
			dialog.text = "そうじゃない。奴を見つけろ、だがここに連れてくる必要はない。殺せばそれで十分だ。あの汚い船ごと沈めてもいいし、 撃ち殺しても、刃で刺しても構わねえ――やり方はどうでもいい、このクズがこの世を汚し続けるのを止めてくれればそれでいい。報酬はたっぷり出すぜ。";
			link.l1 = "はっ！簡単なことだ。そいつの名前と船の名前を教えてくれ。";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			dialog.text = ""+npchar.quest.SeekCap.capName+" の "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 「名付けられた」 "+npchar.quest.SeekCap.shipName+"。彼はよくその港に来る常連だ "+XI_ConvertString("Colony"+npchar.quest.Qcity)+"。支払うぜ "+FindRussianMoneyString(sti(npchar.quest.money))+" 金のドブロンで。";
			link.l1 = "それだけ聞けば十分だ。海ではしっかり目を光らせておくぜ。\nそしてお前の仲間を見つけたら、俺は……（声をひそめて）……生きたままじゃ済ませねえ。";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "そんな仕事には足りねえな。";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "取引が成立して嬉しいぜ。お前の帰りを待ってるからな。";
			link.l1 = "どこでお前に会えばいいんだ？今のうちにはっきりさせておこうぜ、探し回って時間を無駄にしたくねえからな。";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "毎朝、地元の教会で礼拝に出席しているんだ。\n毎日8時から9時まで、そこで会えるぜ。";
			link.l1 = "取引成立だな！すぐに結果を期待してくれ。";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_prisoner": //вариант В
			dialog.text = "その通りだ。奴を見つけて、俺のところに連れて来い。生きたままだ。俺が自分でケリをつけたいんだ。 たっぷり報酬をやるぜ。";
			link.l1 = "まあ、探してみてもいいが、詳しい情報が必要だぜ。";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "野郎の名前は "+npchar.quest.SeekCap.name+"。彼は勤務している "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 「名付けられた」 "+npchar.quest.SeekCap.shipName+"、の指揮下にある "+npchar.quest.SeekCap.capName+"。よくその船は港で見かける "+XI_ConvertString("Colony"+npchar.quest.Qcity)+"。この仕事の報酬は支払う "+FindRussianMoneyString(sti(npchar.quest.money))+" 金のドゥブロン金貨で。";
			link.l1 = "俺にはそれで十分だ。外洋では警戒を怠らねえぜ。";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "そんな仕事には足りねえな。";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "取引が成立して嬉しいよ。帰りを待ってるぜ。";
			link.l1 = "どこでお前に会えばいいんだ？今のうちにはっきりさせておこうぜ、無駄に探し回る時間なんてごめんだからな。";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "毎朝、地元の教会で礼拝に出席しているんだ。\n毎日8時から9時まで、そこで会えるぜ。";
			link.l1 = "取引成立だな！すぐに結果を期待してくれ。";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_peace": //вариант С
			dialog.text = "その通りだ！あいつを見つけて、この町に俺が住んでいると伝えてくれ。\n報酬はちゃんと払うぜ。";
			link.l1 = "そうだな……やってみるぜ。詳しく話してくれ。";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = "彼の名前は "+npchar.quest.SeekCap.capName+"。そして彼は仕えている "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" "+npchar.quest.SeekCap.shipName+"』。彼はよく訪れる "+XI_ConvertString("Colony"+npchar.quest.Qcity)+"。この仕事の報酬は払う "+FindRussianMoneyString(sti(npchar.quest.money))+" 金のドゥブロンで。";
			link.l1 = "取引成立だ！まあ、その友人もすぐに見つけられるだろうぜ。";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "俺にはこれじゃ足りねえ。";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "取引が成立して嬉しいぜ。お前の帰りを待ってるからな。";
			link.l1 = "どこでお前に会えばいいんだ？今はっきりさせておこう、探し回って時間を無駄にしたくねえからな。";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "私はいつも地元の教会で夕方の礼拝に出席しています。\n毎日午後6時から8時まで、そこで私に会えます。";
			link.l1 = "取引成立だな！すぐに結果を期待してくれ。";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		//--> разговор на суше, вариант А
		case "NM_battleCap":
			dialog.text = "それで？何の用だ、旦那？";
			link.l1 = "お前が船長か "+GetFullName(npchar)+"?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "ああ、そうだ。どういう用件だ？";
			link.l1 = "「お前に非常に強い関心を持っている男が一人いる、その名は」 "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"。覚えてるか？";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "お前の船倉にはマホガニーがたくさん積んであるって聞いたぜ。俺が買いたいんだ。俺に売ってくれるか？";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "この名前は初めて聞いたぜ。お前、勘違いしてるんじゃねえか、船長。もう終わりか？";
			link.l1 = "ふむ。わかった、すまねえ…";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "「ほう、本当か？だが、あいつはお前のことをよく覚えているぜ。お前があいつに借りがあるって話してたぞ…」";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "「借金？何の話だ？」";
			link.l1 = "「名誉の借りだ！」";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "勘違いしてるぜ。俺は木材なんて取引してねえ。もう話は終わりか？";
			link.l1 = "ふむ。まあ、失礼する……";
			link.l1.go = "NM_battleCap_exit";
		break;
		
		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;
		
		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант В
		case "NM_prisonerCap":
			dialog.text = "それで？何の用だ、旦那？";
			link.l1 = "お前が船長か "+GetFullName(npchar)+"?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "ああ、俺だ。どういう用件だ？";
			link.l1 = "「という男は "+sld.quest.SeekCap.name+" お前の指揮下で働くのか？";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "ああ、そうだ。奴は俺の部下の一人だ。さて、なぜそんなことを聞くんだ？";
			link.l1 = "もちろん、お話しします。私はこの男を"+GetSexPhrase("当局","当局")+"の命令で捜索しています "+XI_ConvertString("Colony"+sld.city+"Gen")+"、そして俺にはあいつを逮捕して引き渡す権限があるんだ "+XI_ConvertString("Colony"+sld.city)+"。どうかこの件についてご協力いただき、穏便に解決できるようお願い申し上げます。";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "本当か？そんな奴が俺の船員として働いてるのか？マジなのか？";
				link.l1 = "「そんなことは気にするな」 "+GetAddress_FormToNPC(NPChar)+"。俺がお前の船にロングボートを送って、そいつを俺たちで引き取るぜ。";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "そうかい。だがな、旦那、あいつの過去なんざ俺にはどうでもいいんだ。関係ねえよ。で、お前は誰だ？役人か？ 本気で言ってんのか？はっ！俺の部下はお前にも他の誰にも渡さねえ。この話はもう終わりだ。さっさと行きな！";
				link.l1 = "間違った選択だ……最悪だぜ！";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "やるべきことをやれ。";
			link.l1 = "了解だ。";
			link.l1.go = "NM_prisonerCap_good_1";
		break;
		
		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_"+(rand(9)+21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(sld.quest.SeekCap.name+" is under arrest");
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
		break;
		
		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "NM_prisonerDeck_exit":
			dialog.text = "終わりかい、船長？";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = "ごきげんよう。何の用だ、船長？";
			link.l1 = "お前が船長だ "+GetFullName(npchar)+"、そうだろう？";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = "お前の言う通りだ。俺に何か用か？";
			link.l1 = "あるさ。名前は "+GetFullName(sld)+" お前を探している。できるだけ早く訪ねてほしいそうだ。彼は\nに住んでいる "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+".";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "ははっ！あいつも新世界に渡ったのか？それなら、ぜひ会いに行かねえとな……情報をありがとう、旦那！";
			link.l1 = "どういたしまして。あなたの友人が私の報酬を払ってくれることになっている。幸運を祈る、 "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "NM_peaceCap_3";
		break;
		
		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		
		case "NM_peaceCap_exit":
			dialog.text = "「楽しかったぜ。」 "+GetAddress_Form(NPChar)+"!";
			link.l1 = "こちらこそ光栄でした、船長。";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = "「おい、」 "+GetAddress_Form(NPChar)+"。何の用だ？";
			link.l1 = "お前の積荷にレッドウッドがたくさんあるって聞いたんだが、それを買いたいんだ。売ってくれるか？";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "勘違いしてるぜ。俺は木材なんて取引してねえし、あんたの訪問はどうにも怪しいな。 さっさと俺の船から出ていったほうがいいぜ！";
			link.l1 = "わかった、ちょっと聞いただけだ。じゃあな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "揉め事が欲しいのか、旦那？もう一度言わせるのか？";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "「なぜ俺の船を襲ったんだ、この野郎？」";
			link.l1 = "私はここに、からあなたに心からのご挨拶をお伝えするために来ました "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" 、"+man.name+"という男から "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"。今の状況を理解してくれたと思う。";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "ありえねえ！もう俺には失うものなんて何もねえってことか……";
			link.l1 = "お前の人生はどうだ？";
			link.l1.go = "NM_battleBoard_2";
		break;
		
		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		 //--> абордаж, вариант В
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];//квестодатель
			dialog.text = "「なぜ俺の船を襲ったんだ、この野郎？」";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "何か考えはあるか？俺はお前に大人しく士官を引き渡せって言ったんだ。だが今は、その士官も、お前も、 お前のオンボロ船も全部いただくぜ！";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "お前の指揮下にいる悪党が一人いる。その名は "+sld.quest.SeekCap.name+"。権力者たちの "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" 奴らは本当にあいつに会いたがっている。あいつは逮捕されて俺の船倉にぶち込まれるぜ。";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "それで俺の船で虐殺をやらかしたってわけか？この野郎！まだ力は残ってる……お前を殺してやる！";
			link.l1 = "もっと強い男たちも挑戦したことがあるんだ……";
			link.l1.go = "NM_prisonerBoard_2";
		break;
		
		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завершения квеста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+21); //модель для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;
		
		//--> результаты квестов дворян
		case "SCQ_NM_result":
			dialog.text = "どうだい、船長？俺の件は何か進展があったか？";
			link.l1 = "まだだ。だが、今取りかかってるぜ。";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = "どうだい、船長？俺の件は何か進展があったか？";
					link.l1 = "ああ、そうだ。お前もきっと気に入るぜ。"+npchar.quest.SeekCap.capName+" は死んでいて、その "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" 海の底にある。";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = "どうだい、船長？俺の件は何か進展があったか？";
					link.l1 = "ああ、そうだ。お前もきっと気に入るぜ。"+npchar.quest.SeekCap.Name+" 俺の船の船室で拘束されて座っているんだ。";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = "ああ、ここにいたか。会えて嬉しいぞ。任務が成功したと聞いている！";
					link.l1 = "友人があなたを訪ねてきたのか？";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "素晴らしい！お前なら頼りになると思ってたぜ。ほら、金貨を受け取れ。お前の働きだ。";
			link.l1 = "ありがとう。新たな敵が現れたらまた俺に声をかけてくれ。";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "SCQ_NM_result_B1":
			dialog.text = "素晴らしい！すぐに部下に命じて、あいつをお前の船から連れ出させる。もう逃げられねえぞ！ほら、金だ。 お前は十分に働いたからな。";
			link.l1 = "ありがとう。こんな仕事ならいつでも俺に声をかけてくれ。";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		break;
		
		case "SCQ_NM_result_C1":
			dialog.text = "ああ、彼はここに来て君のことを話していたよ。\nほら、金貨を受け取れ。君は十分に働いたからな。";
			link.l1 = "感謝する。さようなら、旦那！";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
//<-- поисковые квесты дворян

		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("ごきげんよう、船長。あなたに助けをお願いしたいのです。","船長！助けてくれませんか？お願いします。","船長、助けをお願いしたいんだ！");
			link.l1 = RandPhraseSimple("俺はいま忙しいんだ。","急いでいるんだ。");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("どうしたんだ？","何か悩みがあるのか？もしかしたら俺が力になれるかもしれねえぜ。");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "一年前、ある船長が俺を連れて行くと約束してくれた場所があるんだ "+XI_ConvertString("Colony"+SelectNotEnemyColony(NPChar)+"Acc")+"。だが、あいつの船に乗っていた時、俺は船倉に放り込まれ、その後奴隷として売られたんだ。命からがら生き延びた。 何度も死にかけたさ……とにかく、あの「友人」に俺がまだ生きていることを思い出させてやりたいんだ。"; // belamour gen
					link.l1 = "どういう意味だ？はっきりと何が望みか言え。";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "俺の妻がさらわれたんだ。船長で、いわゆる海賊ってやつが、妻に言い寄ってきてた。あいつのつきまといのせいで、 妻は何日も家にこもるしかなかった。町の役人に助けを求めたが、うまくいかなかった。そして今は……";
					link.l1 = "「さて、どうする？」";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "あのな、俺は同郷の仲間を探してるんだ。三年前、俺たちはヨーロッパから一緒にここへ来て、 より良い暮らしを求めたんだよ。だが途中で離れ離れになっちまった。\nでも最近、あいつが今じゃ交易船の船長になってるって聞いたんだ！自分で探してみたが、うまくいかなかったんだよ。";
					link.l1 = "それで？";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "あいつを見つけて殺してほしいんだ。あいつが死ぬのを望みすぎて、飯も喉を通らねえ……";
			link.l1 = "なるほど……その件について手を貸してやってもいいぜ。そいつの名前と船の名前を教えてくれ。";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "悪いが、俺は興味ねえんだ。";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = ""+npchar.quest.SeekCap.capName+" の "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 「名付けられた」 "+npchar.quest.SeekCap.shipName+"。払ってやる  "+FindRussianMoneyString(sti(npchar.quest.money))+"、それに私の宝石も全部だ。"; // belamour gen
			link.l1 = "なるほど。海上では注意しておくぜ。もし標的を見つけたら……そいつはもう死んだも同然だな。";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "そんな金額じゃ俺は何もしねえ。他の馬鹿を探して復讐させな。";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "それを聞きたかったんだ！ああ、やっと飯が食える！ついにだ！何か食い物を探さなきゃ…";
			link.l1 = "ごゆっくり召し上がれ。仕事が終わったらお前を探しに行くぜ。";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "地元の教会であなたを待っている。";
			link.l1 = "「よし。」";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "俺は怠けすぎてたんだ、そしたらあの野郎が女房をさらって自分の船に乗せちまった。頼む、この悪党を見つけてくれ！";
			link.l1 = "ふん、なんで同じ悪党同士で戦わなきゃならねえんだ？";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "俺は裕福じゃねえが、持ってる貴重品は全部くれてやるぜ！\nもし俺の女房を解放して連れてきてくれたら、報酬を払うぞ "+FindRussianMoneyString(sti(npchar.quest.money))+"、それに私の宝石も全部だ。";
			link.l1 = "よし、乗ったぜ。詳しい話を聞かせろ。そいつの名前、船、それからお前の女房の名前だな。";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "いや、相棒、そんなはした金じゃやらねえよ。悪いな……";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "彼女の名前は "+npchar.quest.SeekCap.name+"。そしてその野郎の名前は "+npchar.quest.SeekCap.capName+"、彼は泳ぎ続ける "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 「名付けられた」 "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "クソは浮かぶんだぜ、相棒。船長は航海する……";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "はい、はい、本当に申し訳ありません！私は船乗りではありませんので、ご理解いただければ幸いです…";
			link.l1 = "大丈夫だ、心配するな。とにかく、終わったらすぐ戻るぜ。";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "ありがとうございます！地元の教会でお待ちしています。しかし、どうか急いでください。本当に妻のことが心配で……";
			link.l1 = "ああ、俺も彼女が羨ましいとは思わねえよ。";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "問題はな、俺の友人には土地なんてないんだ。奴の船が家そのものさ。だから見つけられねえ、 いつも海を渡ってるからな。それに無駄な旅をする余裕もねえし、生きていくためには稼がなきゃならねえんだ。";
			link.l1 = "金がないなら助けてやれねえんだよ……";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "俺が金を払ってやるぜ "+FindRussianMoneyString(sti(npchar.quest.money))+" それに、私の宝石を全部渡すよ。今の私にはこれが精一杯なんだ。";
			link.l1 = "この金額で問題ないぜ。俺も乗った。実は、お前も乗客として一緒に来てもいいんだ。そうすりゃ、 友達を見つけ次第すぐに会えるぜ。";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "俺にはこれじゃ足りねえ。他の奴にやらせろ。";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "いや、俺はここに残るつもりだ。\nこの捜索がいつまで続くかわからねえし、金を全部失うかもしれねえ。\nここで仕事があるんだ。";
			link.l1 = "なるほど。さて、お前の友達は誰で、どの船に乗っているんだ。";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "彼の名前は "+npchar.quest.SeekCap.capName+"。俺の知る限り、彼は指揮しているのは "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Acc"))+" 「名付けられた」 "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "なるほど。まあ、もし友人に会ったら、あなたのことを伝えておくよ。";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "ありがとうございます。地元の教会であなたの到着をお待ちしています。仕事が終わったら報酬を渡します。";
			link.l1 = "ああ、わかった。じゃあ、これで失礼するぜ、すぐに結果を持ってくるからな。";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "ごきげんよう、船長。もう何か成果はあったか？";
			link.l1 = "お前の問題が何だったか、もう一度言ってみろ…";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "俺の仇は討たれたってことか。そうなんだな？";
					link.l1 = "「その通りだ。」 "+npchar.quest.SeekCap.capName+" は死んでいて、その "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" 海の底にある。";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "お前が俺の妻を見つけてくれたのか！信じられねえ！本当か？";
					link.l1 = "できるさ。彼女は俺の乗客だ。連れて帰ってもいいぜ、もし\n "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+" 本当にお前の女房なんだな……";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "ごきげんよう、船長。私の仲間を見つけてくれましたか？";
					link.l1 = "ああ、話したぜ、お前のことも伝えておいた。";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "「なんだと？俺が船長の仇を討ってくれって頼んだのを本当に忘れちまったのか」 "+npchar.quest.SeekCap.capName+" 俺の奴隷生活の一年分か？";
					link.l1 = "いいや、まだだ。";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "俺の耳を疑うぜ！俺が頼んだのは、俺の妻を探して救い出してくれってことを忘れたのか？あいつは という名の海賊に捕まったんだ "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "まだだ。";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "ちょっと待て……俺の仲間を探してくれるって約束、忘れたのか "+npchar.quest.SeekCap.capName+"?";
					link.l1 = "まだだ。";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "素晴らしい、やっぱりお前は期待通りだぜ！それじゃ、約束通り、お前の\n "+FindRussianMoneyString(sti(npchar.quest.money))+" そして宝石も。助けてくれてありがとう。";
			link.l1 = "どういたしまして…";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "なんてことだ！助けてくれたんだな！どうか、あなたの\n "+FindRussianMoneyString(sti(npchar.quest.money))+" そして宝石もだ。永遠にあなたのために祈り続けることを知っていてくれ！";
			link.l1 = "祈りたければ祈ればいいさ。俺は別に構わねえ。";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "素晴らしい！…ほら、受け取れ "+FindRussianMoneyString(sti(npchar.quest.money))+" そして宝石も。それと、ありがとうございます、船長。";
			link.l1 = "どういたしまして、友よ。さらばだ…";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("ごきげんよう、船長。手を貸してもらえますか？","船長！お手伝いいただけませんか？ご親切にしていただけると嬉しいのですが…","船長、助けてくれ "+GetSexPhrase("少女","俺")+".");
			link.l1 = RandPhraseSimple("俺はいま忙しいんだ。","「すまない」 "+GetAddress_FormToNPC(NPChar)+"……だが、俺には割く時間がないんだ……");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("「何か文句でもあるのか、」 "+GetAddress_FormToNPC(NPChar)+"?","「悩みを話してくれ」 "+GetAddress_FormToNPC(NPChar)+"。お手伝いしてみます。");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "私の夫は商人で、あちこちの植民地に商品を届けています。\n三か月前に海に出て、それ以来まだ帰ってきていません！";
					link.l1 = "「彼に何かあったと思うか？」";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+GetSexPhrase("船長、あんたは勇敢な船長で、まさに極上の悪党だな","船長、あんたは強い女だな。どんな男でも相手にできるってわけだ。")+"...";
					link.l1 = "「それで、なぜそんなことを言うんだ、」 "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "船長、どうか助けてください、お願いします！私の夫が捕まってしまいました！彼を救っていただけますか？";
					link.l1 = "ちょっと待て、よく分からねえ。誰が誰に捕まったんだ？";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "わからないけど、まだ彼が忙しすぎて手紙を書けないだけだと信じてるんだ。\n手紙くらい送ってくれてもいいのに。私が彼のことを心配しているのは知っているはずなのに！";
			link.l1 = "海は安全じゃねえ、何が起きてもおかしくねえんだ……";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "その通りだ！俺の言いたいことがわかったんだな。お前はまるで "+GetSexPhrase("勇敢な船長","勇敢な娘")+"、それであなたに私の夫を探してほしいのです。報酬はお支払いします\n "+FindRussianMoneyString(sti(npchar.quest.money))+"、それに私の宝石も全部あげよう。";
			link.l1 = "わかった。もし海や他の場所で旦那さんに会ったら、あんたの心配事を伝えておくぜ。 旦那さんの名前と船の名前を教えてくれ。";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "そんなはした金には興味ねえよ。";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "彼の名前は "+npchar.quest.SeekCap.capName+"。彼は～に乗って航海している "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 「名付けられた」 "+npchar.quest.SeekCap.shipName+".";  // belamour gen
			link.l1 = "なるほど。これからは待つ必要がある。できるだけ教会で過ごしてくれ、そうすれば俺が見つけやすいからな。";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+GetSexPhrase("そう申しているのはな、旦那、あんたが慣れている仕事を頼みたいからだ……まあ、そういうことさ。","手伝ってほしいの。女として私の気持ちをわかってくれるといいんだけど。")+"ある船長が俺を苛立たせたんだ。あいつを殺してやりたい。";
			link.l1 = "「それで、その哀れな奴があんたに何をしたっていうんだ？」";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "この野郎、私を騙しやがったわ。愛してるふりまでして、あたしに言い寄ってきたのよ。それも全部、 旦那から何か貴重なものを手に入れるためだったんだから！\nそしてあの犬野郎は欲しいものを手に入れたら、「何の意味もなかった、ただの友達だ」なんて言いやがったのよ…";
			link.l1 = "ふむ、もしかして彼が正しかったのか？";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "俺がバカに見えるのか！？口説いてるのとただの雑談の違いも分からねえと思ってんのか？";
			link.l1 = "「そうだろうな……」";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "あの悪党に利用されたんだ！俺は絶対にあいつを許さねえぞ！";
			link.l1 = "ああ、男ってのはそういうもんだぜ。だが、少しは落ち着けねえか？別に恐ろしいことなんて何もねえさ……";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "「何もひどいことはないだと！？」 "+GetSexPhrase("お前は道徳家かよ、本物の海賊じゃねえな！","そんな状況になったことがないみたいだな！ああ、そうよ、誰がそんな危険を冒すのかしら……あたしなんてただのか弱い女だもの……");
			link.l1 = "わかった。もう十分だ。お前の本気度を知りたいだけだ。";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "「ちくしょう、」 "+GetSexPhrase(" 「振られた女の復讐がどんなものか、あんたはまだ知らないんだよ」 ","あんたも女だろう、拒絶される気持ちがわかるはずだ！あたしは復讐したいんだ ")+"!";
			link.l1 = ""+GetSexPhrase("本当だ、こんな経験は今までなかったぜ","まあな、あいつはちょっと泣いて、ガラスを割って、それで終わりさ")+"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+GetSexPhrase("運が良かったと思いな。期待を裏切られ、拒まれた女ってのは、まるでスカートをはいた悪魔、怒れる魔女だぜ！ この世の何をもってしても、あいつの怒りは収まらねえんだ。","俺はあいつとは違う。何も俺の怒りを和らげることはできねえ")+"！\nだから、お前に直接あいつを殺してほしいんだ。死ぬ前に、誰がその死の代価を払っているのか、必ず思い知らせてやれ……";
			link.l1 = "ふむ、何と言えばいいのか……で、いくら払うつもりだ？";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "私の持っているものすべてだ。宝石も渡すし\n "+FindRussianMoneyString(sti(npchar.quest.money))+"「！取引成立か？」";
			link.l1 = "興味があるぜ。そいつの名前と船の名前を教えてくれ。";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "興味ねえ。じゃあな。";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "その悪党の名前は "+npchar.quest.SeekCap.capName+" そして彼は～に乗って航海している "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Gen"))+" 「名付けられた」 "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "「任せとけ」 "+GetAddress_FormToNPC(NPChar)+"。地元の教会で待っていてくれ。少しは落ち着いてくれることを願っている……";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("",""));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "説明します。問題は、私の夫――ただの一般人なのですが――が海賊に捕まってしまったことです！あいつらは皆殺しにして、誰一人として容赦しませんでした……";
			link.l1 = "どうやら船長が抵抗したようだ。そうでなければ乗組員は助けられていただろう。";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "たしかにそうかもしれませんが、私の夫は無実の人です。彼はただの乗客でした。 命を守るために裕福だと嘘をついただけです。海賊たちは夫を見逃してくれましたし、 荷物室に入れられることさえありませんでした。";
			link.l1 = "「それをどうして知っているんだ？」";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "奴は俺に手紙を送ることができたんだ。自分は無事で、他の囚人たちとは違って船室に監禁されていると書いてあった。";
			link.l1 = "「それで、どうするつもりだ？こんな状態は続けられねえぜ。遅かれ早かれ、海賊どもに奴の正体がバレちまうぞ。」";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "お前も海賊なのか？ええ、ええ、わかってるわ……お願い、助けて、うちの旦那を救って！あの海賊船のことも、船長の名前も旦那が書き残してるの。 あなたならきっと見つけられるはずよ！";
			link.l1 = "思っているほど簡単じゃねえぞ。囚人はみんな、あんたの旦那を捕まえた船長の正当な戦利品だし、 それに時間もかかるんだ。";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "でも、少なくとも試してみることはできるでしょ！それに、探す時間は十分あるわ。私の夫は馬鹿じゃないし、 旧世界から来た商人のふりをしているから、あの海賊たちも今のところ彼に金を要求していないの。 もし彼を助け出してくれたら、私の持っているものは全部あなたにあげるわ！";
			link.l1 = "「それで、お前は何を持ってるんだ？」";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "「あまりない」 "+FindRussianMoneyString(sti(npchar.quest.money))+" そして私の宝石もすべて……。でも、あなたの魂のために永遠に祈り続けますわ！";
			link.l1 = "ああ、それじゃ本当に大したことねえな……よし、手伝ってやるぜ。";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "申し訳ないが、それでは俺には足りねえ。";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "「ありがとう、本当にありがとう！」";
			link.l1 = "俺がうまくやったら感謝することになるんだ、だから止まれ。旦那の名前と、 その海賊たちについて知っていることを全部話したほうがいいぜ。";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "彼の名前は "+GetFullName(forName)+"。船長の "+npchar.quest.SeekCap.capName+"、彼は航海を続ける "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 「名付けられた」 "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "なるほど。さて、これからは俺が捜索に成功することを願って待っていてくれ。教会に留まり、待って祈るんだ…";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "ああ、船長、お会いできて本当に嬉しいです！さて、私の依頼について何か新しい情報はありますか？";
			link.l1 = "うーん、思い出させてくれ、 "+GetAddress_FormToNPC(NPChar)+"、どの任務のことを言っているんだ？";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "ああ、船長、夫から手紙が届きました！あなたが彼を見つけてくれたと書いてあります。";
					link.l1 = "「ああ、その通りだ」 "+GetAddress_FormToNPC(NPChar)+"。あなたの旦那、 "+npchar.quest.SeekCap.capName+"、元気で健康だ。あいつはただ忙しすぎるだけさ……";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "どうだい、船長？俺の頼みは果たしてくれたか？船長は "+npchar.quest.SeekCap.capName+" 死んだのか？";
					link.l1 = "「ああ、彼は死んだ」 "+GetAddress_FormToNPC(NPChar)+"。誰が自分の死の原因かを奴に教えてやった。奴が人生で最後に聞いたのはお前の名前だったぞ。";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "あなたが私の夫を救ってくれたのですね！お願いです、本当だと言ってください！";
					link.l1 = "ああ、そうだ。今は俺の船にいるぜ。会いたければ\n "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+"本当にあなたの旦那なのか……";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "本当に私の夫を探してくれると約束したことを忘れたの？彼の名前は "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "「ああ、そうだ、もちろん……忘れてはいないさ。」";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "わからねえ！俺に害をなしたあの"+GetSexPhrase("野郎","女")+",つまり"+GetSexPhrase("船長","女船長")+"の名を持つ奴を殺さなきゃならねえってこと、忘れたのか？ "+npchar.quest.SeekCap.capName+"?!";
					link.l1 = "お願いだから、もちろんまだだよ。ご注文は処理中だから、少々お待ちを……";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "「おい、船長、あんた、私の旦那を自由にするって約束、忘れちまったのか？」";
					link.l1 = "俺はしてねえよ。覚えてるか…「待って祈れ！」ってやつだ。とにかく待つんだぜ、 "+GetAddress_FormToNPC(NPChar)+" "+npchar.lastname+".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "ああ、神よ、本当に感謝しています！それと、はい、あなたのものを持っていってください "+FindRussianMoneyString(sti(npchar.quest.money))+"。改めてありがとう！";
			link.l1 = "ふむ、どういたしまして……";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "素晴らしい！さあ、自分の\n "+FindRussianMoneyString(sti(npchar.quest.money))+" そして宝石だ。さらば……";
			link.l1 = "さらば。 ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			TakeNItems(pchar, "jewelry47", rand(3));
			TakeNItems(pchar, "jewelry43", rand(3));
			TakeNItems(pchar, "jewelry41", rand(3));
			TakeNItems(pchar, "jewelry48", rand(3));
			TakeNItems(pchar, "jewelry51", rand(3));
			TakeNItems(pchar, "jewelry46", rand(3));
			TakeNItems(pchar, "jewelry49", rand(3));
			TakeNItems(pchar, "jewelry40", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "間違いなくあいつだ！ああ神よ、船長、心から感謝します。さあ、あなたの\n "+FindRussianMoneyString(sti(npchar.quest.money))+"。私の生涯、毎日あなたのために祈ります！";
			link.l1 = "いいだろう……";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "同業者よ、挨拶だ。何か用か"+GetSexPhrase("、相棒 ","、娘")+"?";
					link.l1 = "あなたの名前は "+GetFullName(npchar)+"、そうだろう？";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "ああ、お前だ！";
			link.l1 = "運が悪かったな。ひとつ名前を教えてやるから、しっかり覚えておけよ。"+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"。彼のことを覚えているか？";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "ふむ、そうだな……";
			link.l1 = "さあ聞けよ、あいつはお前にすごく怒ってるぜ、相棒。自由な人間を奴隷に売った報いを受ける時だ。";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "「払うだと？！何言ってやがるんだ、クソッタレ！」";
			link.l1 = "つまり、俺は今ここでお前を殺すってことだ。";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "考えてみろよ、お前は誰のために働いてるんだ！？こいつは哀れな奴で、砂糖プランテーションに送られるべきだぜ！";
			link.l1 = "これはお前には関係ねえことだ。今こそ自分のやったことの責任を取ってもらうぜ！";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "おう！俺のやり方でしか答えねえぜ！";
			link.l1 = "続けてくれ…";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "何の用だ？";
			link.l1 = "お前に聞きたいんだが、乗客は乗せてるのか？ ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "「それがあんたに何の関係があるんだ？」";
			link.l1 = "ただ聞いただけだ。";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "ちょっと聞いただけだ…いいか、今のうちにここから出て行った方が身のためだぜ。俺はお前が気に入らねえんだ！";
			link.l1 = "わかった、わかった、落ち着けよ。もう行くぜ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "もう話はしただろう、だから俺を試すんじゃねえぞ！";
			link.l1 = "俺はやらねえ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "やあ、同業者よ！何か用か？";
			link.l1 = "知りたいんだが、お前、あの女を連れて行かなかったのか "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" 「名付けられた」 "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "へっ、あんたの言う通り、あの女は俺の船室にいるぜ！それにしても、あの娘はなかなかの美人で脚も最高だ…で、なんでそんなこと聞くんだ？";
			link.l1 = "おい、相棒。この女は既婚者だぜ。これは間違ってるぞ。";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "だから何だよ？俺はあの女が好きなんだ、それだけだぜ。旦那だからって、 ボロをまとった間抜けに俺たちの関係を邪魔させるつもりはねえ！";
			link.l1 = "こういうことは兄弟団が認めねえってことを言っておくぜ。もし誰かにお前のやったことが知れたら、 ブラックマークが送りつけられるだろうよ。";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "俺に説教でも始めるつもりか？";
			link.l1 = "落ち着けよ、ちょっと興味を示しただけだ……じゃあな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "女のことはもう話しただろう。もう一度この件について話したくねえんだ！";
			link.l1 = "どうでもいいさ…";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "俺の甲板に同業者を迎えられて嬉しいぜ！何の用だ？";
			link.l1 = "「お前がどこかから女をさらったのか知りたいんだが」 "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" 「という名の」"+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "へっ、そうだぜ、あの娘は俺の船室にいる！それにしても、いい女だし、脚もなかなかだぜ！…で、なんでそんなこと聞くんだ？";
			link.l1 = "おい、相棒。この女は既婚者だ。これは間違ってるぜ。";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "だから何だよ？俺はあの女が好きなんだ、それだけだぜ。たとえあいつが旦那でも、 みすぼらしい野郎に俺たちの関係を邪魔させやしねえ！";
			link.l1 = "こういうことは兄弟団が認めねえって教えてやるぜ。もし誰かにお前のやったことが知れたら、 ブラックマークが送りつけられるだろうな。";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "俺に説教でも始めるつもりか？";
			link.l1 = "落ち着けよ、ちょっと興味があっただけだ……じゃあな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "俺に何の用だ、このクズ野郎！？";
			link.l1 = "俺は、あんたが夫から奪った女を迎えに来たんだ。覚えておけ "+XI_ConvertString("Colony"+npchar.quest.cribCity)+"「？彼女の名前は」 "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "くそっ！お前はあの女にも、自分の耳にも絶対に会えねえぞ！";
			link.l1 = "バカめ。鏡でちゃんと見えるんだよ。お前のも今から切り落としてやるぜ！";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_"+(hrand(3)+7); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "お前は誰だ？";
			link.l1 = "こんにちは。旦那さんに頼まれてあなたを迎えに来たんだ。もう自由だ、俺が旦那さんのもとへ連れて行くぜ。";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "夢なのか！？本当なのか！？";
			link.l1 = "そうだ。 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "主を讃えよ！俺は準備できてる、さあ、ここから逃げようぜ！";
			link.l1 = "「ああ」 "+GetAddress_FormToNPC(NPChar)+"、旦那のもとへ無事に帰れるよう準備しなさい。";
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "やあ！陸にいる仲間に挨拶できて嬉しいぜ…";
			link.l1 = TimeGreeting()+"、お前に用があるんだ。";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "聞いているぞ。";
			link.l1 = "お前の仲間が探してるぜ。お前たちは一緒に航海して、旧世界からここに着いたんだ。"+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"、覚えてるだろ？";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "はっ、もちろん知ってるぜ！で、今はどこに住んでるんだ？";
			link.l1 = "In "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = " ありがとう！実は、お前のことを海賊だと思ってたんだぜ！";
			link.l1 = "俺だ。まあ、そんな感じだな。あるいは違うかもしれねえ。だが、とにかく今日は機嫌がいいから、 お前は心配いらねえぜ。じゃあな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "何か問題でも？すみません、ちょっと緊張していて……";
			link.l1 = "大丈夫だぜ、相棒。";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting()+"……俺に何の用だ？俺はただのしがない商人で……";
			link.l1 = "わかってるぜ、相棒。そんなに心配すんな、体に悪いって言うじゃねえか。お前に用があるんだ。";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "「どんな用件だ？」";
			link.l1 = "お前の友達が探しているぜ。名前は "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"。あいつを知ってるか？";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "ああ、やっと来てくれたのですね！それは素晴らしい……こんな無礼な挨拶をしてしまい申し訳ありません、でもあなたのことを海賊だと思ってしまったのです。";
			link.l1 = "そうだ。まあ、そんなところだな。あるいは、違うかもしれねえ。だがまあ、今日は機嫌がいいから心配はいらねえぜ。 お前に伝言を頼まれて、それをちゃんと届けたってわけだ。お前の仲間は\n住んでいる "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+"."; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "すごいじゃねえか！あんたは立派な男だな。ありがとうよ！";
			link.l1 = "どういたしまして。じゃあな、気をつけろよ、相棒。";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "こんにちは。何かご用ですか？";
			link.l1 = "あなたの名前は "+GetFullName(npchar)+"、そうだろう？";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "ああ、俺だ。";
			link.l1 = "馬鹿げて聞こえるかもしれませんが、あなたの奥さんがあなたのことを心配していると私に伝えてほしいと頼まれました。 ";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "ははっ！なるほどな……実は俺も忙しくてな、儲かる話が山ほどあるんだ。女房が心配しすぎるからって、 稼げるチャンスを逃すわけにはいかねえんだよ。";
			link.l1 = "しかし、せめて彼女に手紙を書いて無事だと伝えてやれよ。";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "はい、その通りです。すぐに彼女に手紙を書きます！家族のことに関わってくれてありがとう！";
			link.l1 = "どういたしまして、相棒。";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "ごきげんよう。ご用件は何でしょうか？";
			link.l1 = "あなたの名前は "+GetFullName(npchar)+"……そうだろう？";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "ああ、俺だ。";
			link.l1 = "馬鹿げて聞こえるかもしれませんが、奥さんがあなたのことを心配していると伝えてほしいと頼まれました。";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "ふう、くそっ！あの有名な賞金稼ぎが俺を狙って来たのかと思ってビビったぜ、名前は片目のスティーブとか言うやつだ。 まあ、勘違いでよかったぜ\n見ての通り、俺は仕事で手一杯で、あいつに構ってやる暇なんてねえんだ。儲かる話が次から次へと舞い込んでくるし、 女房の心配ごとだけで断るわけにもいかねえよ。";			
			link.l1 = "もちろん、その通りだ。しかし、せめて彼女に手紙を書いて、自分が無事だと伝えてやったらどうだ。";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "そうだな、君の言う通りだ。最初の港に着いたらすぐにやろう……我が家のことに関わってくれてありがとう！";
			link.l1 = "どういたしまして、相棒。";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "感謝するぞ、船長……";
			link.l1 = "どういたしまして。";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "この町でお会いできて嬉しいです、船長。俺に何か用かい？";
			link.l1 = ""+GetSexPhrase("なあ、船長……ふう、何て言えばいいのかわからねえよ！","ああ、あるぜ。")+"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+GetSexPhrase("ありのまま言え。","面白いな、それは何だ？")+"";
			link.l1 = " お前に聞きたいことがある。"+GetSexPhrase("女","女性")+"の"+GetSexPhrase("名前","名")+"を知っているか "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "へっ、知ってるぜ。あいつと関わって運が悪かった。あれは愚かな娘だよ、俺が言ってやる……";
			link.l1 = "ふむ……そうだ、この愚かな娘が俺にお前を殺せと頼んできたんだ。それだけさ……。";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "馬鹿なことだ。";
			link.l1 = ""+GetSexPhrase("同感だ。悪いが、お前の首には賞金がかかっているんだ","違う。賞金がかかっている")+"。俺がそれをいただくぜ。";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "ほっほっほっ……冗談かい、船長？";
			link.l1 = ""+GetSexPhrase("いや、友よ。","やるつもりなんてなかったぜ！")+"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+GetSexPhrase("お前は俺の仲間じゃねえ、バカ野郎！船長なんて名乗る資格もねえよ。お前はただ、 この愚かな怒りの玩具にすぎねえんだ！","くそっ！悪女がもう一人の悪女を雇いやがった！この世の中、一体どうなってやがるんだ！？")+"!";
			link.l1 = ""+GetSexPhrase("口の利き方に気をつけろ、このクズ野郎。","お前があの女を利用したんだ、だから彼女が復讐を決めても驚くなよ。")+"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+GetSexPhrase("痛いところを突いたか？","「女の連帯感だと！？」")+"";
			link.l1 = "これで終わりだ！";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "もうお前とは話しただろう。消えろ、このバカ野郎！";
			link.l1 = "バカだと！？いいだろう……";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "乗船してくれて嬉しいぜ、船長。何の用だ？";
			link.l1 = "お前に聞きたいことがある。"+GetSexPhrase("女","女性")+"の名前を知っているか "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "へっ、知ってるぜ。あいつと関わって運が悪かったんだ。あれは愚かな娘だよ、俺が言ってやる…";
			link.l1 = "ああ、そしてこの愚かな娘が俺にお前を殺せと頼んできたんだ。";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "船長、笑わせるなよ。大した用がないなら、これで失礼するぜ。";
			link.l1 = "それじゃあな。だが、俺が言ったことをよく考えてみろよ。";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "もちろんだぜ、船長、他にどうなるってんだ！？";
			link.l1 = "さらば。";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "この件についてはもう話したくないぜ、船長。こんなの馬鹿げすぎてる。";
			link.l1 = "あんたの好きにしな…";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "ここで一体何が起きてやがるんだ！？なんで俺の船を襲ったんだ？";
			link.l1 = "「という名のご婦人の依頼で」 "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"。彼女のことを知っているか？";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "なんだと！信じられねえ……";
			link.l1 = "やるしかねえだろ！女ってやつを知らねえのか、相棒？あいつらは噛みつくことだってあるんだぜ。";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "まあ、こんなところでくたばるつもりはねえよ。話してくれてありがとう、おかげで少し元気が戻ったぜ。";
			link.l1 = "役に立たねえぞ。";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "乗船してくれて嬉しいぜ。何か手伝えることはあるか？";
			link.l1 = "できますよ。私はという名の男を探している "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "この男は俺の捕虜だ、そして俺は身代金を取るつもりだ。";
			link.l1 = "俺はあいつを連れて行きたいんだ。";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "残念だが、それは不可能だ。もしそれだけなら、俺の船から出て行ってくれ。";
			link.l1 = "わかったぜ、船長、あんたの言う通りだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "俺の囚人についてはもう話しただろう。何も変わっちゃいねえ。";
			link.l1 = "なるほど……";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "お会いできて光栄です。何かお手伝いしましょうか？";
			link.l1 = "どうぞ。俺はという名の男を探しているんだ "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "この男は俺の捕虜だ、そして身代金を取るつもりだぜ。";
			link.l1 = "俺はあいつを連れて行きたいんだ。";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "申し訳ないが、それは無理だ。";
			link.l1 = "残念だな……";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "くそっ！なんだってんだ！？";
			link.l1 = "俺はお前の捕虜である名前の者が必要だ "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "はっ！そんなの絶対に無理だ、俺の死体を越えてからにしな！";
			link.l1 = "「お尋ねになったからには…」";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+11); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "お前は誰だ？";
			link.l1 = "俺が船長だ "+GetFullName(pchar)+"。心配するな、俺があんたを奥さんのもとへ連れていくぜ。";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "くそっ、夢でも見てるのかよ！";
			link.l1 = "それは違うと断言できる……まあ、もう終わったことだ。さあ、ここから離れよう。";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple("俺はもうくたくただ、助けてくれ。","こんなふうに生きる力はもう残ってないんだ！"),RandPhraseSimple("この仕事に俺たちは食い殺されそうだ。","血まみれの衛兵どもに背中の皮を全部剥がれちまったぜ！"));				
				link.l1 = RandPhraseSimple("なんてこった。","ああ、人生ってやつは厳しいもんだな。");
				link.l1.go = "exit";				
    		} 
		break;
		
		//=====================================================================================================================================
		// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);
			
			if(LoadedLocation.type == "tavern")
			{
				// "Честь мундира".
				if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = "おう、船長、俺と一緒に座れよ。奢ってやるぜ！";
					link.l1 = "喜んで。";
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if(NPChar.sex == "man")
				{
					// "Невольник чести".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
					{
						dialog.text = "やあ、船長。あんたは船長だろう？もしかして海軍の船長か？\nそうだ、あんたは剣の腕も立つに違いない。明日死ぬことになるうちの役立たずの息子とは大違いだ……全部、うちの息子が想いを寄せている女性に目をつけたあの色欲まみれの野郎のせいだ！";
						link.l1 = "ああ、俺は船長だし、これまで何度も剣に命を救われてきたぜ。だが、お前のその陰気な話の続きはどうなんだ？ 説明してくれねえか？";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "Красотка и пират".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "ごきげんよう、船長。お聞きしますが、もしかしてあなたは海賊だったりしますか？ああ、もちろん違いますよね！ あなたは違います。海賊どもは見た目もひどく、獣のように振る舞い、しかもあの臭いときたら……";
						link.l1 = "海賊に恨みでもあるのか？";
						link.l1.go = "AffairOfHonor_BeautifulPirate_1";
						PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;
					}
					
					// "Заносчивый нахал".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
					{
						//if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
						//{
						// Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
							dialog.text = "おい、そこのお前！そうだ、お前だ、ちょっと聞くが、礼儀ってもんはどこにやった？ なんでここに突っ立って俺の邪魔してやがるんだ？いや、見ろよ、こいつ、なんて間抜けだ！俺が話してんだぞ！どけよ！ ここはよそ者が多すぎるんだよ！\n";
							link.l1 = "落ち着いてくれ、邪魔するつもりはなかったんだ。すまない。";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "言葉に気をつけろ、さもないとその舌を切り落とすぞ、旦那。";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "Волки и овцы".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "ごきげんよう、船長。あなたに頼みたいことがあるんだ。もし名誉ある男なら、見て見ぬふりはしないはずだ。\n早速本題に入るぜ――一か月前、貴族がうちの酒場に泊まったんだ。そいつはとんだ放蕩者で、ろくでなしだった！しかも、殺人者なんだよ！";
						link.l1 = "俺の記憶が正しければ、無実の者を殺した罰は絞首刑だぜ。放蕩者やろくでなしってだけじゃ、 法廷じゃ大して役に立たねえだろうよ。違うか？";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "Трусливый фехтовалщик".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "船長、待ってください、お願いします。あなたは剣の腕が立ちそうだ、俺なんかよりずっと上手い。だから、 俺の代わりを頼みたいんだ。";
						link.l1 = "興味深いな。続けてくれ。";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "Божий суд".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "お願いです、どうか行かないでください！待って…あなたのような勇敢な軍人の助けが必要な件で、貧しい私を助けていただけませんか？\n実は、地元の葡萄畑のことで隣人と揉め事がありまして、その隣人は密輸業者と関わっている疑いもあるんです。ええ、 そうなんです、もしかしたら海賊とも繋がっているかもしれません――そうでもなければ、あんな短期間で大金持ちになれるはずがありません！\n一年前は小さなバーク船しか持っていなかったのに、今では私の葡萄畑まで奪おうとしているんですよ、聞いてますか！？ 私の葡萄畑を！";
						link.l1 = "お前さんの葡萄園のことは気の毒だぜ。本当に。じゃあな。";
						link.l1.go = "exit";
						link.l2 = "失礼ですが、地元の役人に相談できないのか？";
						link.l2.go = "AffairOfHonor_GodJudgement_1";
						PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "Навязчивый кавалер".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = "船長、船長、お願いします！無垢な娘の名誉を守ってください！";
						link.l1 = "こんなことに構ってる暇はねえんだ、綺麗なお嬢ちゃん。他を当たってくれ……";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "ごきげんよう、お嬢さん。そんなに震えないでくださいまし！何があったのですの？";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "バグだ。開発者に知らせてくれ。";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "船長、私は駐屯地の士官に、これ以上ないほどあからさまにつきまとわれております。 あの男が私について下劣な噂を流し、私を辱めようとしているのはご存じでしょう！\nああ、私の潔白な名誉を守ってくれる友人など一人もおりません！絶望的です！ああ神よ、あれが彼です！ 助けてください！";
			link.l1 = "心配するな、俺が最後までやり遂げるぜ。";
			link.l1.go = "exit";
			int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_14"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
			float Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;
		
		case "AffairOfHonor_Cavalier_2":
			dialog.text = "ああ、ここにいたのですね、お嬢様！また別の騎士殿ですの？いつになったら落ち着くおつもりかしら？ たぶん一生無理でしょうね……娼館で働いたらいかが？そこが一番お似合いですわ……";
			link.l1 = "士官、侮辱を吐くのはやめろ。俺流のやり方で黙らせてやるぞ！";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "ふむ……お前は誰だ？あ、ああ、海に鍛えられた小舟の勇敢な船長ってわけか、違うか？で、どうするつもりだ、 海の子猫ちゃんよ？";
			link.l1 = "この女は俺の仲間だ！そしてお前にも手袋（ガントレット）をくれてやるぜ！";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "「なんだと！？このことで俺に勝負を挑むつもりじゃねえだろうな…」";
			link.l1 = "もういい！二時間後に灯台の近くで待っているぞ。剣を忘れるんじゃねえぞ！";
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;
		
		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;
		
		case "AffairOfHonor_Cavalier_5":
			dialog.text = "ああ、俺は全部知ってるぜ、旦那！あんたにはどれほど感謝してるか想像もつかねえ！ 主があんたを守ってくださいますように！";
			link.l1 = "お力になれて嬉しいです。幸運を祈ります！";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar, "nobility", 7);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Cavalier_6":
			dialog.text = "ああ、お前も他の奴らと同じだ、俺のことは放っておいてくれ！";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "or in the brothel ";
			dialog.text = "「ああ、」 "+GetAddress_Form(NPChar)+"…ほとんど希望を持てませんが、今回はあなたの剣で私の家族を守っていただけませんか？\n申し上げた通り、私の息子は剣士ではありませんが、夜明けに決闘をすることになっています。ああ、あの女性と忌々 しい名誉のせいでなければ…\nしかし彼は身を引くことができず、今や破滅が待っています、分かりますか？私は絶望しています――彼は私のただ一人の息子であり跡継ぎなのです。ですから、 どうか夜明け前に息子に決闘を挑んだあの悪党を討ってください。必ずお礼はいたします、約束します！\nその男は酒場にいます "+sTemp+" ―あいつみてえなクズどもが暇を潰してる場所だ……頼むよ……";
			link.l1 = "俺はお前にもお前の息子にも興味ねえ。放せ！";
			link.l1.go = "exit";
			link.l2 = "ふん……そう簡単にいくのか？まあいい、どうなるか見てやるぜ。";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "本当に私の息子を助けてくれるのか？ああ、 "+GetAddress_Form(NPChar)+"！あなたとあなたの幸運のために祈っております！";
			link.l1 = "それなら問題ないだろう…待ってくれよ！";
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;
		
		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
			Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04","blade_06"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			if(rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;
		
		case "AffairOfHonor_HonorSlave_3":
			dialog.text = "俺に一体何の用だ？ここで休もうとしてるんだ、邪魔されたくねえ。席もたくさん空いてるし、 話を聞きたがってる奴もいるだろうから、俺のことは放っといてくれ、旦那！";
			link.l1 = "残念だが、休息はもっと良い時まで延期しなければならないぞ。";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "「なんだと！？お前は何様のつもりで俺に指図するんだ！？」";
			link.l1 = "俺のことを忘れちまったのか、ああ？だが俺はお前を覚えてるぜ！そして言いたいのはな、 てめえみたいな悪党がいるだけでこの世が腐っちまうってことだ！";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "ああ！？水夫よ、お前は酔っ払いすぎだぜ！お前を見るのはこれが初めてだ！だがな、お前の態度を見逃すつもりはねえ！ これが命拾いできる最後のチャンスだ！今すぐ言い訳しろ、この膨れたニシン野郎、 そうすりゃ無礼な口の利き方は忘れてやる！";
			link.l1 = "俺が言い訳するのは立派な男にだけだ、汚え豚野郎にはしねえ！";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "なんだと！？ケンカ売ってんのか、この便所虫が！";
			link.l1 = "てめえのその汚え口は、自分の言葉で塞いでやるぜ、このネズミ野郎！二時間後に灯台の近くで待ってるからな、 腰にぶら下げてるその錆びたガラクタも忘れずに持ってこいよ！";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "はっ！俺も行くぜ！";
			link.l1 = "またすぐ会おうぜ！";
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;
		
		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
		break;
		
		case "AffairOfHonor_HonorSlave_7":
			dialog.text = "「あっ、お前か！生きてるってことは……」";
			link.l1 = "ああ、そうだ。だからお前の息子は明日の朝、決闘する必要はないんだ…";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "なんて素晴らしい日だ！妻にこの良い知らせを伝えに行かなくては！\n船長、運命そのものがあなたを私のもとに遣わしてくれたのです。さあ、このコインを受け取って、 我が家族の感謝をお受け取りください！";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(iTemp)+"");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_9":
			dialog.text = "消え失せろ、子殺し野郎！";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "俺か？神に感謝してる、俺は無事だ。でも妹は運が悪かったんだ。妹は酒場で働いてるんだよ。\nそこによく来る私掠船乗りがいてな、あいつは本当に危険な奴だ。海賊だ！あいつの船は少なくとも一週間は海に出てる。 あの男は酒を飲み、人を脅し、話し合おうとする奴は誰でも殺すと脅してるんだ。一番ひどいのは、妹が言うには、 あいつは自分の汚い欲望を満たさなければ妹をさらってどこかへ連れていくって自慢してるらしい！\nどうしたらいいかわからない！役人は下働きの娘なんか気にしちゃいないし、 俺みたいな善良な市民はあの私掠船乗りが怖いんだ。頼む、あいつを何とかしてくれ！";
			link.l1 = "酒場で酔っ払いをなだめている暇なんてねえ。そういうことは司令官に話せ、あいつはそのために給料もらってるんだ。";
			link.l1.go = "exit";
			link.l2 = "ふん、手強い私掠船か？よし、俺が片付けてやる。";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "ああ、ありがとう、船長！きっとあなたの言うことなら、船乗り同士でちゃんと聞いてくれるはずだ！ 妹にもう二度と近づかせないでくれ！うちは裕福じゃないが、あなたの骨折りにはきちんと報酬を払うよ！";
			link.l1 = "わかった、わかった……お前の問題を解決しに行くぜ。待ってろよ！";
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 25+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;
		
		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = "それでどうした？あの海賊と話したのか？奴は俺たちを放っておいてくれるのか？";
			link.l1 = "少し待ってくれ。今やってるところだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "何の用だ？ここで休もうとしてるのが見えねえのか？";
			link.l1 = "ほうほう……見ろよ、ビールジョッキの王様にして女の子泥棒、この小さな町の嵐が現れたってわけだな、そうだろ？ 町の外でも同じくらい勇敢でいられるのか？灯台の近くで、二時間後に決闘だ、どうだ？";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "おおっほっほ！お前、英雄気取りか？まあいいさ、今日は機嫌がいいから許してやるぜ。さっさと行って、 俺にエールを何杯か買ってこい！";
			link.l1 = "俺はお前の仲間じゃねえ。バカなお前のためにもう一度言ってやろうか？ 酒場に現れるくらいの度胸で決闘にも出てこれるのか？";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "俺に喧嘩を売ってるのか！？どうかしてるぜ、お前。生きるのに飽きたのか、死にてえのか、この野郎？いいだろう、 そこまで言うなら、灯台まで歩いてやる。てめえの腸をぶちまけてやるし、この忌々しい酒場もぶっ壊してやるぜ！\n";
			link.l1 = "口だけならタダだが、剣はそうはいかねえ。忘れずに持ってこいよ！";
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;
		
		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = "それで？あの海賊と話したのか？奴はもう俺たちにちょっかいを出さないのか？\n妹が言ってたけど、奴は酒場を出てから戻ってこなかったって……";
			link.l1 = "ああ、話はしたよ。あいつは少し無礼だったが、俺の言い分は筋が通っていて説得力もあった。 今は君の妹さんも何も心配することはないさ。";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "これで……終わったのか？もう安心して息ができるのか？ありがとう、船長！それで……あの悪党はどこにいるんだ！？";
			link.l1 = "あいつは……自分の船にいるよ。できるだけ早くこの町を出ることにしたんだ。";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "この植民地の市民たちに大きな貢献をしてくれたな！さあ、これが君への報酬だ！控えめな額だが、 私の友人たち全員の尊敬を得られるぞ。信じてくれ、私には友人が山ほどいるんだ！";
			link.l1 = "感謝する！君と君の妹に幸運を祈る。妹さんが立派な男と結婚できることを願っているよ。さらば！";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Jackanapes_1":
			dialog.text = "「ほう、本当か？それで、どうやって俺を止めるつもりだ？」";
			link.l1 = "俺の剣でだ、もちろん。お前みたいな無礼な豚には、それしかふさわしい方法はねえからな。";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "素晴らしい！二時間後に灯台の近くで待っているぞ。";
			link.l1 = "いいね！絶対に行くぜ。";
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;
		
		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // Еще успеем.
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
		break;
		
		case "AffairOfHonor_Jackanapes_2":
			dialog.text = "どけ、この腰抜け野郎！";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "船長、あの野郎はただ者じゃねえんだ。トム、俺の古い友人が、あいつと決闘して死んじまったんだよ、 イカサマの濡れ衣を着せられてな！トムは無実だった、俺が誓う。だが総督は、あの忌々 しい決闘には罪はなかったと言いやがったんだ。";
			link.l1 = "ふん……全部お前の友達のせいだ。イカサマ賭博なんて、身の破滅につながるぜ。";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "ああ？ここ二週間でうちの町にはすでに四人のイカサマ師が現れてるんだぜ。 しかも全員がうちの貴族様を騙そうとしたって？どう思うよ？俺が言いたいのはな、 その貴族様こそがイカサマ師本人ってことさ。信じられねえなら、自分の目で確かめてみな。";
			link.l1 = "あいつと賭けをするつもりか？いや、俺は賭け事は好きじゃねえ。絶対に無理だ。";
			link.l1.go = "exit";
			link.l2 = "そうするしかないか……ここは何かがおかしい。";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "船長、俺と仲間たちで、あの貴族の正体を暴き、奴の悪事に復讐してくれる者に払うための金を集めたんだ。 仕事が終わったら、町で報酬を渡すために待っているぜ。";
			link.l1 = "もしお前の言っていることが本当なら、そうするぜ。";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = "ご挨拶を、旦那！貴族様とお見受けしますが……もしかして博打打ちでも？一勝負いかがですか？";
			link.l1 = "もちろんだ！賭け金の話をしようぜ。50枚のコインでどうだ？";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "冗談か？お前はそれを持ってねえじゃねえか！";
				link.l1 = "「その通りだ……」";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "賭け金なんて関係ねえ、これから博打をやるんだぜ、それが一番楽しいところさ。地元の間抜けどものせいで、 もうカードの絵柄も忘れちまいそうだ。";
				link.l1 = "さて、始めよう。";
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = "つまり、賭け金は50コインだ。";
			link.l1 = "...";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
            PChar.GenQuest.Cards.SitType = true;
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = "ちょっと待て、これは何だ……ありえない！旦那、お前はイカサマ師だ！俺のコインを返せ！";
			link.l1 = "俺を告発するには、しっかりした理由があるはずだな。  "+GetAddress_FormToNPC(NPChar)+"。今すぐ撃ったほうがいいぜ、さもないと決闘だ！";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "ああ、そんな簡単に済ませるのか？よし、決闘だ！今日、二時間後に灯台のそばでだ！";
			link.l1 = "「取引成立だ！」";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = "何か知らせはあるか、船長？";
			link.l1 = "お前の言った通りだ、俺もイカサマの疑いをかけられてな、仕方なくあの野郎を決闘で斬り捨ててやったぜ。";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "ほらな？俺は知ってたぜ！俺と仲間たちから礼を言うぜ！さあ、報酬を受け取ってくれ、船長。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_1":
			dialog.text = "俺がここに来たのは、剣術の師範の職に応募するためだって話、したか？してねえか？まあ、 地元の総督が甥っ子のために師範を探しててな、俺にはうってつけなんだ。剣術の基本は知ってるが、 実際にやったことはねえんだよ。\nもうほとんど仕事は決まりかけてたんだが、地元の商人が厄介なことに巻き込まれてるって分かった。なんでも、 いかにも危なそうな悪党に脅されてるらしい。総督は俺の腕前を試すために、この件を片付けろと命じてきたんだ。";
			link.l1 = "ならやれ。さらばだ。";
			link.l1.go = "exit";
			link.l2 = "「で、その悪党は商人に何の用があるんだ？それに、俺に何をさせたいんだ？」";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "俺はあの男を傭兵だと思ってたんだ。傭兵なら、いつだって取引できるもんだろ？昔の借りだとか何だとか……だが、あいつは本気で商人を追い詰めるつもりだった。だから、お前に頼みたかったんだ――商人と俺を助けてくれ、傭兵から救い出して、総督の命令も果たしてくれ\n俺にはこの地位が本当に必要なんだ。自分一人じゃ傭兵をどうにもできねえ。頼む、助けてくれ。貯めた金は全部やる。 それができなきゃ、恥をかいてこの街を出ていくしかないんだ！";
			link.l1 = "わかったよ、手を貸してやるぜ……“剣術の達人”さんよ。";
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;
		
		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
			Scl = 30+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_"+(rand(7)+23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06","blade_10"), RandPhraseSimple("pistol4","pistol6"), "bullet", Scl*3+70);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;
		
		case "AffairOfHonor_CowardFencer_2":
			dialog.text = "何の用だ？俺が忙しいのが見えねえのか！？";
			link.l1 = "「ちゃんとした商人を困らせて、大騒ぎしてるのか！？」";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "ばっ！また用心棒か？毎日護衛を雇うより、俺に払った方が安上がりだぜ。 借金を叩き出す方が殺しの仕事より性に合ってるが、そんなに英雄気取りなら灯台まで来いよ。 そこで一騎打ちで腕を試そうじゃねえか。\nだが、そうじゃねえなら二度と俺に逆らうんじゃねえぞ。";
			link.l1 = "取引成立だ！そこで待ってるぜ。";
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;
		
		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = "どうやらお前は俺よりもっと臆病者みたいだな……";
			link.l1 = "ああ、そうだ。";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "何か知らせはあるか、船長？";
			link.l1 = "傭兵は死んだ。今度こそお前の立場になったんじゃねえか？";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "ああ、船長、ありがとう！報酬を受け取ってくれ、そして俺は総督に報告してくるぜ！";
			link.l1 = "さらばだ……旦那。";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			GiveItem2Character(pchar, "chest"); 
			Log_Info("You have received a chest filled with doubloons");
			PlaySound("interface\important_item.wav");
		break;
		
		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "AffairOfHonor_CoatHonor_2":
			dialog.text = "もう一杯か？";
			link.l1 = "飲み干せ。";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "そして、まだまだあるぜ！";
			link.l1 = "ちょっと待てよ！どこへ急いで行くんだ？";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "質問なんてどうでもいい！飲め！";
			link.l1 = "いいだろう。でも、あとで何があったのか話してくれるか？";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "本当に興味があるのか？じゃあ、俺がまだ話せるうちに聞いてくれ！あと数日もすれば、俺はもう口もきけなくなる……死んじまうからな。そう、死ぬんだ！全部ラム酒のせいだ。飲みすぎたラム、 それに悪魔が俺の頭上に送り込んだらしいこの士官のせいだ！\nもちろん、もし素面だったら、あるいはそこまで酔ってなかったら、 駐屯地でも街でも一番の剣士と戦おうなんて思わなかったさ。でも今さらどうしようもねえ。俺はもうおしまいだ、 破滅だ、死ぬんだ！なんて馬鹿なんだ、俺は……";
			link.l1 = "ああ、確かに愚かなことだったな。だが、これからはもっと賢く振る舞うだろう……もちろん、決闘で生き残れればの話だがな。さらばだ。";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "酔っ払うのも最善の策じゃねえぞ、士官。きっとこの厄介事にも解決策があるはずだ。";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "どんな解決策だ？脱走して名誉と士官の制服を失えってのか？それとも、豚みたいに切り刻まれる前に自殺しろってか？ お前の助言は何だ？";
			link.l1 = "どちらにも味方しない。俺はあんたを助けて、決闘の時まで相手があんたに手出ししないようにしてやる。 そいつはどこにいるんだ？";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "本気か？やってくれるのか！？ああ、絶対に報酬は弾むぜ！\nあいつは街にいるはずだ。愛人がここに住んでいて、全ての士官がその女のことを知ってるが、 残念ながら住所は分からねえ……だから、きっとあいつもそこにいると思うぜ。";
			link.l1 = "もういい。ここで待ってろ。俺があの……「剣の達人」とやらに話をつけてくる。";
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;
		
		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
		break;
		
		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = "俺に何か知らせはあるか、旦那？いい話か、それとも……あまり良くない話か？";
			link.l1 = "まだ知らせはない。ここで待っていろ。すべてうまくいくさ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "俺に何か知らせはあるか、旦那？いい話か、それとも……あまり良くねえのか？";
			link.l1 = "終わったぞ。お前の相手になりそうだった奴はもう誰にも危害を加えられねえ……もう安心だ。だが、この出来事から何かを学んで、知らねえ人間に対して攻撃的にならねえようにしてくれよ。";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "冗談じゃねえだろうな？俺…本当に感謝してるんだ、 "+GetAddress_Form(NPChar)+"！ほら、俺の持ってるものは全部やる。これが俺の給金だ、全部持っていけ！\n教訓だって？ああ、くそっ、あんたの言う通りだ！もう二度とこんなことはしねえ、約束するよ。それと、 もう一度チャンスをくれて本当にありがとう！";
			link.l1 = "そうかい。じゃあな、役人……";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("You have received a purse with doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "「改めて感謝するぜ」 "+GetAddress_Form(NPChar)+"、助けてくれてありがとう！";
			link.l1 = "いつでも歓迎するぜ…";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "おい、なんだと！？俺の女主人の部屋で何してやがるんだ？さっさと出ていけ、 さもないと力ずくで引きずり出してやるぞ！";
			link.l1 = "俺は好きなところを歩くぜ、こんなことでお前を告げ口なんかしねえよ！力ずくで？やれるもんならやってみろ！";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "なんという無礼だ！前代未聞の厚かましさだ！旦那、あなたは大きな勘違いをしている！ 今すぐこの屋敷から出て行きなさい、さもなくば生きてきたことを後悔させてやるぞ！";
			link.l1 = "口だけじゃ意味ねえぞ！後悔するのはお前の方だ、俺じゃねえ。 "+GetAddress_FormToNPC(NPChar)+"! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "本当か？なら気をつけろよ！この屋敷でお前を殺せば、それはただの殺人だ。だからお前が死んでも俺の名誉は汚れねえ。 名誉ある男同士の決着は灯台のそばでつけるもんだ！\n決闘を申し込むぜ。 "+GetAddress_Form(NPChar)+"、この無礼者め！その言葉の責任を取ってもらうぞ！では、二時間後に決闘だな？";
			link.l1 = "「ああ」 "+GetAddress_FormToNPC(NPChar)+" 強気な奴だな。";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "それなら、ちゃんと時間通りに来るんだぜ。まだうちの神父にレクイエムを頼む時間はあるからな。";
			link.l1 = "お前のためにレクイエムだと？一ペソの価値もねえ野郎だ。灯台で会おうぜ！";
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;
		
		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
		break;
		
		case "AffairOfHonor_CoatHonor_9":
			dialog.text = "失せろ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "総督のことを言ってるのか？はっ！俺が文句を言ったら、総督は「神の裁き」だとさ！決闘だとよ！どうだい、こんなの？ 俺はただの静かで平和を愛するプランターであって、盗賊でも戦士でもねえんだ\nこれは決闘じゃなくて殺人だ！それに、あんたの方がこういうことは俺よりずっと得意だろう。だから、 これからの決闘で俺の代理を頼みたいんだ。信じてくれ、必ず恩は返すからよ。";
			link.l1 = "決闘はいつだ？";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "今夜、真夜中前に灯台の近くだ。手を貸してくれるか？";
			link.l1 = "よし、手を貸してやるぜ。町で待ってろよ！";
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;
		
		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05","blade_07"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;
		
		case "AffairOfHonor_GodJudgement_2":
			dialog.text = "そこで何があったんだ？俺たちは……いや、すまない、お前が勝ったのか？";
			link.l1 = "きっと興味があるだろうが、待ち伏せがあったんだ。\nもしかすると、お隣さんは念のために一人だけじゃなく、何人か代表を呼んだのかもしれない。しかも、そいつらは皆、 手練れの盗賊だった。\nだが幸い、俺は剣の腕には自信があるんだ。";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "なんて野郎だ！これで、たぶん我々の総督もあの悪党を逮捕する俺の要請を断る理由はなくなったはずだ！ありがとう！ 報酬を受け取ってくれ、俺はこれから官邸に行かなくちゃならねえ。";
			link.l1 = "さらば。";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("You have received purses of doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		// Диалоги до боя -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = "バグなしで遊ぶのは楽しいぜ、あいつらは見つけるのがやたら難しいからな。";
			link.l1 = "安心しろ、俺が開発者たちに伝えておくぜ。";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "ああ、いたな。こいつらは俺の仲間であり、立会人だ。始めようか？";
					link.l1 = "お任せください！";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "全員集まったぜ。準備はいいか？";
					link.l1 = "ああ、始められるぜ！";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "やっとか！この長い道のりを無駄に歩いたんじゃねえかと思い始めてたぜ…さっさと片付けようぜ、酒場にラム酒と熱い女が俺を待ってるんだ！";
					link.l1 = "もうどちらもお前には必要なくなるはずだぜ！";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "Jackanapes":
					dialog.text = "来ることにしたのか？やっとだな！じゃあ、始めようぜ！";
					link.l1 = "そんなに急ぐなよ、刃物に倒れちまうかもしれねえぞ。";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "「そしてこいつらが俺の副官だ、旦那。さあ、覚悟しろ！」";
					link.l1 = "お先にどうぞ。";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CowardFencer":
					dialog.text = "着いたぞ。剣の用意をしろ、旦那！";
					link.l1 = "喜んでだ、腕の立つ方が勝つといいな！";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CoatHonor":
					dialog.text = "素晴らしい、全員そろったな……始めよう、旦那！";
					link.l1 = "踊ろうぜ！";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "GodJudgement":
					dialog.text = "「お前は誰だ？普通の町人には見えねえな、相棒…」";
					link.l1 = "それで？俺と決闘の約束でもあるのか！？";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1"
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "ははっ！決闘か！どうやらお前が俺たちの依頼人らしいな。野郎ども、こいつを刺してさっさと報酬をもらいに行くぞ。 腹を裂け！";
			link.l1 = "待ち伏せか？情けねえな、こんなんじゃ俺を倒すには全然足りねえぜ…";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;
		
		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if(hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("Seconds will fight");
			}
			// В квесте "Божий суд" всегда нападают.
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("Global massacre");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = hrand(3);
				if(AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for(i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги до боя.
		
		// Диалоги после боя -->
		case "AffairOfHonor_AfterFight_1":
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = "俺たちの仲間を殺して逃げられると思うなよ？武器を取れ！";
				link.l1 = "こんな惨めな野郎にこんなことされるなんて、予想すべきだったぜ！";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "船長、あなたの名誉は回復された、勝利だ。しかし、ひとつ忠告しておこう――しばらくこの町を離れて、顔を見せない方がいいぞ…";
				link.l1 = "「それで、何が問題なんだ？」";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "すべては名誉のためだった、さあ行こう、仲間を迎えに行くぞ。";
				link.l1 = "ああ、止めやしねえよ…";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "問題は、お前が我々の司令官の従卒を殺したことだ。あいつは悪い奴で、誰もその死を惜しまねえ……だが司令官はあいつをとても気に入っていて、友の死を絶対に許さねえだろう。";
			link.l1 = "助言ありがとう、必ず心に留めておくよ。じゃあな。";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;
		
		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				ChangeCharacterComplexReputation(PChar, "nobility", 5);
			}
		break;
		
		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = hrand(3);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for(i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги после боя.
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. He got frightened and run away on his ship" break;
		case 1: sText = "One dishonourable bastard has lost a huge sum to me in gambling and has run away on his ship" break;
		case 2: sText = "One scoundrel has loaned money from me, and when I wasn't at home he has repaid the debt with false coins to my servant. Now he is hiding somewhere on his ship" break;
		case 3: sText = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed and this bastard had run away on his ship " break;
		case 4: sText = "It was my mistake, I have hired some rogue as an accountant. He has committed a great peculation, bought a ship and run away " break;
		case 5: sText = "My ex-guard has stolen a box filled with jewels from my wife's boudoir and run away. Now I see where has he got enough coins to buy a ship " break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. But he got hired as a ship master and sailed away";
			npchar.quest.text1 = " dishonoured a woman and cowardly run away";
		break;
		case 1:
			npchar.quest.text = "One dishonourable bastard had lost a huge sum to me in gambling but he didn't pay me yet, I heard that he got hired as a cannoneer and run away";
			npchar.quest.text1 = "lost all his money in gambling and didn't want to repay the debit ";
		break;
		case 2:
			npchar.quest.text = "One scoundrel has loaned money from me, and when I wasn't at home he had repaid the debt with false coins to my servant. Now he is serving on one ship as quartermaster and hiding from me ";
			npchar.quest.text1 = "counterfeiter who has committed a crime";
		break;
		case 3:
			npchar.quest.text = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed. Luckily for him bastard got hired as a doctor on one ship and run away";
			npchar.quest.text1 = "slanderer and intrigant who has tried to dishonour one good citizen";
		break;
		case 4:
			npchar.quest.text = "It was my mistake, I have hired some rogue as an accountant. He had committed a great peculation and now he is serving on one ship as quartermaster and hiding from me";
			npchar.quest.text1 = "is blamed in peculation and misappropriation";
		break;
		case 5:
			npchar.quest.text = "My ex-guard stole a box filled with jewels from my wife's boudoir and run away. He got hired as an officer for the boarding party on one ship";
			npchar.quest.text1 = "a common thief and his place is in jail. He has stolen jewels from his own employer";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "my old pal, who was my close friend in the Old World";
			npchar.quest.text1 = "he is your old friend";
		break;
		case 1:
			npchar.quest.text = "a man, who basically was my father";
			npchar.quest.text1 = "you were like a father for him";
		break;
		case 2:
			npchar.quest.text = "my stepbrother, who had left the old world in his youth";
			npchar.quest.text1 = "you are his stepbrother";
		break;
		case 3:
			npchar.quest.text = "a man who really helped me in the Old World";
			npchar.quest.text1 = "you have helped him a lot";
		break;
		case 4:
			npchar.quest.text = "my sister's husband who was my friend in the Old World";
			npchar.quest.text1 = "you are his sister's husband";
		break;
		case 5:
			npchar.quest.text = "my friend, my brother in arms in the Old World";
			npchar.quest.text1 = "you were brothers in arms";
		break;
	}
}
