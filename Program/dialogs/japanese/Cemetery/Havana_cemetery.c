// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どうお手伝いしましょうか？","何かご用ですか？"),"「どうした、何か悩みでもあるのか、」 "+GetAddress_Form(NPChar)+"?","「これで三度目だ、」 "+GetAddress_Form(NPChar)+"、何の用だ？","もううんざりだ。出ていけ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった、すまねえな。","たいしたことじゃねえ、すまねえな。"),"許してくれ、なんでもねえよ。","おっしゃる通りだ、もう三度目だな。すまねえ……","申し訳ねえ。",npchar,Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "聞いてくれ、ここハバナやその近くで、ジョアキム・メリマンという名の男を見かけたり会ったりしたことはないか？ 中年のポルトガル人の旦那で、口ひげとあごひげがあり、鋭い目をしているんだ。 入り江やジャングルの中で見かけたことは？俺はそいつを探しているんだ。";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "い、いや、水夫さん、け、決してそんなことはないよ。ここにはめったに訪問者が来ないんだ、ええと……それに……君が言ったような男は見ていないんだ、だから……";
			link.l1 = "本当か？じゃあ、なんでどもって目をそらしてるんだ？今さら嘘つくんじゃねえ、真実は知ってるはずだ。もう一度言え――あの男を見たのか？";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "お、俺は言ってるんだ、旦那、誰も見てねえって！俺は子どもの頃からずっとどもってるんだよ…";
			link.l1 = "嘘だ、全部嘘だ。お前の目を見ればわかる。あいつはどこだ、メリマンはどこにいる！？今すぐ言え！";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "メリマンなんて知らねえ！その名前も聞いたことねえぞ！それに、俺に手を出そうなんて思うなよ、 司令官が砦でお前を絞首刑にするからな！だから気をつけて歩けよ、坊主！";
			link.l1 = "おお、そう思うのか？よし。じゃあ、よく聞けよ。ジョアキム・メリマンは魔術師だ。聖なる異端審問が奴を探している。 何年も前、ヨーロッパで奴は墓荒らしと死者冒涜、そして魔術の罪で火あぶりの刑を宣告されたんだ。しかも今、 奴がどこかこのハバナの外れに隠れているってことを、俺は確かに知ってるんだ……";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "…最近、近くの洞窟のゾンビどもを片付けて、誰が黒幕かも突き止めたんだ！メリマンが行くとしたら墓地しかねえだろう！ あんたは奴の居場所を知ってるはずだ。でもまあいいさ、俺はあんたに手は出さねえ。その代わり、 サンティアゴの異端審問官どもに会いに行くぜ。ヴィンチェント神父は、 ジョアキム・メリマンが仲間の地元の墓守と一緒にハバナの墓地に隠れてるって聞いたら、きっと興味津々だろうな…\n";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "…もう顔色が真っ青じゃねえか？俺は貴族の誓いを立てるぜ：調査結果を報告した翌日には、 この島中にスペイン兵がうようよすることになる。お前は拷問台に縛りつけられて、 あの魔術師の隠れ場所を白状するまで泣き叫ぶ羽目になるんだ。そしたらすぐに、俺が火刑執行（アウト・ダ・フェ） を見物してる前で、お前は共犯者として火あぶりにされるんだぜ。どうだ、気分は？";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "お、お頼みします、旦那！俺は何も関わっちゃいねえ、誓うぜ！俺は…俺には何もできなかったんだ…どうやってあいつに逆らえってんだ！？あいつは恐ろしい男だ、あいつは…あんたには想像もつかねえことができるんだ！どうか、勘弁してくれ、頼む！";
			link.l1 = "俺を信じろ、あいつの力はよく知ってる。自分の目で見たんだ。\nそれで？あいつはどこにいる？教えてくれれば、この件にお前を巻き込んだりしねえと約束するぜ。";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "あいつは……あいつは墓地の下の洞窟に隠れているんだ。そこへ行くには礼拝堂の扉からしか入れない。あいつが外に出ると、 俺は自分の家に隠れてじっとしてるんだ。あの恐ろしい奴から解放されたい気持ち、あんたには分からないだろう！\nでも、近づくなんてとてもできない……俺は、あいつが新しい墓を掘っているのを見たんだ、そしたら……そしたら死体が起き上がって、月明かりの下で墓地を歩き回り始めた！あのときは気が狂いそうだったよ！ でもメリマンが、俺に家を出るのを禁じたんだ。もし勝手に半日でも家を出たら、必ず見つけ出して、あの化け物……歩く骸骨にしてやるって脅されたんだ！";
			link.l1 = "「奴はどれくらいの頻度で洞窟を出るんだ？」";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "そうだな、俺は町からあいつに食い物や治療薬を運んでる…他にもあいつが欲しがるものは何でもだ。あいつは月に一、二度…満月の夜に出かけていく。戸口にメモを残して、必要なものを書きつけていく…お、俺はそれを届けて戸口に置いておくんだ。あいつは戻ったときにそれを持っていくんだよ。";
			link.l1 = "なるほど。その隠れ家への扉は、何かで施錠されているのか？";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "そうだ。いつも鍵がかかっている。とても頑丈で、錠前もでかくて複雑なんだ。";
			link.l1 = "ふむ……メリマンは馬鹿じゃねえ、きっとヨーロッパの屋敷と同じように隠れ家にも別の抜け道があるはずだ。 もし無理やり扉をこじ開けたら、あいつはすぐに逃げちまって二度と見つからねえだろう。うーん……";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "旦那、俺を異端審問官に引き渡さないと誓ってくれるか？";
			link.l1 = "俺は約束したんだ。貴族の言葉は神聖なものだぜ。絶対にお前を裏切ったりしねえと誓うよ。";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "「おお、神のご加護を、旦那！俺は洞窟への行き方を知ってるんだ。鍵がある、二つ目の鍵も……俺が持ってる。メリマンはあの錠前に鍵が二つあることを知らねえ。俺はとても中に入る勇気はねえが、あんたなら……」";
			link.l1 = "鍵を渡せば、この悪夢からお前を解放してやる。";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "ほらよ、旦那。あいつの巣に本気で入るつもりか？";
			link.l1 = "そうだ。家に鍵をかけて中で待っていろ。俺が中に入ってくる間な。もし戻らなかったら、 すべてを捨ててできるだけ早く逃げろ。";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "だが、気をつけてくれ、旦那。あの洞窟からは不気味な音が聞こえてきて、 誰が住んでいるのか考えるだけでも恐ろしいんだ。だがメリマンは一人じゃない――それだけは確かだぜ。\n";
			link.l1 = "できる限りの手は打つぜ。じゃあな。";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
