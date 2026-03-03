// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","どうされましたか？お手伝いできることはありますか？"),"少し前に俺に質問しようとしたよな……","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえな。","質問が多いな。俺の仕事は船を造ることだぜ。さっさとそれを片付けよう。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ふむ、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "ガイウス・マルシェを探しているんだ。最後に聞いた話じゃ、奴は自分のガレオン船『サンタ・マルガリータ』 をお前のところで修理するために寄港したってことだったが…";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "自分のガレオン船だと？はは、いい冗談だな、船長。 ガイウス・マルシェは半分沈みかけたスループしか持ってなかったんだ…私掠船になると決めてから、賞品としてガレオン船を手に入れたのさ。運のいい奴だよ、 初めての襲撃であんな戦利品とはな\n俺はその船にいい金を出すと申し出たが、奴は断ったんだ、信じられるか？その代わりに、 みすぼらしいスループを安値で売って、その金でガレオン船を修理したんだ！新しい帆、新しい塗装、そして新しい名前――普通は縁起が悪いもんだがな\nまあ、名前はやけにカトリック臭かったが、俺の娘もマルガリータって名だから、結局は問題なかったよ…奴はもう暴力はたくさんだと言って、商人になるつもりだと話してた。そして、運にも恵まれてな…";
			link.l1 = "商売か、まあ楽だろうが、パピストのガレオンがスループに拿捕されるなんて普通はねえぜ。で、 あいつの船の新しい名前は何になったんだ？";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "「見事」……そりゃそうだ！あいつはまるで花嫁を追いかけるみたいに新しいガレオンの周りを走り回って、 ずっと惚れ惚れしてやがったからな。";
			link.l1 = "なるほど。ガイウスは今トルトゥーガにいるのか？";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "いいや。あいつは新しい船で出航して、まだトルトゥーガには戻ってきてねえんだ。どこへ向かったのかも知らねえから、 この件は手伝えねえよ。";
			link.l1 = "なんて迷惑な……本当にあいつが必要なんだ。あいつの“立派な”船に乾杯でもしたいくらいだぜ。ともかく、情報をありがとう。";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "ああ、問題ないぜ。また寄ってくれよ、船長。修理が必要なら、いつでもお前の船のための泊地はここにあるからな！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
