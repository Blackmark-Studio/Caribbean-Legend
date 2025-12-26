// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「質問」 "+GetAddress_Form(NPChar)+"?","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("ふん、どういうつもりだ、 "+GetAddress_Form(NPChar)+"? ","また変な質問かい？坊や、ラムでも飲んできなよ……")+"","今日一日で、これで三度目だぜ、この質問を持ち出すのは……"+GetSexPhrase(" これは愛情のしるしか？","")+"","「また質問か、そうだろう」 "+GetAddress_Form(NPChar)+"?","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった","今は話すことは何もねえぜ。"),"いやいや、美しいお嬢さん…","ありえねえよ、お嬢ちゃん…","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "ちょっと聞きたいことがあるんだ。ジンの樽が消えた日のことだが、その日お前はこの酒場で働いてたよな？ その日にここで何があったか、話してくれないか？";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "俺…俺には何と言えばいいのかわからねえ。全部普通だった、特に変わったことはなかったぜ。";
			link.l1 = "そうかい？変わったことは何もねえのか？「シービースト」のあの船乗りがしつこくしてただろう？あいつ、 お前が今夜一緒に過ごすのを歓迎すると思い込んでたみたいだぜ。";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "ああ、あいつか！奴は……ちょっと飲みすぎただけさ、それだけのことだ。ここじゃよくあることなんだぜ。俺がそそのかしたわけじゃねえが、 あいつが勝手に言い寄ってきたんだ。だから、きっちりお灸を据えてやったのさ。";
			link.l1 = "励ましはないのか？あいつは別の話をしているぜ。今回はなんでそんな騒ぎを起こしたんだ、 他の時は大人しかったくせによ？";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "俺…俺にはもう何も言えねえよ！本当に何も知らねえんだ！俺は…俺はずっと夕方までみんなの目の前にいたんだ！何も見ちゃいねえし、何も聞いちゃいねえ！それに樽のことも…何があったのか俺には分からねえ！なんでこんな尋問を受けなきゃならねえんだ？俺はただ…ただいつも通り自分の仕事をしてただけだ！";
			link.l1 = "お前、何か隠してるんじゃねえか。船の貨物室で明かりも食い物もなしで一晩過ごせば、記憶もよみがえるもんだぜ。 試してみるか？それともちゃんと話す気はあるか？";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "お前はまだ隠してることがたくさんあるはずだ。今が滅多にないチャンスだぜ――全部話せば、この茶番でのお前の役割は俺だけの秘密にしてやる。\nだが黙ったままなら……お前にとってもっと悪いことになるぜ。お前の助けがあろうとなかろうと、俺は真実を暴き出すからな。";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "わ、わたし……全部話すよ！全部あたしの……求婚者、ジャックのせいなんだ。ジャック・ヴェイルズ！彼が“シービースト”の船乗りを誘惑するようにあたしにそそのかしたの。で、彼が言い寄ってきたら、 あたしが騒ぎを起こして酒場の主人をカウンターの奥からおびき出すことになってた。騒ぎが少し落ち着いたところで、 二人の船乗りが大喧嘩を始めて、主人をメインルームに引き留めてた。それがまさに起きたことよ\nその間に、“シービースト”の船長が樽を盗み出したの。……それが、あたしの知ってる全部よ "+GetSexPhrase("旦那","奥様")+"！頼む、俺を密告しないでくれ！俺はただ…ただ…ただ…ジャックにやっと少しは敬意を払ってほしかっただけなんだ！結局、俺はあいつを助けたんだから…";
			link.l1 = "一人を助けるために、もう一人を何のためらいもなく狼の餌にしたってのか！？だが、俺は約束は守る――お前が関わったことは口外しねえよ。だが、自分のしたことは自分で背負うんだな！ お前の愚かさで宿屋の主人が大変な危険に晒されたかもしれねえんだぜ。で、そのジャックってやつはどこにいる？ 覚えとけよ、嘘をついたらまた来るからな。俺が戻ってきた時は、絶対に楽しいことにはならねえぜ。";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "お、俺…全部話すよ！全部、あたしの…求婚者のジャック、ジャック・ベイルズのせいなんだ！彼が『シービースト号』の船乗りを誘惑するように言ったの。で、 彼が言い寄ってきたら、あたしが騒ぎを起こして酒場の主人をカウンターの奥から誘い出すことになってたんだ。 騒ぎが落ち着きかけたら、二人の船乗りが大喧嘩を始めて、主人をメインルームに引き止めるって段取りだった。 それがまさに起きたのよ\nその間に、『シービースト号』の船長が樽を盗み出したの。あたしが知ってるのは…それだけよ "+GetSexPhrase("旦那","奥様")+"！頼む、俺を密告しないでくれ！俺はただ…ほんの…ただ…ジャックにやっと少しは敬意を払ってほしかっただけなんだ！結局、俺はあいつを助けたんだから…";
			link.l1 = "一人を助けるために、もう一人を何のためらいもなく狼の餌にしたってのか！？それでも、俺は約束は守る――お前の関与はバラさねえよ。だが、自分のやったことは背負って生きていくんだな！ お前の愚かさで宿屋の主人が大変な目に遭うところだったんだぜ。で、そのジャックって野郎はどこにいる？忘れるなよ――嘘をついたら、また戻ってくるからな。俺が戻った時、お前は絶対に後悔するぜ。";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "そんなに深刻だとは思わなかったんだ！たかが樽じゃねえか…ジャックなら通りの向かいに住んでる。あそこの家を借りてるんだ、俺は…俺はそれ以上何も知らねえ！どうか許してくれ！船長、もう二度とこんなことはしねえって誓うよ！";
			link.l1 = "自分の仕事に戻れ、そして泣き出すんじゃねえぞ――酒場の主人に気取られたら終わりだからな。";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
