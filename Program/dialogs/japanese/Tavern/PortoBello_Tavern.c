// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),"「さっき俺に何か聞こうとしたじゃねえか、」 "+GetAddress_Form(NPChar)+"...","今日一日で、その質問を持ち出すのはこれで三度目だぞ…",
			"また質問かい？","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ああ、本当にこれで三度目だな……",
			"いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "聞けよ、フランソワ・ゴンティエって名の私掠船乗りを見なかったか？最近この町に来てたはずだ。";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "聞いてくれ、商人のハイメ・シリシオって奴を探してるんだが、どこにいるか知らねえか？ あんたに会いに来るはずだったんだが…";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "見てくれ、俺はベルナール・ピネットって男を探してるんだが、聞いたことあるか？つい最近ポルトベロに来たはずだ。 カツラを巻いた威厳のある紳士だ。商人だぜ。ここに来てたかもしれねえ…";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "マリサ・カルデラがどこにいるか教えてくれないか？";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("いや、知らねえな。あいつは酒場にも寄らなかったし、町でも見かけなかったぜ。","そのことはもう聞かれたし、俺はちゃんと答えたぜ。","言っただろ、「そのゴンティエについてはもう聞かれた」ってよ。","聞けよ、さっさとどっか行って俺の邪魔すんじゃねえ！頭がどうかしちまったのか！？","ブロック",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("そうかい、じゃあ俺は引き続き探すぜ。","ふむ、そうかもな……","ああ、そうだ、そのことは俺が頼んだんだ…","「すまねえ、」 "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "勘弁してくれ、旦那、だがそんな話を見知らぬ奴とするのは裏切り者か酔っ払いだけだぜ。揉め事はごめんだ。";
			link.l1 = "酔っ払いだって？またな、相棒。";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "あいつのことなんざ聞いたことねえな、相棒。";
			link.l1 = "あいつはドン・カルロス・デ・ミリヤールの知り合いだぜ。ほんとに聞いたことねえのか？";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "そうだ。もしあいつがド・ミリヤールの友達なら、総督のところへ行ってカルロス旦那を訪ねな。 お前のその商人について教えてくれるぜ。";
			link.l1 = "そうするぜ。助言ありがとな！";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "マリサか？ふむ……しばらく見かけてねえな。旦那の死を知らされてから、町に顔を出さなくなっちまったんだよ。";
			link.l1 = "じゃあ、あの女は未亡人ってわけか？";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Tavern_1_2":
			dialog.text = "ああ。彼女の夫は商用ピナス船『ウェーブリーバー』の船長だったんだ。オランダ西インド会社の許可証のおかげで、 群島のほとんどの港に入港できたらしい。噂じゃ、ベリーズからキャップスターヴィルへ向かう途中で海賊の襲撃に遭い、 生き残れなかったそうだ。こんなことはこの辺じゃ珍しくねえが、彼女にとっては本当に大きな打撃だったんだよ。";
			link.l1 = "「それで、あの女はただ姿を消したのか？」";
			link.l1.go = "LFD_Tavern_1_3";
		break;

		case "LFD_Tavern_1_3":
			dialog.text = "まあ、「消えた」ってのはちょっと大げさかもしれねえな。だが、それ以来あの女は町でほとんど見かけねえんだ。 不思議なことに……時々、あんたみたいな男たちが彼女のことを聞きに来るんだよ、船長。もしあいつがあんなに信心深くなけりゃ……どこかに身を隠して、できることで食ってるんじゃねえかって思うところだがな。でもマリサはな、 旦那が死ぬ前は聖ミサを一度も欠かしたことがねえ――ほとんど教会に住んでたようなもんだ。だから、そんなことはねえと思うぜ。";
			link.l1 = "それだけか？他には何も知らねえのか？";
			link.l1.go = "LFD_Tavern_1_4";
		break;

		case "LFD_Tavern_1_4":
			dialog.text = "俺が知ってることは全部、もう話したぜ、船長。";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;

		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}