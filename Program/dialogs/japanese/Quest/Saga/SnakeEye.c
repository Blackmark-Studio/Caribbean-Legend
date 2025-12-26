// шаман команчей Змеиный Глаз
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
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "「やあ、色白の友よ。」";
				link.l2 = "俺も会えて嬉しいぜ、赤肌の兄弟よ。今回もお前に頼みたい大事な用があるんだ。";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "ごきげんよう、色白の友よ。";
			link.l1 = "俺も会えて嬉しいぜ、スネークアイ。";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "頼まれていたお守りを持ってきたぜ。取引しようじゃねえか。";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "お前のタンバリンを見つけたぜ、スネークアイ。これを見てみろ。";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "面白いインディアンのパイプを見つけたぜ、スネークアイ。見てみろよ。";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "やあ、シャーマン。像を使って、とんでもない旅を体験したよ。あなたの言った通りだった。船の墓場や白い船長、 さらには物資の積まれた貨物室まで見つけたんだ！";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "スネークアイ、助けが必要だ。";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//---------------------------------------- первая встреча------------------------------------------------
		case "SnakeEye":
			dialog.text = "ごきげんよう、色白の友よ。";
			link.l1 = "やあ、シャーマン。なぜ俺があんたの友達だと思うんだ？";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "俺はいろいろ知ってるが、何を正確に知ってるかはいつも分かるわけじゃねえ。\nお前は目的があってここに来たんだろう。運命がここへ導いたんだ、そして俺はお前を助けるためにここにいるのさ。";
			link.l1 = "それは良いことだ！実はお前の助けを求めてここに来たんだ、赤肌の友よ。単刀直入に聞くぜ――ホークの女房にククルカンのことを話したって、どういう意味だ？";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "死んだ魚でさえ流されていく。生きている人間は、運命に導かれて次々と目的地へ向かうのさ。\n鎖につながれた船長――邪悪な連中に密林で追われた男の目的はククルカン像だった。\nもし自らを犠牲にすれば、ここから遠く離れることもできただろう。";
			link.l1 = "俺にはさっぱり分からなかったぜ。お前の神様の像は何のためにあるんだ？それに、 ホークはどうやって誰にも見つからず、今でも行方知れずになるほど遠くまで歩いて行けたんだ？\n";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "もしククルカンがホークを食ったなら、どこにでも吐き出すことができるはずだ。\nもしかしたら、別の世界にさえもな。\nククルカンは俺を三度も飲み込んだ。\nそのたびに、俺は違う場所にたどり着いた。\n昔、ここに流れ着いて、もうこれ以上危険は冒さないと決めたんだ。\n俺はククルカンの口の中には入らなかったし、奴が犠牲者をどこに吐き出すのかも知らない。";
			link.l1 = "なんてこった、俺にはさっぱりわからねえ！石像の偶像が人を遠くへ転送できるって言うのか！？";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "それだけじゃない。ククルカンは空間だけでなく時間さえも支配している。いや、それ以上かもしれない。 俺は鎖につながれた船長に人を喰らう黄金の像の話をした。追っ手が近づいているのを見て、 あいつは賭けに出ることにしたのかもしれねえ…";
			link.l1 = "待てよ、その像は石でできているじゃねえか。しかもお前は金の像の話をしてるんだろう…";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "真夜中になると、その偶像は命を得て黄金へと変わる。その瞬間、ククルカンの精霊が宿るのだ。\n近づくことは控えよ、さもなくば、別の場所で日の出を見ることになるかもしれん。星々さえも空で位置を変えるだろう。 \nまだ生まれていない者と出会うかもしれぬし、遥か昔に死んだ者、 あるいは決して生まれなかった者の誕生を目撃することになるやもしれん。";
			link.l1 = "なんだと…また謎かけかよ…面白い奴だな、スネークアイ。お前は自分が信じる神ククルカンと三度も対峙して生き延びたと言ったな。だったら、 俺が信じちゃいない神の偶像で運試ししちゃいけない理由なんてあるか？\n";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "哀れだな。信じないとは、実に哀れだ。もしかするとククルカンご自身が、 お前を呼び寄せて先祖の地を離れさせたのかもしれん。だが、まだその声が聞こえていないのだろう。 すべては良き理由あって起こるものだ。もし危険を冒す覚悟があるなら、知っておけ。俺が毎回生き延びられたのは、 素晴らしいコマンチ族の薬のおかげだったのだ。";
			link.l1 = "コマンチ？それは別の部族か？";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "それは敵どもが私の民を呼ぶ名だ。私はもう二度と彼らに会うことはないだろう。この薬は力と持久力を回復させ、 さらに傷を癒し、強い毒からも救ってくれる。いくつかの小瓶が必要だが、私の手元にはあと三つしか残っていない。\n本当は四つあったが、一つは奇妙な場所で失くしてしまった。まるで白人の船の墓場のような所だ。 私はそこでこの世界での旅を始めた。もしかするとククルカンが船長をそこに吐き出したのかもしれない。もしそうなら、 彼の身の上を気の毒に思うよ。";
			link.l1 = "ここは何だ？船の墓場か？";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "奇妙な場所だ……本来存在しないはずなのに、確かに存在している。そこには肌の色だけで人を殺す者たちが住んでいる。 やつらはククルカンが俺を吐き出したあの大きな船の中に物資を保管している。 俺はやつらが盗人から守っている船倉には入らなかった。あいつらは信用できる隣人じゃない。もしそこに行くなら、 別の出口を探せ。船倉には入るな、厄介ごとになるぞ。\nもしまだ生きていれば、ホワイトボーイが別の像を見つける手助けをしてくれる。この白いビーズを渡してやれ。 あいつはこういうのが好きなんだ。";
			link.l1 = "ふむ。もう頭がくらくらしてきたが、ますます面白くなってきたな。続けてくれ、俺の赤肌の兄弟よ。";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			Log_Info("You have received a white pearl");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "もし船長が生きていたら、ひどく病んでいるかもしれません。私は薬を渡す時間がありませんでした。\nそこに私のタンバリンを探してください。祖父からもらったものです。\n失くした袋にはいろいろ入っていますが、必要なのはタンバリンだけです。\nそれがないと霊と話すのは難しいのです。";
			link.l1 = "ふむ、この場所はとても面白そうだな！ホークがそこに転送されたことを願おう……君の薬をくれないか？";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "渡してやろう。ただし、その代わりにこの地の護符を三つ持ってきてもらうぞ： "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian)+", "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet)+" そして "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg)+"。アミュレット一つにつきフラスコ一つだ。これで公平だろう。すべてのアミュレットが揃ったら戻ってこい。 その時に交換する。私が欲張りだなんて思うなよ。あるいは、アミュレットを探している間に考え直すかもしれんがな。";
			link.l1 = "そんなこと思わないさ。待ってろよ、スネークアイ、すぐ戻るからな。";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
			pchar.questTemp.HelenDrinking.GiveAmulets = true;
			
			//if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))	// Временно так
			{
				// Квест "Путеводная звезда", начало 4 этапа
				PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
				PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
				locations[FindLocation("Shore9")].DisableEncounters = true;
			}
		break;
		
		// даёт зелья - идем на телепортацию
		case "SnakeEye_potion":
			dialog.text = "よし、友よ。ククルカンのもとへ行くために、お守りを持ってきたのか？";
			link.l1 = "はい。かつて鎖につながれた船長ナサニエルが辿ったのと同じ旅に、私も出発する覚悟です。";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("You have given amulets");
			Log_Info("You have received three versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "この薬を持っていけ。覚えておけ、ククルカンに吐き出された直後に必ず一本飲まねばならん、 さもないと死ぬか重い病にかかるぞ。\nそれから、白人どもが物資を保管している貨物室には絶対に行くな。船を出る別の方法がある。いや、実は二つある。 初日の夜に赤い女を探せ、それがとても大事だ。\nわしが言えるのはそれだけじゃ。";
			link.l1 = "そのことは覚えておくよ、兄さん。";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "なら行け。真夜中にククルカンに触れれば、お前は喰われるだろう。\n精霊たちを呼んで導かせてやる。";
			link.l1 = "ありがとう、スネークアイ。俺のことは心配するな、すべてうまくいくさ。また会おうぜ！";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // телепорты работают!
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
			QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		// пришёл из LSC
		case "LSC_hello":
			dialog.text = "会えて嬉しいぜ、相棒。どうやって船の墓場から戻ってきたんだ？";
			link.l1 = "あなたに言われた通り、そこでククルカンの像を見つけたんだ。ホワイトボーイ――オーレ・クリスチャンセンが手伝ってくれた。像は海に沈んでいたけど、なんとか辿り着いたよ。 像は俺をドミニカのインディアンの村に転送したんだ。";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "モンキテクヴリがそこであなたに会ったのか？";
			link.l1 = "ふむ。モンキテクヴリ？それは誰だ？";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "彼は村長だ。";
			link.l1 = "名前は聞かなかった。モンキテクヴリだったかもしれないし、違うかもしれない。";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "奴の頭に鳥の羽でできた偉そうな頭飾りが乗っていたか？";
			link.l1 = "ああ、確かに持ってたよ。羽根が山ほど……まるでジャングル中のオウムを全部むしったみてえだったぜ。";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "あいつの名はモンキテクヴリだ。あれはオウムの羽じゃなくて、ワシの羽だ。この頭飾りは俺のものだ。 ククルカンに吐き出された時、モンキテクヴリに渡したんだ。そしたら、やつらは俺を別の像のところへ連れて行った……\n";
			link.l1 = "すごいじゃねえか！俺もククルカンへの“生け贄”にされたんだ！それで気がついたら、最初の像の近くにいたんだよ。";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "ああ、色白の友よ。俺の旅もここで終わったんだ。";
			link.l1 = "偶像が円を描いて転移している……だが、それに何の意味があるんだ？何か考えがあるか、スネークアイ？";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "どうやら像がちゃんと動作していないようだな。今のところ、人をあちこちに移動させているが、 本来は一箇所に移動させるべきなんだ。何かがおかしいんだよ。";
			link.l1 = "どうしてそう思うんだ？";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "円の中でテレポートしても意味がないからだ。ククルカンは犠牲者たちをあちこちに移動させるのではなく、 全員を一箇所に集めなければならない。";
			link.l1 = "「その“たった一つの場所”って、どこなんだ？」";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "これは大きな秘密だぜ、白い兄弟、俺にとってもな。";
			link.l1 = "なるほど。いいさ、偶像なんてくそくらえだ。もう二度と近づかないよ。鎖につながれた船長は見つけたし、 もうポータルを通る必要もない。";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "お前が船の墓場にいた時、俺のタンバリンを見つけたか？";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "そう思うよ。見てみな。";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "いいえ。残念ながら、まだ見つけていません。しかし、島の場所は分かっていますし、そこへ行くこともできます。 あなたのタンバリンを探してみます。";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "探してくれ、俺の青白い友よ。頼む、お願いだ。タンバリンがないと、精霊たちの声がよく聞こえねえんだ。";
			link.l1 = "よし、スネークアイ。またな！";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "それは俺のタンバリンだ。ありがとう、色白の友よ。お礼はできるぜ。これをお前にやろう。お前たちの仲間は、 まだしばらく手に入れられない武器だ。これは、俺の時代の色白どもの武器なんだ。";
			link.l1 = "面白いな！見せてくれよ、俺の赤肌の友よ…";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			Log_Info("You have received a Colt revolver");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "受け取れ。残りは三発分しかない、あとは俺が使っちまった。でも、お前ならこの火薬の作り方を覚えるかもしれねえ。 船の墓場で火薬の部品を何十個か失くしちまったから、そこで見つかるはずだ。\n";
			link.l1 = "おおっ！これはピストルじゃねえか！こんなの見たことねえ……なんて変わった仕掛けだ。回転する機構か……五発も撃てるのか！こいつはすげえ！";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "コルトリボルバーって呼ばれてるんだ。お前たちの時代にはこんなピストルは他にねえよ。使い方も簡単で、 ハンマーを起こして引き金を引くだけだ。よく当たるぜ。";
			link.l1 = "ありがとう！ありがとう、スネークアイ！これで敵どもを驚かせてやれるな……弾が三発しかないのが惜しいが……";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "コルトのリボルバー用の弾薬を自分で作る方法を学んでみろ。そうすれば、お前は時代の偉大な戦士になれるだろう。\nああ、色白の兄弟よ、船の墓場で俺のパイプを探してくれと頼むのを忘れていた。とても綺麗なパイプだったんだ。";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "ははっ！誰の飾り立てたパイプかと思ってたが、見てみろよ。";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "わかった。お前のパイプも探してやるよ。またな！";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "これは俺のパイプだ、兄弟。見つけてくれて嬉しいぜ。それのお礼にもう一つ贈り物をやろう。 これは俺の時代の白人どもの賢い本だ。俺にはさっぱり分からねえ。これを読んで理解できる賢い奴を探してみな。";
			link.l1 = "ありがとう、スネークアイ。これに興味を持ちそうな奴を知ってるんだ。";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			Log_Info("You have received a Lavoisier's chemistry textbook");
			PlaySound("interface\important_item.wav");
			dialog.text = "渡してやれ、白い兄弟よ。この本には白人の知恵の大いなる秘密が記されているんだ。";
			link.l1 = "よし。またな、スネークアイ！";
			link.l1.go = "exit";
		break;
		
		// лечение Натаниэля
		case "Saga_nathaniel":
			dialog.text = "聞いてるぜ、色白の兄弟よ。";
			link.l1 = "私は船の墓場で探していた鎖につながれた船長を連れてきました。彼はとても重病です。 彼を癒せるのはあなただけだと知っています…";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "ククルカンが彼の健康を蝕んだ。私なら癒す手助けができると思う。しかし、満月が一度巡るほどの時間がかかるだろう。 ククルカンはずっと前に船長を食らい、その病は彼の奥深くまで広がったのだ。";
			link.l1 = "癒してください、シャーマン！必要なものは何でも持ってきます！";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "やってみるぜ、白い兄弟よ。俺には何も持ってこなくていい。全部持ってるからな。時が経てば病は強くなるが、 縛られた船長も一月もすればまた元気になるさ。";
			link.l1 = "ありがとう、俺の赤肌の兄弟よ。今回もまた命を救ってくれたな。";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "鎖につながれた船長は俺の小屋に置いていけ、白い兄弟よ、心配せずに歩いて行け。女房も連れて来い、 俺の儀式は誰にも見られねえさ。";
			link.l1 = "わかったぜ、スネークアイ。ダニエルを連れていく。じゃあな！";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "聞いてるぜ、相棒。";
			link.l1 = "ククルカン像について話したことを覚えているか？「それらは人々を特別な場所へ導くはずだ」と君は言っていたな。";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "覚えてるぜ、白い船長。";
			link.l1 = "ククルカンに食われた人々を、あの像たちがどこへ連れて行ったのか知っている。";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "どこだ？";
			link.l1 = "古代マヤの都市タイアサルへ。そこはメインの密林の奥深くに位置している。";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "とても興味深いな。どうしてそれを知っているんだ？";
			link.l1 = "長い話だぜ、スネークアイ。お前がここにいる理由も分かるよ。まだ生まれてもいねえんじゃねえか？";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "私の父でさえ、あなたの時代に生まれたわけではありません。しかし、私はあなたの時代に生きている――それこそが大いなる謎なのです。";
			link.l1 = "実は説明できることなんだ。タイアサルに住むイッツァの司祭カネクが、ククルカンにこの世で人間として生まれ、 白人の知恵を吸収するよう祈ったんだ。さらに彼は時の穴も作り、未来から何人かの人間をこの時代に転送したんだ…\n";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "ククルカンに未来の人々の知恵を吸収させるためか？";
			link.l1 = "そうだ。そしてククルカンは、はるか昔に亡くなったマヤの民に知識を授けるため、過去へ向かうつもりだ。\n歴史は変わり、マヤがアメリカ、あるいはそれ以上の地を支配することになるかもしれない……";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "だが、何かがポータルに起こって、テヤサルへ転送するはずが、人々 をぐるぐる同じ場所に転送するようになってしまったんだ。それで俺はここに来たんだ、スネークアイ。 お前の助言が必要なんだ。";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "「なぜ俺なんだ、白い船長？」";
			link.l1 = "ククルカンに食われたからだ。それに、お前の村の近くにあるククルカン像がこの地図に奇妙な印で記されていて、 それがカネクの儀式と強く結びついているからだ。";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "この地図を見せてくれるか？";
			link.l1 = "ほら、見てみろ…";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "（見ている）この丸い印だな？で、これは何の意味だ？";
			link.l1 = "わからないな、シャーマン。俺が知っているのは、三体あるククルカン像のうち一つだけにこの印があるってことだけだ。 そして、その印がある像はお前のものだ。つまり、お前の像は特別なんだと思うぜ。何か心当たりはあるか？";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "明日の朝まで待ってくれ、白い兄弟よ。この革の地図は置いていってくれ。精霊たちに尋ねる必要があるんだ。 明日また来てくれ。";
			link.l1 = "わかったぜ、赤肌の兄弟。俺は明日ここにいる。助けてくれてありがとうな。";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "後で来い、白い兄弟よ。今は俺の邪魔をするな。";
			link.l1 = "ああ、シャーマンよ…";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "白い兄弟よ、話したいことがあるんだ。";
			link.l1 = "何か見つけたか？それとも何か心当たりでもあるのか？";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "祖霊たちが私に幻視を与えてくれたので、私は地図を持ってククルカンのもとへ行った。\n探し回って、ついに見つけた。これこそ、白き兄弟よ、お前が探しているものに違いない。";
			link.l1 = "何を見つけた？";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "ククルカン像には鉄のクランプが二つと、くぼみがある。\nそのくぼみは丸くて滑らかだ。\nくぼみは、革の地図に描かれていた丸くて平たい物の方を向いている。";
			link.l1 = "何だ？";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "わからない。ただ、丸くて平らで、小さなカボチャくらいの大きさで、 たぶん指一本分くらいの厚さだってことしか知らないんだ。\nくぼみとクランプは自分で見に行けばいい。クランプでそれを固定する必要があるんだ。";
			link.l1 = "何か心当たりはあるか？それとも、何だと思うか、見当はつくか？";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "石には火の痕跡が残っている。\n何があったか、私は知っている。\n天の火がそれを打ったのだ。";
			link.l1 = "雷か？雷に打たれたのか？";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "それは確かだ。私はこの偶像についてミスキート族に尋ねた。ある戦士が、 昔その像のそばで色鮮やかな物がいくつか見られたと言っていた。岩によく似ていたそうだ。 とても美しい赤い石だったと教えてくれた。その赤い石を白人の村から来た男が買っていったそうだ。";
			link.l1 = "ふむ。私の理解では、この丸い「何か」に雷が落ちて、それがバラバラになり、その破片がどこかの白人に売られた、 ということか？";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "そのようですね。";
			link.l1 = "「それで、あの白人は誰だったんだ？お前の戦士が教えてくれたのか？」";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "彼が話してくれた。ミスキート族の大親友で、ブルーヴェルド村に住んでいる。名前はフォレスト・デビルだ。 俺は知ってるし、お前も知ってるはずだ。";
			link.l1 = "ヤン・スヴェンソン？ちょっと待て……赤く塗られた岩だと？どうやら俺はとんでもなく運がいいみたいだな。見てくれよ、シャーマン、この赤い岩を！ 森の悪魔が俺にくれたんだ。";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("You have given ornamental pattern fragments");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "きっとあいつらだ。五つの岩だぜ。見てみろ、白い兄弟。こうやって並べると……（岩を合わせながら）";
			link.l1 = "...";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "…それから丸い物がある。見てくれ！ぴったり合うだろう。もともとは一つの物だったんだ。";
			link.l1 = "くそっ！こんなものがずっと俺のポケットに入ってたなんて……なあ、シャーマンよ、もし俺がこの破片をくぼみに入れたら……";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "ククルカンは、あなたが言った通り、古いインディオの都市で犠牲者を吐き出すだろう。";
			link.l1 = "それは素晴らしい！ぜひそこへ行きたいんだ！\nもし装飾品が粉々に壊れていたら、ちゃんと機能すると思うか？";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "私たちはそれらを集めてから、装飾品をくぼみに置く必要があると思う。";
			link.l1 = "「一緒にするって？でも、どうやって元に戻せばいいんだ？」";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "俺と先祖の精霊たちに任せてくれ、白き兄弟よ。あれはただの石じゃねえ。奇跡の品だ。三晩後に戻ってきてくれ、 白き兄弟よ。精霊たちと、生きとし生ける者の知恵と技を呼び寄せて、破片を一つにしようと試みるぜ。";
			link.l1 = "信じられない……どうやってお前に恩返しすればいいんだ、スネークアイ？";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "礼は後でいい、白い兄弟よ。今は行け。三晩後に戻ってこい。";
			link.l1 = "よろしい。うまくいくことを願っている……";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "俺があんたを幸せにしてやれるぜ、白い兄弟。";
			link.l1 = "破片を一つにまとめることができたか？";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "ああ。簡単じゃなかったし、暦には傷跡も残ったが、今はもう完成した。";
			link.l1 = "「暦？なぜそう呼ぶんだ？」";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "なぜなら、この丸い物は暦だからだ。私はじっくり調べたんだ。そこには時間の記録がある。 古代都市のインディオたちは夜、月、年、そして時代を数えているんだ。\n";
			link.l1 = "信じられない……だが、マヤの神官たちの力を考えれば、この暦の作成もそれほど驚くことではないな。";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			Log_Info("You have received a Maya calendar");
			dialog.text = "受け取れ、白い船長。像のくぼみにそれを置け。そうすれば、 もしかしたらインディアンの都市にお前を吐き出してくれるかもしれん。";
			link.l1 = "どうやってお返しすればいいんだ、スネークアイ？";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = "「ありがとう」と言いなさい。神々はお前の道を導いている、たとえそれが見えなくてもな。白人たちは運命と言う。 ククルカンがお前を呼び、神々が導いているのだ。さあ行け。自分の役目を果たし、善き精霊たちの導きに従うのだ。";
			link.l1 = "ありがとう、スネークアイ！あなたのことは決して忘れません。";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			Log_Info("You have received four versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "待ってくれ。最も大事なことを忘れるところだった。ククルカンは人間を喰らい、その命を奪うんだ。 お前のために薬を作った。コマンチェの薬だ。それを渡そう。四つの小瓶を用意したから、 忠実で勇敢な仲間を三人まで連れて行けるぞ。";
			link.l1 = "俺のために、こんなにも尽くしてくれたな、同胞よ……";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "兄弟という言葉は、コマンチ族のインディアンにとって単なる言葉ではないんだ。\nククルカンの都から戻ったら、ぜひ我々の村に来てくれ。\nたっぷりサライアカを作って待っているよ。\n君にまた会えるのを楽しみにしている。";
			link.l1 = "もちろんだぜ、俺の赤肌の兄弟！必ず会いに行くからな！";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // кожаную карту можно выкладывать 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
