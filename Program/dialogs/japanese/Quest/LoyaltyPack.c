void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
			link.l1 = "「何でもない。」";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			// --> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "...";
				Link.l1 = "アロンソ、話があるんだ。";
				Link.l1.go = "SharlieEpilog_Alonso_1";
				break;
			}
			// эпилог <--
			
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "話してもいいかい、船長？";
					link.l1 = "「またな、Alonso。」";
					link.l1.go = "exit";
					link.l2 = "どうぞ。";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "話していいかい、船長？";
					link.l1 = "「またな、アロンソ。」";
					link.l1.go = "exit";
					link.l2 = "どうぞ。";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "話してもいいかい、船長？";
					link.l1 = "「またな、Alonso。」";
					link.l1.go = "exit";
					link.l2 = "どうぞ。";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "話していいかい、船長？";
					link.l1 = "またな、Alonso。";
					link.l1.go = "exit";
					link.l2 = "どうぞ。";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = " 報告は何もねえぜ、船長。";
			link.l1 = "そのままでいいぞ、アロンソ。";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "調子はどうだ？";
			link.l1 = "どういう意味だ？";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "お前はもう何ヶ月もこのカリブの海を航海してるが、ここじゃ一週間ももたない奴もいるんだぜ。 船員たちはお前をちゃんと認めてる、それは間違いねえ。だが俺はな、お前のこれからが心配なんだよ。\n"+
                          "考えを聞かせてくれよ、船長。たまには船員たちにサービスしてくれ。どこにその "+pchar.ship.name+" どこへ向かうんだ？";
                          
            link.l1 = "俺には計画なんてねえ。まずは様子を見てみたいんだ。冒険の方から俺たちを見つけてくれるさ。";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "この海域は捕食者だらけだ、アロンソ。しかも "+pchar.ship.name+" 今のところ、それが一番小さいんだ。";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "俺は金を稼ぐのが好きだ。できれば合法的にな。だが、どうなるかはこれからだぜ。";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "あの話は知ってるだろう。ユリシーズ号でのあの忘れがたい会話のあと、すべてがさらにややこしくなったんだよ…";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "これぞ自由だぜ！ただし、船を維持するだけの金と、いざという時のための蓄えは忘れるなよ。\n"+
                          "気分でも、冒険でも、財宝の地図でも、どこへ行こうと――乗客の運搬、貨物の輸送、目についた仕事は何でも引き受けろ。\n"+
                          "ちょっとした商売に手を出しても損はしねえぜ――安い所で買って、売れる所で売るんだ。\n"+
                          "それに、もし途中で一隻だけの商船を見かけたら……へっ。あんたが言った通りだな、船長。冒険はきっと俺たちを見つけてくれるぜ。";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "良い助言をありがとう、Alonso。";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "儲かる商売だぜ、お前の船が耐えられるならな。孤立した商人を見つけて、「安物買いの銭失い」 がどういうことか思い知らせてやれよ。\n"+
                          "残念だったな、もう一つの格言があるぜ――「真実は必ず明るみに出る」ってな。どこの港に着こうが、必ず誰か船員の口が軽くて、 お前の所業をしゃべっちまうもんさ。\n"+
                          "つまり、みんなから少しずつ奪うか、一生敵の旗を選ぶかだな。\n"+
                          "少し気が早いかもしれねえが、もし本当にヤバくなったら、ポートロイヤルに腕のいい弁護士がいるぜ。 金さえ積めば役人どもとの揉め事を丸く収めてくれるんだ。まあ、海賊税ってやつだな、へっへっ！";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "良い助言をありがとう、Alonso。";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "うーん、その件じゃあんまり力になれねえな、船長。ちゃんとした商船が必要だぜ――バークンティンか、できればバークだな。こんなこと言って後悔しそうだが、軽い砲に換えるか、 大砲なんざ全部捨てちまった方がいいぜ。\n"+
                          "店主から貨物契約を受けて、途中で自分のために交易し、乗客を運ぶんだ。\n"+
                          "十分に貯めたら、店や銀行に投資しな。俺の言葉を覚えとけ、船長――いつか金が金を生むようになって、何百人も乗せられる本物の船が手に入るぜ。\n"+
                          "ちなみに、これはお前の商売が払うんであって、お前自身じゃねえからな。";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "助言ありがとう、Alonso。";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "俺はそうは思わねえな、船長。ユリシーズ号じゃあんたはただの乗客だった――ああいう哀れな連中は自分の運命をどうにもできねえ。だが今のあんたは帽子を手に入れた立派な船長だ。つまり、 どんな問題だって自分で解決できるってことさ。前にも言っただろ――俺たちの世界でこれ以上の地位はねえんだぜ。\n"+
                          "俺の勘だが、お前の兄貴とのこの騒動は何年も続きそうだぜ。だからまずは自分の身を大事にしろよ。 ミシェル旦那はどこにも行きゃしねえさ、へっへっ…\n"+
                          "カリブで悩みを抱えているのはお前だけじゃねえ。今こそ、他人を助けながら金や装備、 人脈を手に入れる絶好の機会だぜ。\nこの家業に必要なことは、道中ですべて学べるさ……";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "アドバイスありがとう、Alonso。";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "一つの役割に自分を縛るなよ、船長。やりたい時に、やりたいことをやれ。全部奪って、何も返すな。 それでうまくやっていけるさ。";
            link.l1 = "そして、知恵もありがとう。";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "へっ、それが俺の仕事だろ、船長。船員たちがあんたの命令を聞くのは、わずかな給金のためだけだと思ってるのか？\n"+
                          "何十人もの男たちが狭い船室に押し込められ、次に陸地を見るのがいつになるか、いや、 そもそも見られるのかさえ分からねえ。\n船を沈めるなんざ、あまりにも簡単なことだぜ。";
            link.l1 = "ああ、ああ、その話は前にも聞いたぞ、アロンソ。さっき船について何か言ってたよな？";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "へっ！船ってのはな、牢屋であり、軍の野営地であり、修道院でもある――全部まとめて一つだぜ。つまりは男どもの集まりってわけよ。だからな、問題は言葉か鞭かで解決されるもんだ。 あんたの場合は後者は……へへっ、無理だから、こうして話をすることにしたんだ。あんたのためにも、少しは楽にしてやろうと思ってな。";
            link.l1 = "お前、本当に牢屋に入ったことはあるか？軍隊は？まさか修道院なんてことはないだろうな？\nそういえば、アロンソ、お前自身のことを聞かせてくれよ。俺はお前のこと、ほとんど知らねえんだ。";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "まあ、修道院は避けてきたんだ、嘘はつかねえよ。だが、かつては聖なる異端審問所で働いたこともあるんだ……";
            link.l1 = "「一体全体、どうしてそんなことになったんだ？」";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "おお！こういうことさ。俺はヨーロッパの戦争で傭兵としてしっかり働いてたんだ。どう始まったのか、 誰が誰と戦ってたのかなんて悪魔にしか分からねえ。ただ分かってたのは、戦争が三十年も続いてて、 どの指揮官がまあまあ定期的に報酬を払ってくれるかってことだけさ。あれこそ冒険だったぜ！\n"+
                          "あれは42年だったか……いや、41年だったか？まあ、どっちでもいい。皇帝のために仕える二つの部隊が、森の中で出くわしたんだ。霧の中でな。 そいつらは互いに斬り合いを始めた！三日三晩の殺し合いだったぜ！";
            link.l1 = "「そんなことがありえるのか？」";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "あの霧の中で味方と敵を見分けてみろよ。それに、三ヶ月も給料が出てなかったから、 みんな戦利品のことしか考えてなかったんだぜ。\n"+
                          "俺たちはお互いに半分ずつ殺し合っちまった。\n気づいた時にはもう手遅れだったんだ。\nその時にこのモスコビットと出会ったのさ。熊みてえにでかいが、心は金みたいに優しい奴だぜ！";
            link.l1 = "次はどうなったんだ？";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "戦争ってどういうものか知ってるだろ？最初に報告した奴が英雄になるんだ。だから俺たちは考えたんだ――この災難を利用してやろうってな！\n"+
                          "野郎どもを集めて、会計係のところへ行き、「輝かしい戦いだった」と報告したんだ。死んだ奴らの給料は減らされ、 生き残った連中はちゃんと支払われて、俺と相棒はボーナスをもらい、司令官も自分の取り分を手に入れた。";
            link.l1 = "じゃあ、アロンソ、お前は金持ちってわけだな。";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "ははっ！俺たちは一週間もワインを飲みながらカードで遊んでたんだ。運が良かったぜ、 雪国モスクワから来た新しい友人が珍しい小物に目がなくてな。そうじゃなきゃ、俺は借金牢にぶち込まれてたところだ。 あいつは俺から戦利品――見事な三連発のピストルを買ってくれたし、値段も悪くなかった。俺の不幸につけ込むようなことはしなかったぜ。";
            link.l1 = "なかなかの話だな、アロンソ。俺にはお前が今作った話にしか聞こえねえぜ。";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "俺を傷つけるじゃねえか、船長。ほら、これを受け取れよ。";
            link.l1 = "何だ？";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "マスケット戦用の弾帯だ。俺のモスクワ出身の友人の故郷じゃ、みんなこれを身につけてるらしい。 そう本人が言ってたぜ。\n"+
                          "役立ててくれよ、船長。これは乗組員一同からの贈り物だぜ。";
            link.l1 = "予想外だな！ありがとう、アロンソ。それで異端審問の奉仕についてはどうなんだ？";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "えっ…\n"+
                          "鐘が鳴ってるぜ、船長！仕事に戻る時間だ。また今度続きだな。";
            link.l1 = "この話は必ず続けるぜ。贈り物、ありがとな！";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Level 8) - Continuing the story
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "前に話した時からずいぶん成し遂げたな、今や誰も――船員たちも、俺も――お前の腕を疑う奴はいねえよ。";
			link.l1 = "疑いがあったのか？";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "もちろんいたさ。俺たちは単純な連中だ――最悪に備えてるのさ。自由を楽しめよ、船長。この調子でいけば、カリブのまったく別の顔を見ることになるぜ。";
            link.l1 = "それは良かった。さて、異端審問官としての務めについて話してくれ。前回は軍隊の話から始まって、 結局その話で終わったじゃねえか。";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "何を話せってんだ？あの無意味だが儲かった森の虐殺の後、俺とあのモスコビット野郎はすっかり意気投合して、 さらにいくつも悪だくみを働いたのさ。\n"+
                          "俺たちが一度、帝国の補給隊を襲うことに決めたのを覚えてるぜ。偵察隊の話じゃ、やつらは戦利品や金貨、 武器なんかを運んでたってさ…";
            link.l1 = "で、うまくやったのか？";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "楽勝だったぜ。両側から襲って、護衛どもを散らして、荷馬車を開けたら……キャベツだ！腐って悪臭を放つキャベツが、どっかの駐屯地向けによ。だがな、分かるか？ 俺たちゃ一週間も何も食ってなかったんだ。だから、それでも嬉しかったんだぜ！";
            link.l1 = "俺の船の飯だって大してマシじゃねえさ。";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "まあ、今じゃ慣れたもんさ。でもあの頃はな……一週間も食い物探して歩き回ったら、木の皮までかじる羽目になるんだぜ！\n"+
                          "だが、俺の友はめげなかった。自慢の酒を入れたフラスコを取り出してきた――モスクワ風のレシピだってさ。酢じゃなきゃ何でもよかったんだ！\n何口か飲んだら、あのキャベツですらご馳走みたいな味になったぜ！";
            link.l1 = "気持ち悪い。";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "気持ち悪いのは俺たちの水樽の中身だが、あの日はあのモスコビアの悪酒が命を救ってくれたんだ。";
            link.l1 = "どういうことだ？";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "俺たちはその場の泥道で、キャベツが周りに浮かぶ中、目が回るほど飲んじまったんだ。まあ、いろいろあって、 俺はどっかの貴族野郎と口論になっちまった。ドイツ人で、やけにきちんとしてやがる。 俺たちと飲むには身分が高すぎるって顔で、ただ座って銃を磨きながら皮肉ばっか言ってやがったんだよ。\n"+
                          "だから俺たちはそこに座って、キャベツをつまみに憂さ晴らししてたんだ。 そしたらあいつが軍事の知恵について説教を始めやがってさ。俺たちが信じてきた剣や槍なんてすぐに忘れ去られるが、 銃剣こそが未来であり、すべての鍵だって言うんだよ。\n"+
                          "だから俺はあいつと口論になって、なぜか決闘することになっちまったんだ――しかも銃剣でな。どうしてそうなったのか、俺自身も覚えてねえよ、聞かないでくれよ。\n"+
                          "だが、俺たちの中隊に銃剣は二本しかなかったんだ。一つはあの小柄な将校のもので、 もう一つはイギリス人のフォックスのだった。俺はフォックスのフュジルを借りて、そのドイツ野郎をぶち殺してやった――それからさっさと姿を消したのさ。";
            link.l1 = "しかし、お前は腹を空かせて酔っ払ってたじゃねえか。";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "後になって気づいたんだが、友人の酒は重いマスケットを振り回す時に手元がしっかりするんだよな。\nだから今は、あの死んだドイツ野郎の考えにも賛成したくなってきたぜ。";
            link.l1 = "「それが異端審問官としてのお前の務めとどう関係あるんだ？」";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "また信じてくれねえのかよ、船長！ほら、これを受け取れ。";
            link.l1 = "「瓶と紙切れか？」";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "これが俺が話してた酒だぜ。あと、レシピもな。気に入ったら使ってくれよ、へっへっ。";
            link.l1 = "悪いな、相棒。でも、ただの落書きとよく分からねえ液体じゃ……";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "わかった、わかったよ、船長。どうせこれを渡すつもりだったんだ。こんな武器は俺には合わねえが、 お前には役に立つだろう。銃剣なんて珍しい代物だぜ。でも一度使い方を覚えちまえば、 サーベルを振り回すのなんて忘れちまうさ。";
            link.l1 = "待て、それはあの帝国将校の持っていたマスケットか？お前が殺したやつのだろう？";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "その通りだ。見ての通り、俺は本当のことを言ったんだぜ、船長。";
            link.l1 = "「でも、それは俺が聞いたことじゃねえ。」";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "鐘が鳴ってるぜ、船長！仕事に戻る時間だ。また今度続けよう。";
            link.l1 = "この話は必ず続けるぜ。マスケット銃、ありがとな！";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "船長、新しい新兵の件ですが……";
			link.l1 = "何かあったのか？";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "今晩のミサで、新入りの一人が特にあなたの船に乗り込みたいと話していたことを報告したかったのです。";
            link.l1 = "「それは一体どういう意味だ？」";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "やがて彼みたいな奴がもっと現れるかもしれねえな。今やお前にも名前がついたぜ、船長。";
            link.l1 = "おかしいな、まだお前の名前の由来を知らないんだぜ。異端審問についての話も、 結局最後まで聞かせてくれなかったしな。";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "ああ、どこまで話したっけ……そうだ！それから俺たちは軍需品供給業者として身を立てることにしたんだ。戦争も終息に向かっていたし、 将来のことを考えなきゃならなかった。俺の友人の頭の中はいつも将来のことでいっぱいだったぜ。";
            link.l1 = "そりゃあ大出世だな。ついこの前まで、略奪された荷馬車のキャベツで酔っ払ってたくせに。";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "待てよ、もっと面白い話があるんだ。ある連隊から兜を百個注文されたんだぜ。しかも前金がたっぷり入った。 だから祝杯をあげてな……カードなんかもやったんだよ。\n"+
                          "朝起きたら――金が消えてるし、軍隊は二日後に出発するし、まだ百個の兜を用意しなきゃならねえ！";
            link.l1 = "それで、お前は何をしたんだ？";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "新しい戦場に行って、死体から帽子を集めたんだ。それにいろんな金属片を打ち付けて、板も付けて……見た目は滑稽だったが、ちゃんと役に立ったぜ！サーベルの一撃くらいなら確実に防げる。まあ、一度はな。 どんな兜にも負けねえだろ！？";
            link.l1 = "四分士はお前の機転を評価したか？";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "横領と詐欺で裁判にかけられたんだ。\nでもな、あとでわかったことがある――あの帽子が何度も命を救ったんだよ。\n俺たち自身の命もな、結局のところ。";
            link.l1 = "「どういうことだ？」";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "まあ、俺たち二人とも牢屋にぶち込まれたんだ。それに、仲間は任務に送り出された。どこへ、 誰と戦うのかも分からねえし、たぶん奴ら自身も知らなかったんじゃねえか。結局、誰も戻ってこなかったさ。\n"+
                          "……\n"+
                          "悪いな、船長。また今度続けよう。この帽子と説明書を受け取ってくれ。昨日、 お前を元気づけようと思って作ったんだが……結局、自分が余計に悲しくなっちまっただけだ。";
            link.l1 = "もちろんだ、Alonso。贈り物をありがとう。";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "船長、ちょっと報告したいんだが、今じゃあんたの部下は酒場や娼館で大歓迎されてるぜ。 あんたの旗の下で働くってのは、今や特別な意味があるんだ！";
			link.l1 = "ありがとう、アロンソ……俺自身はまだその王様扱いをあまり受けてないのが残念だぜ。";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "すぐにわかるさ。カリブ海は数十人の船長どもで分け合うパイみてえなもんだ。お前もすぐにその席に座って、 自分の分け前をつかみ取ることになるぜ。\n"+
                          "誰にも分からねえさ。もしかしたら、お前がカリブの伝説になって、全部かっさらうかもしれねえぜ。";
            link.l1 = "それで、話の続きをしてくれるのか？俺たちはお前が牢屋に放り込まれたところで終わってたぜ。";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "ははっ！偉大なる帽子泥棒事件だな。どこかフランドルの小さな牢屋にいるモスクワ人とポルトガル人。 判決を待っている。もちろん、絞首刑さ。\n"+
                          "偉い紳士が俺たちを助けてくれたんだ――なんとモスクワの大使だった！ファデイの古い友人さ。通りがかりに俺たちの窮地を聞いて、 身代金を払って自由にしてくれたんだ！";
            link.l1 = "ファディ？あのファディなのか？それを黙ってやがったのか！？";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "ああ、そうだ。そこで俺たちは別れたんだ――あいつは自分のモスクワに戻って、ポーランド人と戦うか、何かでかい商売でもやるつもりだったんだろう。 俺はもう少し故郷をぶらついて、それで今ここにいるってわけさ。\n";
            link.l1 = "感心したぜ、アロンソ。こんなに長い間話してくれたのに、自分のことだけは一切語らなかったな。 賢いあんたが異端審問についてうっかり漏らすなんて、妙な話じゃねえか。";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "俺は本当のことを言ったんだぜ、船長！信じられねえなら、ファディ本人に聞いてみな。 バステールで簡単に見つかるはずだ。";
            link.l1 = "そうかもな。で、俺の贈り物はどこだ？";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "「え？」";
            link.l1 = "お前は物語のたびに最後に俺に贈り物をくれたな。";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "聞こえるか？鐘が鳴ってるぜ。仕事の時間だ。";
            link.l1 = "元のままでいい、アロンソ。";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
		
		// --> Эпилог
		case "SharlieEpilog_Alonso_1":
			dialog.text = "フローランのことか？あいつにはもう言ったんだが...";
			link.l1 = "いや、相棒、全然別の話さ。ヨーロッパへ向かうことにしたんだ。いつ戻るかは未定だ。";
			link.l1.go = "SharlieEpilog_Alonso_2";
		break;

		case "SharlieEpilog_Alonso_2":
			if (GetCompanionQuantity(pchar) <= 1) sStr = "俺たちの船";
			else sStr = "俺たちの艦隊";
			dialog.text = "問題ないぜ、キャプテン。船は頑丈だし、クルーも経験豊富だ。ただ補給がちょっとな...";
			link.l1 = "俺は他人の船で行く。乗客としてな。お前には"+sStr+"を港務局に預けて、クルーを解散させてほしい。そして決めてくれ——ここに残って別の船に乗るか、それとも俺と一緒にフランスへ行くか、友として。";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;

		case "SharlieEpilog_Alonso_3":
			dialog.text = "...";
			link.l1 = "ちなみに、まったく関係ない話だけどさ…（小声で）ボルドーにいい女が何人かいるんだよ。カリブにはあんな魔女みたいな子、絶対いないぜ。お前みたいな奴には目がないし、戦いの武勇伝でも語ってやればもうメロメロよ...";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;

		case "SharlieEpilog_Alonso_4":
			dialog.text = "女の子が目的なら...一緒に行くさ。へへ。だが、なんで俺たちの船じゃないんだ？ それに、なんで乗客なんだ？ クルーは文句言うかもしれないが、あんたとなら天国でも地獄でも行くぜ。";
			link.l1 = "最初にここへ来たとき、自分が船乗りになるなんて想像もしてなかった。今じゃ、他の人生なんて考えられない。キャプテンじゃなくなる現実を受け入れられるか...それに、略奪や海の暮らしを捨てられるのかも、確かめたいんだ。";
			link.l1.go = "SharlieEpilog_Alonso_nothing";
			link.l2 = "話せば長い。酒場でラムでも飲みながら話そう。クルーも呼んでくれ。盛大な送別会を開こうぜ。ほら、これだ——彼らにひと月分の給料を渡してくれ、餞別としてな。";
			link.l2.go = "SharlieEpilog_Alonso_salary";
		break;

		case "SharlieEpilog_Alonso_nothing":
			dialog.text = "運命からは逃げられねぇよ、キャプテン。あんたが最後まで船長であるべきなら、きっとそうなるさ。";
			link.l1 = "どうなるか見ものだな、"+npchar.name+"。さて、そろそろ動くぞ。2週間後に出航だ。どの船で行くか、当ててみろよ...";
			link.l1.go = "SharlieEpilog_Alonso_5";
		break;

		case "SharlieEpilog_Alonso_salary":
			dialog.text = "それはいいな！ それなら知らせるのも楽になるぜ。";
			link.l1 = "どの船で行くか、当ててみろよ...";
			link.l1.go = "SharlieEpilog_Alonso_5";
			salary = GetSalaryForShip(PChar);
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;

		case "SharlieEpilog_Alonso_5":
			dialog.text = "引っ張らないでくれよ、キャプテン。";
			link.l1 = "ピナス船 '"+GetShipName("Ulysse")+"' だ。";
			link.l1.go = "SharlieEpilog_Alonso_6";
		break;

		case "SharlieEpilog_Alonso_6":
			dialog.text = "まさか…あのとき乗ってた船で出航するのか？ 信じられねぇ…";
			link.l1 = "そうさ、"+npchar.name+"。どうやって見つけたかは後で話すよ。酒場で、ラム片手に。今はやることがある。";
			link.l1.go = "SharlieEpilog_Alonso_7";
		break;

		case "SharlieEpilog_Alonso_7":
			dialog.text = "了解だ、キャプテン…はあ…クルーと別れるのはつらいな。あいつら、俺にとっちゃ家族みてぇなもんだからな。でも仕方ねぇか...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alonso";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			AddDialogExitQuestFunction("SharlieEpilog_Alonso_exit");
		break;

		// эпилог <--
	}
} 