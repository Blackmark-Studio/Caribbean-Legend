// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("「すべての噂話は」 "+GetCityName(npchar.city)+" お役に立ちますぜ。何を知りたいんだ？","ちょうどその話をしていたところだぜ。お前、忘れちまったのか…","今日はこれで三度目だぜ、この質問を持ち出すのは……","お前、オウムみたいに同じことばかり繰り返してるじゃねえか…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、」 "+NPChar.name+"、また今度だな。","そうだ、なぜか忘れちまってたんだ……","「ああ、本当にこれで三度目だな……」","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "島で大きな騒ぎがあったって聞いたぜ…奴隷のことか？";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "あの忌々しい悪党、ポルトガル人のバートがついに裁きを受けたって聞いたぜ！奴は牢屋にいるのか？ 処刑がいつか知ってるか？俺も見に行きたいんだ、あのクズには個人的に恨みがあるんでな…";
                link.l1.go = "Portugal";
            }
			//--> Тайна Бетси Прайс
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
			{
				link.l1 = "「聞け、」 "+npchar.name+"、最近新しい美人の給仕が入ったって聞いたんだが……もういなくなっちまったのか？";
				link.l1.go = "TBP_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
			{
				link.l1 = "「教えてくれ、 "+npchar.name+"「ベッツィがいなくなった夜、近くで怪しい奴を見かけなかったか？誰かと話していたかもしれねえだろ？」";
				link.l1.go = "TBP_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
			{			
				sld = CharacterFromID("Villemstad_waitress");
					if (CheckAttribute(sld, "model") && sld.model != "Marquesa")
					{
						link.l1 = "「さて、」 "+npchar.name+"、いい知らせだ――あんたの大事な給仕は無事に生きてるぜ。ラム酒を補充しときな、すぐに客が戻ってくるからな。";
						link.l1.go = "TBP_Tavern3_21";
					}
					else
					{
						link.l1 = "「さて、」 "+npchar.name+"「もう終わったぜ――お前らの大事な給仕娘が戻ってきた。ラム酒をまた仕入れとけよ、客がすぐ戻ってくるからな。」";
						link.l1.go = "TBP_Tavern3_21_1";
					}
				
			}
			//<-- Тайна Бетси Прайс
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "ああ、こんな大騒ぎは今までなかったぜ……千人を超える黒人たちが反乱を起こしたんだ。二つのプランテーションは焼き払われ、それぞれの主人も殺された。 司令官は奴隷たちが町を襲いに来るんじゃないかと心配して、戒厳令を敷いたのさ。 すべてはタマンゴって雄とイサウリって雌、二人の黒人から始まったんだ……";
			link.l1 = "ずいぶん劇的じゃねえか。全部話してくれよ、その黒人たちは何者なんだ？";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "タマンゴとイザウラ――ブレナム農園の奴隷で、最初に焼き払われた農園だ。この二人の黒人は互いに愛し合っていた。だが、 ヨーロッパからプランターの息子レオンシオがやって来て、イザウラに目をつけた。 彼はイザウラを自分の妾にしようとしたんだ。黒人のタマンゴはもちろん、イザウラもそんなことは許さなかった。 彼女は本当にあの黒い悪魔を愛していたからな。タマンゴはアフリカじゃ何かの首長だったらしい……罪よりもなお黒く、斧を振るえば死神のような巨漢で、他の黒人たちも彼を恐れ、同時に敬っていた。 そんな男が奴隷たちを率いて反乱を起こしたんだ。夜に見張りを襲い、大屋敷の外にいた白人は皆殺し、 ムラートも同じ運命だった。それからイザウラが農園の扉を開け、反乱者たちは中の者を皆殺しにした。 ブレナムは跡形もなく焼け落ちた。それから奴隷たちはジャングルへ逃げ込み、姿を消したんだ……";
			link.l1 = "さて、どうだいこの話、まるで小説のネタじゃねえか！本格的な奴隷反乱、まるで古代ローマみてえだな。ところで、 どうやってそんなこと全部知ったんだ？";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "噂話なら、旦那、世の中にあふれてるぜ。ラムを飲めばみんな口が軽くなる、あとは耳を澄ませるだけさ…";
			link.l1 = "「それで結末はどうなったんだ？あいつら黒人を見つけたのか？」";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "はっ、そんなわけねえだろ！援軍がやっと到着するまで、誰一人ジャングルに足を踏み入れなかったんだ。\nそれから会社の軍艦が兵士を連れてやって来て、島中を捜索したさ。\nだが、逃げた黒人の痕跡も縮れ毛一本も見つからなかったぜ。";
			link.l1 = "へえ、どういうことだ！千人もの黒人がみんな煙のように消えちまったのか？";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "実は水の中へ。";
			link.l1 = "何を言ってるんだ、 "+npchar.name+"？お前も俺と同じくらい知ってるだろ、黒人は泳げねえってことをよ。";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "へっへっ……いやいや、あの黒人どもがそんなに簡単にサメの餌になるわけねえさ。実はな、反乱の翌晩に、 埠頭からバーク船が一隻消えちまったんだ。もしあれがタマンゴって野郎とその仲間の黒人どもの仕業じゃなかったら、 俺が黒塗りになってバンジョー弾いて踊ってやるぜ！だからもう奴らはこの島にいねえのさ。";
			link.l1 = "「ははっ、これで全部聞いたぜ」 "+npchar.name+"……半分野生の黒人どもが帆を操って航海できるなんて、俺に信じろってのか？ むしろギニアから猿の船が突っ込んでくる方がまだ信じられるぜ。";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "俺も信じられなかったぜ、旦那。でも証拠は消えた船さ。もしかしたら、あの黒人どもの中に昔船で給仕をしてて、 航海の技術を覚えた奴がいたのかもな。あるいは黒魔術でも使ったのかもしれねえ、誰にも分からねえさ！ また寄ってくれよ、 "+pchar.name+"、次に来た時にはもっと面白い話を聞かせてやるぜ。";
			link.l1 = "ありがとう！さて、そろそろ俺は行く時間だな。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "ああ、その通りだ。あの海賊は捕まったんだぜ。しかも、どうやってだと思う？海のど真ん中で、 たった一人で小舟に乗ってるところを拾われたんだよ。ネズミと一緒に船倉に放り込まれるまで、 一言も発しなかったらしい。危険な海賊が、そんなドジなやつみたいに捕まるなんて、面白い話じゃねえか！";
			link.l1 = "「それで、なんであいつは海でひとりぼっちだったんだ？」";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "たぶん、あいつは手下どもと縁を切ることにしたんだろうな、間違いねえ…戦利品の分け前で揉めたんだろうぜ。今じゃあ、あいつはカンパニーの連中の手の中さ。あいつら、 冗談なんざ通じねえ連中だぜ。どうやら、あいつはカンパニーの船の一隻と何か貴重なものを手に入れたらしい。 今すぐ首をくくってねえのは、どうやら何か情報を吐かせたいからみてえだな。";
			link.l1 = "それで、奴の処刑がいつになるか知ってるか？";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "誰にも分からねえさ。会社が欲しいものを突き止めたら、あいつの首に麻縄を巻きつけるだろうよ。ポルトガル野郎は今、 信頼できる見張りの下で牢にぶち込まれてるぜ\n最近はあいつのボースンもここに連れてこられた。そいつの話はさらに驚きだったぜ、 自分からフィリップスバーグのオランダ人に出頭したんだとよ。だから今じゃ元船長の隣の独房に入れられて、 二人はお隣同士ってわけさ、へへ…";
			link.l1 = "奇跡って本当に起きるもんだな！よし、噂話には気をつけておくぜ。あの絞首刑は見逃したくねえからな。じゃあな、 "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
		
		//--> Тайна Бетси Прайс
		case "TBP_Tavern_1":
			dialog.text = "ああ、もしあんたが彼女を見ていたらなあ、船長！ベッツィ……あの優雅さ、あの笑顔！男たちは彼女を見るためだけにここへ集まったもんさ。そして、 やつらが俺の酒場に落としていった銀貨の山……だが三日前、彼女は仕事に来なかったんだ。当然、俺は人を家にやったが、そこにもいなかった。部屋はめちゃくちゃで、 身の回りの物も消えていた\nもう何を考えればいいのかわからねえ。衛兵どもは、いつものように肩をすくめて終わりさ。 行方不明の娘を探すより大事な仕事があるってよ。どうせちょっと出かけただけで、すぐ戻るだろうとも言ってた。船長、 あんたが彼女を見つけてくれねえか？ここに連れ戻してくれたら、百ドゥブロン払うぜ。 彼女を失うわけにはいかねえんだ、わかるだろ？本物の宝なんだ！どうしても取り戻さなきゃならねえ！";
			link.l1 = "さて、俺にできることを考えてみるか。彼女が姿を消す前に、何か変わった様子はなかったか？ それとも悪い知らせでも受け取ったのか？";
			link.l1.go = "TBP_Tavern_2";
			link.l2 = "「多分逃げ出しただけの娘を探せだと？俺にはもっと大事な用があるんだ。自分で何とかしな。」";
			link.l2.go = "TBP_Tavern_End";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern_End":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TBP_Tavern");
			CloseQuestHeader("TBP");
		break;

		case "TBP_Tavern_2":
			dialog.text = "彼女が姿を消す前の最後の日は、とても上機嫌で、むしろ幸せそうだったんだ！何のトラブルの兆しもなく、 出て行くなんて一言もなかった。突然いなくなっちまったんだよ！";
			link.l1 = "面白いな……彼女の家はどこにあるんだ？";
			link.l1.go = "TBP_Tavern_3";
		break;

		case "TBP_Tavern_3":
			dialog.text = "彼女はこの通りをもう少し先に住んでいたんだ。青いバルコニーのある屋敷の向かいの家のすぐ裏手の小屋さ。 ここから遠くないぜ。";
			link.l1 = "じゃあ、無駄話はやめとくぜ。何か見つけたら知らせてやる。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Poorman");
		break;

		case "TBP_Tavern2_11":
			dialog.text = "怪しいって？あの娘のまわりにはいつも求婚者が群がってたぜ、そいつら全員がそれぞれ怪しかったもんさ！ あいつはなかなかの小悪魔で、人の目を引くのが上手だったんだ。";
			link.l1 = "それくらいは分かってたぜ"+GetSexPhrase(""," 「外」")+" もうすでにそうだな。しかし、目立った奴はいたか？";
			link.l1.go = "TBP_Tavern2_12";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern2_12":
			dialog.text = "ふむ……そうだな、ひとつあったぜ。その晩、あいつは彼女に宝石付きのペンダントを渡したんだ。ここに座って、目を離さず、 夜通し彼女のそばをうろついてたよ。";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
			{
				link.l1 = "そのペンダント、もしかしてこれじゃねえか？（物乞いから買ったカメオを見せる）";
				link.l1.go = "TBP_Tavern2_13";
			}
			else
			{
				link.l1 = "宝石付きのペンダントだと……";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			}
		break;

		case "TBP_Tavern2_13":
			dialog.text = "それだ！まさにそれだぜ！船長、もう何か見つけたのか？";
			link.l1 = "詳細は後で。 "+npchar.name+"、今は時間を無駄にしている場合じゃねえ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			RemoveItems(pchar, "jewelry24", 1); 
			notification("Given: Cameo pendant", "None");
		break;

		case "TBP_Tavern3_21":
			dialog.text = "それは素晴らしいですね、船長！もう二度と彼女に会えないかと思い始めていたんだ。\nそれで、どうなったんだ？本当に逃げたかったのか？";
			link.l1 = "まあ、彼女は過去の問題に対処しなきゃならなかったってことさ。\nでも今はもう全部終わったみたいだし、すぐに仕事に戻るだろうぜ。";
			link.l1.go = "TBP_Tavern3_22_leadership";
			link.l2 = "そうだな、お前の退屈なツラを見続けるのにちょっと休憩が必要だったってことにしとこうか。ははっ！ そんな顔すんなよ、冗談だぜ。女ってのは誰でもちょっとした秘密を持ってるもんさ…";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership":
			dialog.text = "まあ、大事なのは彼女がまた働けるようになるってことだ。報酬はしっかり受け取ってくれ、船長。ほら、 約束通りドゥブロン金貨百枚だ。\nそれと、この地図も持っていきな。常連の一人が置いていったまま、二度と戻ってこなかったんだ。 どうやら宝のありかを示しているらしいぜ。";
			link.l1 = "じゃあ、ちょっと見てくるぜ。ありがとな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune":
			dialog.text = "まあ、とにかく彼女はまた働けるようになるってわけだ。報酬はちゃんと受け取ってくれ、船長。ほら、 約束通り百ドゥブロンだ。それと、この地図も持っていきな。 常連の一人がここに置いていったまま戻ってこなかったんだ。どうやら宝のありかを示してるらしいぜ。";
			link.l1 = "じゃあ、ちょっと見てくるぜ。ありがとな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		
		case "TBP_Tavern3_21_1":
			dialog.text = "助かったぜ、船長！もう二度とあの娘に会えないかと思ってたんだ…\nで、実際に何があったんだ？本当に逃げるつもりだったのか？\n俺自身じゃ怖くて聞けなかったんだよ。";
			link.l1 = "まあ、昔の未解決の問題に片をつけなきゃならなかったってことさ。\nでも今はもう全部終わったみたいだし、すぐにまた仕事に戻るだろうぜ。";
			link.l1.go = "TBP_Tavern3_22_leadership_1";
			link.l2 = "まあな、あの娘もお前のつまらねえツラを見続けるのにちょっと休憩が必要だったってこった。ははっ！ そんな怖い顔すんなよ、冗談だぜ。女には誰だってちょっとした秘密があるもんさ…";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership_1":
			dialog.text = "まあ、大事なのは彼女が仕事に戻ったことだ。報酬はちゃんと受け取ってくれ、船長。ほら、約束通り百ドゥブロンだ。 それから、この地図も持っていきな。客の一人が置いていったまま、二度と戻らなかったんだ。 どうやら宝のありかを示しているらしいぜ。";
			link.l1 = "わかった、調べてみるぜ。ありがとう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune_1":
			dialog.text = "まあ、大事なのは彼女が仕事に戻ったことだ。報酬はちゃんと受け取ってくれ、船長。はい、 約束通りドゥブロン金貨百枚だ。それから、この地図も持っていきな。客の一人が置いていったまま、 戻ってこなかったんだ。どうやら宝のありかを示しているらしいぜ。";
			link.l1 = "よし、調べてみるぜ。ありがとう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
