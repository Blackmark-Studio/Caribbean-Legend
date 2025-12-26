// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),"「少し前に俺に質問しようとしたよな」 "+GetAddress_Form(NPChar)+"...","今日一日で、その質問を持ち出すのはこれで三度目だぞ…","「まだ質問があるのか？」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえぜ。"),"うーん、俺の記憶はどこへ行っちまったんだ……","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "「聞け、」 "+npchar.name+"、今日はちょっと変わった用件で来たんだ。サン・ピエールの店で商人の助手として、 湾で静かに穏やかに暮らしたい男を探している。給料も悪くないし、住む場所も用意されている。 誰か心当たりがあれば紹介してもらえないか？";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "俺の船に積み込む予定のワイン樽について話があって来たんだ、グアドループへの配達の件でな…";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "「知ってるか、 "+npchar.name+"「俺の友人を探してるんだ。ここに来るはずだったが、体調が悪かったみたいでな。 もしかしたら仲間が助けてくれたかもしれねえ…」";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "ふむ…ここには船乗りの暮らしを捨てて陸の者になりたがってる連中が何人かいるぜ。手を貸してやってもいいが、 今のうちに言っとくぞ、タダじゃねえからな。";
			link.l1 = "へっ！で、いくら欲しいんだ？";
			link.l1.go = "storehelper_1";
		break;
		
		case "storehelper_1":
			dialog.text = "千枚のエイト金貨だ。あんたがやることは何もねえよ。1時間もすりゃ、仕事を希望する連中が俺の酒場に集まる――何人もな。あんたはそいつらと話して、気に入った奴を選べばいいってわけさ。";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "ああ…わかった、ほら、千枚持ってけ！";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "悪いが、そんな大金は持ってねえんだ！";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "心配すんな、相棒。この金額の半分は候補者から返してもらえるぜ。お前の手数料だって伝えておくからな、へっへっへ……五百以上は出さねえよ。一時間後に俺の酒場に寄ってくれ。その頃にはお前が必要な連中を用意して待たせておくぜ。";
			link.l1 = "「わかった。1時間後に戻るぜ。」 "+npchar.name+".";
			link.l1.go = "storehelper_3";
			npchar.quest.storehelper = "true";
			DelLandQuestMark(npchar);
		break;
		
		case "storehelper_3":
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			Storehelper_hire("");
		break;
		
		case "storehelper_exit":
			dialog.text = "あんたもそんな大金は持ってないんだな、すまねえな。だが自分でもわかってるだろ、こういうことは「ありがとう」 だけじゃ済まねえんだぜ。だからよ……";
			link.l1 = "わかったよ。でも本当に金がねえんだ。じゃあな、またな…";
			link.l1.go = "exit";
			//pchar.quest.storehelper.over = "yes";
			//AddTimeToCurrent(2,0);
			//DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			//CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			DelLandQuestMark(npchar);
			dialog.text = "何を言ってるんだ、相棒？どの酒のことを話してるんだ？";
			link.l1 = "ウォルター・キャッチャーという男に頼まれて来たんだ。\nグアドループまでワインの貨物を運ぶために船が必要で、報酬は一万ペソだと言ってたぜ。\nしかも、この仕事にはまさに俺の船が必要だって話だったが……";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "聞けよ、俺はワインなんざ扱っちゃいねえし、お前の世話にもならねえ。 それにウォルター・キャッチャーなんて知らねえぞ。";
			link.l1 = "なんだと！じゃあ、あのキャッチャーはお前が差し向けたんじゃなかったのか……じゃあ、この茶番は一体なんなんだ？";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "へっ！まあ、これは何かの間違いか悪い冗談か、それとも……";
			link.l1 = "「それともどうする？」";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "自分で考えられねえのか？誰かがお前をル・フランソワに誘い込む必要があったんだろうが、理由までは知らねえ。 俺がお前なら、さっさとここを出て、用心に用心を重ねるぜ。これはきな臭え話だ、相棒…";
			link.l1 = "あんたの言う通りかもな。あのキャッチャーのツラは気に入らなかったし。よし、あんたの助言に従うぜ。じゃあな、 セサール！";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
			
			pchar.quest.NewGameTip4.win_condition.l1 = "location";
			pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.NewGameTip4.function = "ShowNewGameTip";
			pchar.quest.NewGameTip4.text = "Your first sea battle is coming! Save you game!";					  
		break;
		
		case "Portugal":
			dialog.text = "ああ、あんたの友達はここに来たぜ、船長。昨日ここに着いて、二階の部屋を借りたんだ。仲間も一緒にいるぜ、へへ……あそこに座ってる連中さ。声をかけてみな！";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
