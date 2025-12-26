// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問があるんだ？","「どうなさいましたか、」 "+GetAddress_Form(NPChar)+"?"),"「さっき俺に何か聞こうとしたじゃねえか、」 "+GetAddress_Form(NPChar)+"...","今日一日で、その質問を持ち出すのはこれで三度目だぞ…","「また質問かい？」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "どうやら誰かがお前の大事なジンを奪ったって噂だぜ。あるいは、噂がデタラメなのか？";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "「良い知らせだ」 "+npchar.name+"「おう！樽を取り戻してきたぜ！」";
				link.l1.go = "OS_Tavern3_1";
			}
		//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "なんてこった、本当だったのか。他に何か聞いたのか？何か知ってるのか？頼む、 どこで見つかるか知ってると言ってくれ。もし取り戻せなければ……この町から逃げなきゃならねえ。自分の足でか、それとも松の棺桶でか、どっちかだ。";
			link.l1 = "確かに、お前さんの状況は厳しそうだな、相棒。いや、お前さんの不運について噂をちょっと耳にしただけさ。 どうしてそんな貴重な積み荷を逃しちまったんだ？";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern1_2":
			dialog.text = "ちくしょう……何と言えばいいんだ？俺の目の前から盗まれちまった！樽は確かに朝ここにあったんだ。二日前に届いて、 念のため夜は家に持ち帰った。朝になってまた持ってきて、カウンターの下に隠しておいたんだ。 夕方には跡形もなく消えてた！誰一人として見た者も聞いた者もいねえんだよ。";
			link.l1 = "へえ、こりゃ驚いたぜ……";
			link.l1.go = "OS_Tavern1_3";
		break;

		case "OS_Tavern1_3":
			dialog.text = "俺に少しでも手がかりがあれば、とっくに探しに行ってるさ。だが、残念ながら何もねえ――まるであの樽はこの世には贅沢すぎて、天が持っていっちまったみたいだ。 あれを持ち帰ってくれた奴には百五十ドゥブロン払うぜ。それだけじゃねえ、その名を刻んだ盾を酒場に飾って、 みんなにその武勇伝を知らしめてやる！";
			link.l1 = "できることをやってみるぜ。この銘板の話は後でまたしよう。代わりに教えてくれ、この樽のことを知ってたのは誰だ？ それと、お前以外にカウンターの裏にいた奴はいるか？";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "樽一つで百五十ドゥブロンだと？おもしれえな。\nだが、その面倒は俺の知ったこっちゃねえ。自分で何とかしな。";
			link.l2.go = "OS_Tavern1_end";
		break;

		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");

			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;

		case "OS_Tavern1_4":
			dialog.text = "ほとんど誰もいなかったよ！強いて言えば、うちの給仕娘くらいだが、それはありえねえ。 あの日の酒場はめったにない盛り上がりでな――「シービースト号」の連中が狩りから立派な獲物を持ち帰ってきたんだ。あの娘は一息つく暇もなかったし、 ましてや俺のカウンターの裏にこっそり回り込む時間なんてなかったさ。";
			link.l1 = "「それは本当か？」";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "間違いないぜ！休みなく働くのはあの娘の性分に合わなかったらしくて、 夕方にはまるでバネみたいにピリピリしてたんだ。\n水夫の一人が言い寄ったら、店中が耳をふさぐほどの大騒ぎになっちまってな。 俺が持ち場を離れて収拾つける羽目になったぜ。\nだが不思議なもんだ――普段なら、ああいう言い寄りももっと落ち着いて受け流すんだがな。";
			link.l1 = "それだけか？その日、他に変わったことはなかったのか？";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "俺が最初の騒ぎを鎮めている間に、別の揉め事が起きた――奥の隅で二人の水夫が殴り合いを始めたんだ。\nだが、その小競り合いも長くは続かなかった。どうやら同じ船の仲間だったようで、すぐに引き離されたよ。\nその後は本当に静かになって、特筆すべきことは何も起こらなかったぜ。";
			link.l1 = "よし、捜索を始めるぜ。\n待ってな。すぐに樽はまたお前さんの、ええと……見張りの目の下に戻ると思うぜ。";
			link.l1.go = "OS_Tavern1_7";
		break;
		//<-- Старые счёты
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "見つけてくれたのか？！本当なのか？船長、あんたは俺の命の恩人だ！誰がこんなことを仕組んだんだ？ その悪党の名前を知りたいんだ！";
			link.l1 = "それは「シービースト号」の船長と共謀したジャック・ヴェイルズという男による、綿密に計画された策略だったんだ。\n奴らは自分たちの水夫を巻き込み、手の込んだ陽動作戦を仕掛けてお前を引き離したんだよ。\nお前が持ち場を離れた隙に樽は無防備になり、奴らは簡単にそれを持ち去ったってわけさ。";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "なんてこった！ジャック・ヴェイルズ！あいつが戻ってきたのか……しかも、こんな卑怯な手で酒場を取り戻そうとしたとはな。あの狐め、決して負けを認めねえ！";
			link.l1 = "つまり、あいつはかつてこの店の主人だったってわけか？安心しな。もう二度と企むことはねえ。 俺があの世へ送ってやったぜ。";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "船長！これは驚くべきことだ！お前さんが…お前さんが、俺の毎日につきまとっていた絶え間ない不安から俺を解放してくれたんだ！あいつがいつか戻ってくると、 俺はずっと分かっていた…数年前、俺たちはこの酒場の権利を巡って争っていたんだが、あいつに一度は負けちまった\nだが、勝利の喜びがあいつの破滅を招いた――祝いのどんちゃん騒ぎの最中、あいつは知らずにこの店をカードで俺に賭けてしまったんだ。もちろん、 朝になったらあいつは駆け込んできて、酒場を取り戻させてくれって、何でもすると懇願してきたさ\nだが、そんな条件を呑むほど俺も馬鹿じゃねえ。それからあいつは姿を消した…だが、あいつがこのまま引き下がるはずがないと分かっていた。いつか必ず戻ってくると感じていた。そして今、 その日が来たんだ。";
			link.l1 = "評価すべきところは評価しないとな――奴は巧妙に計画を実行したぜ。";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "ちょっと待て！どうやって奴が樽のことを知ったんだ？そうか…そういうことか、やっと分かってきたぜ！あの給仕女だ！だからあいつは火傷した猫みたいに逃げ出したんだな、 別れの挨拶もなしに。お前がジャックを片付けたって噂を聞きつけたに違いねえ。これで全部つながった。船長、 俺はお前にいくら感謝してもしきれねえ、あんたは…";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
