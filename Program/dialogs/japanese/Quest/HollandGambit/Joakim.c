// Жоаким Мерриман - португальский сумрачный гений
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "ごきげんよう、旦那！私は医師のヨアヒム・メリマンです。お話ししているお方は船長でいらっしゃいますか "+GetFullName(pchar)+"?";
					link.l1 = "ああ、俺だ。それにしても、どうして俺の名前を知ってやがる？お前と会った覚えはねえぞ。";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "お会いできて嬉しいです、船長。足取りの軽さからして、私をとても喜ばせてくれる予感がしますね。 ユム・シミルの頭蓋骨は持ってきましたか？";
					link.l1 = "お前が言っていた頭蓋骨は俺が持ってるぜ。まるで燃え盛る炉のようにバチバチとエネルギーを放ってやがる。";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "他に言いたいことはあるか、船長？";
				link.l1 = "いいえ、メリマン旦那。私は出発します。";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "ごきげんよう、旦那！私は医師のヨアヒム・メリマンです。お相手は船長でいらっしゃいますか "+GetFullName(pchar)+"?";
					link.l1 = "ああ、それは俺だ。だが、どうして俺の名前を知ってやがる？お前と会った覚えはねえぞ。";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "お会いできて嬉しいです、船長。足取りの軽さから、私をとても喜ばせてくれる予感がします。 ユム・シミルの頭蓋骨は持ってきましたか？";
					link.l1 = "お前が言っていた髑髏は俺が持っているぜ。まるで燃え盛る炉のように、ビリビリとエネルギーが走ってやがる。";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "他に付け加えることはあるか、船長？";
				link.l1 = "いいえ、メリマン先生。私は出発します。";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "ごきげんよう。私に何かご用ですか？";
			link.l1 = "いいえ、すみません。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "もしメリマン医師に会いに来たのなら、ここにはいないぞ。もうここには住んでいないんだ。";
			link.l1 = "なるほど。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "もしメリマン医師に会いに来たのなら、残念ですが今は家におりません。\nただいま旅に出ており、いつ戻るかは分かりません。";
			link.l1 = "なるほど。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "もしメリマン医師に会いに来たのなら、ここにはいないよ。もうここには住んでいないんだ。";
			link.l1 = "なるほど。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "お前の事情は思っているほど秘密じゃねえぞ、船長！だが心配するな、提案があるんだ！俺は科学者、 いわば自然哲学者で、スペイン領本土や西インド諸島のインディアン異教徒の魅力的な文化を研究している。 もしよければ、俺の家まで一緒に歩いて、居間で非常に儲かるかもしれない話の詳細を聞いてくれないか？\n";
			link.l1 = "君には興味も注意も向けている。案内してくれ。";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "これを断るつもりはないだろう、旦那！私の家はここから遠くない。ついてきてくれ！";
			link.l1 = "...";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "ここなら誰にも聞かれる心配はありません。あなたは最近、私の隣人ソロモン・シュヌールを訪ねましたね。 ちょうど通りかかったのですが、申し訳ありません、船長、あなたとソロモンの会話の一部を偶然耳にしてしまいました。 あまりにも興味深くて、つい最後まで聞いてしまったのです！";
			link.l1 = "「盗み聞きしながら、他の盗み聞きが怖いってわけか？」";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "まあまあ、船長！全然そんなことじゃないんだ！ソロモンは俺の隣人で、よく遊びに来るんだよ。宗教が違っても、 俺たちは仲のいい友達さ！あいつの災難については知ってる……ウィレムスタッドの誰もが知ってるさ！ソロモンは朝から晩まで、聞いてくれる奴なら誰にでも自分の不幸を語るからな。 まあ、その話はもういいだろう。あのユダヤの爺さん、きっとお前にも言ったはずだぜ、 どこか知らない島に金と一緒に隠してある古い翡翠の髑髏のことを。あいつ、その話をしたか？";
			link.l1 = "奴は俺に頭蓋骨の話をしたが、それが翡翠でできてるとは言わなかったぜ。しかも、 それは自分の祖父の頭蓋骨だとも言ってた。本当のことを言うと、俺はそれがカバラの呪物か、 あるいはあの爺さんがちょっとイカれてるのかと思ったんだ。";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "いや、船長、ソロモンは正気だ。ただ変わり者なだけさ。頭蓋骨は実在する。あれは古代インディオの財宝、 ユム・シミルの翡翠の頭蓋骨だ！あのユダヤの爺さんがどうやって手に入れたのか、俺にはさっぱり分からん。 俺は人生の半分をかけてそれを探してきたんだ\nソロモンが一族の財産を隠した島を見つけてくれ。頭蓋骨はきっと彼の宝箱の中にあるはずだ。 その翡翠の頭蓋骨を俺に渡せば、五十万ペソ払おう。";
			link.l1 = "五百？そんなはした金、俺の時間の無駄だ――待てよ……今、五十万枚のエイト金貨って言ったか！？冗談だろ？そんな大金、一度に見たことなんて人生で一度もねえよ！";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "まだ若いな、船長…。それで、どうする？お前が翡翠の髑髏を渡せば、俺は代わりに五十万ピース・オブ・エイトを払うぜ。取引成立か？";
			link.l1 = "はは、古い頭蓋骨に大金だと？もちろん乗ったぜ。";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "素晴らしい。利益を理解する男と仕事ができるのはいつだって嬉しいものだ。\nまた用があればここ、私の屋敷にいるからな。幸運を祈る！";
			link.l1 = "ありがとうございます、メリマン先生。あまりお待たせしません。";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-02.wav");
			dialog.text = "ああ、そうだ！その力についてはまったくおっしゃる通りだ…だが、もう話はいい、見せてくれ、待ちきれなくて震えているんだ。";
			link.l1 = "どうぞ、お受け取りください。私の判断は間違っていなかったでしょうか？";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "ああ、信じられない！そう、これだ。素晴らしい、船長、実に素晴らしい！ついに！ついに手に入れたぞ！ この瞬間を何年も待ち続けていたんだ！";
			link.l1 = "メリマン先生、約束してくれた金はどうなったんですか？";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "ああ、もちろんだとも！八エスクード五十万枚だ。持っていけ、君が稼いだ金だ。";
			link.l1 = "取引できて光栄だよ。こんな小さな物がこんなに高値になるなんて信じられねえな……";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "小さなことだと？お前は自分が何を言っているのか分かっていないな。これは……まったく、野蛮人のお前の頭じゃ、この貴重な頭蓋骨の背後にある途方もない力の大きさなんて到底理解できまい。 正直なところ、私にはもうこれ以上時間の余裕はないのだ\n船長、これまでのご厚意に感謝する。さて、そろそろお別れの時だ。私は行かねばならない。";
			link.l1 = "さらばだ、メリマン先生。またどこかで会うかもしれませんね。";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "ここで話そう、船長。お前が隣人ソロモンの娘、アビゲイル・シュヌールと親しい仲だということは知っている。 彼女はお前の船で恋人のもとへ旅立った……だが、それはどうでもいいことだ。";
			link.l1 = "「何が言いたいんだ、ドクター？」";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "もしソロモンを知っているなら、奴が難破とどこかの無人島に隠した失われた財宝の話をしているのも知っているはずだ。 \nこの話はすでにウィレムスタッドの誰もが聞かされているぜ。";
			link.l1 = "なぜ俺がその話を聞いた上に、あの年寄りユダヤ人の不幸にまで関心があると思うんだ？";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "ソロモンが気に入らないのか？あいつはただの無害な変わり者の老人だって保証するよ。気にするな。 ビジネスの話をしよう\n俺はソロモンと何度も長話をしたんだ。何年も探し続けてきた古代の貴重な秘宝を、 このユダヤ人の爺さんが持っていると知ったときの気持ちなんて、お前には想像もつかないだろう！あのイカれた老人は、 みすぼらしい金と一緒にその秘宝をどこかの島に隠したくせに、場所すら思い出せないんだ\n俺はその秘宝が必要だ。それを持ってきてくれたら、五十万ピース・オブ・エイト払おう。";
			link.l1 = "八十万ピース・オブ・エイトだと？冗談だろう、先生。そんな大金、一度に見たことなんて人生で一度もないぞ！";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "まだ若いんだろう。で、どうする？お前がその髑髏を渡せば、俺が五十万エイト銀貨を払う。それに加えて、 ソロモンの金も持っていっていい。あの爺さんの話じゃ、二十万ペソはあるはずだ……つまり、合計で七十万エイト銀貨がお前のものだ。どうだ、船長？";
			link.l1 = "畜生！もちろん、それは取引成立だぜ！だが、どうやってその島を見つけりゃいいんだ？";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "アビゲイルに話してみろ。何か思い出すかもしれない。ソロモンにも聞いてみろ。いいか、 もし俺が島の場所を知ってたら、最初からお前に助けなんて頼まねえさ。";
			link.l1 = "なるほど。愚かな質問をしてすまない。さて、この島を探さねばな。ちゃんと報酬を用意して待っていてくれよ。";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "その通りです。お互いに理解し合えて嬉しいですよ、船長。捜索の幸運を祈ります。私はいつでもここ、 自分の屋敷におりますので。";
			link.l1 = "あまりお待たせしませんよ、メリマン先生。さようなら！";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("Voice\English\LSC\Chymiset-03.wav");
			dialog.text = "うおおおお。生け贄の石は俺の敵どもの血で真っ赤に染まったぜ！ユム・シミルが俺に死者を操る力を授けてくれた！ この力さえあれば、やがて生者どもも俺の支配下に置いてやる！";
			link.l1 = "ずいぶん芝居がかった口ぶりだな、メリマン。歩く死体の軍隊で何をするつもりだ？ シーザー気取りで世界征服でも狙ってるのか？";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "黙れ、この愚か者め！俺が独り言で自分の秘密の計画を明かすとでも思ったのか！？まあ、 お前はこの場で生きて帰れないのだから、話してやっても構わんだろう！ 俺の不死の軍勢はまずカリブのすべての暗い洞窟や地下牢を占拠する。俺の前哨基地はすべての村に配置され、 俺の合図を待つのだ。そして時が来れば、俺の歩く死体どもが進軍し、生者の地を蹂躙する！\n残念だが、お前のような哀れな善人ぶった小物、主人公気取りの小僧には、それを見ることは叶わん！ここは俺の聖域――生きては出られんぞ！俺が闇の軍勢を率いるのだ！";
			link.l1 = "聞けよ、相棒、お前が仕切れるのはジャックとクソだけだが、そのジャックももう町を出ちまったぜ。";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "おほほほ！俺と俺の骸骨のしもべどもに挑むつもりか！？ならば、俺の真の姿を見せてやろう、恐怖に震えるがいい！";
			link.l1 = "かかってこい。";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "ああっ！イエス様！";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\English\hambit\Joakim Merriman-04.wav");
			dialog.text = "今やっと分かったか、目の前に立っているのが誰か、この泣き虫のウジ虫め！？俺はお前に言いたいことがあるんだ！ ユム・シミル様ご自身が俺を贔屓してくださる！お前の魂、俺が喰らってやるぞ！";
			link.l1 = "よし、ド阿呆。踊ろうじゃねえか。";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("あなたは "+GetSexPhrase("泥棒だ、旦那！衛兵、そいつを捕まえろ","泥棒だ、あの娘だ！衛兵ども、あいつを捕まえろ！")+"!!!","見てくれよ！俺がちょっと目を離した隙に、俺の箱を漁ったな！泥棒だ！泥棒を捕まえろ！！！","衛兵！強盗だ！泥棒を捕まえろ！！！");
			link.l1 = "くそっ！";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
