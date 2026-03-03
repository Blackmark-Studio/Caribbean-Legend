// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "おお！ごきげんよう、旦那。どうやってここに来られたのですか？";
				link.l1 = "ごきげんよう、ジーノ。これから親しくしようじゃないか。私は船長 "+GetFullName(pchar)+" それに、俺はジョンの許可を得てここに来ているんだ。\nはっきり言っておくが、俺はお前の助けが必要だ。でも、俺もお前を助けることができるぜ。";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "おお！ごきげんよう、旦那。どうやってここに来たんです？それにジョンはどこに？";
				link.l1 = "ほうほう……この閉ざされた扉の向こうにいつも隠れていたのは、あんただったのか！面白いな……ジョンのことか……あいつはもういない。この家は今や俺のものだ。だが心配するな。まずはお互いを知ろうじゃないか。あんたは誰で、 ここで何をしているんだ？";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "「こんにちは。」 "+pchar.name+"。顔つきからして、何か重要なものを見つけたようだな。真実の守護者のすべての部品を集めたのか？";
					link.l1 = "その通り！俺は三つとも持ってるぜ――短剣、地図、そしてコンパスだ！";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "「こんにちは」 "+pchar.name+"……どうしたんだ？妙な顔をしているじゃないか……";
					link.l1 = "ジーノ、お前と話したいことがあるんだ。大事な話だ。";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"「ええ、覚えていますよ。二日が過ぎて、あなたは真実の守護者について知りたいのでしょう、違いますか？」";
					link.l1 = "ああ、そうだ！何か掘り出せたか？";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "5,000ペソは持ってきたか、 "+pchar.name+"?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "もちろん。ほら、金だ。必要なものを全部買ってこい。";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "残念ながら、今は手元に金がないんだ。";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "「ああ、」 "+pchar.name+"、本当に申し訳ありません――患者は亡くなりました。急に容体が悪化し、あっという間に息を引き取りました。";
					link.l1 = "残念だ……神が彼の魂をお救いくださいますように！";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "「こんにちは」 "+pchar.name+"……何かあったのか？とても心配そうな顔をしているな……";
					link.l1 = "ジーノ、ちょっと変わった頼みがあるんだ！俺の船に高熱を出している男がいて、うわごとを言いながら意識もないんだ……助けてやれるか？";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+pchar.name+"、私は患者を待っている。急いでくれ、君が早くここに連れてくれば連れてくるほど、 私が助けられる可能性が高くなるんだ。";
					link.l1 = "はいはい、すぐに彼をここへ連れて来させます。";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "「ちょうどいい時に彼を連れてきてくれたな」 "+pchar.name+"。彼は危篤状態ですが、まだ望みはあります。\n船長、薬の材料がもう尽きそうですし、ジャングルで集める時間もありません。地元の薬草屋から全部買うには5,000ペソ必要です。その金額をご用意いただけますか？";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "もちろん。ほら、金だ。必要なものを全部買ってこい。";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "残念ながら、今は金がないんだ。";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "「今は何も言うことはない」 "+pchar.name+"私は患者の命を救うために戦っています。まだ希望はあります。後でまた来てください、 もう少し具体的なことをすぐにお伝えできると思います。";
					link.l1 = "わかったよ、ジーノ、後でまた来る。";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "「知らせがある」"+pchar.name+"……あんたの仲間が無事だとは言わねえが、生きてるぜ。病気は引いてきてるし、回復の兆しも見える。正直なところ、 俺の薬がここまで効くとは思わなかったな。";
					link.l1 = "それは朗報だな、ジーノ。でも教えてくれ、いつ彼を引き取れるんだ？俺たちは長い航海が待ってるし、 時間も迫ってるんだ。";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "ごきげんよう、船長。お会いできて嬉しいです。";
					link.l1 = "「患者の様子はどうだ、ジーノ？」";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "ごきげんよう、船長。ご機嫌いかがですか？私の助けが必要ですか？";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "ああ。ジーノ、君は博識な男だとお見受けするし、もしかするとラテン語も知っているのではないか…";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "少し違うものがあるんだ。君へのささやかな贈り物さ。ほら、この本を見てごらん。";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "ああ、ジーノ。君にこのピストルを見せたいんだ。こんなの見たことあるかい？";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "私のピストル用の火薬の見本を持ってきた。";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "ピストルの容疑についてはどうだ？何か手がかりは見つかったか？";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "ジーノ、船長の日誌で「gord」という見慣れない言葉を見つけたんだ。意味が分かるかい？";
					link.l3.go = "mtraxx";
				}
				link.l9 = "ごきげんよう、ジーノ。私は元気で、助けはいらないよ。ちょっと様子を見に来て、少し話したかっただけなんだ。";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "俺の名前はジーノだ。ジーノ・グヴィネリ。俺は科学者だぜ。俺の仕事は、ムルドック旦那のために粉薬や混合薬、 その他の薬を作ることさ。だが、あいつがいなくなっちまってからは……";
			link.l1 = "さて、私は "+GetFullName(pchar)+"。自分の船の船長だ。で、お前は錬金術師ってわけか？";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "私は錬金術師であるだけでなく、医者でもあります。医学についてもかなりの知識を持っています。 治療に使う薬草にも詳しく、それらから調合薬や秘薬を作ることもできます。しかし、 本当に私が情熱を注いでいるのは化学です。私は多くの実験を重ねており、私の発明のいくつかはあなたのような方々 の役に立つかもしれません。\n私はラテン語、フランス語、英語、イタリア語が分かります。 もしあなたがマードック旦那のように薬局を経営するつもりなら、私の助けは欠かせないものになるでしょう……";
			link.l1 = "おおっ！こんな博識な男に会えるのは滅多にないことだな。薬屋稼業も悪くねえが、俺は船乗りでな……ん、俺が言うのも変な感じだが……ま、とにかく、きっと俺たちは友達になれるさ、ジーノ。ここに住み続けて、好きなだけ科学の研究をしてくれていいぜ……";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "それに、もし錬金術師や治療師、科学者の助けが必要になったら、誰に頼めばいいか分かったよ……ところで、どうしていつも家の中にいるんだ？外に出たりしないのか？\n";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "実験の材料や薬草を買う必要がある時は外に出ますよ。私は一人で暮らすのが好きなんです、それが私のやり方です。 人生を科学に捧げてきたので、普通の生活には興味がありません。本や論文、試験管、レトルト……\nマードック旦那は、薬を作る手伝いを条件に、そんな機会を私に与えてくれました。";
			link.l1 = "これでさらに時間ができるな、ジーノ。ただし、俺が手伝いを頼むときは、実験の時間を少し譲ってもらうぞ、いいな？";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "もちろんでございます、船長。これからは船長とお呼びいたします。 "+GetAddress_Form(NPChar)+"、もしよろしければ？私の実地経験や理論的知識が必要な場合に備えて、すべての研究資料を残しておきます。";
			link.l1 = "素晴らしい。こうしてすぐにお互い理解できて嬉しいよ。費用のことは心配しなくていい、私か会計係が時々 適切な金額を渡すからな。";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "ありがとうございます、船長。私には多くは必要ありません……船長、ちょっと考えがあるんですが……錬金術の技術を学んでみてはいかがですか？きっと役に立つかもしれませんよ。";
			link.l1 = "ふむ。兄が昔言っていたんだ――自分の手で物事を学ぶのをためらうなって。だから、まあいいさ。何を見せてくれるんだ？";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "まあ、確かに鉄を金に変えることはできない、それは今のところ不可能だ……だが、指示通りに材料を混ぜて薬や他の便利な品を作る方法は学べるぞ。さあ、この袋を受け取れ。 初心者の錬金術師に必要なものが全部入っている：試験管、フラスコ、レトルト、蒸留器、へら、ガラス管、 バーナーなどなど……";
			link.l1 = "「これは興味深い！」";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("You have received an alchemist's kit");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "薬やアイテムを作るには、まずレシピを知っていなければなりません。レシピは商人から購入することも、 どこかで見つけることもできます。一度レシピを学んだら、必要な材料をすべて集め、 そこに書かれている通りに正確に作業してください。\n 錬金術の道具を使い、乳鉢と乳棒を探すか購入し、坩堝も探しましょう――残念ながら、余分なものは持っていません。薬草、酒精、薬剤、鉱石、ガラクタ――正しいレシピと道具さえあれば、何でも役に立ちます。";
			link.l1 = "なるほど。暇なときに何か混ぜてみるよ。ありがとう、ジーノ！簡単なレシピを教えてくれないか？ 最初に作るのにちょうどいいやつをさ。 ";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "簡単なものはないが……ほら、この解毒剤のレシピを持っていけ。君ならこの仕事をこなせるだろう。受け取れ。";
			link.l1 = "ありがとう！覚えておくよ。それじゃあ、さようなら、ジーノ！俺の家を頼むぞ。ここにはあまり来られそうにないから、 自分の部屋だけじゃなく、建物全体を自由に使ってくれていいからな。";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("You have received an antidote recipe");
			PlaySound("interface\notebook.wav");
			Log_Info("You need to have the Alchemy skill in order to craft potions, amulets and items!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "はい、船長、私は古代ローマ人の言語を知っています。学者なら誰でも、 特に治療師や錬金術師ならラテン語を知っていなければなりません。\n私のラテン語の知識が必要ですか？";
			link.l1 = "ああ。ジーノ、俺を馬鹿にしないでくれよ、でも……その、どう説明したらいいか……";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "はっきり言えよ、船長。遠慮すんな。";
			link.l1 = "わかった。学術的なラテン語の格言をいくつかリストにしてくれないか？\n実はな……自分の「博識」をひけらかすのが好きな男がいて、時々ラテン語のフレーズを使って、俺の無知を見せつけてくるんだ。 例えば……「si vis pacem, para bellum（平和を望むなら、戦争に備えよ）」みたいなやつだ……";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "「『Si vis pacem, para bellum』、つまりそういうことか？」";
			link.l1 = "はいはい。あいつ――いや、友人をやっつけるために、その技を覚えたいんだ。";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "あなたのご要望には、船長、何もおかしなことも恥ずかしいこともありません。 歴史に名を残した古代人の格言を知っているのは、教養ある人物の証です。さあ、この書物をお受け取りください。 ご所望の品です。";
			link.l1 = "ありがとう、ジーノ！感謝するよ！暇なときに読ませてもらうな…";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("You have given Lavoisier's chemistry textbook");
			dialog.text = "見せてくれ…（読む）ありえん！「ちょっとした贈り物」だと？この本は値がつけられんぞ！どこで手に入れたんだ！？これは…本物の宝だ！";
			link.l1 = "気に入ってくれて嬉しいよ。";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "（読みながら）信じられない！こんなの聞いたこともない……で、これは？全然わからない……だが、絶対に理解してやる、くそっ！ああ、もうすぐ俺の研究室は仕事で沸き返るぞ！ "+pchar.name+"……お前は自分が俺に何を渡したのか、まるで分かっていないんだな……";
			link.l1 = "なぜだめなんだ？もちろんだ。科学者には科学の本を…";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "しかし、この奇跡の著者は誰だ？アントワーヌ＝ローラン・ド・ラヴォアジエ、フランス……聞いたことがないな。\nだが待て！そんなはずはない！印刷年は1789年だと？でも、どうして……";
			link.l1 = "その年がなぜそこに書かれているのか、俺にも分からねえ。いや、もしかしたら分かるかもしれねえが、 あまり深く考えない方がいいぜ。本が役に立つ、それだけで十分だろう。";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "私が期待していた以上に有望ですね。それに、その年は何かの印刷ミスに違いありません……まあいいでしょう。ありがとうございます、船長！";
			link.l1 = "どういたしまして、ジーノ。全部お前のものだ。";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "それだけじゃないんだ、ジーノ。これを見せたいんだ、このピストルさ。こんなの見たことあるか？";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "私は銃職人ではありませんが、ちょっと見てみましょう……いや、こんなものは見たことがありません。なぜそんなことを聞くのですか？";
			link.l1 = "このピストルは強力で破壊力もあるが、使うには特別な弾薬が必要なんだ。他のものじゃ使えない。\nしかも、どうやって弾を作ればいいのか全く分からない。\nだから、君の助言を求めてここに来たんだ。";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "見本として少なくとも一発は見せてくれるか？\nもし持っていないなら、残念だが手助けできそうにない。";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "ええ。弾薬は二つの部分から成っている。弾丸入りの火薬包本体と、この火薬に火をつけるためのものだ。";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "なんて失敗だ！なんて恥だ！まあいい、もっと見つけて持ってきてやるさ。";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("You have given a revolver's cartridge");
			Log_Info("You have given a capsule");
			PlaySound("interface\important_item.wav");
			dialog.text = "面白いな！見た感じは単純だ、中に火薬が入ってて、上から弾を込めるんだが、ちょっと変わってるな。それにこの 「部品」…ふむ。これがないと火薬は爆発しねえんだろ？興味深い…なあ船長、これ全部俺に任せてくれよ：ピストルも火薬も。ひと月後にまた来てくれ、仕組みを調べる時間がいるんだ。";
			link.l1 = "素晴らしい！どうやって使うのか試してみてくれ、俺はこのピストルを撃ってみたくてたまらないんだ。";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "主な問題は、この火薬を爆発させる物質が何でできているのかを突き止めることだ。\nこの本が役に立つだろう。\n私はこの謎の核心に迫ってみるつもりだ。";
			link.l1 = "よし。じゃあな、ジーノ！";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "はい、ピストルの弾薬が何でできているか突き止めました。\nあなたが贈ってくれた本のおかげです。あれがなければ無理でした。\nしかし警告しておきます、船長。この武器の弾丸やカプセルを作るのは簡単ではありません。";
			link.l1 = "「カプセル？」";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "カプセルというのは、あなたが言った通り、火薬に火をつける“あれ”のことだ。\nだが、最初から説明しよう。準備はいいか？";
			link.l1 = "はい！私はあなたの話をとても注意深く聞いています。";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "まず最初に、特別な弾丸を作る必要がある。普通の弾じゃ駄目だ。特別な円錐形をしていなきゃならねえ。そのための型――俺は弾丸型と呼んでるが――を探さなきゃならん。普通の鉛弾を用意して、るつぼで溶かし、その溶けた鉛を弾丸型に流し込むんだ。鋳型が冷めたら、 出来上がった弾を取り出せばいい。\n";
			link.l1 = "「そんな弾丸の型はどこで手に入るんだ？」";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "わかりません、船長。私は錬金術師であって、鍛冶屋じゃありません。この弾丸を例に取ってください、 もしかしたらどうすればいいか思いつくかもしれません。";
			link.l1 = "よろしい。続けてくれ…";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "それから火薬を入れる容器を作らないといけない。そこに弾丸を入れるんだ。\n君のために分かりやすい手順を書いておいた。よく読んで、試してみてくれ。";
			link.l1 = "「よし…」";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "さて、今度はカプセルを手に入れなければならない。\nとても薄い銅板が必要だ――銅の塊から自分で作れ。\n弾丸と同じ大きさの円をその板に彫り出すんだ。\nそれから、蝋を使って中に雷銀を詰めろ。";
			link.l1 = "フルミネート銀？それは何だ？";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "私自身もそのことは知らなかった、君の本からその秘密を知ったんだ。\nそれは銀、アルコール、硝酸から作れる白い粉末で、擦ったり揺らしたりすると簡単に爆発する。だからこそ、 君のピストルの弾薬の火薬に点火するのに役立つんだ。\n厄介な代物でね、私の実験中にも二度爆発してしまったよ、レシピを思いつくまでに。";
			link.l1 = "この本を持っていて運が良かった！";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "気をつけろよ、これはとんでもなく爆発しやすいんだ！俺も自分で作れるが、雷銀の保管は危険すぎる。 作ったらすぐカプセルに詰めるのが絶対に必要なんだ。銅のカプセルは作れないぞ、 前にも言ったが俺は鍛冶屋じゃないからな。";
			link.l1 = "わかった。レシピを渡してくれ、自分で覚えるよ。";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "どういたしまして。手順通りに正確にレシピを守り、工程の順番にも気をつけなさい。 さもないとフラスコごと天高く吹き飛ばされるぞ。";
			link.l1 = "気をつけます。";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "それから、この二つのフラスコも持っていきなさい。\nこちらには硝酸が入っていて、もう一方にはアルコールが入っている。\nこれで雷銀をカプセル約20個分作ることができるだろう。";
			link.l1 = "ありがとう、ジーノ！";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("You have received a flask of nitric acid");
			Log_Info("You have received a flask of spirit");
			PlaySound("interface\important_item.wav");
			dialog.text = "ピストルと見本の火薬も持っていけ。\n火薬作り、頑張ってくれよ、船長。\n無事に生き延びてくれることを願ってるぜ。";
			link.l1 = "自分の身は自分で守るつもりだ。それと、ジーノ、お前が天才だって言ったことあったか？";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "赤面してしまいますよ、船長、本気なんです……";
			link.l1 = "わかった。さようなら、ジーノ！お前は俺の最高の錬金術師だ！";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "ゴード、ゴード……その船長についてもっと教えてくれないか？どこの出身なんだ？";
			link.l1 = "わからないな。北のどこかで生まれたらしいが、時々バイキングと呼ばれていたぜ。";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "バイキングか！ああ、そうだ、覚えている、歴史書で読んだことがある。ゴルドは自由なヤールの要塞化された集落だ。";
			link.l1 = "自由なヤール？それは誰のことだ？";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "それは北方人の王子だ。かつて自由なヤールたちが自分の戦士団を率いて、 何世紀も前にドラッカルという船でヨーロッパを襲撃し、略奪していた。海賊と呼んでもいいだろう。 ゴルドは彼らの拠点であり住まいだった。休息し、農耕し、宴を開く場所だったのさ。";
			link.l1 = "なるほど。このゴルドは奴の海賊の隠れ家ってわけか……ありがとう、ジーノ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "熱と妄想だと？それは興味深いな。すぐにここへ連れて来い！私にできることを見てみよう。ただし、 もし容態が重すぎるなら何も約束はできん……彼はあなたの部下か？";
			link.l1 = "いや、ありがたいことに、そうじゃないんだ。\nジーノ、聞いてくれ、彼が誰かは聞かないでくれ、とにかくできることをしてほしいんだ、 俺にとって本当に大事なことなんだ！";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "よし、彼を家の中のお前の部屋に運びなさい。私がいくつかの調合を用意しよう……もしかするとこの根が……";
			link.l1 = "今すぐ彼をここに連れてくる！";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "できるだけ早く見つけてくれ、薬がなければ彼を治せないし、急がなければ手遅れになるかもしれない。";
			link.l1 = "仕方ない、金は俺が用意する。";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "素晴らしいです、船長。これからいくつかの薬を調合しますので、私の患者から離れてください。 明日またここに来てください。";
			link.l1 = "いいだろう、ジーノ。お前の調合と才覚は信じているぞ。";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "そうですね、二週間もあれば大丈夫だと思いますよ。踊れるようになるとは約束できませんが、 少なくとも自分の足で立てるようにはなるはずです。";
			link.l1 = "くそっ、二週間も待てねえ！俺は……できるだけ早く出航しなきゃならねえんだ！";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "船長、私は魔法使いではありませんが、あの男は今はあまりにも弱っています。 数日間でも船の上で生き延びられるかどうかも分かりません、動かすのは無理です！";
			link.l1 = "わかった、わかったが、二週間――いや、一週間でも長すぎる！";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "三日間……そうだな、三日後には出航を試みてもいいだろうが、彼には看護と薬が必要だし、途中で寄港しなければならないぞ。";
			link.l1 = "医者はいる、彼が面倒を見る。三日後に戻ってきて、そいつを引き取る、それが俺にできる精一杯だ。 途中で止まりながらでも進まなきゃならねえ……ああ、それともう一つ――ジーノ、お前は天才だ！";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "ありがとうございます、船長。三日後に友人を迎えに来てください。それまでは邪魔しないでください。 彼には完全な休養が必要です。";
			link.l1 = "わかったよ。三日後にあいつを引き取る。";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "彼は順調だが、進展は遅い。まだ連れて行くことはできない。";
			link.l1 = "ああ、ああ、ジーノ、覚えているよ。三日間……";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "悪化はしていませんが、特に回復もしていません。彼はいまだに意識がなく、自分がどこにいるのか、 なぜここにいるのかも理解していませんが、あまり気にしていないようです。まだ熱があるので、 今すぐ彼を船に乗せるのは良い考えかどうか分かりません。";
			link.l1 = "もうこれ以上待てねえ、ここにはもう十分長く居すぎた。あいつの航海に役立つ薬をまとめろ、出発するぞ。 この野郎が死刑宣告を受けるまで、せめて生き延びられるくらいには丈夫だといいがな……";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "待ってくれ、船長！俺は死刑囚の治療をしてたのか？なんだって！？ここでは莫大な作業をしたんだぜ、 乾燥火薬を作るのがどれだけ大変かわかってるのか…";
			link.l1 = "ジーノ、それを知る必要はなかったんだ。あまり心配するな、彼は海賊で、この辺りでも指折りの悪名高い男だ。 できるだけ早く彼をキュラソーに連れて行って、会社の当局と会わせなければならない。以上だ。";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "わかったよ、あんたの方が詳しいんだろう。じゃあ、海賊ってことで……キュラソーだな。まあ、どうでもいいが、よく聞けよ。あいつはほとんどの時間眠ってるだろうが、 船の揺れとむっとする暑さで治療が遅れるかもしれない。何日か航海したら一度寄港して……囚人を陸で休ませることを勧めるぜ。そうしないと、キュラソーで吊るすのは死体になっちまうかもしれねえぞ…… ";
			link.l1 = "わかった、そうしよう。マルティニークで十分だ、キュラソーへのほぼ中間地点だからな。風向きが良いことを祈るよ。 今から彼を連れて行って出発する。改めてありがとう、ジーノ。";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "どういたしまして、船長。四日間あることを忘れないでくれ――いや、五日間だが、それ以上は無理だ。それからもう一つ……俺はな、治療した後で患者が絞首刑になるために治すわけじゃねえ。医者は患者が誰であろうと責任があるんだ。 それなのに、なんだかすごく気分が悪い……";
			link.l1 = "こんなことに巻き込んでしまって申し訳ないが、君がいなければ俺たちに勝ち目はなかったんだ。\n今すぐ出航しないと、ポルトガルの連中がボスを迎えに押しかけてくるぞ。";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "興味深いな……で、具体的にどうやって俺を助けてくれるってんだ？俺は助けなんて必要としてねえし、頼んだ覚えもねえぞ……";
			link.l1 = "だが、お前にはそれが必要になるぜ。まず俺の話を聞いてから、決めるんだ。";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "お聞かせください。";
			link.l1 = "私は最近サンティアゴに行ってきたんだ……ヴィンチェント神父を訪ねてね。彼は行方不明になった秘書を探していたんだ、名前は……ジーザス、おい、ジーノ、なんでそんなに顔色が悪いんだ？";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "お前……異端審問官を見たか？彼は……";
			link.l1 = "心配するな、ジーノ。あいつにお前を引き渡すつもりはない、たとえそれが命令だったとしてもな――お前を探して連れて来いと言われたが。\n俺はイツァ族のインディオについて情報が欲しいんだ。タイアサル、その財宝、そしてそれを取り巻く「邪悪」 について教えてくれ。";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "よくご存知のようですね。これはヴィンチェント神父が教えてくれたのですか？";
			link.l1 = "彼からも、他の者たちからも情報は得た。だが、君の話も聞きたい。君はかつて彼の書記だったから、 尋問の記録をつけていたはずだろう、違うか？";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "あの哀れなインディアンに彼が何をしていたか、あなたには想像もできないでしょう…！\nあの尋問を思い出すたびに、今でも身の毛がよだつんです。";
			link.l1 = "それでも、話してみよう。あのインディアンは誰だったんだ？どうしてヴィンチェント神父の手に渡ったんだ？";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "彼はイッツァ族のインディオたちの一員で、タイアサルからククルカンの仮面――古代マヤの神ククルカンの遺物――を探しに旅していたんだ。そのインディオたちは、 スコットランド出身の財宝探しの冒険者アーチボルド・カルフーン率いる白人の一団と遭遇した。 生き残ったインディオはただ一人、名をクサトル・チャという。彼は三つの興味深い品を持っていたが、 それについては後で話そう。\nカルフーンは捕虜に財宝について話すよう強要したが、男は沈黙を守った。 そこでスコットは彼をサンティアゴのヴィンチェント神父のもとへ連れて行き、 一年間スペイン領の都市に出入りする許可と引き換えに引き渡した。 カルフーンは異端審問官がこの地のあらゆる謎や伝説に興味を持っていることを知っていたのだ。 ヴィンチェント神父はインディオに口を割らせた。彼は饒舌になり、知っていることをすべて話した。その内容は、 異端審問官自身をも驚かせるものだった。";
			link.l1 = "そうかい？で、その閣下を震え上がらせるものとは何だ？";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "順を追ってすべてお話ししましょう。ユカタンの密林の奥地には、タイアサルという古代マヤの都市があります。 そこにはマヤの末裔であるイッツァ族が住んでいます。彼らは祖先の掟や伝統に従って生きようとしています。当然、 現代世界の有様――つまり白人の支配――を快く思ってはいません。\n彼らは古き良き時代を夢見ているのです。そして、ここからが一番興味深いところです。ある白人の冒険者たちの一団が、 偶然タイアサルに近づき、イッツァ族の最高首長の娘を誘拐してしまいました。それはほぼ四半世紀前の出来事です。\nこれが最後の一線となり、首長カネクは激怒しました。彼はマヤでも最も危険で秘密とされる儀式――インディアンの神を呼び出し、白人征服者の末裔をすべて消し去るというもの――を執り行う決意をしたのです……";
			link.l1 = "ふむ……これがヴィンチェント神父が話していた悪魔か。だが、 このインディアンの神はどうやって白人の植民者たちに対処するつもりなんだ？\n竜の姿で現れて、みんなを焼き払うのか？";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "「ああ、」 "+pchar.name+"、こんな火の怪物の話は年寄り婆さんに任せとけ！まあ、あんたが全く間違ってるわけじゃねえが、 俺たちの件はもっと厄介で深刻なんだ。大洪水だってヨーロッパが新世界へ進出するのは止められねえ。 一人死んでも十人がやってくる。カネクはヨーロッパ人の植民そのものの可能性を根絶やしにする必要があったんだ。";
			link.l1 = "もう、すでに起こってしまった。";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "考え方は正しいですよ、船長……カネクの儀式の目的は、ただ高次の存在を呼び出すことだけでなく、時空の裂け目を生み出すことにもあったのです。";
			link.l1 = "「何だ？」";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "古代マヤ人は驚くべき知識を持っていました、船長。カネクが時間を操ることができる儀式の記述を見つけたのです。";
			link.l1 = "うおっ！すげえ！";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "聞いてくれ。儀式の最終目的は、過去を改変し、白人が新世界に到達すること自体を不可能にすることだ。 そんなことを成し遂げるために、やつらは誰かを過去に送り込もうとしている――権威と力を持ち、人々の運命を変えることができる者をな。だが、最も重要なのは、 その者が現代の知識を持っていなければならないということだ。\nよく考えてみろ。 "+pchar.name+"、もしコロンブスのキャラベル船が、 近代の大砲を備えたインディアンのフリゲート艦やガレオン船の艦隊に迎え撃たれていたらどうなっていただろう？\nそして、白人兵士たちの火縄銃に立ち向かったのが弓や槍ではなく、 臼砲やマスケット銃だったらどうなっていただろうか？";
			link.l1 = "アメリカ大陸はそもそも発見されなかったのではないか……。";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "まさにその通りだ！それに、もしかしたらインディアンの“コロンブス”がヨーロッパを発見していたかもしれないな…";
			link.l1 = "面白いな、それでカネクは誰を過去に送るつもりなんだ？裸の戦士の一人か？ご先祖様に何か教えられるとは思えないが…";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "笑うなよ、船長。カネクはマヤの神殿で何年もただ書物を読んで過ごしていたわけじゃないんだ。 インディオの神は人間の姿で過去に送られなければならないんだ……";
			link.l1 = "ジーノ、何を馬鹿なこと言ってるんだ？お前は……";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "我らが主の御子、イエス・キリストさえも、人の姿でこの世に降り立ち、 聖母マリアという人間の女性からお生まれになったのです……";
			link.l1 = "ジーザス、ジーノ……本気か？";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "もちろんさ。クサトル・チャはとても説得力があったからな……";
			link.l1 = "「だが、カネクはそんな『高貴』な任務のためにどの神を選んだんだ？」";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "その儀式は本来、一柱の高位なる存在のみを呼び出すためのものだった。羽毛を持つ蛇、ケツァルコアトル、ククルカン……";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "ククルカンだと！？私はすでに、あの像に宿る「精霊」とやらに無謀にも遭遇したことがある。今、分かった……続けてくれ！";
			else link.l1 = "ふむ。興味深いな。その名前はすでにヴィンチェント神父から聞いたことがある……続けてくれ！";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "カネクはククルカンを召喚することを決めた。なぜならイッツァ族はすでにこの神の古代の遺物──ククルカンの仮面──を所有していたからだ。仮面を持つ者はポータルを通過することができ、 そしてその者だけが古代マヤ人に生ける神として受け入れられるのだ。\n神父は儀式を執り行い、ククルカンを呼び出して、神が人間の体に受肉するようにした。また、時空の裂け目も作り、 未来から何人かの人間をこの時代に引き寄せた。\nこの召喚の目的は、ククルカンの受肉体に我々の時代だけでなく未来の知識も授けることだった。 しかし何かがうまくいかず、彼らはみなテヤサルではなく別の場所に現れてしまった。私はその誰とも会ったことがない。 \n諸島のあちこちにいくつものポータルが作られた。 それらは未来の知識の持ち主やイッツァの使者たちを各地からテヤサルへ運ぶためのものだった。 しかしこれらのポータルは役目を果たせず、過去25年間、誰一人としてテヤサルに運ばれてきていない……";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "そうか……このポータルは捕まえた人間同士を移送するだけなんだな。信じられないぜ！";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "「面白い…」";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "あのポータルを見たか？教えてくれ！";
			link.l1 = "後でな、ジーノ……今はお前の話の方が気になるんだ。続けてくれ！";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "ヴィンチェント神父は、私があなたに話したすべてを知っています。当然、彼も心配しています。 もしククルカンが人間の姿で、仮面と彼が集めたすべての知識を携えてポータルにたどり着いたら……それは終末、黙示録です。\n過去が変われば、未来も同じように変わります。我々の現実は変化し、消え、溶けてしまうでしょう。 あなたも私も生まれてこないかもしれません。あるいは、まったく別の存在になるかもしれません。 ククルカンが過去に到達した瞬間、私たちは存在しなくなるのです。";
			link.l1 = "「それで、ククルカンの化身とは誰なんだ？」";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "誰にも分からんさ。儀式が行われた四半世紀前に生まれた者なら誰でもあり得る。例えばお前とか……冗談だよ。だが、まだ望みはある。まず、ククルカンの化身も所詮はただの人間だ。溺れることもあれば、 刺されることも、撃たれることも、熱病で死ぬこともある。そうなれば、終末なんて決して起こらない。\nそれに、仮面がなければ過去に到達することは不可能だ。カネクは仮面をとても上手く隠した――いや、隠しすぎたかもしれないな。もしかすると、化身となったククルカンですら見つけられないかもしれん。";
			link.l1 = "もっと詳しく話してくれ。";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "儀式のしばらく後、スペインのコンキスタドールたちの一団がタイアサルに迫り、 もう少しで財宝庫にたどり着くところだった。イツァ族は彼ら全員を討ち取ったが、一人だけ――七尺もある大男――を除いては。カネクは、仮面がどんなよそ者にも奪われるのではと心配し、遺物を守ることを決意した。 彼は古代マヤの知識を使い、自らの儀式を考案した。彼は白人の力が宿ると信じた三つの品――かつてコルテス自身が持っていた短剣と、コンパス――を手にした。そして三つ目の品として、その捕らえたスペイン人巨漢の背中から短剣で皮膚を切り取った。 その男自身はククルカンの祭壇で生け贄にされた。三つの品が儀式に使われた。\nそしてこの儀式から、新たな島が生まれた。ユカタンの沖合、外海に浮かぶ島だ。その場所を知る者はいないが、 仮面はそこに隠されている。見つけるには、短剣、コンパス、そして皮膚の切れ端が必要だ。さらに、 財宝庫のすべての品には呪いがかかっている。この諸島から一つたりとも持ち出すことはできない。\nもし持ち出そうとすれば、嵐が起こり、船は仮面が隠された島の岩礁へと叩きつけられる。その島の名はクソチェアテム。 賢いだろう？";
			link.l1 = "頭が良すぎるかもな。それは否定できねえ。\nだが、どうしてクサトル・チャがあんなに詳しく知ってたんだ？ カネクがそんな情報を普通の戦士どもに教えてたとは思えねえが…";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "実はな、今のイツァ族の族長カネクの息子ウラカンが、この戦士にすべてを話したんだ。 ウラカンはカサトル・チャを戦士たちの一団と共に、秘密の島とククルカンの仮面を探しに送り出した。そのために 「真実の守護者」を託したんだ。それは三つの品の総称で、人間の皮でできた短剣、羅針盤、地図のことだ。";
			link.l1 = "地図だと？それに、なぜウラカンは仮面を必要としたんだ？まさか自分で過去を変えようとしたのか？";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "その皮膚には諸島の輪郭が刻まれているため、「地図」と呼ばれている。ウラカンが仮面を欲した理由は極めて単純だ――彼は現実を壊したくもなければ、古代人の栄光のために自分や仲間の命を犠牲にしたくもなかったのだ。\nだからこそ、彼はどんな犠牲を払ってでも仮面を破壊しようと決意した。 しかしクサトル・チャはカルフーンに捕らえられてしまい……まあ、その後の話は知っているだろう。彼は決してクソチェアテムに辿り着くことはなかった。";
			link.l1 = "つまり、仮面を見つけて破壊すれば世界の終わりを防げるってことか？\nそれで……その「真実の守護者」とやらは今どこにいるんだ？";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "短剣『酋長の爪』とコンパス『道しるべの矢』はカルフーンに渡され、皮の地図『二つの貌』 は今も異端審問官のどこかにある。\nカルフーンは囚人の口を封じるための冗談としてそれを使った。\n彼はこれらの品が何のためのものか全く知らなかった。";
			link.l1 = "今なんて言った？「酋長の爪」だと？くそっ、この短剣なら今まさに俺が持ってるぜ！ ファディが兄貴への借金の返済として俺に渡したんだ！見てみろよ！";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "信じられない……本当にそうだ。覚えている。";
			link.l1 = "ジーノ、お前の話についてヴィンチェント神父は一体どこまで知っているんだ？";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "真実の守護者に関する情報と、ククルカンの仮面が隠された秘密の島の場所を明かさせる方法以外はすべてだ。 カサトル・チャはそのことを、俺たちが二人きりになったときに話してくれた――ちょうど俺が彼に苦しみを終わらせる毒薬を渡す直前だった。彼は微笑みを浮かべて息を引き取った。\nあんなことをした後じゃ、サンティアゴにはとてもいられなかった。 俺が異端審問官にとって重要かつ危険な証人になったのではないかと、強く疑っていたんだ。ヴィンチェント神父は、 どんな手を使っても自分の望みを叶える男だ。カサトル・チャは彼に、タイアサルの財宝について話したんだ。";
			link.l1 = "これらの財宝はすでにミゲル・ディチョソという名の冒険者に発見されたんだ。彼のことを聞いたことがあるか？";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "いいや。で、今そいつはどこにいるんだ、宝と一緒に？";
			link.l1 = "私自身を知りたいんだ。だからこそあなたのもとに来た、あのインディオの黄金を探しているんだ。 ディチョソがその財宝をヨーロッパへ持ち去り、姿を消したんだ。";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "財宝とディチョソ本人がどこにいるか教えてやる。";
			link.l1 = "ジーノ、お前には驚いたぜ。どうしてそれを知ってるんだ！？";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "私の話から自分で考えてみてください、船長。タイアサルの財宝には呪いがかかっていて、 ひとつたりともこの諸島から持ち出すことはできません。どんな船であっても…";
			link.l1 = "…嵐に巻き込まれて、ククルカンの仮面が隠された島へ投げ出されることになるだろう！ 私は今まで何も見えていなかったが、今ははっきり分かる。どうやら、クソチェアテムや財宝、 そして仮面そのものを見つけるのに十分な手がかりを得たようだ！";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "世界を救いたいかい、船長？";
			link.l1 = "俺は放蕩者の兄を見つけたいんだ……ジーノ、どうやったら「真実の守護者」に島の場所を明かさせられる？お前は方法を知ってるって言ったじゃねえか！";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "方法は知っているが、詳しいことは分からない。ガーディアンのすべての部品が揃うまでは、君を助けることはできない。 ";
			link.l1 = "ふむ。短剣はもう手に入れている。残るはコンパスと地図だけだ。コンパスはカルフーンが持っていて、 地図はヴィンチェント神父が持っている……";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "異端審問官のところへ戻るつもりか？しかし、どうやって報告するんだ…";
			link.l1 = "ジーノ、お前が死んだとヴァンチェント神父に納得させなきゃならないんだ。そうすれば、あの人も捜索をやめるだろう。 \n俺を見た瞬間、急に発作を起こしたことにしよう。\nお前の死を証明できる品を何か渡してくれ。";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "ヴィンセントは心臓発作の話なんて信じないだろうが、 俺がアーモンドの香りがする毒を飲んで自殺したと言えば信じるはずだ。\n俺の暦を彼に渡してくれ、あいつは俺がそれを手放さないことを知っているからな。";
			link.l1 = "いいだろう。俺にはあの異端審問官との繋がりが必要なんだ。あいつはきっと俺たちの商売について色々知ってるはずだ。 ";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "ヴィンチェント神父には気をつけろ。あいつは虎のように危険で、自分だけのゲームをしているんだ。 財宝も名声もお前とは分け合わないぞ。";
			link.l1 = "わかったよ。よし、ジーノ、お前の暦を渡してくれ。それから、インディアンが「真実の守護者」 について話していたことを思い出してみろ。俺は全部をつなぎ合わせたいんだ。クソチェアテムを見つけなきゃならない。 そこには仮面や財宝だけじゃなく、きっと愛しい兄上もいるはずだ。";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "受け取れ。幸運を祈るぜ、船長！";
			link.l1 = "さよならは言わないよ、ジーノ……";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("You have received an almanac");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "大変でしたか、船長？";
			link.l1 = "その話はやめておこう……この品々を手に入れるために、あまりにも多くの人が死んだ。多すぎるほどにな。\n謎のクソチェアテムを探しているのは、俺だけじゃないようだな。 ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "想像はつくよ……ところで、ヴィンチェント神父は元気か？定期的に連絡を取っているのか？";
			link.l1 = "今のところはそうしているが、もうその必要はないと思う。真実の守護者の全ての部品を手に入れたから、 クソチェアテムの所在の鍵を握っていることになる。なぜか、私は閣下にこの成功を報告する気になれないんだ。";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "「気をつけて」 "+pchar.name+"……ヴィンチェント神父には何百もの目と手があるんだ。しかも、その手はとても長い……";
			link.l1 = "ここ数ヶ月でいろいろ経験したから、今さらヴィンチェント神父も、あいつの目や手も、全然怖くないさ。まあ、 どうでもいい。\nそろそろガーディアンの部品を使ってクソチェアテムを見つける時だ。やり方は知ってるか？ ";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "いや、そうでもない。クサトル・チャはかなり曖昧だった。 あのインディアンもガーディアンの使い方を本当に分かっていたわけじゃないと思う。部品は私に任せてくれ、 何とか解明してみるよ。二日後にまた来てくれれば、この謎が解けているかもしれない。";
			link.l1 = "わかった、ジーノ。頼りにしているぞ。ほら、これを持っていけ。";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "私と一緒なら、彼らは必ず無事で安全に過ごせます。";
			link.l1 = "それは疑っていないよ。まあ、今は邪魔しないでおくよ、ジーノ。研究、頑張ってくれ！";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "部分的にはね。つまり、何かは掴んでるけど、どうやって本当にうまくやるかは分からないんだ。\n一緒にこの謎を解いてみよう。";
			link.l1 = "やってみよう！君のアイデアを聞かせてくれ。";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "クサトル・チャはこう言ったそうだ：「酋長の爪が地図を明らかにする。道の矢が出現の方角を示す。」";
			link.l1 = "「それで、お前は何をやったんだ？」";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "地図が「自ら現れる」仕組みを解明したんだ。\n「二つの姿」の地図をもう見てみたか？";
			link.l1 = "ふむ。それで、何か変わったことはあったか？群島の輪郭に妙なところとか……";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "受け取って、もう一度よく見てみろ。注意深くな。";
			link.l1 = "そうかい、そこまで言うならやってやろうじゃねえか。";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "「地図を見ていないな。」 "+pchar.name+"...";
			link.l1 = "はいはい、今やりますよ…";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "見たよ。新しいものは何も見えなかった。島や本土のぼんやりした影があるだけだ。俺はそこで何を見ればいいんだ？";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "ちょっと待て。これからこの地図を浮かび上がらせなきゃならない。短剣を取って、その刃先で地図にそっと触れてみろ。 押し付けるな、傷つけたくないからな。短剣を取れ。そして、よく見てろよ！";
			link.l1 = "面白いな！さて、見てみよう…";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "さて、今は何か違いが見えるか？";
			link.l1 = "はい。短剣で地図に触れると、ドクロの印が二つ現れるんだが、いつも同じ場所に出るんだ…";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "「同じ二か所で」 "+pchar.name+"！だからこそ「二つの姿の地図」と呼ばれていたのだ！";
			link.l1 = "「それはどういう意味だ？」";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "たくさんだと思う……だが、次はもっと謎が待っているようだ。これらの髑髏がクサトル・チャが話していた亡霊なんだろうな。つまり、 コンパスはそこからクソチェアテムへの正しい方向を示すはずだ。コンパスを見たことがあるか、\n "+pchar.name+"?";
			link.l1 = "はい。見た目は普通の海軍用コンパスだが、挙動がおかしいんだ。針があちこちにピクピク動いたり、 突然激しく回り出したりするんだよ。";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "コンパスを頭蓋骨の上に置けば針が止まって、地図に何かはっきりした方向を示してくれると思ったんだ。\nそれで、まず一つの頭蓋骨にコンパスを置き、次にもう一つの頭蓋骨に置き換え、同時に短剣で地図に触れてみたんだ。";
			link.l1 = "それで？";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "無駄だった。コンパスの動きは変わらなかった。針は相変わらず激しく回っている。 どうやら私が何か間違っているようだ。あるいは、クサトル・チャの言葉を誤解したのかもしれない。";
			link.l1 = "つまり、短剣と地図は使えるが、コンパスは使えないってことか？";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "「道の矢」は確実に動くはずだが、どうやって作動させるかはまだ分かっていないんだ。 "+pchar.name+"……お前の方がこの諸島の地理に詳しいだろう……教えてくれ、「二つの顔の地図」が示す場所はどこだ？";
			link.l1 = "ちょっと待て！（見ている）…ふむふむ…左手の陸地は西インディアス本土だな。右手のはドミニカ島に見えるぜ。そんなところだ。";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "それで教えてくれ……その場所には……何か注目すべきものがあるのか？";
			link.l1 = "どういう意味だ？";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "私にもよく分かりませんが……まあ、何か特別なことですか？";
			link.l1 = "ジーノ、謎かけみたいな話はやめろ。簡単に説明しろ。";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "これらの頭蓋骨は実際の場所を示しているとしか思えないな。\n地図の絵の上に「道の矢」を置いても反応しない。\nもしかすると、地図が示す本物の地形の近くで使えば反応するのかもしれないな？";
			link.l1 = "ジーノ、お前は天才だ！ウェスタンメイン、ドミニカか？頭蓋骨が大きすぎて正確な場所は示せねえな。";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+"では、こうしよう。諸島の紙の地図を持ってきて、「二つの出現」の地図と合わせて、出現した場所に十字を記してくれ。 \nもしかしたら、そこから何か推測できるかもしれないぞ。";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "この群島の古い地図を持っているんだ。";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "この素晴らしい諸島の地図を持っているんだ。";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "この群島の素晴らしい地図を持っているんだ。";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "取引成立だ。俺が地図を持ってきたら、続きを話そう…";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "「おい、勘弁してくれよ」 "+pchar.name+"！このコロンブス時代の羊皮紙なんて、皮の地図と大して変わらんじゃねえか。 世の中にはもっとマシなもんがあるはずだぜ。もっと新しい地図を持ってこいよ！";
			link.l1 = "……わかった……";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "素晴らしい！では、その地図に出現場所を記してくれ。そうすれば仮説を立てやすくなる。";
			link.l1 = "ちょっと待て、ジーノ！";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "こんな素晴らしい地図に俺たちの印なんか付けて台無しにできるわけねえだろ。お前自身が必要になるんだからな。 "+pchar.name+"「もう一枚地図を持ってこい、もっと控えめなのを頼む！」";
			link.l1 = "……わかった……";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "諸島の地図を持ってきてくれたのか、 "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "この群島の古い地図を持っているんだ。";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "この素晴らしい諸島の地図を持っているんだ。";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "この素晴らしい群島の地図を持っているんだ。";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "まだだが、もう注文はしてある。すぐに手に入るから、そしたら続けよう…";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "終わった……印をつけたが、情報はまだ正確じゃない。\n最初の場所はブルーウェルドの北西あたりだ。\n二つ目はドミニカ島の中央だ。";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "何か考えはあるか？";
			link.l1 = "いいや。しかし、「アロー・オブ・ザ・ウェイ」をそこに連れて行って、その反応を観察すべきだと思う。もちろん、 干し草の山から針を探すようなものだけど、他にいい案もないしな。";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "「あなたに同意します」 "+pchar.name+"。私も一緒に航海させてくれませんか？";
			link.l1 = "自分の仮説を試してみたいのか？俺の船の甲板にお前を迎えられたら光栄だぜ、ジーノ。荷物をまとめろ！";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "時間はかからない。数時間で準備できる。ほら、「道しるべの矢」を持っていけ。";
			link.l1 = "乗船を歓迎する！";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "「はい、はい、」 "+pchar.name+"、準備を整えているところだ。すぐに用意ができる。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "だから何だ "+pchar.name+"「俺たちの捜索、うまくいってるか？」";
			link.l1 = "俺たちの考えは正しかった。これだ。インディアンの偶像はその一形態なんだ。";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "おお！これはきっと、人々をテヤサルへ転送するって言われていたあの偶像の一つだな！前に話しただろ、覚えてるか？ それで、「道の矢印」はどこを指してるんだ？\n";
			link.l1 = "北西を指している。地図にその方向を記しておいた。だが、その線はカリブ海をほぼ横断している。 ドミニカで別の出現場所を探して、クソチェアテムを見つけなければならないな。";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "きっとあそこでもう一つの偶像が見つかるはずだ……私の仮説に同意してくれるか、 "+pchar.name+"?";
			link.l1 = "ああ、ジーノ。さあ、時間を無駄にせず捜索を始めよう。";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "それがどうした "+pchar.name+"、何か面白いものを見つけたか？";
			link.l1 = "俺たちの考えは正しかった。これだ。インディアンの偶像はその一つの形なんだ。";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "おお！これはきっと、テヤサルへ人を転送するって言われてたあの偶像の一つだ！前に話しただろ、覚えてるか？それで、 「道の矢印」はどこを指してるんだ？";
			link.l1 = "北西だ。地図に方向を記しておいた。\nただ、その線はカリブ海をほとんど横断している。\nクソチェアテムを見つけるには、本土の別の上陸地点を探さなきゃならないな。";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "だから何だ、 "+pchar.name+"、二つ目の偶像は見つけたか？";
			link.l1 = "ああ。私は道の矢が示した方角を描いた。これでクソチェアテムの場所がわかったぞ。正確な地点じゃないが、 探すべき場所は特定できた！線が交わるその一帯を全部探し回って、あの忌々しい島を必ず見つけてやる！";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "あなたの声からそんな熱意が感じられて嬉しいですわ。\nしかし、これからの遠征にはしっかり備えなければなりませんの。\nそこで何が待ち受けているのか分かりませんし、温かく迎えられるとは思えませんわ……";
			link.l1 = "何か具体的に心配しているのか、それともただ不安を口にしているだけか？";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "考えてみろ "+pchar.name+"「……クソチェアテムはカネクによるマヤの魔術で創り出されたものだ。自然の地形ではなく、邪悪で破壊的な力を持っている。 あそこに何が待ち受けているかは分からないが、陽の光や穏やかな海、女たちや静かな風など、期待できそうにないな。」 \n";
			link.l1 = "わかった、ジーノ。君の言葉を考慮して遠征の準備をするよ。自分の船を整えて、薬や弾薬の用意もしておく……";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "とても賢明なご判断です。さて、船に戻りましょうか？";
			link.l1 = "もちろんだ！行こうぜ！";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "着いたぞ。 "+pchar.name+"「うっ、風が唸ってるぞ！」";
			link.l1 = "ああ、ジーノ、お前の言う通りだ、俺たちを迎える陽の光はねえ……それに娼婦の姿も見当たらねえ。正直、ここで何が待ってるのか全く分からねえな。";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "おい、船長、こんなひどい場所に上陸するなんてよ！周りは岩と崖ばかりじゃねえか！\nここからどうやって島の内陸に行くつもりだ？";
			link.l1 = "この忌々しい嵐のせいで、この島に上陸できそうな入り江は他に見当たらなかった！\nまあ、何もないよりはマシだ。岩場の間をどうにかして進むさ、もっとひどい目にも遭ってきたんだ。\n慌てるな、相棒！";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "「俺はこの島が気に入らねえ」 "+pchar.name+"！気味が悪いな。それに、この嵐は島にまとわりついてるに違いねえ。この場所はもう終わりだ、間違いねえ！";
			link.l1 = "俺もこの場所はあまり好きじゃねえよ、ジーノ！だが、この島は実在する。つまりククルカンの伝説は本当ってことだ。 もし奴が仮面を持ってタイアサルにたどり着いたら、俺たち全員危険な目に遭うぞ…\n";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "仮面を探してくれ、船長！それは世界中の財宝よりも大事なんだ！この辺りにあるはずだ！ 手に入れたらククルカンの計画を打ち砕き、過去を変えさせたりはしないぞ！\n";
			link.l1 = "それで、その仮面はどんな見た目か、知っているのか？";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "全然わからねえ！でも見ればきっとわかるはずだ、古代インディアンの遺物だからな、他のものと間違えようがねえよ！";
			link.l1 = "なるほど。気をつけておくぜ！よし、ジーノ、船に戻れ！島をうろつく必要はねえ、 お前の首は危険にさらすには高すぎるからな！\n";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "嘘はつきませんよ、船長。私は戦いが苦手で、この場所はどうにも落ち着きません。少し助言をしてもよろしいですか？ ガーディアンのすべての部品はこの島の魔法と繋がっています。クサトル・チャは、 短剣がこの地の住人たちに対して力を持つと言っていましたが、私にはその意味がよく分かりません。\n私は船に残ります。もし助けが必要なら、そこで私を探してください。";
			link.l1 = "よし。じゃあ、幸運を祈ってくれ、ジーノ！";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "「幸運を祈る」 "+pchar.name+"！神のご加護とお守りがありますように！";
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "「調子はどうだ、」 "+pchar.name+" ？何か助言が必要か？ ";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "この忌々しい島はアンデッドどもで溢れてやがるし、あのクソ骨野郎どもは思ったより手強いぜ。 どうやって戦えばいいのか、さっぱり分からねえ。";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "分かれ道を左に進めば、いずれ洞窟にたどり着くはずだ。\nだが、この先どこへ行けばいい？\n洞窟が行き止まりなのではと不安だ……";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "濡れた洞窟に入る道を見つけたが、水中部分には潜れるぞ。だが、そこからの出口は見当たらないんだ…";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "分かれ道を左に行けば洞窟に着く。でも、次はどこへ行けばいいんだ？洞窟は行き止まりなんじゃないかと不安だ…";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "大きな洞窟の中に、水没した区画へ潜れる場所がある。\nだが、そこから外へ出る道はなさそうだ……";
				link.l1.go = "adversary_5";
			}
			link.l10 = "今のところ全て順調だ、ジーノ。俺は大丈夫だ。";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "クサトル・チャが酋長の爪について話していたな。骸骨どもに対して使ってみろ。あのインディアンが言うには、 この短剣はクソチェアテムの住人たちに対して力を持っているそうだ。";
			link.l1 = "絶対に挑戦してみます！";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "「それで、その洞窟はどんな様子なんだ？」";
			link.l1 = "そうだな、岩の中に小さな洞窟があるんだ。中は湿っていて、底では水が波のように揺れている……";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "もし水が揺れているなら、この洞窟は海とどこかで繋がっているはずだし、行き止まりじゃないはずだ。\n通路を探せ、きっとどこかにある。";
			link.l1 = "向かっているところだ……";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "もし主洞窟から水没した洞窟への道があり、主洞窟の水が波のように揺れているなら、 水没した洞窟にはもう一つ通路があるはずだ。\nもっと念入りに探せ、だが気をつけろ、さもないと溺れるぞ。";
			link.l1 = "俺はこれから潜るぜ…";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "「それで、その洞窟はどんな様子なんだ？」";
			link.l1 = "そうだな、かなり広くて洞窟がいくつかあり、湿っぽいし、静かな水が溜まった小さな穴もあるんだ…";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "もし水が動いていなければ、その洞窟は海とつながっていない可能性があり、行き止まりかもしれない。";
			link.l1 = "私も同じことを考えた。あそこを長い間探していたが、入口は一つしかなく、それが出口でもあるんだ……";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "もし洞窟の中の水がまだ動いていないなら、君の言う通りかもしれないな。もう少し探してみてくれ、 でも何も見つからなくても落ち込むなよ。行き止まりの可能性が高いからな。";
			link.l1 = "なるほど……";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+"「スペイン船が俺たちに迫ってるぞ！今は話してる場合じゃねえ！」";
			link.l1 = "ああ、もちろん…";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "あなたの嬉しそうな目を見れば、探していたものが見つかったと分かりますね。";
			link.l1 = "ああ。ミゲル・ディチョソの財宝とククルカンの仮面だ。これで奴の化身は二度と未来を変えられない！";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "信じられない！あなたは英雄だ、 "+pchar.name+"...";
			link.l1 = "ジーノ、これでククルカンを止めるには本当に十分なのか？";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "クサトル・チャによれば、そうだ。そして彼はウラカンの言葉を引用していた。この騒動を始めたのは彼の父親、 カネクだったんだ。疑いはあるか？";
			link.l1 = "湾で私を出迎えたのは、過去からの客人――アロンソ・デ・マルドナードだった。彼はカネクが真実の守護者を生み出す儀式を行った時、タイアサルにいた。 時空の裂け目に引きずり込まれながらも生き延びてきた……今日までは。";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "彼は、我々の世界を守るためにはポータルそのものを閉じなければならないと言った。\nそのためには、テヤサルのどこかの祭壇で仮面を破壊しなければならないんだ。";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "「それでテヤサルへ行くつもりなのか？正気じゃないぞ！」 "+pchar.name+"、お前は仮面を手に入れたから、ククルカンの化身も何もできやしねえ！カネク自身もそれを確信してるんだ！ だからこそ、ウラカンはクサトル・チャをクソチェアテム探しに送り込んだ――仮面を手に入れて、それを破壊するためにな。";
			link.l1 = "もしこのウラカンがタイアサルで仮面を破壊するつもりだったらどうする？";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+"今のところ、タイアサルから生きて脱出できた男は一人だけだ、それがミゲル・ディチョソだ。\nマルドナードもいるが、あれは例外だ。たとえククルカンの化身が過去に戻ったとしても、古代マヤ人に殺されるだろう！ ";
			link.l1 = "もし奴らが彼を殺さずに、正体に気づいたらどうする？";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "それで、タイアサルへの遠征を計画しているのか？";
			link.l1 = "わからないよ、ジーノ。本当にわからないんだ……";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "それなら考えてみろ、なぜそんなことをする？俺の意見は聞いたはずだ。あとはお前次第だ……"+pchar.name+"「セントジョンズまで連れて行ってくれるか？」";
			link.l1 = "ああ、ジーノ。できるだけ早く出航しよう。このひどい島にはもううんざりだ。";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "「もうすぐ家に帰れるのか」 "+pchar.name+"……俺のフラスコや試験管が恋しいな……";
			link.l1 = "ああ、ああ、ジーノ、もうすぐアンティグアに着くぞ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "やっと戻ってこれて嬉しいですわ！あなたたち水夫がどうやってあんなに長い時間も船の上で過ごせるのか、 私には想像もできませんわ……";
			link.l1 = "慣れの問題だよ、ジーノ。";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "私は大地の上にしっかり立ったまま、ベッドに横たわるつもりだ…大いに楽しみたいものだが、願わくば。 "+pchar.name+"、テヤサルを訪れることなど考えもしなかったのか？";
			link.l1 = "まだ分からないんだ、ジーノ。正直に言うと、俺もまだ確信が持てないんだ。";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "ククルカンの仮面を破壊して、心配なく生きてください、船長。\nご希望なら、私が持つ最強の酸でその仮面を溶かすこともできます。\nそんなことで恨みはしませんよ。";
			link.l1 = "そうだな、しばらく待つとしよう。壊す時間ならいくらでもあるからな。";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "決めるのはあなたです。この遺物からこの世界を救うことを選ぶなら、私のところへ来てください。 素晴らしい航海をありがとう、船長！";
			link.l1 = "いつでもいいぜ、Gino。またな！";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("あなたは "+GetSexPhrase("泥棒だ、旦那！衛兵ども、そいつを捕まえろ","泥棒だ、あの娘だ！衛兵、あいつを捕まえろ！ ")+"!!!","見てよ！僕が物思いにふけっていたその隙に、君は僕の胸を探ったんだね！泥棒だ！誰か、この泥棒を捕まえてくれ！！！ ","衛兵！強盗だ！泥棒を捕まえろ！！！");
			link.l1 = "くそっ！";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
