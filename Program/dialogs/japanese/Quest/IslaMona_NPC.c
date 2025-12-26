void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何もない。」";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "他にご用はありますか、船長？";
			link.l1 = "今のところ何もない……";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "ハハハ！イエス・キリスト旦那！守護聖人サンティアゴに栄光あれ！聖母マリアに栄光あれ！俺たちは助かったぞ！ ハハハ！";
			link.l1 = "スペイン野郎どもだ！武器を取れ！";
			link.l1.go = "Himenes_1_1";
			link.l2 = "こんにちは。何かお困りのようですね？あなたは誰だ？";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "「ハハハハハハハハハ！」";
			link.l1 = "わかったよ、落ち着けって。癖なんだよ。";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "ハハハ！旦那、俺の名はロドリゴ・ヒメネスだ。俺は測量士であり、 運命のいたずらでこの不運な連中のエル・ヘフェを務めている。";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "俺たちは……ここに上陸させられたんだ。しかし、旦那、俺たちは犯罪者じゃねえ！ハハハハハ！";
			link.l1 = "「何がおかしいんだ？」";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "ああ……すまねえ、旦那！子供の頃からの癖でな、ひどく緊張するとつい笑っちまうんだ。はは。";
			link.l1 = "「それでお前がリーダーに選ばれたってわけか？…まあいい。人は理由もなく無人島に上陸したりしねえんだ、旦那。説明してもらおうか？チャンスは一度きりだぜ。」";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "すみません、旦那、お名前を聞きそびれてしまいました。あなたはイギリス人ですか？";
			link.l1 = nationManName[sti(pchar.BaseNation)]+"。そんなに重要か？今は俺の名前なんて気にするな。";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "確かに、カトリックのスペイン教会から異端者と認定された俺たちは、 聖なる異端審問の正義の法廷に出頭しなきゃならねえ。だからこそ、あんたの国籍が俺たちにはとても重要なんだ。 スペイン人の船長だったら、俺たちを地元の役人に引き渡さなきゃならねえからな。そんな目にもう一度遭ったら、 生き延びられねえぜ！ハハッ！";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "ハハハハハハ！これが俺たちの運命だぜ。まあ、どうせ失うものなんて何もねえしな。 "+dialog.text;
			link.l1 = "まあ、お前にとって幸運だったな、異端審問のことなんざ俺には関係ねえ。\nそれで？お前らは異教徒か？";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "いいえ、誓います！我々の共同体は、栄光あるカディスの街で五十年間、工芸や交易に従事してきました。すべて順調で、 ついには船と帝国植民地との交易許可証まで手に入れたのです。今になって思えば、あの時に何か一線を越えてしまい、 新たな競争相手――そして奴らのやり方――にまったく備えができていなかったのだと分かります。";
			link.l1 = "お前はヨーロッパで誰かと取引しなかったせいで、コミュニティ全体がカリブの無人島に取り残されたってわけか？ 俺なんてまだマシな方だと思ってたぜ……";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "残念ながら、その通りだ。我々の共同体は、新しい信仰に改宗し、 スペインに帰る機会を与えられたユダヤ人たちによって設立されたんだ。この古い歴史だけで、 非難や公式な調査の理由になってしまったんだ。";
			link.l1 = "……つまり逃げたんだな……";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "ああ！ハハハ！俺たち自身の船でな！新しい家と新しい商売を作るためにキュラソーへ向かっていたんだ。だが、 異端審問官どもの執念深さを甘く見ていた。高くついたぜ。 あいつらの使者がここからそう遠くない場所で俺たちを捕まえて、船長に俺たちを故郷へ連れ戻すよう命じやがったんだ…";
			link.l1 = "くそっ！";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "まだあるぜ！ははっ！うちの船長は、俺たちを大西洋を越えて連れ戻すのも、 近くの港で責任を放棄するのも面倒だったんだ。で、まるでソロモン王みたいな決断をして、 食料を渡してここに上陸させて、それで終わりさ。";
			link.l1 = "まったくもって悲劇的な話だな、間違いねえ。まとめると、故郷には帰れねえし、友好的な植民地はお前を通報する、 よその港も歓迎しちゃくれねえ――この地で戦争が終わる気配もねえ。さて、これからどうするつもりだ？\n";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "あんたはあまりにも暗い話をしてくれたから、俺は言葉を失っちまったぜ。 まるでこの島以外に俺たちの居場所なんてないみたいじゃねえか。";
			link.l1 = "そうは思わねえ、もっといい島があるぜ。";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "本当か？スペイン語か？";
			link.l1 = "それは俺のものだ。運命によって、無人島にあった元海賊の隠れ家を受け継いだんだ。\n今じゃそこが俺の拠点で、これから拡張したり、島を探検したり、できれば工場も建てたいと思ってる。";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "お前は海賊か？";
			link.l1 = "「ああ。」";
			link.l1.go = "Himenes_14_1";
			link.l2 = "いやだ。";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "新世界！本当に俺たちはここに来たんだな。故郷じゃ、海賊はまるで悪魔みたいな存在で、 人間ですらないって言われてる。子供を食い、女を犯し、善良なカトリック教徒の皮を生きたまま剥ぐって話だ。本当か？ ";
			link.l1 = "曜日によるな。\nこの話はまた今度にしよう。\n俺は人を探しているんだ。\n数年間文明から離れて暮らす覚悟があって、勤勉で有能な奴らだ。\nお前、そういうことに興味はあるか？";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "残念だな、どうせ俺はもう犯罪者なんだから、せめて一人くらい海賊を見てみたかったぜ。";
			link.l1 = "もしかしたら、またそんな機会があるかもしれねえな。\nその話はまた今度にしよう。\n俺は数年間文明から離れて暮らす覚悟のある、働き者で腕の立つ奴を探してるんだ。\nお前、そういう仕事に興味はあるか？";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "他に道はない。しかし、それは実は悪くない選択だ。俺たちは、平和に暮らし働くことを許してくれるなら受け入れるぜ。 いつか故郷に帰してくれると約束してくれ！\n約束してくれ、旦那、そして名前を教えてくれ…";
			link.l1 = "俺、船長 "+GetFullName(pchar)+"、俺の言葉を信じてくれ。？";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "ははは！助かったぞ！そういうことだ！俺たちは数家族、総勢三十人ほどだ。全員読み書きができて、 職人や商売にも長けているんだ。";
			link.l1 = "運命が決めたんだ……さあ、乗船してくれ！";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "はじめまして、ロドガー旦那。これからしばらく一緒に暮らし、働くことになりそうですね……まあ、この暑さ、どうやって耐えているんですか？";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "もしよければ、俺が口を挟ませてもらうぜ。船長、俺たちが落ち着いて在庫と土地をざっと調べるのに一日くれ。 ロドガー旦那はこの土地で何をするか、きっといろいろ考えがあるはずだ。俺たちはいいチームになれると思うぜ。";
			link.l1 = "選択肢なんてねえんだよ、ヒュメネス。ははっ！";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "「ハハハハハハ！」";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "はい、船長？";
			link.l1 = "「ハイメネス、俺にいい知らせはあるか？」";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "船長、これは悪夢だぜ。あんたの家は悪くねえ、もちろんだ。だがな……他は最悪だ。こんな藪に囲まれた小屋なんか住めたもんじゃねえし、 旦那ロドガルは島の反対側で何が起きてるかさえ知らねえんだぞ！！信じられねえ！ははっ！";
			link.l1 = "今緊張してるのか、それとも本当に今笑ってるのか？";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "もちろん、おかしいじゃねえか！やつらは今まで何してたんだ？まずは家を二、三軒建て終えて、 この小屋どもをまともな状態に修理しねえとな。人間、ちゃんとした暮らしができねえと、真面目に働けねえからな。 それから、島の偵察を海賊どもに頼むつもりだ。もしかしたら、この場所は岩や砂だけじゃなく、 もっと何かあるかもしれねえ。全部終わったら、この土地をどうすりゃいいか、はっきり教えてやるぜ。";
			link.l1 = "いいじゃねえか！俺に何をやらせたいんだ？";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "家や家具、それに仮設の避難所のための資材だ。全部計算しておいた。ほら、これがリストだ。";
			link.l1 = "見事だな……";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "本当かい？旦那、俺たちは大聖堂まで建てたんだぜ！それはすごいことじゃねえか…";
			link.l1 = "信じてやるぜ！ただし、うっかりここに大聖堂なんか建てるんじゃねえぞ。毎回大量の資材を運ばされる羽目になるのか？ ";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "いや、これらの資材でしばらくは持つが、後でまた何かを持ち込む必要があるだろう。\n今後こんな面倒を避けたいなら、資材を二倍持ってくるんだな。";
			link.l1 = "ふむ、納得したよ。できることをやってみよう。締め切りはあるか？";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "いいえ、旦那。しかし、どうかご猶予なさらぬようお願い申し上げます――これは物事を前に進めるために必要な仕事ですし、人々にも住む場所が必要ですから。資材を倉庫に積み込んで、 すべて準備が整ったら必ず私に知らせてください。\nああ、もう一つ忘れていました！ロドガーさんに島の調査について話してください。";
			link.l1 = "同意だ！";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "おう、船長？";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "やあ、Jiménez。倉庫を確認してくれ。";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "やあ、ヒメネス。俺の部下たちは島中をくまなく探したぜ。どう思う？";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "見事にこの責任を果たしたな！カディスに来ることがあったら、俺の店の番頭として働いてくれよ！";
			link.l1 = "今行くぜ！なあ、相棒、これからどうするつもりだ？";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "旦那船長、まずは住居と物資の手配を済ませましょう。その後で計画を立てます。 倉庫であなたのリストにある品物をお待ちしています。";
			link.l1 = "わかった、了解だ。まずは家を建てて、この場所をきれいにしなきゃならねえ。品物はすぐに届くぜ。";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "船長、まずは住居と物資の手配から片付けましょう。計画は後で立てればいいです。 倉庫であなたのリストにある品物を待っていますよ。それに、あなたの海賊仲間も補給品と薬を待っています。";
			link.l1 = "わかった、了解だ。まずは家を建てて、この場所を片付けねえとな。品物はすぐに届くぜ。俺の海賊仲間の分もな。\n";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "「半年ください、船長。そうすりゃ、この場所が見違えるぜ。」";
			link.l1 = "半年後にはお前も、この集落も、資材も何も残らねえってことか？またな！";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "この盗賊との用事が片付いたら、すぐに作業を始めるぜ。あいつはお前に食料と薬を要求したが、俺も同意する――筋の通った要求だ。";
			link.l1 = "あなたの言葉を彼に伝えておきます。";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "どうだ、船長？お前の海賊が頼んだことは全部やったのか？";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "ロドガーとの問題はすべて解決した。\n島の偵察も始まっているし、食糧と薬も倉庫にある。\nあとはお前の番だ。";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "心配するな、何とかなるさ。俺が何とかするぜ。";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "旦那船長！どう思うんだ？ハハハ！";
			link.l1 = "ずいぶん良くなったな。報告しろ、ヒメネス！";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "これで本当にここに住めるようになったぞ！俺たちは全部の家を片付けて建て直したんだ、お前の家以外はな。\n贅沢じゃねえが、俺たちのベリーズと比べても悪くねえぜ。";
			link.l1 = "ベリーズはずっとイングランドのものだったんだぜ、ヒメネス。";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "それを家々が知っているかどうかは分かりませんよ、船長、ははっ！";
			link.l1 = "これで住む場所もできて、入植地もちゃんとした感じになったな。次はどうする？";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "周りを見て、ヤンセン旦那と話してから俺のところに戻ってこい。\n島の偵察の結果と今後の計画について話し合おう。";
			link.l1 = "いつからロドガーのことをそう呼ぶようになったんだ？お前たち、ずっと仲が悪かったんじゃねえか？";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "そして今もそれがある。しかし、どうにかして協力関係を築かないとな。";
			link.l1 = "ありがとう、Rodrigo。すぐ戻るよ。";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "船長。ヤンセン旦那。";
			link.l1 = "さあ、島の偵察の結果を教えてくれ。";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "はい、船長。俺が直々にうちの探鉱者といくつかの場所を調べてきたぜ。まあ、なんと言うか……イスラ・モナは貧しくて小さくて、特に目立つところのない島だ。建設できる場所はほとんどなく、 地形は険しくて急だし、肥沃な土地もほぼ皆無だ。浜辺が三つ、水没した洞窟が一つ、密林、オウムが二羽、ヤギの群れ、 そして俺たち……";
			link.l1 = "本気か？この島で一番価値があるものがヤギの群れだって言うのか？";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "ハハハハ！俺は聞こうと思ったんだぜ、旦那！ハハハ！お前が最後まで言わせてくれなかったんだ！";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "わかった、わかった、落ち着いて続けてくれ。俺はな、この場所にずいぶん投資してきたんだぜ。";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "無駄じゃなかったぜ！洞窟には十分な真水があるし、果樹を育てるのに適した土もある。ヤギも飼えるしな。 漁と仲間たちの努力があれば、食糧の問題もすぐに解決するだろう。\n";
			link.l1 = "じゃあ、もうここに食料を運ぶ必要はないんだな？悪くない。俺がずっと世話しなくても、 この場所がやっていけると期待してたんだ。続けよう。";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "すべておっしゃる通りです、旦那。でも、それだけじゃありません！まず第一に、 ロドガー旦那が酒場を建てるという考えを思いついたんです。あなたにどんな利益があるかはわかりませんが、 あの悪党は何か企んでいますよ。";
			link.l1 = "あいつは酔っぱらいたいだけだぜ、まったく！";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "次に、総督湾は当初思っていたよりもずっと深かったんだ。これなら本格的な桟橋を建設できるぜ。";
			link.l1 = "俺にはどう得になるのかよく分からねえが、それでもいい知らせだな。だが、それだけじゃねえだろうな？";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "ボコーテの木立を見つけた。工場を建てるには理想的な場所だな。";
			link.l1 = "嬉しいぞ、ロドリゴ！本当に、素晴らしい知らせだ！";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "今はこれで全部だ、旦那。将来また何か思いつくかもしれねえ。分かるだろ、 最高のアイデアってのは仕事中に浮かぶもんさ！何か聞きたいことはあるか？";
			link.l1 = "バコーテについて教えてくれ。なんだか期待できそうだな。";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "私の見積もりでは、小規模な工場なら数年間はこの貴重な木材を採取できるだろう。備蓄は控えめだが、 この資源は戦略的価値がある。島の中央に用地を整地し、そこに倉庫付きの家を建てることができる。それが第一歩だ。\n建築資材のほかに、手錠とマスケット銃をそれぞれ十五セットほど用意する必要がある。";
			link.l1 = "「それで、なんで手錠が必要なんだ？それに、なぜちょうど十五個なんだ？」";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "きつい労働だぜ、旦那。いや、まるで奴隷の仕事と言ってもいいくらいだ。";
			link.l1 = "わかったぜ。へっへっ…";
			link.l1.go = "Himenes_57_1";
			link.l2 = "気は確かか？俺は奴隷の持ち主になんかならねえぞ！";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "「それで、なんでマスケット銃が必要なんだ？しかも一丁だけで？」";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "俺はこの海賊に同意するよ、旦那。船長、あんたの言ってることがわからねえ。 この地域の経済はすべて奴隷労働に支えられてるし、これから何年もそうだろう。俺たちが何か違うってのか？";
			link.l1 = "俺が決めるまで待て。その間に、なぜ火縄銃が必要なんだ？しかも、なぜ一丁だけなんだ？";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "もちろん、工場には維持管理が必要だ。この建設によって、この島はお前を主要な交易相手とする経済を持つことになる。 奴隷たちの食事はこちらで用意するが、警備と生産の費用はお前自身が負担しなければならない。 入植者たちは一回ごとに20ドゥブロンとワイン5本を受け取る。警備の件については、ヤンセン旦那と交渉してくれ。";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "毎月四十樽だ。それに金貨は未来のためさ。いつかお前が俺たちをここから連れ出してくれる、 その約束を覚えているだろう？どんな仕事にも報酬が必要だ。お前のドゥブロンで、 俺たちは猟師や職人に入植地での働きの対価を支払う。そうすれば交易が生まれ、そして交易があれば――文明も生まれるってわけだ！";
			link.l1 = "その意気だぜ！よし！今のところ、全部それらしく聞こえるな…";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "他に興味があることは？";
			link.l1 = "それで、酒場の話はどうなってるんだ？なぜ劇場を建てないんだ？";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "船長、あんたがその家の案を気に入らねえって俺は警告したぜ。でも、これしか手はねえんだ。あんたの家が……ええと、この町で一番でかいからな、一階をホールに改築して、テーブルと厨房を設置する。 地下室には酒と食い物を貯蔵するつもりだ。料理人も楽士も揃ってるぜ。二階はそのままあんたの領域で、手はつけねえ。 あんたの荷物は全部、俺たちが一階から二階へ運ぶから安心しな。";
			link.l1 = "よし。それで、酒場は俺たちに一体何を提供してくれるんだ？";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "俺たちがちょっとした文化を盛り上げてやるぜ、 しかもカリブのど真ん中で三百人ほどを控えとして確保できるチャンスもあるんだ。";
			link.l1 = "面白いな……考えておくぜ。";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "他に何か興味があるのか？";
			link.l1 = "さて、桟橋はどうするんだ？";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "簡単なことだ。総督湾の暗礁を取り除き、信号灯を設置し、桟橋を建てるんだ。旦那ヤンセンは、この湾には三隻の船、 あるいは一等船一隻を停泊させられるようになると言っている。それに、毎回浜辺で小舟を引きずることなく、 ここに戻ってくるのもずっと快適になるだろう。\n";
			link.l1 = "それはいいな。";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "何を知りたいんだ？";
			link.l1 = "今はこれで終わりだ。また何を建てるか決めたら戻ってくるぜ。";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "旦那船長、この書類を受け取ってくれ。何度も同じことを繰り返さなくて済むように、詳細はすべて書き記しておいた。\nよく読んで、材料を持ってきて、作業に取りかかってくれ。";
			link.l1 = "ありがとうございます、Rodrigo。";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно ещё 10 рабов
			{
				dialog.text = "旦那船長、工場で働かせる奴隷が10人必要だ――言っただろう、忘れてないよな？";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "すでに届けた。荷を下ろして生産を始めろ。";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "俺の記憶ははっきりしてる。すぐに奴らを連れてくるぜ。";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "さて、旦那船長、どうするんだ？";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "俺はきれいな湾と安全な桟橋が欲しいんだ。\nそこを俺の艦隊の拠点にするぜ。";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "さあ、酒場を建ててくれ。みんな喜ぶし、俺もここに備蓄を置けるからな。";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "プランテーションの建設を始めろ。そろそろ投資を回収する時だ。";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "ロドリゴ、最も貴重な専門家と設備は工場に届けられた。作業を始めていいぞ。";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "ロドリゴ、俺は鉄木を取りに来たぞ。";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "ロドリゴ、俺たちの大工事は終わったか？";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "ロドリゴ、君の教会を建てよう。";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "ロドリゴ、教会の品を持ってきたぞ。";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "今のところ何もない……";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "資材は揃っている、すべて準備万端だ。工事には4か月かかるぞ。";
				link.l1 = "急いでるわけじゃねえだろ！じゃあ、幸運を祈るぜ、ロドリゴ。";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "倉庫に材料が足りないようです。どうか、もう一度リストを確認してください。";
				link.l1 = "俺が引き受けるぜ。";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "資材は揃っていて、すべて準備万端だ。\n工事には三ヶ月かかる。";
				link.l1 = "急いじゃいねえだろ！まあ、幸運を祈るぜ、ロドリゴ。";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "倉庫に材料が足りないようです。どうか、もう一度リストを確認してください。";
				link.l1 = "俺がやっておくぜ。";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "資材は揃っている、すべて準備万端だ。\n建設には6か月かかる。";
				link.l1 = "急いでるわけじゃねえだろ！幸運を祈るぜ、ロドリゴ。";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "倉庫に材料が足りないようです。どうか、もう一度リストを確認してください。";
				link.l1 = "俺がやっておくぜ。";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "ようこそ、船長。新しい港の居心地はどうだ？";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "暗いじゃねえか、ロドリゴ！お前の自慢の桟橋にぶつかりそうだったぞ！まあ、 せめて明かりをつけてくれたのは褒めてやるよ！";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "悪くないな、ロドリゴ！些細なことに見えるかもしれねえが、こうして桟橋を歩いて岸に行けるのは気分がいいぜ。 しかも湾の航行も楽になった。\nってことは、この小さな湾にもっと船を停泊させられるってわけだな？";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "はい、船長。正直に言うと、ちょっと誇らしい気持ちになりますね。大規模な建設計画について、 どう進めたいか遠慮なくお知らせください。";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "建設と言えば、俺の工場ももう完成しているはずだよな、ロドリゴ？";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "ひっく！船長！ここで祝ってるんだぜ！";
			link.l1 = "ロドガー。ロドリゴ。くそっ！";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "どうしたんだ、せ、船長？壁の色が気に入らねえのか？";
			link.l1 = "今になって初めて気づいたが、お前たち二人は同じ名前なんだな！ハハハ！スペイン人と海賊が、 同じ名前で無人島に酒場を建てて、まるでインディアンの神々 が夜明けに全員を食い尽くして世界を終わらせるかのように、一緒に飲んでるとはな！ハハハ！俺も混ぜてくれ！";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "ハハハ！まったくだぜ！やったな！";
			link.l1 = "やったぜ！";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "すべて準備できたぜ。行こうか？工場を案内するぜ。";
			link.l1 = "案内してくれ。";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "船長、作業開始の準備はほぼ整いました。労働者用の住居、原材料用の倉庫、加工エリア――立派な工場が建設されました。ジャングルでは伐採に最適な木もすでに目印を付けてあります。労働者十五人と、 約束通りの備品――足枷十五個とマスケット銃十五丁――を持ってきてくれれば、すぐに作業を始めます。";
			link.l1 = "俺たち？奴隷のことか？";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "ははっ！奴隷が伐採し、開拓者が加工し、海賊が警備する。みんな仕事があるってわけだ――大事業に乗り出したな、船長。";
			link.l1 = "まるで約束の地みたいだな、え？\n品物を待ってろ、俺はこれから狩りに行くぜ。";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "哀れな運命だな……奴らはここから決して出られねえ。";
			link.l1 = "ロドガー…いや、ロドリゴ！まず第一に、奴らは出て行くかもしれねえ。それに第二に、 もしトルクス島で他の誰かに会ってたとしても、お前の運命は大して良くなかったはずだぜ。";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "それはよく承知していますよ、船長。そして、そのことは忘れていません。では、 この工場の運営についてご説明しましょう。来月から、毎月十五日に加工済みのバカウト材を四十本納品します。 もちろん、毎月の納品ごとにわざわざ来ていただく必要はありません――すべての分はここ工場で保管し、あなたのお越しをお待ちしています。\n";
			link.l1 = "じゃあ、一度にいくつかの荷をまとめて受け取れるのか？";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "もちろん常識の範囲内で頼むぞ――あまり長く留守にするな。\n人は何年も給料なしで働けないし、唯一の取引相手が生きているかどうかも分からないままじゃやっていけねえ。\n俺の考えじゃ、六回分の荷を届けたら、しばらく取引を休止するつもりだ。";
			link.l1 = "一度に全部の商品を集めなきゃいけないのか？それと、値段はどうだったか、もう一度教えてくれないか？";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "ああ、一度に全部だ。標準的なバカウト材一本の値段はドゥブロン金貨十枚だ。それに加えて、 一回の取引ごとに上質なラム酒五本と同じ数のワインボトルを渡してもらう。ロドガー曰く、 こんな値段は世界中どこを探しても見つからねえってさ。";
			link.l1 = "確かに、俺も同感だ！ありがとう、ロドリゴ。さあ、仕事に取りかかろうぜ！";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "素晴らしい！さあ、仕事に戻るぞ！";
			link.l1 = "「よし。」";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "もちろんだ、船長、持っていきな。次の出荷用に用意してあるバッチは以下の通りだ：\n "+sti(pchar.questTemp.IslaMona.Factory.Part)+"、それが "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" 丸太だ。だから、お前は俺たちに借りがあるんだ "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" ドゥブロン金貨 "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" ラム酒の瓶、それに "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" ワインの瓶、全部そろってるか？";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "もちろんだ。これが報酬だ。";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "どうやら全部は揃っていないようだ。すぐに持ってくる。";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "素晴らしい。工場からあなたの倉庫へバカウトを運ぶぜ、そこから好きな時に引き取ってくれ。";
				link.l1 = "いいだろう。次の分を用意しろ。";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "待ってくれ、船長！倉庫が満杯だ――収穫したバカウトを全部積み込めねえぞ。倉庫のスペースを空けてから、また俺のところに来てくれ。";
				link.l1 = "わかった、俺が片付けてやる。";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "もちろんだぜ、船長！";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "はっ！船長、これ以上何かを建てるのは無駄な愚行でぜいたくだと思いますぜ。……ただし、もし……";
			link.l1 = "「何がなければ？」";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "船長、こんなことを聞くのは気まずいんですが……もうこの場所にかなりの金を投資してますよね！";
			link.l1 = "売春宿か？";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "「教会か？」";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "サンティアゴ聖人に誓って、それも悪くねえな！\nだが初日の夜には、うちの女たちが燃やしちまうさ。俺たちごと、な。\nいや、船長、俺が言ってるのは教会のことだ。\nそうさ、住む所も給料も悪くねえし、海も娯楽もある。家族も仲間もいる。\nだが、それでも何かが足りねえんだ、わかるだろ？";
			link.l1 = "想像できるよ。";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "お見通しですね、船長。そう、住む場所も給料も悪くないし、海も娯楽もある。家族も仲間もいる。\nでも、やっぱり何かが足りないんだよ、わかるか？";
			link.l1 = "想像できるぜ。";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "その通りです。あなたの助けなしでは神の家を建てることはできません。こういう場所は特別で、 この世のものとは思えぬほどでなければなりません。だからこそ、高くつくのです。ろうそく、金の延べ棒、琥珀、 そしてもちろん建築資材も必要ですが、安物ではいけません。あなたには何の利益ももたらしませんので、 お願いするのも恐れ多いのです。";
			link.l1 = "それで、ここに神父を連れてくる必要があるのか？";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "いやだ。";
			link.l1 = "「お前たちの中にもう神父はいるのか？」";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "いいえ、船長。もうすべてお分かりだと思います。";
			link.l1 = "それで、異端審問の聖職者たちがお前たちを迫害する理由があったのか？お前たちは異端者なのか？";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "教会法によれば、俺たちは最悪の異端者だ。神と交わるのに、この世の仲介者が必ずしも必要だとは信じていねえからな。 ";
			link.l1 = "この世からか？";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "船長、俺たちはサタニストじゃねえし、俺たちの共同体もカルトなんかじゃねえ。 俺たちもあんたと同じくキリスト教徒だが、物事をかなり広い視野で見ているんだ。学のある立派な連中からすりゃ、 広すぎるって言われるくらいにな。\nもしあんたの心に少しでも寛容さや理解の余地が生まれたら、もっと詳しく話してやるさ。だが今は、 とりあえずこのリストを受け取ってくれ。念のためにな。";
			link.l1 = "もっと早くこのことを話してくれればよかったんだ、ロドリゴ。ある日突然戻ってきて、 自分の土地で魔女の集会や新しい宗教が生まれていたら困るからな！\nお前は待っていろ――俺が決断を下す。";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "見事な一覧だな。どうして神父たちがそんなに金を必要とするのか、だんだん分かってきたぜ！ロドリゴ、 お前の申し出について考えて、決断を下すとしよう。";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "もし結果が良ければ、あんたのリストにある品物を全部倉庫に運ぶぜ、そして宝物はテーブルに並べてやるからな。";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "もし結果が良ければ、お前のリストにある品を全部倉庫に運び込むぜ。それから宝物はテーブルの上に並べてやる。";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "我々一同を代表して、感謝します、船長。絶対に後悔はさせません、誓います！";
			link.l1 = "お前がまったくの手抜きで作ったら、俺は後悔するだけだぜ。";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "船長、建築資材はすべて揃っております！\n指定された贅沢品をお持ちいただければ、すぐに建設を開始いたします。それらは宝飾品や儀式用の道具に使われます。\n改めて、ありがとうございます、船長！\nムチャス・グラシアス！";
			link.l1 = "どういたしまして！";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "本当にありがとうございます、船長！すべて準備が整いましたので、これから建設を始めます。最初のサービスのために、 2、3か月後にまた来てください。\nあ、それからもう一つ、ぶどうがちょうど熟しました！自家製ワインを作って、お祝いをして、 あなたのために宴を開きますよ！";
				link.l1 = "俺たち全員、祝うに値すると思うぜ。二ヶ月後に戻ってくるからな。";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "船長、まだ "+sAdd+" 「出発した。」";
				link.l1 = "もちろん、もう少しだけ時間をください。正直言って、ろうそくがなけりゃ、お宝を埋めるつもりかと思うところだぜ。";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "ハハハハハハハハハハハ！";
			link.l1 = "俺はてっきり、その馬鹿げた癖はもう直したと思ってたぜ。";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "that we won't have to sit here for weeks waiting for events to unfold.";
			else sTemp = "that not everyone will have to participate in the battle.";
			dialog.text = "ハハハハハ……はあ。俺もそう思ったぜ、船長！ロドガーの言う通り、あんたがここにいるってことはすでに―― "+sTemp+"";
			link.l1 = "もう何が起きたかは知っている。負傷者はいるか？";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "そんなに気にするな、ロドガー。お前のせいじゃねえ、銃兵どもが早すぎたんだ。 どうせ俺たちの陣地の後ろに抑えておくことなんてできなかったし、全員斬り捨てる時間もなかったんだぜ。";
			link.l1 = "スペイン人たちはどうするんだ？";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "三人だけがこちらまでたどり着き、生き残ったのは一人だけだった。その一人が船長本人だ！ どうやらかなり高位の海軍士官らしい。しかし、まだ助けにならない――少なくともあと二、三日は寝たきりだろう。\nところで船長、俺たちは銃声を聞いたし、あんたの様子を見る限り、あんたも聞いたんだろう？";
				link.l1 = "そうとも言えるな。招かれざる客どもは、まさかこんな不意打ちを食らうとは思ってなかったらしく、 海へ叩き落とされたぜ。";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "三人だけがここまでたどり着き、そして生き残ったのは一人だけだ。船長本人さ！どうやら、 かなり厳格な海軍士官らしいぜ。だが、まだ助けにはならねえ――あと数日は寝てなきゃならねえんだ。\n";
				if (i >= 50) 
				{
					link.l1 = "前回、俺はここにかなりの部下を警備に残していったはずだ。 だからお前たちの方がフュジリア兵よりずっと多かったはずだろう。どうして一気に全員を海に叩き込まなかったんだ？\n";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "よし、この問題を片付けよう。作戦はこうだ：俺が奴らをおびき出して正面から攻撃する、そして今すぐやるぜ。 ぐずぐずしても意味がねえ。散弾とマスケットの用意をしろ、海賊どもは門で待機、他の連中は家に残ってじっとしてろ。 ";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "船長、あいつらは全員が職業軍人で、指揮官までいるんだ。こっちはまともな武器すら持ってねえ。もちろん、 数で押し切ることもできたかもしれねえが、それじゃあ少なくとも倍以上の犠牲が出てただろうし、 ここじゃ一人ひとりが大事で必要なんだぜ。";
			link.l1 = "よし、この問題を片付けよう。計画はこうだ：俺が奴らをおびき出して正面から攻撃する、しかも今すぐだ。 ぐずぐずしても意味がねえ。散弾とマスケットの準備をしろ、海賊どもは門で構えろ、残りは家にいて――じっとしてろ。\n";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "船長、戦う準備はできてるぜ！";
			link.l1 = "分かってるさ、ロドリゴ。だが、まだ話は終わっちゃいねえ。もし敵が一人でも門を突破したら、 全員で四方八方からそいつに襲いかかるんだ。戦いの最中なら、弾や破片に当たる確率も減るってわけさ。 ほかに質問はあるか？";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "よくやった！もちろん、仲間たちがそんな運命に遭ったのは残念だが、また俺たちの味方になってくれて感謝しているぜ。 ";
			link.l1 = "簡単じゃなかったさ、ロドリゴ。普通の奴らなら裏切りだと言うだろうし、その通りだ。";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "ここは俺の土地だ、ロドリゴ。誰が相手でも、必ず守らなきゃならねえんだ。";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "ああ、ロドリゴの爺さんはカディスを出たとき、まさか新世界でこんな冒険が待ってるなんて思いもしなかっただろうな。 ";
			link.l1 = "言わなくてもわかるぜ。俺も時々まったく同じことを考えるんだ。";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "もちろん、あなたの仲間たちがそんな運命に遭ったのは残念だ。しかし、再び我々の味方になってくれて感謝している。";
			link.l1 = "簡単じゃなかったんだ、ロドリゴ。普通の奴らなら裏切りだと言うだろうし、その通りだ。";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "ここは俺の土地だ、ロドリゴ。誰が相手でも、必ず守らなきゃならねえんだ。";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "承知しました、船長。それでは、あなたが不在の間に我々の居住地で起こった状況を簡単にご説明させていただきます。";
			link.l1 = "本当か？ちょっと待て……船長？";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "承知しました、船長。それでは、あなたが不在の間に我々の居留地で起きた状況について簡単にご説明いたします。";
			link.l1 = "本当か？待てよ……船長？";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "悪気はなかったんだ。ただ、ロドガーがあの言葉をあまりにも旨そうに言うから、俺も使ってみたくなっただけさ。 すごく…海賊っぽいだろ。";
			link.l1 = "問題ない、ただ驚いただけだ。で、ここで何があったんだ？";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "まずは教会を建てたんだ。少し時間がかかるが、中に入ってくれ。見せたいものがある。船長、 あんたは偉大なことをしてくれたぜ。あんたにはそうは思えないかもしれねえが、 神と語り合えることは俺たちにとって本当に、本当に大事なんだ。今日から俺たちはイスラ・モナを我が家と呼ぶぜ。";
			link.l1 = "我が家、甘い我が家ってか？絶対に見てやるぜ。せっかくあんなにロウソクを運んだのに無駄だったのか？";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "タダじゃねえぞ！それに、工場は潰れちまった――労働力も全部失ったんだ。新しい奴隷を一団連れてこなきゃならねえ。だが幸いにも、仕事の効率を見直した結果、 奴隷は十人いれば十分だと分かった。だから、お前の手間も減るってわけだな。";
			link.l1 = "わかった。他に何かあるか？";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "祝宴の準備はすべて整った。いや、ほとんどだな……ここを片付けて、不運な者たちの遺体を埋葬しなきゃならん……だから、明日教会に来てくれ、そこで始めるぞ。";
			link.l1 = "教会へ？宴の始まりにしては妙な場所だな。ロドリゴ、お前、まさかプロポーズでもするつもりか？";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "ははは！いや、船長、うちの娘たちの中には歓迎する者もいるがな。あんたがやる分には俺たちは気にしねえぜ。";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "同意だ、明日教会に行くぜ。もちろん祈るためにな。";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "それからもう一つだ、船長。祝宴の前に、まず囚人の件を片付けてくれ。決断は下さねばならんし、 どちらにせよ気が重いのは分かっている。";
			link.l1 = "わかった。今すぐ行くぜ。";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "みんな集まってるぜ！旦那、あんたが最初にこの場所に何を求めてたのか、今はどう思ってるのか、 俺たちには分からねえ。でもな、俺たちにとっては、最初は仕方なく逃げ込んだ避難所だったが、 今じゃ本当の故郷になっちまった。あんたの水夫も、海賊も、スペインから逃げてきた異端者も、ここで暮らしてる。 ほかのどこにいたって、俺たちはとっくに殺し合ってただろう。でもここじゃ、みんな友達だし、一緒に働いて、 人生を楽しんでる。イスラ・モナは、この世界の地図の上で誰にとっても最終目的地じゃねえが、もしかしたらここで、 人生で一番幸せで実りある年月を過ごすのかもしれねえ。これは全部、あんたの成し遂げたことだ。この土地も、この人々 も、あんたのものだ。ムチャス・グラシアス、\n "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "わかった、わかった。船長、俺たちはあんたのために贈り物を集めたんだ――役に立つものや、ただ嬉しいものがたくさんあるぜ。いくつかは持ってきたもので、いくつかは自分たちで作ったんだ。 どうかこの贈り物を素直な気持ちで受け取ってくれ、残りは俺たちが汗水流して働いて渡すからな。";
			link.l1 = "ありがとう……まさかこんなことがあるとは思わなかった。俺の旅路には、明るい瞬間や人間らしい優しさなんて本当に少ないんだ……だから、これは俺にとって大きな意味があるんだ、信じてくれ。";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "さあ、仕事に戻るぞ！";
			link.l1 = "いや、今は――酒場へ行くぞ！ロドリゴ、行くぞ！";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "ああ、この素晴らしいひとときをもう少し味わおうじゃねえか。";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "「ハハッ！　ひっく！」";
			link.l1 = "ところで、最近は何もかもにやたらと笑い転げるのをほとんどやめたようだな。カリブの新鮮な空気のおかげか？";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "どちらかと言えば、ロドガーの腐った影響だな。あいつを見てて、何もかもくたばれって思うことを覚えたぜ。";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "俺はあそこの立派な人たちをたくさん知ってるぜ。";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "いや、俺はラムを飲み続けて、お前をにらみつけていたいんだ。";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "船長！ひっく！";
			link.l1 = "ああ、ロドリゴ、お前も元気そうだな。今夜は色々あったみたいじゃねえか？";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "聞かないほうがいい……。一ヶ月……酒はやめるぜ。ああ、そうだ！知らせがある！船長が……正気に戻ったんだ。";
			link.l1 = "生き残った唯一のスペイン人か？";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "ひっく！いてっ！ああ、あいつはファクトリーに入れられて、見張り付きの家にいるぜ。";
			link.l1 = "そうか。俺があいつのところへ行く。無理しすぎるなよ。";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "ひと泳ぎしてきたら、すっかり元気になったぜ！俺たちは生きて働くんだ。 できる限りファクトリーを動かし続けてみるつもりだ。まあ、修理やちょっとした建築作業もやるさ。もしかしたら、 うちの奴と子どものことも考えるかもな。";
			link.l1 = "みんな、本当に良かったな！すごく神経がすり減って、金もかかった……でも素晴らしい冒険だったし、俺たちにとってうまくいって嬉しいぜ。みんなに幸運を、 そしてこれから出航する仲間にはさらに大きな幸運を祈るぜ！";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "止まれ！伍長 "+GetFullName(npchar)+"。ここは戦闘区域だ！すぐに身分とここにいる目的を名乗れ！";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "伍長、下がれ！ "+GetFullName(pchar)+"フランス海軍の船長だ。貴官の上官のもとへ私を護衛せよ。命令を実行しろ！";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+"「『」という名の船の船長"+pchar.ship.name+"まったくの偶然でこの島に到着した――修理の可能性と真水の補給のためだ。";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "はい、旦那船長！どうぞこちらへお進みください。お願いです、どうかお気をつけて！この島は盗賊だらけなんです。";
				link.l1 = "";
			}
			else
			{
				dialog.text = "失礼します、船長。制服を着ていないので、士官任命書を確認させていただきます。";
				link.l1 = "見ただろう？満足か？さあ、さっさと命令を実行しろ、伍長！";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "俺と一緒に来てもらうぞ、船長。上官があんたと話すそうだ。今この瞬間から、 あんたの船はフランス海軍の必要により一時的に徴用されたと見なす。今すぐ当直に知らせて、俺について来い。";
			link.l1 = "「チャールズ・プリンス号を徴用するだと？そんなこと、俺は認めねえぜ！」";
			link.l1.go = "Capral_5";
			link.l2 = "どうやら選択肢はなさそうだな。言われた通りにするぜ。";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "船長、敵の野営地への道は右手にあります。俺がご案内します。";
				link.l1 = "下がってくれ、伍長。俺は一人で行きたいんだ。";
			}
			else
			{
				dialog.text = "船長、敵の野営地への道は俺たちの右手だ。迷うことはねえぜ。";
				link.l1 = "ご心配いただきありがとうございます。";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Captain "+GetFullName(pchar)+"！神に感謝します！自己紹介させてください―中尉 "+GetFullName(npchar)+"。あなたの大ファンだよ！こんなみじめな土地で何をしているのか知らないが、ちょうどいい時に来てくれた！\n正直に言うと、船長、あなたは我々の士官たちの間で非常に人気者になっている。あなたの…「独特」なやり方に苛立つ者も多いが、みんなあなたの任命によって艦隊が強くなったことは認めている。 今は完全な膠着状態だから、あなたのような人物の助けは計り知れないほど貴重だ！";
				link.l1 = "俺に何ができるんだ？それと、ここで何が起きてるんだ？";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Captain "+GetFullName(pchar)+"。艦隊の報告書で何度も君の名前が挙がっている。しかも、いつもあまり芳しくない内容だ。だが、 今こそこの不名誉な流れを断ち切り、祖国に尽くすチャンスだぞ。";
				link.l1 = "俺に何ができる？それに、ここで何が起きてるんだ？";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "俺たちは「ウォリアー号」に乗ってたんだ。任務はごく普通――特に大胆なスペインの襲撃者どもを狩るってやつさ。やることは単純だぜ。間者が標的のエリアと情報を渡してくれて、 こっちは水平線の向こうから仕留めるだけ。特に語ることもねえが、結末は最悪だった。 スペイン野郎どもが先に俺たちを見つけて攻撃してきやがったんだ。しかも自分たちもコルベットなのによ。 もしもっとマシな船だったら、あいつらと一緒に海の藻屑にはならなかっただろうが……せめてやつらの船体ごと吹き飛ばしてやったぜ。生き残ったのは俺の部隊だけだ。 カスティーリャの連中も何人か生きてたがな。もっとも、長くはなかったがな、ははっ！\n";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "フリゲート艦『ウォリアー』のことか？ショック船長は死んじまったのか？";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "彼のことを聞いても驚きませんよ、船長。あなたが『アルカンタラ』を拿捕した件については耳にしています。 大した手柄です――その時点で、すでに特許の礎を築いていたのですね！ショッケ司令官は死んでいません――むしろ逆です！昇進して、本人の希望で地中海勤務に就きました。今の我々の状況を考えると、 彼がうらやましい限りです。さて、実はその我々の状況についてですが……\n";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "島で集落を見つけたぜ――しかも、聞いて驚けよ――海賊とスペイン野郎どもが一緒に住んでる、まるで賑やかな盗賊の巣窟だ。信じられるか？普通なら、 あいつらは互いに斬り合ったり吊るしたりするもんだが、ここじゃ――見ろよ、群島のど真ん中で、まるで家族みてぇに協力してバッカニアの木材を採ってやがる。 自分たち用に桟橋まで作りやがって、見たか？ここに来る客は手漕ぎボートなんかじゃ来ねえんだ。 俺たちの任務は至って明快だぜ：お前の力を借りて集落を制圧し、バッカニアの木材と捕虜を手に入れ、 お前が全員をカプスターバーグまで連れて行く。その間に役人どもは勝手に頭を悩ませるだろうよ……で、あいつらが悩んでる間に、俺たちはバッカニアの木材を片付けて、 俺の本隊の士官連中と盛大に祝杯をあげるって寸法さ！\n";
			link.l1 = "今まで自分でその居留地を奪わなかった理由は何だ？";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "There are probably many more bandits than us - we saw tents on the shore. And besides tents, they also have a wall, gates, cannon!";
			else sTemp = "There are probably not so many bandits, otherwise they would have kicked us out of here already, but they still have a wall, gates, cannon and plenty of time!";
			dialog.text = "何が俺たちを止めたって！？俺たちにはフジリア兵が十二人、水夫が七人しかいねえ。全員くたびれてボロボロだ。 マスケット銃も五丁しか救えなかったし、せいぜい一発分の弾しかねえんだぞ！ "+sTemp+"";
			link.l1 = "「でも、策はあるのか？」";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "聞けよ、俺たちは時間なんて無駄にしちゃいねえ。まず最初にこの工場を乗っ取って、 食料と水の補給品を手に入れたんだ。だが一番の収穫は、バッカニア用の木材が満載の倉庫と十数人の奴隷さ！ どうせ奴隷どもを見張る余裕なんてなかったから、すぐに武力偵察を兼ねて、奴らを元の主人どもに向かわせたんだ、 俺たちのマスケット銃で援護しながらな。そしたら、あの盗賊どもが武器を隠し持ってやがるって分かったってわけさ。";
			link.l1 = "俺の理解で合ってるか？今度は奴隷の代わりに、俺と部下をその武器の始末に行かせたいってことか？";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "いや、だが休戦旗を掲げて賊どものもとへ行くことはできる。お前が来たことで奴らの隠れ家は露見し、 今や王の兵士たちは船と増援を手に入れた。さて、奴らが警戒して様子を探っている間に、 できるだけ大砲に近づいて手榴弾をその下に投げ込め。味方やお前の部下が到着するまで死なないようにな。 自信がないなら、代わりに部下の誰かを行かせてみろ。";
			link.l1 = "まずは爆弾なしであいつらのところへ行って、降伏の機会を与えてみるぜ。\n周囲を見渡し、やつらの様子や戦力を探って、不安の種を心にまいてやる。\nもし降伏しなけりゃ、今度は爆弾を持ってもう一度行くさ。";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "…その頃には、もうあんたに慣れてるだろうから、破壊工作もしやすくなるってわけだ！賢いな！さすがだぜ、船長。 準備ができたら始めてくれ。だが、これも持っていけ…役に立つかもしれねえ。";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "…その頃には、やつらもお前に慣れているだろうから、破壊工作もやりやすくなるはずだ。そうするぞ。続けろ！";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "この辺りでスペイン人との激しい戦闘があったんだ。両方の船が沈み、生き残った者たちがここに流れ着いた。 大半はフランス人だが、敵の何人かも生き延びたんだ。\nそれ以上のことは話せない、悪いな、船長。機密事項なんだ、察してくれ。";
			link.l1 = "承知した。";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "島で集落を見つけたぜ――しかも、かなりの人数がいる盗賊の巣窟だ。聞いて驚けよ、海賊とスペイン野郎が一緒にいるんだ。信じられるか？ 普通なら、あいつらは互いに斬り合ったり吊るし合ったりするもんだが、ここじゃ――見ろよ、群島のど真ん中でまるで家族みてぇに協力してバッカニアの木材を採ってやがる。 自分たち用に桟橋まで作ってやがるのを見たか？この連中のところには、客が手漕ぎボートなんかで来ることはねえ。 俺たちの任務は至って明快だ――お前の力を借りて集落を制圧し、バッカニアの木材と捕虜を奪い、お前が全員をカプスターバーグまで連れていく。 その間に役人どもが勝手に事後処理をするだろうさ…そして、そいつらがごちゃごちゃやってる間に、 お前にもちょいと貴重な材木を好きなだけ持っていくチャンスをやってもいいと思ってるんだ。";
			link.l1 = "今まで自分でその居留地を手に入れなかった理由は何だ？";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "来たな！何か新しい知らせはあるか？";
			link.l1 = "これは儀仗兵か？";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "明らかに、次の行動についてはまもなく決定されるだろう。 新たな命令を出すために島中で自分の部下を探し回る羽目にはなりたくないな。";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "素晴らしい判断だ！命令を出すぞ。偵察は済ませた。敵は弱く、大砲も弾切れだ。直ちに賊どものアジトを攻撃せよ、 中尉。手をかばっている場合じゃない。艦隊ではこれが日常だ。実行せよ！";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "俺の考えじゃ、「奴隷」偵察の後ですぐに力ずくで奴らを取れたはずだぜ。防御なんて笑っちまうほどだ、 まともな戦士はほんの数人だしな。あれこれ考える必要なんてねえ――今ごろは鉄木の山に座りながら戦利品のワインを飲んでたってのによ。";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "了解だ、船長！";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "「これが君の偵察の結果か？軍人ではない者に多くを期待するのはおかしいかもしれんが、私は事実が必要なんだ！ 事実だ、船長、君の意見ではなく！」";
			link.l1 = "俺を侮辱したな、中尉。報告するぞ！";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "今ここに、あんたが沈めたスペイン船の生き残りの船長が俺たちと一緒にいるんだ。経験豊富な指揮官で、 すぐに回復するだろう。もしぐずぐずしてたら、あいつは回復して軍学通りに防衛を組織するぞ、 そうなったら手強くなる。急がないといけねえ――繰り返すが、今の奴らは弱って士気も下がってるんだ。";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "援軍がもうすぐ来る――バッカニアの材木を押収するためにな。はったりじゃねえと思うぜ。お前自身、 波止場と工場倉庫に積まれた出荷待ちの品を見ただろう。急がなきゃならねえ――もう一度言うが、奴らは弱って士気も下がってる。ぐずぐずしてると、海賊船の到着を待つ羽目になるぜ。";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "この穴蔵の住人のほぼ半分は女だ。お前が戦ってきたのは民兵ですらねえ。 ずっと相手にしてきた戦闘員はせいぜい十数人だ。奴らは弱くて士気も下がってるぜ。";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "大砲の弾薬が尽きた。俺はこれまでに山ほど大砲を見てきたから、 乗組員が発射の準備ができているかどうかはすぐに分かる。砲がなけりゃ、あいつらはただの情けない戦士だ。 弱くて士気も下がってるぜ。";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "戦利品と栄光のことを考えてみろ、少尉！スペインの襲撃者に単独で勝利し、盗賊の巣を制圧し、 バッカニアの木の特別な供給源を手に入れる――これらすべては自分の船を指揮するにふさわしい手柄だぜ！もう一度言う、奴らは弱って士気も下がってる、 今こそ叩き潰す時だ！";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報ですし、あなたの言う通り、ここでぐずぐずする必要はありません。 俺の部下は全員揃っていて、強く、訓練されており、準備もできています。すべては三十分で終わります。船長、 あなたの船で人員、捕虜、そして積荷を受け入れる準備をお願いします。ここには長居しません。";
				link.l1 = "準備は万端だ、少尉。あんたを待ってただけさ。また後で会おう！";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報だ。その場合は、桟橋へ向かい、乗り込み部隊の準備をしてくれ。 俺たちは一緒に賊どもの巣をすぐに急襲する。俺の部下とお前の部下の中でも最精鋭が先陣を切る――やつらが門を制圧するのだ。残りのことは、共に兵力を点検した後で話そう。俺や祖国を失望させるなよ。 "+GetFullName(pchar)+".";
				link.l1 = "……そうか。ではまたな、中尉。";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報ですし、あなたの言う通り、ここでぐずぐずする必要はありません。 俺の部下は全員揃っていて、強く、訓練され、準備万端だ。すべては三十分で終わるだろう。船長、あなたの船で人員、 捕虜、そして積荷を受け入れる準備をお願いします。ここには長居しません。";
				link.l1 = "準備は万端だ、少尉。あんたを待ってただけさ。また後でな！";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報ですな。\nそれなら、桟橋へ向かい、乗り込み部隊の準備をしてください。俺たちは一緒に賊どもの巣をすぐに急襲する。\n俺の精鋭とあなたの部下の中でも選りすぐりの者たちが先陣を切る――やつらが門を奪取する役目だ。\n残りのことは、共に兵を点検した後で話し合おう。\n俺やあなたの祖国に恥をかかせるなよ。 "+GetFullName(pchar)+".";
				link.l1 = "……そうか。ではまたな、中尉。";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 70, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報ですし、あなたの言う通り、ここでぐずぐずする必要はありません。 俺の部下は全員揃っているし、精鋭で訓練も万全、準備もできている。すべては三十分で終わるだろう。船長、 あなたの船で人員、捕虜、積み荷を受け入れる準備をしておいてください。ここには長居しません。";
				link.l1 = "準備は万端だ、少尉。あんたを待ってただけさ。また後で会おう！";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 70, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報ですな。そういうことなら、桟橋へ向かい、 乗り込み部隊の準備をしてください。俺たちはすぐに一緒に賊どもの巣を襲撃する。 俺の部下とあんたの部下の中でも精鋭が先陣を切る――やつらが門を制圧するのだ。残りのことは、共に兵力を確認した後で話そう。俺や祖国に恥をかかせるなよ。 "+GetFullName(pchar)+".";
				link.l1 = "……そうか。では、また会おう、中尉。";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報ですし、あなたの言う通り、ここでぐずぐずする必要はありません。 俺の部下は全員そろっていて、強く、訓練も十分、準備万端です。すべては三十分で終わります。船長、 あなたの船で人員、捕虜、そして積荷を受け入れる準備をお願いします。ここには長居しません。";
				link.l1 = "準備はすべて整ったぜ、中尉。あんたを待ってただけだ。じゃあ、またな！";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報ですな。では、桟橋へ行き、乗り込み部隊の準備をしてください。 すぐに一緒に盗賊どもの巣を強襲します。私の部下とあなたの部下の中でも精鋭たちが先陣を切り、 門を制圧する役目を担います。残りのことは、共に兵力を確認した後で話しましょう。 私やあなたの祖国を失望させないでください。 "+GetFullName(pchar)+".";
				link.l1 = "……よかろう。また後で会おう、中尉。";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				Notification_Skill(true, 90, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報ですし、あなたの言う通り、ここでぐずぐずする必要はありません。 俺の部下は全員揃っていて、強く、訓練も積んでおり、準備万端です。すべては三十分で終わります。船長、 あなたの船で人員、捕虜、そして積荷を受け入れる準備をお願いします。ここには長居しません。";
				link.l1 = "準備は万端だ、少尉。あんたを待ってただけさ。また後でな！";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Skill(false, 90, SKILL_LEADERSHIP);
				dialog.text = "ありがとうございます、船長。これは貴重な情報ですな。そういうことなら、桟橋へ向かい、 乗り込み部隊の準備をしてください。俺たちは一緒に賊どもの巣をすぐに襲撃するぞ。 俺の精鋭とあんたの腕利きが先陣を切る――やつらが門を制圧する役目だ。残りのことは、共に兵力を確認した後で話し合おう。俺や祖国を失望させるなよ。 "+GetFullName(pchar)+".";
				link.l1 = "……よかろう。また会おう、少尉。";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "それなのに、俺はバカみたいにお前を称賛してたんだ！ああっ！フランスの誇りよ、船長 "+GetFullName(pchar)+"！！お前にはその特許状の資格がねえ！！";
			else dialog.text = ""+GetFullName(pchar)+"、クズ野郎、裏切り者、そして呪われた海賊め！この忌々しい巣窟がお前の臭い縄張りだと気づくべきだったぜ！ フランスはお前のような奴を決して忘れも許しもしないからな！";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "準備はいいか、船長？お前の船員たちは頼もしいぜ！";
			link.l1 = "ありがとうございます、中尉。始めましょうか？";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "ああ、すぐに進もうぜ！";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "「はっ！」 "+GetFullName(pchar)+"！なんてこった、こんなところで会うとはな。おい、そいつを捕まえろ！こいつがここを全部仕切ってやがるんだ！ この島はこいつのもんだぞ！";
			link.l1 = "なんて日だ……";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "船長、ご命令は？待機して強襲隊を送れという合図が出てるぜ。";
			link.l1 = "命令は変わらねえ。野郎ども、ついて来い、俺たちの家から厄介者を追い出すぞ。獲物は俺のもんだが、 戦利品はお前らのもんだ！";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "「おおっ！」";
			link.l1 = "戦闘開始だ！";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "ごきげんよう、旦那。この土地の持ち主でいらっしゃいますか？自己紹介させていただきます。 私はグラン・フランシスコ・デ・アルバ、かつて『ペロ・マリノ』コルベットの船長でございました。";
			link.l1 = "ああ、ここは俺の土地だ。俺は "+GetFullName(pchar)+"「、『」の船長"+pchar.ship.name+"「……壮観だと？こんな立派なお客人はここに来たことがねえよ。」";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "「ああ、旦那」 "+GetFullName(pchar)+"！お前の名前は有名だぜ。最近、カサ・デ・コントラタシオンの報告書にお前の名前がやたらと出てくるもんだから、 てっきりお前を始末しろという命令が来るんじゃないかと本気で思ってたんだ。";
			link.l1 = "俺とやり合うつもりか？";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "もうごまかす意味はないと思う。俺の仕事は、世界中の海でスペインとフェリペ王の敵を見つけ出し、滅ぼすことだ。";
			link.l1 = "そのような命令がまだ来ていないのは幸運だ。あなたは明らかに非常に優秀な海軍士官だ。";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "今こうして俺が、海賊だらけの小島で半死半生の囚人になり、同胞たちも逃亡中って事実が、 あんたの結論を裏付けてるな、はは！本当に危険な任務だったが、命令は命令だ。もう少しで成功するところだった！ 部下たちには本当に申し訳ない――みんな名前まで知ってたし、長年一緒に仕えてきたんだ。だが、帝国の威信を保つためには、 我が国はこれからも息子たちの血を流し続けなきゃならん。我が家はそのことを誰よりもよく知っている。";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "今はもっと差し迫った問題に戻ろう。さて、グランド、お前をどうしたものか。";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "ところで、ド・モール旦那、『ウォリアー』――あの小さな船には見覚えがあったんじゃないか？ポルトベロでのお前の大胆な作戦、見逃されてはいなかったぜ。無謀、 いや自殺行為と言ってもいいくらいだ。金が相当必要だったんだろう？ははっ！";
			link.l1 = "おれのことをよく知ってるな、グランド。だが、そろそろお前の運命について話そうぜ。";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "考えることなんてあるか？どんな良い物語でもそうだが、選択肢は三つだぜ。俺を殺すか、ここに置き去りにするか、 自由にするかだ。もし俺を自由にしてくれるなら、デ・アルバ家の名にかけて、 この場所やお前が俺の災難に関わったことは誰にも絶対に口外しないと誓う。それに、俺はお前に借りができる。 その借りを返すまでは、絶対にお前に刃向かうことはない。";
			link.l1 = "俺には無理だ、グランド。";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "ここでしばらく過ごすことになる。\n同胞たちと対等な立場で暮らし、働くのだ。";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "俺の船へようこそ、グランド。時が来たらサンティアゴ灯台にお前を上陸させてやるぜ。約束は守ってくれるだろうな。";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "分かった、旦那。まあ、どのみち俺はあの戦いで部下たちと一緒にもう死んでるんだ。いい結末さ。";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "正直に言うと、俺は中途半端なのが嫌いだ。だが、捕虜になることに不名誉はない。だから、 お前の命の恩恵を受け入れて、この親切で、どうやらとても幸せそうな人々と平和に暮らすつもりだ。\nそれでも、もしここを出ることがあれば、お前に借りはないからな。";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "俺が約束する、そしてデ・アルバ家の名にもかけて誓う！船で会おうぜ！";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Captain "+GetFullName(pchar)+"！命を救い、私を元の場所へ連れ戻してくれたのですね。あんな危険を冒すのがどれほど大変だったか、よく分かります――私には到底できなかったでしょう。恩義があります、旦那。あの不運な戦いの事情については、 決して誰にも口外しないと誓います。もしあなたが旧世界に戻ることがあれば、必ず私を訪ねてください。 マドリードの我が家の屋敷は、いつでもあなたを歓迎します。今は、これを受け取ってください…";
			link.l1 = "地図の一部か？";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "俺が持っていた価値のあるものはそれだけだ。他の欠片もきっと簡単に見つかるだろう。さらばだ！幸運を祈るぜ、友よ。 ";
			link.l1 = "さらばだ、グランド。約束を忘れるな、幸運を祈るぜ！";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("ごきげんよう！調子はどうだ、船長？俺たちはうまくやってるぜ。","「共同体のために働くことこそ、最高の喜びだぜ！」","あなたの島は素晴らしいですね、船長。私たちはその繁栄のためにできる限りのことをしますよ。");
			link.l1 = LinkRandPhrase("それは良かった。","すべて順調だと聞いて安心したぜ。","お前の情熱には感心するぜ、旦那。");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("無礼だとは思わないでくれ、旦那、だがここで暮らすのは無理だ。","異端審問官の牢屋に座っているよりは、何だってマシだ……"),RandPhraseSimple("助けてくれてありがとうございます、船長。","「こいつら……海賊はお前の仲間か？」"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("ここも悪くねえな！ただ、ちょっと退屈だぜ。","船長、会えて嬉しいぜ。たまには寄ってくれよな！"),RandPhraseSimple("誰かが浜辺で頭蓋骨を見つけて朝の集会に持ってきたんだ。ここじゃいつもこんな感じなのか？","秘密を教えてやろう、ジメネス旦那は明らかにこの場所の新鮮な空気と安全に恩恵を受けているんだ。"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("ここも悪くねえな！ただ、ちょっと退屈だぜ。","船長、会えて嬉しいぜ。たまには寄ってくれよな！"),RandPhraseSimple("誰かが浜辺で頭蓋骨を見つけて、朝の集会に持ってきたんだ。ここじゃいつもこんな感じなのか？","秘密を教えてやろう、ジメネス旦那は明らかにこの場所の新鮮な空気と安全さの恩恵を受けているんだ。"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("神のご加護を、船長！","週に一度、浜辺や酒場で芝居をやってるんだ。たまには寄ってくれよ。"),RandPhraseSimple("お前さんの水夫たちは、いつもいろんなガラクタを新鮮な食べ物と交換しに持ってくるんだ。 こういうやり取りを促してくれて感謝するぜ。","ここがまだ誰にも見つかっていないなんて驚きだな。\nこのまま誰にも知られずにいてほしいぜ。"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "ありがとうございます、旦那。あなたのおかげで、本当の新世界を見ることができました。神のご加護を！";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("安全と平和――それがこの場所の好きなところだぜ！","素晴らしい楽園だ！まあ、ほとんどな……","こんなにも多くの苦難を乗り越えて、ここで新しい故郷を見つけられて嬉しいです。");
			link.l1 = LinkRandPhrase("あなたとあなたの仲間たちのことを嬉しく思うよ。","ああ、俺もこの小さな島が気に入ってるぜ。","満足してくれていると知って嬉しいよ。");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("「ああ……こんにちは。」","旦那、あの……武器を持った荒くれ者たちは誰ですか？","助けてくれてありがとうございます、船長。");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("俺たちの連中はよくやったぜ――家も素晴らしい出来だ。だが、俺たちも頑張ったんだぞ！","旦那船長、ご心配なく。我らの小さな一族の女たちは、困難や一時的な不便なんぞ恐れはしません。","ここはなんて空気だ！それに、この海！神様に近づいた気がするぜ！");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("俺たちの連中はよくやったぜ―家も見事だ。だが、俺たちも頑張ったんだぞ！","旦那船長、ご心配なく。我らの小さな一族の女たちは、困難や一時の不便なんぞ恐れはしませんぜ。","ここはなんて空気だ！それに、この海！神様がすぐそばにいるような気がするぜ！");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("もっと頻繁に来てくれ、旦那船長。あんたに会えるといつも嬉しいぜ。","ロドガー旦那は素晴らしい語り部だ。いつまでも彼の話を聞いていられるぜ！","へへっ。俺たちの仲間の中に、もうすぐ家族が増えるやつがいるって話だぜ。イサラ・モナでも人生は続いていくんだな！ ");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "お前さん…本当にありがとう、旦那！またちょくちょく来てくれよ…";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("大丈夫だぜ、船長！","奴隷たちはちゃんと管理してる、心配すんな。"),RandPhraseSimple("心配いらねえ、反乱なんてありえねえよ。","ラム酒をありがとう！これから仕事に取りかかるぜ！"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("スペイン人か？お前からこんなことをされるとは思わなかったぜ。","「今じゃ、静かに眠るためにわざわざ浜辺まで歩かなきゃならねえんだぜ！」"),RandPhraseSimple("なんでこんなこと全部決めたんだ、なあ、船長？","あの時、親分はお前を信じてた――間違っちゃいなかったぜ。今回もお前を信じるさ。"));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("骨の折れる労働の後に、一杯やるくらい罪じゃねえさ……","もうすぐ終わるから家に帰るぜ。女房が待ってるはずだ…","ああ、仕事の後に我々の酒場でくつろぐのは最高だな！みんなあんたに感謝してるぜ、船長！");
			link.l1 = LinkRandPhrase("酒を楽しめよ、相棒、ハハッ！","気楽にしろよ、相棒。ただし飲みすぎるなよ、奥さんに叱られるぜ、ははっ！","気楽にいこうぜ、相棒、人生は仕事ばっかりじゃねえんだ！");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Who's that pretty mulatto woman living here?";
				else sTemp = "Captain, nice place you got here!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("船長、いい場所を手に入れたな！","もし急にラム酒がなくなったらどうするか想像してみろよ。お前ならきっと新しいのを手に入れてくれるよな？"),RandPhraseSimple("こんな休暇、ずっと夢見てたんだ。だけど娼館にも行きたいな……まあ、ちょっとした妄想だぜ、船長。",sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("休暇をくださってありがとうございます、船長。","ここはいい場所だな――整理整頓の腕前はさすがだ、船長。"),RandPhraseSimple("新鮮な食い物に酒、しっかりした陸の上……まるで夢みてえだな。","もう少しここに滞在したいんだ。"));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("もう疲れ果てて、立っているのもやっとだ。","こんなふうに生きる力なんてもう残っちゃいねえ！"),RandPhraseSimple("この仕事は俺にはきつすぎるぜ。","監督たちは俺の肌に生きた細胞一つ残さなかったんだ！"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("何かお手伝いしましょうか、船長？","入れよ、地元のパエリアを食ってけ。ただし、頼むから中身は聞くなよ！","ようこそ、船長。ここは気に入ったかい？");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("旦那、ようこそ！","やあ、船長。泊まっていくのか？","俺に用か？どうぞ、中へ入ってくれ、散らかってるのは気にしないでくれ、旦那。");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}