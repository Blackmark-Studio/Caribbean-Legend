// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "話せ、聞いているぞ";
			link.l1 = "俺の勘違いだった。さらばだ。";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "「トルトゥーガへの訪問目的は何だ、船長？」";
			link.l1 = "頼む！俺の仲間を助けてくれ、そしたらお前の質問には全部答える！";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "あんたはそんなに偉い人なのに、銃声が監獄中に響いた直後、護衛も連れずにここへ来たのか！？";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "お前が返事を渋っている間に、あいつは血を流して死にかけてるんだ。もう一度聞くぞ。";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "何が起きたかは十分に知っている。もう一度質問するぞ。";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "最後のチャンスだぞ、船長。";
			link.l1 = "総督から任された任務を遂行しているんだ！";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "俺が自分の船の船長で、契約で働いてるのはお前もよく知ってるだろう。\nそれに、お前の素敵な島には年に何度か寄らせてもらってるぜ！";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "俺も疑ってはいたが、完全には確信できなかった。だが運がいいな、 ちょうど数日前にキャップスターヴィルで重要な会合があったんだ。かなりの有力者たちが合意に達した。だから、 もうお前は俺の敵じゃねえ。";
			link.l1 = "俺たちを助けてくれるか？";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "すぐにお前を解放してやる。仲間は船に移されて治療を受けることになる。";
			link.l1 = "ありがとう…";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "危うく座礁しかけたじゃねえか、チャールズ！さっさと出て行け、 少なくとも一ヶ月はトルトゥーガに戻ってくるんじゃねえぞ。\nほとぼりが冷めて、みんなの怒りが収まるまで待て。";
			link.l1 = "そうするぜ。じゃあな！";
			link.l1.go = "exit";
			link.l2 = "何も説明しないのか？少しくらい話してもいいだろう…";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "誰かがお前を密告したんだ。どうやら、お前は狂信的なカトリック教徒で、この美しい島にやって来て、 名誉ある総督を悪意を持って殺そうとしているらしい。";
			link.l1 = "俺は狂信者じゃねえ！";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "巧みに書かれているんだ、信じてくれ。こういうのは俺の得意分野さ――最高の中傷文ってのは、少なくとも一粒の真実が含まれているものなんだぜ。";
			link.l1 = "誰が報告書を書いたんだ？";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "誰があの殺し屋を牢に入れたんだ？";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "誰かが、お前をすぐにラ・ロシュの地下にあるユグノーの拷問台へ送るのではなく、 数日間この牢獄に閉じ込めておきたかったんだ。\nもういい、シャルル。出ていけ。まずは目の前のことを片付けろ、それから…まあ、言いたいことは分かるだろう！";
			link.l1 = "ああ。そうする。ではな、司令官。";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "俺がやった。";
			link.l1 = "俺がここを出る前に、もう一人呼んでおいた方がいいぜ。";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "聞いてるぜ、司令。";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "俺はお前に何も説明する義務はねえ、チャールズ。俺の手に渡ったことをありがたく思えよ、 俺の上官の手に落ちなかっただけマシだ。\nそれにな、お前じゃなくてお前の雇い主がこの騒ぎの埋め合わせをしてくれるんだ、感謝しろよ。";
				link.l1 = "そうかよ……お前は俺の親分を俺ほど知らねえんだな。じゃあな、司令。";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "なあ、知ってるか？教えてやろう。特別守備隊年金基金に気前よく、しかも非課税で寄付があったんだ。 その感謝のしるしとして、寄付者には悪名高い犯罪者の迅速かつ合法的な処刑に協力する機会が与えられたのさ！";
				link.l1 = "俺の部下か？";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "俺の友か？";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "俺はお前に何も説明する義務はねえ、チャールズ。俺の手に落ちたことをありがたく思えよ、俺の上官の手じゃなくてな。 \nそれに、お前の上司がこの騒ぎの賠償をすることになるんだ、お前じゃなくてな。それも感謝しとけよ。";
				link.l1 = "そーかよ……お前は俺の親分のことを俺ほど知らねえんだな。じゃあな、司令。";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "なあ、知ってるか？教えてやろう。特別守備隊年金基金に寛大な寄付が、しかも無税でなされたんだ。 その感謝のしるしとして、寄付者には悪名高い犯罪者の迅速かつ合法的な処刑に協力する機会が与えられたのさ！";
				link.l1 = "俺の部下か？";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "俺の友か？";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "出て行け、チャールズ。そいつも連れて行け。お前の仲間の選び方には…がっかりだ。";
			link.l1 = "せめて、お前の…後ろ盾がどこにいるか教えてくれねえか？";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "本土でな。さらばだ、チャールズ。";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "お前に対して報告が上がっている。しかもかなり悪質な内容だ。船長、どう見ても誰かにハメられたようだが……俺にはお前をここにあと数週間閉じ込めて、お前の仲間を死なせる権限が十分にあるんだぜ。だが……\n";
			link.l1 = "いくらだ？";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "誰が俺をはめたんだ？殺し屋を牢屋に入れたのはお前か？";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "トルトゥーガ守備隊の年金基金に、地元の金貸しを通じて五百ドゥブロンを預けてくれ。";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" 「それから、この島の高貴な女と関わって昔起こした騒ぎの分として、さらに百ドゥブロン追加だ。」";
			}
			link.l1 = "さっさとこのクソ扉を開けろ！";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "もう十分に時間を取らせたな。金貸しのところへ行って、トルトゥーガ守備隊の年金基金に五百ドゥブロンを預けてこい。 ";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" 「それから、この島の高貴な女と関わったせいで起きた昔の厄介事の分として、さらに百ドゥブロン追加だ。」";
			}
			link.l1 = "さっさとこのクソ扉を開けろよ！";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "資金は預けてある。エルキュールはどこだ？";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "応急処置を施してお前の船に送り返したぜ。あの悪党はしぶといから、たぶん助かるだろう。\nじゃあな、船長。しばらく俺の島で見かけたくねえからな！";
			link.l1 = "こんな歓迎を受けた後じゃ、ここにはもう近づかねえぜ！さらばだ、司令。";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
