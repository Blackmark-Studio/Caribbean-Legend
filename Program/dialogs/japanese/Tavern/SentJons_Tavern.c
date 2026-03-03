// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),"「さっき俺に何か質問しようとしたよな、」 "+GetAddress_Form(NPChar)+"...","今日一日で、この質問を持ち出すのはこれで三度目だぞ…","また質問かい？","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直したぜ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ……","ああ、本当にこれで三度目だな……","いや、何の質問だってんだ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, Сага, Тени прошлого
			if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
			{
				link.l1 = "俺は元死刑執行人のレイモンド・ベイカーを探してるんだ。あいつが生きてるかどうか、そしてどこにいるか知ってるか？ ";
				link.l1.go = "baker";
			}
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "ジョーンズさんを探してるんだ。捜索を手伝ってくれねえか、相棒？";
				link.l1.go = "terrapin";
			}
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
			{
				link.l1 = "聞いてくれ、この町に錬金術師が来ていないか、医者だ。イタリア人で、三十歳くらい、 名前はジーノ・グヴィネリっていうんだ。何か聞いたことはあるか？";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Сага, Тени прошлого
		case "baker":
			dialog.text = "「うちのデブちゃんはフォックス大佐より人気者になっちまったぜ！生きてるよ、あの可哀想な野郎は。\nだが今は町にいねえんだ。お前さんみたいな大物が興味を持ってるってレイモンが知った途端、 奴はあのボロ家を二束三文で売り払って、風のように消えちまったよ。」";
			link.l1 = "風とともに消えたって、どこへ行ったんだ？";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "ああ、どうだろうな。あいつは最初に寄港した船の船医として乗り込んだんだ。\nだが、その船が今日戻ってきたばかりで、ベイカーがまだ上陸したのを誰も見てないんだよ。";
			link.l1 = "船長をどうやって見つければいいんだ？";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "なんであいつを探す必要があると思うんだ？どうせいつも通り船室で酔っぱらってるに決まってるさ。あいつのボロ船は『 カロウ・メギー』って呼ばれてるんだぜ。船長が船長なら、船の名前もそんなもんさ…";
			link.l1 = "助けてくれてありがとな、相棒！";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			DialogExit();
			AddQuestRecord("Shadows", "2");
			pchar.questTemp.Saga.Shadows = "baldmaggy";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "ジョーンズさん？冗談だろ、相棒。この島にジョーンズって奴が何人いると思ってんだ？もっと詳しく言ってくれよ。";
			link.l1 = "あいつには大人の姉貴がいる、モリーって名前だ。とんでもなく美人だって噂だぜ。";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "いや、そんなことは思い当たらねえな。悪いな、相棒…";
			link.l1 = "「わかった、知らねえなら仕方ねえな…」";
			link.l1.go = "exit";
			npchar.quest.terrapin = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "いや、聞いてねえな。それに、この町に錬金術師は一人しかいねえ、薬屋のジョン・マードックだ。 あいつの薬はすげえぞ――どんな病気でも治しちまうんだ。";
			link.l1 = "「奴が自分でこの薬を作ってると思うか？」";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "いい質問だな。俺も時々自分にそう問いかけるぜ。ジョンは薬瓶や薬草、粉薬の専門家にはまるで見えねえ。 むしろ元兵士か傭兵って感じだ……そっちの方が真実に近いな。";
			link.l1 = "まあ、その男は腕がありすぎるってことだな……";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "もしかしたらそうかもな。だが、一つだけ確かなことがあるぜ。あいつの二階には誰かが住んでるんだ。 窓はいつも閉ざされてるし、ジョンが下にいる時でも、 ガラス瓶や小瓶がカチカチ鳴る音や煮えたぎる薬草の匂いがするんだ。それに、夜になっても明かりは消えねえ。だから、 あの部屋の住人こそがジョンの薬を売るために調合してる奴だと俺は睨んでるんだ。";
			link.l1 = "ふむ。面白い指摘だな。ありがとな、相棒！";
			link.l1.go = "exit";
			pchar.questTemp.Guardoftruth = "merdok1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
