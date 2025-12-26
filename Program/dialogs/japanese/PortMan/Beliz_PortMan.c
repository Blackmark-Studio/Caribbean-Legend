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
				link.l1 = "その通りだ、旦那。規則に従ってここで登録しなきゃならねえんだ。";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしたじゃねえか "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の同じ質問だな……","港の用件について何も話すことがないなら、くだらない質問で俺を煩わせるな。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","確かに、もう三度目だな……","悪いが、今は港のことには興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "誰かがお前の命を狙ったって噂だが、犯人を追っているのか？";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "あなたの命を狙った男は倒れました、旦那。 "+npchar.lastname+"。もう何もお前を脅かすものはない。";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
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
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "ふむ……お前はレガッタの規則を破ったから、俺は失格にせざるを得ない。すまないな。次の航海には参加できないぞ。 すでにポートロイヤルへの通達も用意してある。";
			link.l1 = "おっと……残念だな！だが、ここでは俺にできることは何もねえ。お前が用心深すぎたんだ。じゃあな！";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "登録しよう：船長 "+GetFullName(pchar)+"、船は "+pchar.Ship.Name+"…レガッタの所要時間（時間単位）は "+sti(pchar.questTemp.Regata.FirstTransitionTime)+"。完了しました、結果は記録されましたので、どうぞお進みください。";
			link.l1 = "俺の階級を教えてくれ。";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "ここにいるのにお前の船が見当たらねえ。どこにあるんだ？";
			link.l1 = "申し訳ありません、旦那。すぐに私の船を港へ移します。";
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
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "君が先頭だ。おめでとう！この調子でいけよ！";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "お前が最後だ。急いだほうがいいぞ。";
				link.l1 = "今向かっているぞ！";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "お前は二番手だ。リーダーは "+sName+" 船の上で "+sShip+"。まだあいつから逃げ切れるだろう。";
					link.l1 = "ありがとう！やってみるぜ！";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "あなたの階級は "+n+"。あなたの最も近い対戦相手は "+sName+" 船の上で "+sShip+".";
					link.l1 = "ありがとう！";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "俺の命を狙ったのは事実だ、それは間違いねえ。\nだが、捜索ってわけじゃねえんだ。俺が欲しいのは逃亡者を捕まえることじゃねえ――奴の首だ。\nそれだけが、俺に安らぎをもたらすんだ。";
			Link.l1 = "お前を襲ったのが誰で、なぜなのか心当たりはあるか？";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "俺…俺はあいつが誰なのか知らねえ！どこから来たのかも、なぜ俺を襲ったのかも分からねえ。だが一つだけはっきりしてる――あいつは俺を殺すつもりだった。そして今…今の俺は、あいつの死を同じくらい激しく望んでるんだ！分かるか？\nだからくだらねえ質問はやめてくれ。お前の好奇心なんざ俺にはどうでもいい――今必要なのは行動だけだ。あいつの首には二百ドゥブロン払う。それが俺の条件だ。狩りを始めろ、 さもなきゃこれ以上俺の時間を無駄にするな。";
			Link.l1 = "恐れや怒りで頭が混乱しているのは分かるし、その口調も大目に見てやる。だが、しっかりしろ。 お前の問題を解決しようとする志願者が列をなしているわけじゃねえんだ、だから少し落ち着け。 二百ドゥブロンなら悪くねえ。だが、その仕事を引き受ける前に、全部詳しく聞かせてもらうぜ。";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "お前の言葉はただの戯言だし、手がかりもない。\nジャングルで正体もわからん奴を探すなんて、干し草の山から針を探すようなもんだ。\n無駄な捜索に俺の時間は使わねえ。\n幸運を祈るぜ。きっと必要になるだろうよ。";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "うう……許してくれ、 "+GetAddress_Form(NPChar)+"……神経がすり減っているんだ……一体何を知りたいんだ？";
			Link.l1 = "彼を特定できるような特徴に気づいたか？一人だったのか、それとももっと力のある者が後ろ盾についていたのか？ 詳しく話してくれればくれるほど、早く安心して眠れるようになるぞ。";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "「敵だと！？俺には敵なんていない！今までも一度もなかった！真っ昼間の通りで殺されるような覚えは何もないんだ\nあの悪党め…ただの卑屈な狂人さ、こういう植民地の町にはどこにでもいる連中だ\n居場所については…あいつはジャングルに隠れていると思う。あの呪われた森じゃ姿を消すのも簡単だが、 きっと洞窟や入り江に向かうはずだ――そっちの方が隠れやすいからな\n見た目については、顔はスカーフで覆われていて、頭には帽子、そして国王陛下の護衛よりも多くの武器を持っていた。 他に気づける暇なんてなかったよ。」";
			Link.l1 = "まあ、大した額じゃねえが、捜索を始めるには十分だ。すぐに出発するぜ。金はしっかり持ってろよ——すぐ戻ってくるからな。";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_5");
		break;
		
		case "GS_Portman_6":
			dialog.text = "「素晴らしい」 "+GetFullName(pchar)+"！なんと見事だ！お前の腕前は他の追随を許さねえぜ。ここに褒美として二百ドゥブロンをやる。さあ、受け取ってくれ！ ";
			Link.l1 = "感謝する！だが教えてくれ、お前の以前の依頼人の誰かが殺し屋を雇ったと疑う理由があるのか？";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "以前の依頼人だと？…馬鹿なことを言うな！…私は正直者だ、これまでの取引もすべて公明正大だ！だが、君が助けてくれたからには、少し話そう。つい最近、 海賊どもが私のもとにやって来たのだ\n商船の情報を金で買おうと持ちかけてきた。私は断ったが、奴らは脅しと呪いの言葉を浴びせて出ていった。 あの暗殺者も奴らの仕業だろう。奴らは「ノー」と言われるのが気に食わんのだ。";
			Link.l1 = "その場合は、自分の身を大事にしろよ。あの“海賊”どもが、あと何人の雇われ剣士を送り込んでくるかわからねえからな。\nそれじゃ、俺はこれで失礼する。務めがあるんでな。";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "待ってください、船長。もう一度お礼を言わせてください。金以上のものを、あなたは私の信頼を得ました。 私がこの港の責任者でいる限り、あなたの船はどれでも、どれだけ長く停泊しても、五割引で預かります。どうですか？";
			Link.l1 = "なんと寛大な申し出だ！改めて感謝するぜ！";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "改めてご尽力に感謝いたします。大切なことに集中し続ければ、 今日のようにあなたの事業はこれからも繁栄し続けると確信しております。ごきげんよう、船長。";
			Link.l1 = "さようなら。";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_10");
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
