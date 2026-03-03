void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "ごきげんよう。あなたが船長か "+GetFullName(pchar)+"?";
			link.l1 = "ああ、俺だよ。それで、どういう用件だ？";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "ジャマイカ総督エドワード・ドイル旦那からの手紙をお持ちしました。";
			link.l1 = "うわっ！こんなの予想してなかったぜ…それで、総督は俺に何の用だ？";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "手紙をお読みください、旦那。要するに、あなたは全諸島を横断するレガッタ、 つまり大規模なレースへの参加に招待されています。あなたの海での腕前や並外れた速さの噂は、 しっかりと広まっています。";
			link.l1 = "信じられない！まあ、俺は……考えてみるぜ。";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "さらに、ポートロイヤル港への自由な出入りも許可する。これは30日間有効の通行許可証だ。これで私の任務は完了だ。さようなら、船長。";
				link.l1 = "ありがとうございます。免許はとてもありがたいです。では、さようなら！";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "よし。これで俺の任務は完了だ。さらばだ、船長。";
				link.l1 = "さらば！";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "ごきげんよう。あなたもレガッタに参加なさるのですか？";
				link.l1 = "まさにその通りです、旦那。私の名は "+GetFullName(pchar)+"。招待状を受け取りました。";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "「何かご用ですか、旦那？」";
				link.l1 = "いや、なんでもねえ。もう行くぜ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "お会いできて嬉しいです、船長 "+GetFullName(pchar)+"。では始めようか。手紙で基本はもう知っているだろう？ラガー船のみ、 しかも艦隊にその船一隻だけでレガッタに参加できるんだ。これらの条件は満たしているか？";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "まだだ。今やって、すぐ戻るぜ。";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "ああ、持っている。";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "レガッタに参加しに来たのか、だが船はどこだ、船長？";
				link.l1 = "失礼します、旦那。すぐに私の船を港に寄せます。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "ああ、またお前か。レガッタの条件をすべて満たしたのか？";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "まだだ。今やって、すぐ戻るぜ。";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "ああ、あるぜ。";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "船長、あなたの船が停泊しているのを確認するまでは話すことは何もない。\nわかったか？それとももう一度言ったほうがいいか？";
					link.l1 = "失礼します、旦那。すぐに私の船を港に着けます。";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "何かご用ですか、旦那？";
				link.l1 = "いや……なんでもねえ。もう行くぜ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "よし。では、次の質問だ。お前の船の名前は何だ？";
			link.l1 = "「」"+pchar.Ship.Name+"「。」";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "レガッタはイギリス当局の主催で、定められた規則により、 イベント期間中はあなたの船の名前を変更しなければなりません。\n心配はいりません、これは全ての参加者に適用されます。";
			link.l1 = "船の名前を変えるのは不吉だって言われてるぜ。";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "レガッタの後で名前を元に戻しても構わないぜ。だから、お前のラガー船は『セント・キャサリン』 という名前を名乗ることになるぞ。";
			link.l1 = "わかりました、旦那。名前を変更します。";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "さて、レガッタそのものについて話そう。よく聞いてくれ。ルールを書いた紙も渡すぞ。\nレガッタはポートロイヤルで始まり、ポートロイヤルで終わる。到達すべきポイントは五つある。\n最初はポートロイヤルからベリーズ、西インディア\n次はベリーズからポルトープランス、イスパニョーラ\n三つ目はポルトープランスからセントジョンズ、アンティグア\n四つ目はセントジョンズからブリッジタウン、バルバドス\n最後はブリッジタウンからポートロイヤルだ\nここまでで分かったか？";
			link.l1 = "「了解だ、旦那。」";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "素晴らしい。次の都市それぞれの港役所で必ず受付を済ませてくれ：ベリーズ、ポルトープランス、セントジョンズ、 ブリッジタウン。このうちどれか一つでも抜かしたり、正しい順番を守らなかった場合は失格だぞ\nレガッタ期間中、役所は二十四時間開いている。扉をノックすれば中に入れてくれる。";
			link.l1 = "承知した。";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "自分の船を変更したり、艦隊に新たな船を加えたりすることは禁止されている。\nこれはどの町でも確認されるから、覚えておけよ。";
			link.l1 = "考えてみるぜ。普段は誰が勝者と見なされるんだ？それと、賞品について話してもいいか？";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "レガッタの勝者はただ一人――最初にポートロイヤルへ到着した船の船長だけだ。賞品は非常に価値がある。勝者には25万ペソもの大金が贈られる。さらに、貴重な贈り物のセットも授与されるぞ。";
			link.l1 = "じゃあ、負けた奴らには何もないのか？";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "その通りだ。それに、イギリス植民地の裕福な市民も貧しい市民も、レガッタの勝者に賭けをするんだ。 お前自身にも賭けられるぜ。たいてい、どの船長も自分に賭けるもんさ。勝てばさらに稼げるし……やる気も出るだろう。普段は俺が賭けを受け付けてるんだ。自分の勝利に賭けるか？";
			link.l1 = "はっ！もちろんだぜ。いくら賭けられるんだ？";
			link.l1.go = "Regata_rate";
			link.l2 = "考えてみるぜ。もしかしたら賭けてみるかもな。";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "考えてみるんだな。レガッタが始まるまで少し時間があるぜ。";
				link.l1 = "いいだろう。いつ始まるんだ？";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "考えてみるんだな。レガッタが始まるまで少し時間があるぜ。";
				link.l1 = "「いいだろう。」";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "三日後の正午、十二時だ。桟橋に来い、遅れるなよ。お前には五人の競争相手がいるぞ。\n"+pchar.questTemp.Regata.AdversaryName.a+"、の "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+"、の "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+"、の "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+"、の "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+"、の "+pchar.questTemp.Regata.AdversaryShipName.e+"\nみんな百戦錬磨の船長たちだ。まあ、どうやらそれだけらしいな。念のため規則書を持っていけ。スタートで会おうぜ！";
			link.l1 = "さようなら、旦那。";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "待て！イギリスとフランスの港に出入りできる30日間の許可証をやる。レガッタは一ヶ月も続かないだろう。どうぞ、受け取ってくれ。";
			link.l1 = "ありがとう！";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "いくら賭けるんだ？";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "まだ少し考える時間が必要だと思う。";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "旦那、これは面白くもなければ冗談でもありません。そんなはした金じゃ働きませんよ。";
				link.l1 = "失礼だが……賭け金をもう一度考え直そうじゃねえか。";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "旦那、レガッタの規則上、そんな賭け金は受け取れません。もっと妥当な額に減らしてください。";
				link.l1 = "残念だな。金額をもう一度考え直そう。";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"？それは立派な賭け金だな。俺は受けるぜ。金はどうした、旦那？";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "どうぞ、受け取ってくれ。";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "今はコインが足りねえんだ。後でまた来て賭けをしようぜ。それに、もう少し考えてみて、 賭け金の額も見直すかもしれねえ。";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "素晴らしい！あとは一番乗りになるだけで、賞品はお前のものだ。その最終的な価値は変動するかもしれねえ。 結局のところ、最後にどれだけの奴が賭けてくれるか次第だぜ。";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "なるほど。レガッタはいつ始まるんだ？";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "なるほど。始まりを待ってるぜ。じゃあな！";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "ああ、また来たな、船長 "+GetFullName(pchar)+"？何の用だ？";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "俺は自分の勝利に賭けたいんだ。";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "いや、なんでもねえ。ただ挨拶したかっただけだ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("船長、これが初めてかい？忠告しておくぜ、気をつけたほうがいい。あんたの競争相手は、 かなり嫌なサプライズを用意してるかもしれねえからな…","船長、俺はお前に賭けたんだぜ。期待を裏切るんじゃねえぞ！","船長、レガッタの港にいる地元の連中が何か売ろうと持ちかけてくるかもしれませんぜ。 たいてい役に立つものだったりします。覚えておくといいですよ。"),LinkRandPhrase("ご無事の航海を、船長！","船長、どうかお気をつけください。カスティーリャ人はスペイン領海を航行する者たちのラガー船をよく狙ってきます。","「レガッタの船長たちには、怪しい連中がよく“サービス”を持ちかけてくると聞いたぜ。そいつらの申し出を受けるかどうかは、お前の判断だ。」"));
			link.l1 = "ああ、ああ、もちろん……ありがとう、まあ一応な。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("船長、私と夫はあなたの勝利に一万賭けました。期待を裏切らないでください！あなたのために祈りますわ！","船長！幸運を祈るぜ！","うーん……あなたは本当に勇敢で勇ましい船長ですね……");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("おい、水夫！あの美人に手を振れよ！お前の帰りを待ってるぜ！","おい、塩っ気のある船乗り！奥様が、レガッタの勝者には私を賞品としてタダでくれるって言ってたよ……頑張って勝ってよ、あなた本当に素敵なんだから！","戻ってきたら、忘れずにまた来てね、イケメンさん。最高のおもてなしで楽しませてあげるわよ！");
			link.l1 = "ふん、はは……考えておくぜ、ありがとう！";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "船長、レガッタは十二時に始まるぜ。今は休んでくれ、俺たちは祝祭の準備をしているんだ。\n正午に戻ってきてくれよ、他の競争相手も同じようにするはずだ。";
				link.l1 = "承知しました、旦那！始まりをお待ちしております…";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "お待たせしました、船長。";
				link.l1 = "俺と船員たちは準備万端だ、旦那！合図を待ってるぜ…";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "さて、諸君、ここに集まったな。これよりレガッタを開始する。ルールは知っているだろう。 一番最初にここへ戻ってきた者が勝者と称えられる。皆さん、勇敢な船長たちに幸運を祈ろう！\n諸君！準備はいいか？よし！位置について！スタート！";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("The regatta has started! Get aboard! Head to Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "ごきげんよう、船長！カリブのレガッタに参加されると伺いました。";
			link.l1 = "本当だ。噂は本当に風よりも早く諸島中に広まるんだな。";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "そうだぜ、船長。お前さんに提案があるんだ。お前さんの船とレガッタに関することだ。";
			link.l1 = "へっ！面白いな。話を聞いてやるぜ、旦那。";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "ラガー用の完璧な帆があるぜ、最高級の綿で作られてるんだ。この帆を使えばお前の船の加速が上がって、 相手よりも時間で有利になるぜ\nもし欲しいなら、俺はこれをお前に売る用意があるが、どうする？";
			link.l1 = "「この帆はいくらで売ってくれるんだ？」";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "たったの15,000ペソだ。この状況にしては、かなり控えめな値段だと認めざるを得ないだろう。";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "同感だ。俺のラガー船用にこの新しい帆を買うつもりだ。ほら、代金だ、旦那。俺が宿にチェックインしている間に、 船まで届けてくれないか。";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "そんな金は持ってねえ。だからお前の帆は買えねえんだ。";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "承知しました、旦那。俺の部下たちは合図を待っているだけですし、きっと後悔はさせませんぜ。\nそれに、この帆は青くてきれいに染まってますからな。あんたの美人もきっと気に入るはずですぜ。";
			link.l1 = "よし、じゃあな！俺は行くから、お前は帆を頼むぞ。";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "残念だな。まあ、それがお前の選択だ。さらばだ、船長。";
			link.l1 = "じゃあな！";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "やあ、船長 "+GetFullName(pchar)+"…あなたと話がしたいんだ……いや、実は……商談の提案さ。";
			link.l1 = "ふむ。面白いな、どうして俺が誰か知ってるんだ？";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "何と言えばいいかな、昔から才能があるって言われてたんだよ…ははっ、さて、レガッタは真っ盛りだし、あんたも参加してるし、有名な船長じゃねえか！";
			link.l1 = "なるほど。さて、言いたいことを言え。";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "お前の前にもう一人参加者がいることは承知している― "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" の "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+"。彼はつい最近港を出て、まもなくゴナイーブ岬を通過するだろう。";
			}
			else
			{
				dialog.text = "俺たちはお前のすぐ後ろにもう一人参加者がいることを知ってるぜ― "+pchar.questTemp.Regata.AdversaryName.b+" の "+pchar.questTemp.Regata.AdversaryShipName.b+"。数時間後にはここに来るだろう。";
			}
			link.l1 = "ふむ……ずいぶん詳しいじゃねえか。";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "letting you pass ahead of him and take his position";
			else sTemp = "therefore you will be taking a lead for a long time";
			dialog.text = "もちろんだ。じゃあ、本題に入ろうぜ。俺たちはお前の金と引き換えに手を貸す。 うちの船から持ち出した大砲四門をゴナイーブ湾の岬の裏手に設置してある。 どんなレガッタの船もそこを回らなきゃならねえ\n大砲にはチェーンショットを装填してある。もし取引成立なら、砲撃仲間にお前のライバルの帆をぶっ壊すよう伝える。 そうすりゃ、奴は修理に時間を食って遅れるってわけだ。 "+sTemp+".";
			link.l1 = "この仕事にいくら欲しいんだ？";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "いいや。そんな手は使わないぜ。俺のことを誤解してたな。さらばだ、旦那方。";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "さて、船長、選ぶのはあんただ。じゃあな。";
			link.l1 = "岬についての情報、ありがとう。そこからは距離を取るようにするぜ。";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "あまりない。たった "+iTemp+" ペソだ。それに、お前の競争相手の一人は……事故のせいでほぼ二日も遅れることになるぜ、ははっ！";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "へっ！話がわかるじゃねえか、相棒！金は俺が払う。だが、お前がちゃんと仕事をする保証はあるのか？それに、 俺が岬を通るときにお前が俺の船に砲撃しないって保証もな。";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "そんな金は持ってねえ。だからあんたのサービスは利用できねえな。";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "船長、どうか、俺たちは密輸業者であって、海賊じゃねえんだ。俺たちはみんな、それぞれのやり方で正直者さ……。あんたも俺たちの世話になったことがあるだろ？俺の言葉に偽りはねえ。信じてくれていいぜ。";
			link.l1 = "わかった、いいだろう、金を受け取れ。";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "この取引には満足してもらえるはずだぜ、船長。すぐに砲手たちにも知らせておく。幸運を祈るぜ！";
			link.l1 = "「そちらも同じく…」";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "ごきげんよう、息子よ。ご挨拶申し上げ、謹んでお尋ねいたします――あなたはイングランドと偉大なる主への忠実なる僕として、教区の財政にご寄付いただけませんか？";
			link.l1 = "神父様、人は魂に呼ばれて慈善を行うものであって、強制されてやるものではありません。\nこの諸島の皆がレガッタの船長たちを狙って盗みを働くと決めたんじゃないかと、俺は思い始めています……";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "もちろんです、神父様。いくらあれば十分でしょうか？";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "あなたのご希望とご都合の許す範囲でいいのですよ、息子よ。たとえわずかな額でも、我々の教区は感謝いたします。";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "それは間違った態度だ、息子よ。誰しも罪を持っている、自分の魂を忘れるな。 やがて我らの創造主の前に立たねばならん……それも、もしかしたら近いうちにな。";
				link.l1 = "説教なんかいらねえよ、神父さん。じゃあな。";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "私たちの教区と私は、このささやかな贈り物に感謝いたします。";
				link.l1 = "どういたしまして、神父様。";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "私たちの教区と私はこの贈り物に感謝します。\nそして息子よ、あなたに警告しておきたい。何人かの罪深い男たちがあなたに危害を加えようと企んでいるのだ。\n海では気をつけなさい！";
				link.l1 = "神父、毎日誰かが俺に陰謀を企てているんだ……。でも、俺の身を案じてくれてありがとうよ。";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "この貴重な贈り物に、我が教区を代表して感謝いたします。そのお返しとして、あなたに警告したいことがあります。 実に邪悪な者たちがあなたに対して陰謀を企てているのです。これらの不届きな背教者どもが、 まさにこの港であなたの船を沈めようとしていると聞きました。\n彼らはすでに火薬を満載した船を、この悪事のために用意しています。気をつけなさい、息子よ、 あの迷える魂たちは本気で邪悪な企みを実行しようとしている……神のご加護を！";
				link.l1 = "ありがとうございます、神父様。気をつけます。";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "あなたはとても寛大だな、息子よ。神のしもべとしての慎み深さゆえ、 教会のためにあなたが差し出そうとしている全額を受け取るわけにはいかない。1万ペソだけ頂こう。\nその代わり、あなたに警告しておきたい。邪悪な者たちがあなたに対して陰謀を企てているのだ。 あの卑劣な背教者どもは、この港であなたの船を沈めるつもりらしいと聞いた。\nやつらは火薬を満載したラガー船を用意し、その名は『"+pchar.questTemp.Regata.BranderName+"「彼女はイギリスの旗の下で航行しているのは、お前に疑いを抱かせずに近づくためだ。気をつけなさい、息子よ、 あの迷える魂たちは邪悪な企みに本気なのだぞ。\nやつらを滅ぼしなさい、この罪については赦しを与える。神のご加護を！お前のために祈ろう、息子よ。」";
				link.l1 = "ありがとうございます、神父様。もしこいつらが悪さをしやがったら、俺が地獄に叩き落としてやるぜ！";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "怒らないでおくれ、息子よ。怒りは罪だ。施しをしないのもお前の権利だ。安らかに歩みなさい、息子よ。";
			link.l1 = "さらばだ、神父様。";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "ごきげんよう、船長！私の名は "+npchar.name+" …そして俺は……";
			link.l1 = "…俺に何か差し出すつもりか…そうだろう、お嬢ちゃん？";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "もちろんだよ、船長！それに、なんでそんなに驚いてるんだ？あんたはイケメンの水夫で、 レガッタにも参加してるんだぜ。だからみんな、役立つ海の品を喜んで売ってくれるのさ。";
			link.l1 = "わかったよ、美人さん、確かに一理あるな。で、俺に何があるんだ？";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "ほら、見てくれ。これは親父から受け継いだものだ。親父もお前と同じく船乗りでな、 航海用の道具をたくさん持っていたんだ。俺には必要ないが、お前にはきっと役立つはずだ。俺が頼みたいのはただ一つ\n "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" そのためにな。";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "ほう、ほう……"+sTemp+"！面白いじゃねえか！おい、俺が買ってやるよ。お前のきれいな目のためにな。で、欲しいのは "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" それのために？どうぞ、お金を受け取ってくれ。";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "ふむ……"+sTemp+"？いや、娘さん、悪いが俺には必要ねえんだ。もう自分の上等な望遠鏡を持ってるからな。だから……残念だが！";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "ありがとうございます、船長。役に立つことを願っています。お役に立てて嬉しいです。レガッタでのご健闘を祈ります！ ";
			link.l1 = "ありがとうございます。 "+npchar.name+"！さらばだ。";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "残念だな、船長。お前の役に立つと思ってたんだが。まあ、他の誰かに売ってみるさ。じゃあな！";
			link.l1 = "「さようなら」 "+npchar.name+".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "ごきげんよう、船長。お前さん、レガッタの参加者じゃねえか？俺の言う通りだろう？";
			link.l1 = "ああ。で、どういう話だ、役人？";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "すでにご存知かと思いますが、我々の植民地はスペイン軍の包囲下にあります。\nそのため、総督があなたとお話ししたいと望んでおります。\nどうか総督のもとへお越しいただけませんか？非常に急を要する件です。";
			link.l1 = "ふむ……わかった、すぐに閣下のもとへ行こう。ただ、俺がどうやって軍事作戦に関わることになるのか、正直よくわからないが。 ";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "お前も関わってるんだ、船長。時間を無駄にせず屋敷へ向かおう。ついて来い。";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "旦那！民間人をあなたの船に送り出す準備ができました。今すぐ行きますか？";
			link.l1 = "ああ、もちろんだ。すぐに出航するぞ。皆にロングボートに乗り込むよう伝えろ。";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "やったな……どうやらこのスループは艦隊の偵察船で、こいつらカスティーリャの野郎どもがうろついてやがったんだ。\n船長、頼む、女たちを洞窟まで連れて行くのを手伝ってくれ。まだ他にもスペインの部隊がいるかもしれねえ。";
			link.l1 = "よし、行くぞ！";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "助けてくれて感謝するぜ、船長！あんたとその勇気がなけりゃ……本物の英雄だよ。自分の利益や危険を顧みず、この作戦をやり遂げてくれた。どうやって報いるか考えてたんだが……レガッタであんたの勝算を上げる方法があるんだ。";
			link.l1 = "面白いな。それで、その方法とは何だ？";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "ごきげんよう、船長 "+GetFullName(pchar)+"。来てくれてよかった。私たちの町はあなたの助けを必要としているんだ。";
			link.l1 = "旦那、もし今まさにあなたの植民地を襲撃しているスペイン艦隊のことを言っているなら、俺にどう助けろっていうんだ。 俺が指揮してるのはラガー船であって、戦列艦じゃねえんだよ…";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "俺の話を聞いてくれ、船長、そうすれば分かるはずだ。俺たちは深刻な危機に陥っている。 街はスペイン軍に包囲されているんだ。砦を巡る決戦が今にも始まろうとしている。それに、 すでに数百人のスペイン兵が上陸して、街からの全ての出口を封鎖した； 今や奴らは海と陸の両方から俺たちを攻撃できる状況だ\n砦の守備隊は艦隊から街を守る準備をしているが、入植地自体には兵士が足りない。 武器を扱える男は全員動員されているが、他の者たちはどうなる？\nブリッジタウンには百人の女たちがいる。もし俺たちがこの植民地を守れなかったら、 彼女たちがどうなるか想像できるか？お前なら分かってくれると信じている。";
			link.l1 = "旦那、あなたのお気持ちは分かりますが、改めてお聞きします、どうお手伝いすればいいのでしょうか？\n私に何を望んでいるんです？戦列艦と戦えと？それとも俺の船員を町の民兵に加えろと？";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "You are English , help us to save English citizens and what is important - women!" break;
				case FRANCE: sTemp = "You are French, so you basically are our ally, help us to save English citizens and what is more important - women!" break;
				case SPAIN: sTemp = "I know that you are Spanish and these are your people in the sea, so I know that I am already asking for a lot, but these women are innocent and have nothing to do with this battle. So please I beg of you, help them!" break;
				case HOLLAND: sTemp = "I know that you are Dutch and our nations are at war, but you are participating in the English regatta under the English flag. Don't you think that it is right to fight for innocent and peaceful people, for women? Please captain, help them!" break;
			}
			dialog.text = "どちらでもない。俺が頼みたいのはただ一つだ。女や子供たちをお前の船でここから連れ出してくれ。人数は多くない、 百人ほどだ。マホニー中尉と一緒にハリソン岬まで連れて行ってくれ。彼が洞窟で安全を確保してくれるだろう\nスペイン人が彼らを捜すことはないはずだ。俺にはもう使える船がない。 持っていたものはすべてスペイン艦隊に沈められた。お前が最後の望みだ。船は満載になるが、 一度の航海で岬まで運べるはずだ。戦列艦が追ってくることもない\n他の誰にも頼めないんだ。 "+sTemp+"";
			link.l1 = "旦那、申し訳ありませんが、俺の船はすでに積載量を超えていて、 二往復してもそんなに多くの人を乗せることはできません。近くに砲弾が一発でも落ちれば、 俺の船もあなたの女たちも海の底行きです。どうかご容赦ください、お力にはなれません。";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "承知した、旦那。お手伝いしよう。水夫の誇りが俺にそうさせるんだ。";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "同意してくれて嬉しいよ。君は本物の兵士だ。マホニー中尉が女性と子供たちを君の船まで連れて行く。幸運を祈る、 船長！";
			link.l1 = "ありがとうございます、旦那。時間を無駄にしないようにしようぜ！";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "急げよ、船長。時間がなくなってきてるぜ。";
			link.l1 = "もう航海に出てるぜ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "信じられないな。お前は挑戦すらしないのか？まあ、それもお前の権利だ。俺がお前に何かを強制することはできねえ。 もしお前がただの船長だったら、百人の女たちのために船を没収してやるところだが、今はレガッタに参加しているから、 イングランド植民地の総督の庇護下にあるわけだ\nお前の良心が勝ることを期待していたが、俺の間違いだった。行け、そして神がその魂を憐れんでくださるように！";
			link.l1 = "さらばだ、旦那。";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "スペイン人どもに気付かれた！\n神よ、助けてくれ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "マホニー中尉は死んだ……これは悪夢に違いない。彼は勇敢な士官だった。船長、どうか私たちを洞窟まで連れて行ってくれませんか？ そこまで連れて行ってくれれば、あとは自分たちで何とかします。";
			link.l1 = "ああ、ついて来い！";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "ここまで来ましたね…ありがとうございます、船長！あなたは私たち全員を救ってくれました！どうお礼をすればいいか考えていたのですが…レガッタで勝つための秘訣を教える方法があります。";
			link.l1 = "続けろ。";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "ポートロイヤルへ向かうのか？最短ルートはキュラソーを通る道だ。ブリッジタウンへ戻れ。 ウッドロウ・ドハーティという名の男を探せ。彼は古い船乗りで、経験豊富な航海士だ。 バルバドスとジャマイカの間の海域を完璧に知り尽くしているから、お前にとって大きな助けになるだろう\nこれで勝利に必要な貴重な時間を大いに節約できるはずだ。地元の教会でその男を見つけて、こう伝えるんだ "+GetFullName(npchar)+" - お前を寄越したのなら、あいつはお前を追い返したりしねえさ。あいつをポートロイヤルまで連れていけ、 どうせそこへ向かうつもりだったんだろう。";
			link.l1 = "よし！腕のいい航海士は俺にとって役に立つぜ。じゃあな。";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "さらばだ、船長！幸運を祈るぜ！";
			link.l1 = "また会うこともあるかもしれねえな……";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "ごきげんよう。何かご用ですか？";
			link.l1 = "お前の名前はウッドロウ・ドハーティで合ってるか？";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "おっしゃる通りです。どうお役に立てますか？";
			link.l1 = "お前が熟練の航海士で、バルバドスとキュラソーの間の海域をよく知っていることは知っている。\nそれに、ポートロイヤルへ行きたいと思っていることもな。\n俺はレガッタの参加者で、最後の寄港地がポートロイヤルなんだ。\nこの最終航海の航海士として、俺の船員に加わってほしいんだ。";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "面白いな……それで、俺がどうしてお前の船員になると思ったんだ？";
			link.l1 = "「いや、お前のことを聞いたからだ」 "+pchar.questTemp.Regata.Name+" 断る理由がないほどの保証付きだ。\nそれに、この危機的な時にブリッジタウンを助けた俺の働きもあってな……";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "From "+pchar.questTemp.Regata.Name+"？なるほど、わかったぜ。よし、船長、ポートロイヤルまで最短航路で案内してやる。今すぐ出航するのか？";
				link.l1 = "「ああ。」";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"？そうか。しかし、船長、こんな危険な時期に俺は自分の街を離れるわけにはいかねえんだ。 無償で助けてくれた兵士として、俺の気持ちも分かってくれ\nスペインとの最後の戦いを前に、ウッドローの爺さんが逃げ出したなんて陰口を叩かれたくねえ。俺はここに残る。 恨みっこなしだぜ、船長。";
				link.l1 = "「それがあなたの最後の言葉か？しかし、俺はあんたの植民地を助けたんだぜ…」";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "それじゃあ、時間を無駄にしないようにしよう。荷物をまとめたら、すぐにあなたの指示に従うよ。";
			link.l1 = "俺の水夫たちが埠頭で待っていて、「セント・キャサリン号」まで案内してくれるぜ。ありがとう、ウッドロー！";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "船長、レガッタはスポーツだが、スペイン軍による我が家への包囲は生死に関わる問題だ。俺はお前とどこにも行かない。 そしてもう一度言うが、俺の言うことを理解してくれ――この世界では、名誉と義務はまだ意味を持っている。これが俺の最終的な言葉だ、もう変えるつもりはない。ただし、 最も安全なルートで素早くそこへ行く方法について助言はできる。北西に向かってドミニカへ航海し、 そこからマルティニークかグアドループへ向かうといい、あとはお前と風次第だ。 それから直接ポートロイヤルへ向かうか、キュラソーを経由してもいい――俺はおすすめしないが、もしオランダ人と良好な関係なら、ぜひそうしてくれ。";
			link.l1 = "まあ、ありがとう……だが、がっかりしたぜ。さらばだ、ウッドロウ。";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "お前はレガッタの最後の段階で規則を破った。その結果は失格だ。もう言うことはない、船長。";
				link.l1 = "えっ…なんだと！まあ、しょうがねえな、お前が用心深すぎたんだ。じゃあな！";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Captain "+GetFullName(pchar)+"、おめでとう！かかったのは "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" 君がレガッタを終えるまでの残り時間で、すべての相手をはるか後方に置き去りにしたな。これは素晴らしい結果だ！";
					link.l1 = "ご親切なお言葉、ありがとうございます、旦那！";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "船長、残念だが、結果は最悪だぜ、お前は使い果たした "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" 時間だ。落ち込むなよ、お前の相手は本当に手強かったんだからな。";
						link.l1 = "俺は悲しくねえよ、旦那。レガッタに参加して自分の腕を試せて嬉しいんだ。";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "船長、あなたは今 "+n+"第十位。見事な結果だ、おめでとう。立派なタイムを見せてくれたな― "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" 時間だ。損失があったにもかかわらず、おめでとう！";
						link.l1 = "大丈夫です、旦那。こんな厳しい競争の中で良い結果を出せて嬉しいです。";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "旦那、ちょっと聞きたいんだが――船はどこにあるんだ？見当たらねえぞ…";
			link.l1 = "申し訳ありません、旦那。すぐに彼女を港へ連れて行きます。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Come and see me in my office. I will give you your prize for your stake.";
			else sTemp = "And if you had made a stake on your victory as I offered you to, you would have gotten an extra prize too.";
			dialog.text = "明日総督のところへ行けば、25万ペソと貴重な贈り物をもらえるぞ。 "+sTemp+" 町を離れるな。伝統によれば、勝者が一週間以内に賞品を受け取らなければ、 それらは町の財務官に渡されることになっている。";
			link.l1 = "分かりました、旦那。明日彼のところへ伺います！";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "名誉ある返答を聞けて嬉しいぜ。幸運を祈る、船長！";
			link.l1 = "さらばだ、旦那。";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "他にご用ですか、船長？";
			link.l1 = "いや……なんでもない。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "ああ、そこにいたのか、旦那 "+GetFullName(pchar)+"。会えて嬉しいぜ。賞品を受け取りに来たのか？もう用意できてるぜ。";
			link.l1 = "それは良い知らせだな！俺の追加の報酬はどれくらいの額なんだ？";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "すべての賭けを考慮すると、あなたの最終的な賞品は "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+"。どうぞ、お受け取りください。おめでとうございます！";
			link.l1 = "ありがとう！";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "もちろん、ポートロイヤル市民の間でのあなたの評判は高まっている。\nそれは自分でも感じているだろう……だが、残念ながら人々の記憶は短いものだ。\nだから、今のうちにその輝かしい栄光を存分に味わっておくんだぜ！";
			link.l1 = "最高のことを語っているな、旦那……さて、栄光に浸るのがどんなものか見せてもらおう。\nさらばだ！楽しかったぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "おめでとうございます、船長！素晴らしい結果だ！";
						link.l1 = "ありがとう！";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "落ち込むなよ、船長。レガッタで勝つのは簡単じゃねえし、参加できるだけでも名誉なことだぜ！";
						link.l1 = "俺のことは心配するな。自分の結果には満足してるぜ。";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "会えて嬉しいぜ、船長！スティーブンソン旦那に話して自分を登録したほうがいいぞ。";
					link.l1 = "なるほど。これから彼のところへ向かうぞ！";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "ああ、船長、どうしてそんな失敗をしたんだ、しかも最後の段階で！";
				link.l1 = "「ああ、俺もなんて間抜けなんだ……」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "おめでとうございます、船長！素晴らしい結果だ！";
						link.l1 = "ありがとう！";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "落ち込むなよ、船長。レガッタで勝つのは簡単じゃねえぜ。参加できるだけでも名誉なことさ！";
						link.l1 = "俺のことは心配するな。自分の結果には満足してるぜ。";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "会えて嬉しいぜ、船長！スティーブンソン旦那に話して自分を登録したほうがいいぞ。";
					link.l1 = "なるほど。今すぐ向かうぜ！";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "ああ、船長、なぜそんなふうに失敗したんだ、しかも最後の段階で！";
				link.l1 = "ああ、本当に俺はバカだったな……";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "おめでとうございます、船長！素晴らしい結果だぜ！";
						link.l1 = "ありがとう！";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "落ち込むなよ、船長。レガッタで勝つのは簡単じゃねえし、参加できるだけでも名誉なことだぜ！";
						link.l1 = "俺のことは気にするな。自分の結果には満足してるぜ。";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "会えて嬉しいぜ、船長！スティーブンソン旦那に話して自分の登録を済ませるんだな。";
					link.l1 = "なるほど。これから向かうぜ！";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "ああ、船長、どうしてそんな失敗をしたんだ、しかも最後の段階で！";
				link.l1 = "「ああ、俺もなんて間抜けなんだ……」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}
