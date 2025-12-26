// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ、」 "+GetSexPhrase("息子よ","娘よ")+"?","何でも聞いてくれ、聞いてるぜ…"),"聞いてやる、今話せ。 "+GetSexPhrase("息子よ","娘よ")+"...","「三度目だが、」 "+GetSexPhrase("息子よ","娘よ")+"、必要なことがあれば言ってくれ。","聖職者にはたくさんの仕事があるんだ、君は俺の邪魔をしているぞ。 "+GetSexPhrase("息子よ","娘よ")+"...","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は違うんだ、神父……"),"申し訳ないが、俺から言うことは何もねえ。","後で聞くぜ。すまねえな、神父さん。","失礼します、神父様……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "神父様、マリサ・カルデラを探しているんだ。彼女はとても信心深くて、よく教会に通っていたと聞いた。 彼女の居場所を教えてもらえないか？";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "マリサは我々の最も信心深い信徒の一人であり、まさに教会の魂だった。彼女の不在は信徒たちにとって大きな損失だ。 なぜ彼女が姿を消したのか、私には分からないが、確信している――彼女は不当な試練に遭い、悪魔とその手先の仕業が絡んでいたに違いない\n時折、町で彼女を見かけたという噂を耳にするが、それ以上のことは分からない。我々にできるのは、主の御心を信じ、 いつの日か彼女が戻り、再び教会の屋根の下で安らぎを得られるよう願うことだけだ。";
			link.l1 = "もしかして、彼女についてもっと詳しく教えてくれる人を知っているか？";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("息子よ","娘よ")+"、教えてくれ、なぜマリサを探しているんだ？時々彼女を訪ねてくる者がいるのは知っているが、 みんなが正しき者の顔をしているわけじゃねえ。この世は誘惑に満ちていて、 彼女を追う者すべてが善意とは限らねえんだ。俺が口を開く前に、 あんたが彼女や彼女に関わる者に害をなすつもりがないと確信しなきゃならねえ。";
			link.l1 = "ご心配はわかります、神父様。しかしご安心ください、悪意はありません。ただ、 彼女に届くまでに時間がかかりすぎた手紙を渡したいだけなのです。もしかしたら、 彼女にとって大事なことが書かれているかもしれません。\nさあ、ご覧ください。";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;

		case "LFD_Church_1_3":
			dialog.text = "ああ、この手紙はお前の手元に届くまでに、幾多の嵐をくぐり抜けてきたようだな。中身が何なのか、 そして読まれた後にどんな結果が待っているのかは誰にも分からん……だが、正当な持ち主に返すとは、船長、お前は立派な行いをしたぜ。今マリサがどこにいるか知っているとすれば、 それは彼女の友人ドロレス・モンホだけだ――マリサが唯一信頼していた相手さ\n彼女の家は港役所の左手にある。どうかこの手紙がマリサにこれ以上の苦しみをもたらさぬことを祈るよ。 彼女はもう十分すぎるほど耐えてきたのだからな。";
			link.l1 = "ありがとうございます、神父様。主があなたを見守ってくださいますように。";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;

		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
