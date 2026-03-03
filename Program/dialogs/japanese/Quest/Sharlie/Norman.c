// Абрахам Норман
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何かご用ですか？";
			link.l1 = "いいえ、何もない。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("何の用だ？自分の道を歩いて、自分の用事を済ませろ。俺のことは放っておいてくれ。","おいおい、旦那。散歩かい？まあ、そのまま歩いて、エイブラハムさんには構わないでくれよ。 あいつも今から散歩なんだ。海の新鮮な空気を吸いに行くんだからな。","やあ、友よ。話でもしたいのか？だがな、一つ問題がある。今は話す気分じゃないんだ。 だから他の誰かにちょっかいを出してこい。酒場でゆっくりして、ラムでも飲んでな…");
				link.l1 = "聞いてくれ、エイブラハム。最近イスラ・テソロでミゲル・ディチョソという男に会ったことはないか？ ここらじゃちょっとした有名人なんだ。";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("何の用だ？自分の道を行って、自分の用事を済ませろ。俺のことは放っておいてくれ。","おいおい、兄弟。散歩か？まあ、そのまま歩いて、エイブラハム旦那には関わるなよ。あいつも今から散歩だ。 海の新鮮な空気を吸いに行くんだ。","やあ、相棒。話でもしたいのか？ただな、一つ問題がある。俺は今、話す気分じゃねえんだ。 だから他の奴にでも絡んでくれ。酒場でのんびりして、ラムでも飲んでろよ…"),LinkRandPhrase("おい、水夫。なんだよ、お前、頭が固いのか？俺ははっきり言ったつもりだぜ。","相棒、ちょっと休んでこいよ。どうも耳が遠くなってるみたいだぜ。","おい、相棒、なんだよ、お前バカか？もうほとんど全部説明してやっただろうが。"),"相棒、俺を怒らせるなよ。これまでに陸の野郎どもを何人もぶっ殺してきたんだ、 あと一人増えたところで大して変わらねえんだよ。","よし、もう頭にきたぜ。さあ、錆びた剣を抜くか、全力で逃げるか選びな。俺は後者をおすすめするがな……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("わかったよ、友よ。邪魔はしないさ。","わかった、わかったよ……","おおっと、まるで海の雷みたいな風格だな！よし、俺はここから退散するぜ。","何だって！？",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("何の用だ、相棒？自分の道を行け、余計なことに首を突っ込むな。俺のことは放っておいてくれ。","おいおい、兄弟。散歩か？まあ、そのまま歩いて、エイブラハム旦那には構わないでくれよ。あいつも散歩中なんだ。 新鮮な海の空気を吸いに来てるだけさ。","やあ、相棒。話でもしたいのか？ただな、一つ問題がある。俺は今、話す気分じゃねえんだ。 だから他の奴にでも絡んでくれ。酒場でのんびりして、ラムでも飲んでろよ…");
				link.l1 = "聞いてくれ、アブラハム、最近イスラ・テソロでミゲル・ディチョソという男に会ったことはあるか？ この辺りじゃちょっとした有名人なんだ。";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "動くな！俺はこの島の総督だ。何だ、信じられねえのか！？";
					link.l1 = "もちろん知ってるさ！イスラ・テソロの総督を知らねえ奴なんているかよ…";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "はは、自分のことを提督とでも呼んでみろよ、絶対に信じてやるぜ！";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "注目せよ！見よ――バルバリゴ提督だ！俺の有名な騎兵刀を知らねえのか？";
					link.l1 = "申し訳ありません、提督！これからはもっと注意深くします。";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "お前の騎兵刀は広く知られているぜ。惜しいことに、今は馬鹿者の手に渡っちまってるがな。";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "ご覧の通り、私はここで亡命中です。\nモンク将軍からのさらなる連絡を待っています。\nどうか、私の隠された王族の身分を明かさないでください。\nクロムウェルの諜報は耳が早いのです。";
					link.l1 = "「もちろんでございます、陛下。誰にもカール二世が西インド諸島に身を隠していることは知られません。」";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "じゃあ、俺は教皇インノケンティウス十世ってわけだな。";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "どうしたんだ、ブレイズ？俺は二日間もお前を探していたんだぞ。父さんのことなんてすっかり忘れてしまったのか、 ニコラスが！";
					link.l1 = "父上、あなたにかまっている暇はないんです！私は手一杯なんです。";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "お間違いですよ、旦那。私の名前は "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "しっ……俺はデイヴィ・ジョーンズだ。教えてくれ、お前は死ぬのが怖いか？";
					link.l1 = "もちろんだよ、ジョーンズさん。特に二日酔いの後はね。";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "「一人の死は悲劇だが、千人の死はただの数字に過ぎない。」";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "新作の戯曲を早く仕上げたいんだ。君も『生きるべきか、死ぬべきか』という台詞を完成させるのを手伝ってくれよ！？";
					link.l1 = "それが問題だ！この侮辱に耐えて先へ進むべきか……";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "酒ならいいが、売春宿で病気をもらってもおかしくねえな！";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "何を言ってやがるんだ？「テソロ」だと！？それならいっそバミューダって呼べばいいじゃねえか！ この島は俺の名を取ってノーマン島って言うんだ、忘れるんじゃねえぞ！ 地理ってもんを叩き込んでやらなきゃならねえな…";
			link.l1 = "はっ！？どういう意味だ！？";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "その通りだ、水夫。俺は本当にバルバリゴ提督だが、それはここだけの話だぜ。出発の準備をしろ。もうすぐ移動するぞ。 それはお前の役に立つはずだ。";
			link.l1 = "本当に感謝しています！";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("You've received a three-barreled shotgun");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("You've received a match-lock musket");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("You've received a paper cartridge");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "今すぐどっちが馬鹿か分かるぜ。構えろ！";
			link.l1 = "本気か！？";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "俺が言っただろう！さあ、俺の健康に乾杯しろ。";
			link.l1 = "乾杯だぜ、提督！";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("You've received a gold doubloon");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("You've received a chest of doubloons");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "俺の名前を広めるなって言っただろうが！これじゃあ危険な証人としてお前を消さなきゃならねえな……";
			link.l1 = "「ああ、これを待ってたんだ！」";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "お許しください、閣下！このご服装ではお気付きできませんでした。どうか、 真のカトリック信者からのささやかな贈り物をお受け取りください。";
			link.l1 = "狂気が口を挟む……";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("You've received the Wonderworker Amulet");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("You've received the Talisman of the Accomplice");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("You've received a wax candle");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "みんな俺を狙ってるんだ！息子そっくりのスパイを捕まえたぞ！絶対にトマスが送り込んで、 俺のもう片方の目を潰そうとしてるんだ！";
			link.l1 = "消えろ、このバカ野郎！";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "疲れてるし、顔色も悪いぞ、坊や。さあ、治療を受けてこい。";
			link.l1 = "ありがとう！";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("You've received a potion");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("You've received the Scorpion Amulet");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("You've received remedial essence")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "怖がるなよ、相棒。ほら、死ぬのなんて全然怖くねえだろう…";
			link.l1 = "冗談じゃなかったみたいだな！";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "どうやら怖がっていないようだな。やっぱりな。それが勇気ってやつだ！";
			link.l1 = "お前は面白いじいさんだな……";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("You've received a fire-eater waistcoat");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("You've received a parade cuirass");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("You've received some tobacco");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "お前は下手くそな詩人だな、水夫。もしかして、お前の剣の方が舌よりもよく動くんじゃねえか？";
			link.l1 = "カランバ！お前のその騎兵刀、全然飾りじゃねえな！";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "くそっ！お前はずいぶん順調にやってるじゃねえか！これがお前の想像力の成果ってやつかよ！";
			link.l1 = "またお越しください。";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("You've received a bottle of rum");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("You've received a throat of cast iron");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("You've received a glass flask");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "あはは、見覚えがあるぞ！ははっ！";
			link.l1 = "「また……」";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "よし、相棒、話は済んだぜ。もう行きな。";
			link.l1 = "おっしゃる通りでございます……";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "「ディチョソ？あいつが何の用だ、え？」";
			link.l1 = "まあ、俺にはあいつが必要なんだ。ただ必要なんだよ。で、あいつを見かけたか？";
			link.l1.go = "tieyasal_1";
			link.l2 = "「何だよ、“何のためにミゲルが必要なんだ”って？ミゲルは俺の昔からの仲間でな、友達みたいなもんさ。あいつは本来……」";
			link.l2.go = "tieyasal_2";
			link.l3 = "あいつには、かつてシャーク・ドッドソンのためにやったみたいに、俺のために新しい船を引っ張ってきてほしいんだ。";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "ミゲル・ディチョソが人を殺したんだ。だから俺はあいつを探している。";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "あんたにはあいつが必要なんだろ…あんたにはあいつが必要なんだ！必要なのはミゲル・ディチョソだけだ！いや、見てない。もう長いこと会ってないんだ。 俺にできることは何もねえよ、水夫。";
			link.l1 = "ふむ……わかった、じゃあな。";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "友達、だと……？あいつは友達を山ほど作ってきたようだが、もうすぐ一人減ることになるな……";
			link.l1 = "おい、じいさん。どうしたんだ？";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "ああ、ディチョソはどう見てもその道の達人だよ。だが、今どこにいるかは知らねえ。ちょっと顔を出したが、 またどこかへ行っちまった。だから、アレクスのところに行きな、船乗り。 あいつならお前に素晴らしい船を用意してくれるぜ。";
			link.l1 = "ふむ……助言ありがとな、相棒。";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "で、ディチョソが誰をやったからお前が奴を追う羽目になったんだ、なあ、相棒？";
			link.l1 = "ブレイズ・シャープ";
			link.l1.go = "tieyasal_5_1";
			link.l2 = "ニコラ・シャープ";
			link.l2.go = "tieyasal_5";
			link.l3 = "「アロンソ・デ・マルドナード」";
			link.l3.go = "tieyasal_5";
			link.l4 = "教皇";
			link.l4.go = "tieyasal_5_bud_joke";
		break;

		case "tieyasal_5_1":
			dialog.text = "シーッ…（周りを見渡す）お前もディチョソがブレイズ・シャープを殺したと思ってるのか？";
			link.l1 = "ああ。ただの勘じゃねえぜ――証拠もあるんだ。航海日誌の記録がな…";
			link.l1.go = "tieyasal_6"
		break;

		case "tieyasal_5_bud_joke":
			dialog.text = "もう冗談を言うつもりか？全然敬意がねえな！さあ、もっと近くに来いよ…";
			link.l1 = "ありえねえ。";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_5":
			dialog.text = "ああ……まあな。奴はそいつを殺した、それだけのことだ。ここにどれだけ人殺しがうろついてるか知ってるか？ 二人に一人はそうだぜ！いや、水夫よ。ディチョソにはもう長いこと会ってねえ。お前の力にはなれねえよ。";
			link.l1 = "哀れだな……";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "静かにしろよ、相棒。名前は何だったっけ？どうも思い出せねえな……";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "「聞け、」 "+pchar.name+"ディチョーソが可哀想なブレイズを殺したんだ。俺はこの目で見たんだぜ、そうそう。でも誰も信じちゃくれねえ。 分かるだろ、みんな俺が頭おかしいと思ってるんだ。仲間なのに、狂ってるってさ。 昔はニコラス・シャープの船で一番の斬り込み隊長だったのによ！あの頃は良かった……。でも結局、爪も蹄もレンズも失って、陸に上がっちまった。\nなんだって？ああ、そうだ！みんなシャークのせいだと思ってたけど、違うんだ。いやいやいや。シャークの歯――ドッドソンのお守りがあったが、あれを仕込んだのはディチョーソだったんだ。\nあいつはシャークと一緒に「フォーチュン」ってフリゲートで航海してた時に、その歯を盗んだに違いねえ。 その日はよく眠れなくて、外に散歩に出たんだ。そしたらディチョーソがシャープの屋敷に忍び込むのを見た。 誰かの叫び声がして、それからうめき声が聞こえた。しばらくしてディチョーソが屋敷から出てきたが、 両手は血まみれだった。\n誰も信じちゃくれなかった、いやいや。だってその日、島にいたのはシャークだけで、 ディチョーソはいなかったことになってたからな。で、あいつの歯が見つかった。でも俺はディチョーソを見たんだ、 間違いねえ。あの日、誰もあいつがそこにいるなんて知らなかった。「ラッキー」 はとんでもなくずる賢くて恐ろしい野郎さ……";
			link.l1 = "「ディチョソを『幸運の男』と呼ぶのはお前が初めてじゃねえな。どうしてだ？あれはあいつのあだ名か？」";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "スペイン語がわからねえのか、旦那？「Dichoso」ってのは、カトリック野郎の言葉で「幸運な」って意味だぜ。ラッキー・ミゲル、幸運なミゲル。つまり、 それがあいつの名前ってわけさ。";
			link.l1 = "運のいいミゲルか……ふむ。それは何か思い出させるな。うーん、その言葉、どこかで聞いたことがあるような……";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "まあ、名字がディチョーソでも、やっぱりあいつはスペイン人じゃないと思うな。\nいや、違う、スペイン人じゃない。\n見た目はスペイン人っぽいけどな。";
			link.l1 = "じゃあ、奴は何者なんだ？イギリス人か、フランス人か？";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "俺が言ってるのはそういうことじゃねえ、船乗り……あっ、失礼しました、船長。ええ、ディチョーソはフランス語を見事にペラペラ喋りますよ、あなたに負けず劣らずね。 英語も同じくです。ただし、奴の血にはインディオの血が流れてます。俺はこういう奴を何人も見てきたんだ。 見分けるのは簡単じゃねえが、あいつは混血だ。保証しますよ。";
			link.l1 = "彼は現地の言葉を話せるのか？";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "ああ、そんなの知るかよ。もしかしたら知ってるかもな。いや、待てよ。知ってるぞ！あいつ、 昔から妙な言葉で変な文章をしょっちゅう口にしてたんだ。まるで賢者みたいな怖い顔して、頬を膨らませてさ。例えば、 こう言ってたぜ：「コギト・エルゴ・スム！」とか。そのあと目をぐるぐる回して、水夫たちの反応をじっと見てたんだ。 あるいは、こんなふうに叫んだりもした：「アウト・カエサル、アウト・ニヒル！」他にもいろいろ口走ってたよ。 全部は覚えてねえな。";
			link.l1 = "それはインディアンの言葉じゃない。ラテン語だ。ラテン語……ラテン語！？なんてこった！";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "なんでそんなにビクビクしてるんだ、旦那？何をそんなに叫んでる？まさか蛇にでも噛まれたのか？どこに行ったんだ？";
			link.l1 = "最初から気づかなかったなんて！全部目の前にあったのに！ラテン語だ！ミゲル…運のいいミゲル！！！";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "おい、相棒。もう大声を出すのはやめてくれよ。みんなこっちを見てるじゃねえか。どうしたんだ、水夫……いや、船長？";
			link.l1 = "私はミゲル・ディチョーソの本当の正体を知っている。彼はスペイン人じゃない。フランス人なんだ！ああ、 私はなんて愚かだったんだ！";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "違うぞ、間抜け。あいつはフランス人じゃねえ。混血だ。白人の親父がカリブのインディアン娘――アラワクかミスキートか、あるいはイッツァか――と寝て、そいつが聖なるミゲル・ディチョソってわけさ。お前には分からねえだろうが、俺には見える。 あいつの目に全部書いてあるんだよ…";
			link.l1 = "彼の出自の話はひとまず置いておこう。\n奴はどこだ、アブラハム！？ここにいたのか！？";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "しっ、しっ……ああ、彼ならここにいたよ。でももう出て行った。今はイスラ・テソロにはいないんだ。";
			link.l1 = "彼は何のためにここへ来たんだ？どんな船を持っているんだ？";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "奴の船はガレオンだ。でかい戦闘用ガレオンさ。何しにここへ来たのか……まあ、あちこち嗅ぎ回って質問してたぜ。だがな、俺は奴の会話を盗み聞きしたんだ、そうだとも！ 奴はシャルル・ド・モールとかいう奴を探してた。そう、それだ。シャルル・ド・モール。待てよ、それってお前だろ、 シャルル・ド・モール！奴はお前を探してたんだ、相棒。";
			link.l1 = "何のためか知ってるか？";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "まあ、間違いなく酒場に行ってお前とラムを飲むためじゃねえよ。あいつはお前を捕まえるつもりだったんだ。そうさ、 そうだとも！お前を捕まえるためにな！船長、ヤバいことになってるぜ！";
			link.l1 = "疑ってはいない……";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "それで、お前は？なぜあいつを探してるんだ？ああ、わかった、わかったぞ――殺すためだろ！殺してやれ、殺せ、この野郎を！ブレイズ・シャープの仇を討て！ブレイズは最高の男だった。 よく覚えてる、子供の頃からニコラスそっくりだったよ。";
			link.l1 = "ディチョソはどこへ行った？";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "彼はブルーウェルドへ向かっていた。シャルル・ド・モールは森の悪魔の庇護下にいる者を探せと言っていた。しかし、 彼は仲間をここに残していった…待て。もう君は見つかっていると思うぞ！";
			link.l1 = "誰が俺に気づいた？";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "ディチョソの手下たちだ。あいつはお前をここで見張るよう命じている。ああ、分かってる、分かってるさ！気をつけろ、 船長。イスラ・テソロの礁は船で囲まれていて、お前の首を待ち構えてるんだ。あの船長は狐のようにずる賢い。 騙されるなよ。";
			link.l1 = "やってみるよ……";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "それからもう一つだ。ほら、俺の騎兵刀を持っていけ。遠慮するな、持っていけ。お前には必要になるぜ。 これはバルバリゴ船長ご自慢の剣だ。素晴らしい刃だぞ。諸島一の名刀だ。恥ずかしがらずに、受け取れ。 ブレイズ・シャープの仇は必ず討つんだ！";
			link.l1 = "ありがとうございます、Abraham。";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("You've received Barbarigo's sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "さあ、行け。行くんだ、見張られているぞ。賢そうに見せても、愚かに見せても構わない。\nどちらでもいい。ただ、気をつけろ！";
			link.l1 = "助かったぜ、相棒。お前がどれだけ助けてくれたか、わかってねえだろうな。幸運を祈るぜ！";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
