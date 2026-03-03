void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "悲しい話だよな？";
				link.l1 = "「お前は誰だ？」";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "ごきげんよう、船長。";
				link.l1 = "待て！俺たち、前に会ったことがあるじゃねえか！";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "一つ。二つ。三つ。";
				link.l1 = "この茶番はやめよう。お前は何者だ？";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "「四つ。」";
				link.l1 = "「あと二人か？」";
				link.l1.go = "DiegoDeLanda_Meeting_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "この墓所の特別なところがわかるか？ここには血で繋がれた二つの魂が眠っているんだ。アラメダ家の父と息子さ。\n一人は罪人の手にかかって倒れ、もう一人は……ふむ、神のもとへ導かれたのさ。";
				link.l1 = "ドン・フェルナンドの日記が俺をここに導いたんだ。";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "レディ・ビショップを見たか？哀れな運命だよな、そうじゃねえか？だが、仕方ねえことだったんだ。";
				link.l1 = "エリザベスを知ってるのか？";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "モーティマー・グリム。";
				link.l1 = "もちろん、あいつのことを知ってたんだろう？";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_ClockTower"))
			{
				dialog.text = ""+GetCharacterName("Hendrik")+" "+GetCharacterName("「ファン・ドールン」")+".";
				link.l1 = "「お前の依頼人か？」";
				link.l1.go = "DiegoDeLanda_ClockTower_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nあと三人だ。六人目で全てが分かるぜ。";
			link.l1 = " 今すぐはっきり答えてもらえないなら、俺は……";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nやるじゃねえか、船長。お前には俺の名前を教える価値がある。ディエゴ・デ・ランダだ。";
			link.l1 = " お前、本当に神父なのか？";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "まず第一に、俺は芸術家だ。だが、焦ることはねえ……";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		
		case "DiegoDeLanda_Meeting_Fourth_2":
			dialog.text = "\nその通りだ、船長。第三幕の始まりだ。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "ああ…日記か。書かれた言葉というのは実に素晴らしいものだ。まるで…闇の中の道のようだな。啓示が待つ場所へと導いてくれる。ドン・フェルナンドはよく我々の教区を訪れていた。 特に去年は頻繁だったよ。\n";
			link.l1 = "地元の教区で働いているのか？ドン・フェルナンドを知っていたのか？";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "俺は……あいつの行動を見ていたんだ。\nそれと、お前が持ち去ったあの本。\nあれが何か特別なものだってわかってるか？";
			link.l1 = "古そうだな。";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "年寄り？いや、違う。これは…啓示だ。ドン・デ・アラメダ旦那の聖書さ。書かれている一言一言が、闇を照らす灯台のようだ。\n受け取りなさい。キリストの兄弟たちを助けなさい。そうすれば、もしかしたら…これがあなたを、もっと偉大なものへと導くかもしれません。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие
		
		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "ああ、そうだ。かわいそうな女性だよ。旦那は……あまり優しい男じゃない。やつのプランテーションはバルバドスで一番の生産量だと言われてるが、 同時に一番残酷でもある。毎月どれだけの奴隷がそこで死んでるか知ってるか？最近も、 イングランドから来た本物の医者――優れた知性と才能を持った男を殴り殺したんだ。でも、あの奥さんの運命も大して変わらない、信じてくれ。";
			link.l1 = "ずいぶん詳しいようだな。";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "人々は告解のために私のもとへ来るのです、船長。彼らは愛する者にも言えないことを私に打ち明けます。恐れ、罪……そして苦しみを。";
			link.l1 = "迫害が怖くないのか？イングランドの地でカトリックの神父として生きるのは簡単じゃないぞ。";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "俺の恐怖なんて、今お前があの扉の向こうに置いてきたものに比べりゃ大したことねえよ。それに、 お前があの哀れな女から奪ったあの小さな本……もし恐怖に形があるなら、まさにあれそのものだろうな。\n"+
		"ごきげんよう、船長。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "虎よ、虎よ、燃え盛る輝きで\n"+
			"夜の森の中で、\n"+
			"どんな不滅の手や眼が\n"+
			"お前の恐ろしい均整を形作れる者がいるのか？\n"+
			"もちろん知っていたさ、船長。だが、お前はどうだ？";
			link.l1 = "これほど悲劇的な運命を持つ男には今まで会ったことがない。";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "お前はもう手に入れているが、まだ気づいていないだけだ。\n"+
			"じゃあ、お前はグリムを知らなかったんだな。たとえその頭蓋骨を手にしていてもな。";
			link.l1 = "「なんだって！？」";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "死者をそんなふうに扱うのはキリスト教徒のやり方じゃねえ。ほら、これを受け取れ。死後の心得だ。 俺からお前への贈り物だぜ。\n"+
			"ごきげんよう、船長。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//<-- Мементо
		
		//--> Башня с часами
		case "DiegoDeLanda_ClockTower_2":
			dialog.text = "洒落がきいてるな、船長。あんたはあいつの客で、あいつは俺の客だったんだぜ。\n"+
			"なんて似ているんだ。\n"+
			"お前がどうやって名簿に載ったか、忘れてねえだろうな？\n最初は栄光あるウィレムスタッドの町を助けた。\nだがその後、多くの町の息子たちを血に沈めたんだ。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_3";
		break;
		
		case "DiegoDeLanda_ClockTower_3":
			dialog.text = "もっとも、ヘンドリックは後者を成し遂げられなかった。\n厄介な依頼人だ、本当に手強い。\nほら、これだ。\n暇なときに読んでみてくれ――まったくの謎だ。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_4";
			// получаем документы Маартена
			ClockTower_AddVisserKey();
			
		break;
		
		case "DiegoDeLanda_ClockTower_4":
			dialog.text = "人は皆、建物のようなものだ。\n本当にその人を突き動かしているものを知りたいなら、地下室を覗いてみろ。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_5";
		break;
		
		case "DiegoDeLanda_ClockTower_5":
			dialog.text = "「ほら。」";
			if (CheckAttribute(pchar, "questTemp.ClockTower_GotHint"))
			{
				link.l1 = "地下室の鍵か？俺はもうそこに行ったぜ。";
				link.l1.go = "DiegoDeLanda_ClockTower_6";
			}
			else
			{
				link.l2 = "「お前の地下室には何があるんだ？」";
				link.l2.go = "DiegoDeLanda_ClockTower_7";
			}
		break;
		
		case "DiegoDeLanda_ClockTower_6":
			dialog.text = "\nそれなら、もう話すことはないな、船長。";
			link.l1 = "気を悪くしたか？お前の地下室には何があるんだろうな？";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		case "DiegoDeLanda_ClockTower_7":
			dialog.text = "\n俺たちが話すたびに、一歩ずつあそこへ近づいていくんだぜ、船長。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			ClockTower_AddBook_FromDiegoDeLanda(); // получаем ключ от подвала
		break;
		
		//<-- Башня с часами
		
		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "教えてくれ……なぜだ？あれは危険で愚かな行為だった。何があんたを突き動かすんだ、船長？あんたの情熱は何だ？";
				link.l1 = "お前には関係ねえだろ。";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "「二番目。」";
				link.l1 = "前回は謎めいた話し方をしていたな。今回もまたそうするつもりか？";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "待て、デ・ランダ。そう簡単に持って行かせて帰すわけにはいかねえぞ。";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "ヒントばかり、芝居じみたことばかりで、何の行動もねえ\n"+
				"少なくとも俺の方はな。お前は十分に活躍してきただろう。";
				link.l1 = "それを解決する方法が思いついた。";
				link.l1.go = "DiegoDeLanda_Leaving_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "俺にはわからねえ。他の連中は――ああ、わかる。だが、お前は違う。まだだ。";
			link.l1 = "他の連中は？";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "例えば、一人は正義を求めている。もう一人は……死の暗い海に取り憑かれている。人間は欲望に簡単に溺れてしまうものだ。そう思わないか？";
			link.l1 = "あんたは変わった神父だな、神父さん。";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "俺は行くぜ。";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "もちろんだ。お前の仕事はまだ始まったばかりだぜ、船長。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\n本当の謎が俺の前に立ちはだかっている。お前はもう二つ……遺物を集めたな。こういうものを集めるのが好きなのか？コレクターか？";
			link.l1 = "「どうして知ってるんだ？」";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "「戦利品狩りか？」";
			link.l1 = "もう一度聞くが、どうして知っているんだ？";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;
		
		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "スリルを求める奴か？";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nああ。もちろんだ。ごもっとも。さて、船長、これ以上引き止めはしねえよ。";
			link.l1 = "待ってください、神父様。まだ私の質問に答えていませんよ。";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "ああ、船長。俺にはできねえ。時には、答えが無知よりも深く傷つけることがあるんだ。安らかに行け。 そして自分のコレクション……戦利品を大事にしな。これからの旅できっと役に立つぜ。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "さあ、船長。面白くないか？楽しんでないのか？戦利品はもう十分か？\n"+
			"それがあんたの炎だ、船長。次に何が起きるか気になって仕方ねえんだろう。 美しい船や面白いガラクタが大好きなんだな。\n"+
			"どうしても全部集めずにはいられねえんだよな。\n"+
			"\n"+
			"今すぐ俺を撃ってもいいぜ。";
			link.l1 = "「なんだと！？」";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "先に進めばいいさ。ただし、それじゃあ全てを知ることはできねえし、トロフィーも全部は揃わねえぜ。まあ、 船は全部手に入るけどな……\n"+
			"ごきげんよう、船長。";
			link.l1 = "（行かせてやれ）";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "（撃て）";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_Fourth_2": // Четвёртое прощание
			dialog.text = "\n遅かったな、船長。お前には俺を撃つチャンスがあったんだぜ。しかも絶好の機会だった！三つ数えるぞ――一、二、三……何も起きねえ。でも心配すんな。六になったら、俺が見せてやるよ。もうすぐだぜ。\n"+
			"ごきげんよう、船長。";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 