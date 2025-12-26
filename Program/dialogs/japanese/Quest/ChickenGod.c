int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin,   
				float  DmgMax, 
				float  EnergyP,
				bool   MultiDamage, 
				int    MisFire,     
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "これは見ちゃいけねえんだ。";
			link.l1 = "バグ報告を提出する時間だ。";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "おっと！タカヒ、若造。無礼を働くつもりはねえが、どうやってここに入ったんだ？ あたしが滞在している間は店を閉めるよう、マダムに強く勧めたんだぜ。";
			link.l1 = "まったくだな。どうやってお前を中に入れたんだ？どうしてこの売春宿は、 怒れる信心深い連中にもう焼き払われてねえんだ？";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "金のドゥブロンはすべての道を開き、白人どもをもっと幸せにするんだぜ。知らねえのか？";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" まるでヴェルサイユの風化した空気の匂いまで感じられるぜ、あんたがあのきしむ音とともに中へ通されたあの場所のな。 ";
			}
			link.l1 = "そんな口のきき方はやめろよ、赤ら顔。確かに俺はここじゃ新参者だが、どうやってそれを知ったんだ？ この場でお前を撃ち殺してもいいんだぜ。そのあとで女を一人呼んで、面倒の埋め合わせにすることだってできるんだ。";
			link.l1.go = "native_var1";
			link.l2 = "誰がそんなデタラメを吹き込んだのか知らねえが、口は達者だな、そこは認めてやるぜ。 こんな教養のある土着民を見るのは初めてだ。";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2+" 「ヴェルサイユだと？ふざけんな！」";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "いいえ、船長、あなたは何も知らないんだ。俺はここで――まあ今のところは――まったく安全さ。だが、こんなに早く打ち解けたんだ、もう一度やり直そうじゃねえか。飲むか？";
			link.l1 = "それはできるぜ、すっかり興味が湧いてきたからな。";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "ブラボー！もう名前で呼び合って皮肉も飛ばしてるじゃねえか。さて、平和のために一杯やって、 それから商談といこうぜ。";
			link.l1 = "それはできるぜ、確かに俺の興味をそそったな。";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "この場所の目的を考えると、船長のその発言はかなり心配になりますよ！ 私はもうほぼ一ヶ月もここに閉じ込められているんです。思いつく限りのことは全部試しましたし、 退屈と虚しさで壁をよじ登りたくなるほどですよ。";
			link.l1 = "じゃあ、出て行け。たまには教会でも訪ねてみろよ……もっとも、中には入れてもらえねえだろうがな。";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "そんなに簡単な話じゃねえんだ。俺はな……契約のせいで、あと二十四時間この売春宿にいなきゃならねえんだよ。";
			link.l1 = "そりゃあ恐ろしい話だが、俺から同情はしねえぜ。高級娼館を一ヶ月まるごと貸し切りなんて、夢のような話じゃねえか！ ";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "欲望を恐れろよ、船長。どうやってここに来たのか知らねえが、本来なら今月は俺一人で過ごすはずだったんだ。 女と酒だけでな。だが三日も経たねえうちに、酒しか相手にできなくなっちまった。そして今日になって、 その酒にも飽きちまったってわけさ。";
			link.l1 = "「それで俺に何をしてほしいんだ？女と酒をお前と分け合えってのか？」";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "まあな、だがまずは賭けをしようぜ！一枚につき銀千枚だ！俺の名はアグエイバナだ、よろしくな。";
			link.l1 = "俺のだ "+GetFullName(pchar)+"。もちろん、やろうぜ。";
			link.l1.go = "native_accept";
			link.l2 = "俺のだ "+GetFullName(pchar)+"……千ペソか？悪くねえな。少し考えてみるが、約束はできねえぜ。";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "気が変わったのか、船長？行くか？";
			link.l1 = "ああ、いいだろう、なんでダメなんだよ。";
			link.l1.go = "native_accept";
			link.l2 = "「まだだ。」";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "遊んでくれてありがとう、船長。気が晴れるかと思ったが、全然ダメだった。頼む、放っておいてくれ――なんとかあと一日くらい自分でやってみるさ。くそっ、あの野郎め！";
			link.l1 = "それだけか？正直、がっかりした気持ちは大金を失った苦さよりも大きいぜ。";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "本来ならここにいるはずじゃなかったんだぜ、船長。でも、もし何が起きたのか知りたいってんなら……大陸にある古代の神殿を探せ。たっぷりとトゥウニチ・カアネも持っていくんだ。ほら、一つやるよ。";
			link.l1 = "アダー・ストーンか？穴の開いた石なら、確かにこの場所に合ってるな。ありがとう、アグエイバナ";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "さらばだ、船長。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "おっと！ありがとう、船長！金は残念だったが、少なくともまた人生の味を感じられたぜ！";
			link.l1 = "ああ、こんな航路であんなに興奮してる奴を見るのは初めてだぜ。ところで、その金はどこで手に入れたんだ？";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "同等の相手には絶対に聞かないような失礼な質問だな、船長！だが夜はまだこれからだし、 俺にはまだたっぷり金が残ってる。もう一勝負どうだ？";
			link.l1 = "なんでだよ？もう一発やろうぜ！";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "今回はサイコロをやって、少し賭け金を上げようじゃねえか。\nそれに、あんたに話したいこともあるんだ。だから二人分、上の階の部屋を借りてくれよ。ここじゃ耳が多すぎるからな！ \nできればマダムのところに行って、部屋代を払ってきてくれると助かるぜ。残念ながら、 俺の信用はあんたには及ばねえんだ。";
			link.l1 = "部屋を借りるだと？二人で？ここで？くそっ、アグエイバナの野郎め！俺はもう出ていくぜ！";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "ああ、くそったれ。この話は面白い笑い話で終わるか、えらく高くつく血の海になるかのどっちかだな。 俺の剣は手放さねえから、変な真似はするなよ、ははっ！ここで待ってろ、俺が片付けてくる。";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "それで？";
			link.l1 = "本当に酒と賭博だけのために俺を呼んだんだろうな、と心から願ってるぜ。";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "心配するなよ、船長、そんなくだらねえことには興味ねえさ！でもな、もし初日にここに現れてたら……ははっ！さて、始めるか？";
			link.l1 = "「運は勇者に味方する！」";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "おっと！こりゃ気持ちいいぜ！勝利おめでとう、船長。";
			link.l1 = "無理はするな。そろそろここで一体何が起きてるのか、俺に教えてもらおうか？";
			link.l1.go = "native_dice_story";
			link.l2 = "お前は変わっているな、アグエイバナ。さて、俺が今すぐここを立ち去らなければ、 貴族としても男としても俺の評判は取り返しのつかないほど傷ついてしまう。俺の銀貨を返してくれ、そしてお互い別々 の道を行こうじゃないか。";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "残念だな、今日はもっと違う形で締めくくりたかったんだが…";
			link.l1 = "こんな下賤な遊びで勝ったのに、こんなに取り乱してる男を見るのは初めてだぜ。\n一体ここで何が起きてるのか、そろそろ説明してくれねえか！？";
			link.l1.go = "native_dice_story";
			link.l2 = "ふざけんな、アグエイバナ！もう我慢できねえんだよ！";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "できる限りお答えしますよ、船長。許されているかは分かりませんが……それでも、あなたのおかげでこの数日が明るくなりました……この娼館で、という意味です。";
			link.l1 = "「それで、これは一体何の話だったんだ？」";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "気にするな……よく聞け、白人よ！俺はタイノ族の偉大なる酋長、アグエイバナだ。時々、 百年前に生まれてスペインの侵略者どもを俺の島々から叩き出した夢を見るんだ！だが現実は違った――俺は部族の仲間三千人を、一人十ドゥブロンで鉱山に売り飛ばしたのさ。";
			link.l1 = "立派な経歴だな。急にお前を撃ちたくなったぜ、アグエイバナ。この酸っぱくて酒臭いゴミ溜めに置き去りにして、 腐らせてやりてえ。";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "どうでもいいさ、船長。俺がずっと望んでたのはあんたみたいになることだけだったんだ。";
			link.l1 = "俺みたいにか？";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "俺はお前たちの船を見た――人間の天才が生み出した驚異だ――そして俺も自分の船が欲しくなったぜ。お前たちの女がきついコルセットを着ているのも見たし、 自分でそれを脱がせる夢も見た。お前たちのどんなに出来の悪い指揮官でさえ、 俺たちの指導者が夢にも見ないほどの権力を振るっているのを見てきた。ヨーロッパや、ただ生きるだけじゃなくて人々 が住む巨大な石造りの家の話も聞いた。そして、俺は全部手に入れたんだ！それどころか、 去年はヨーロッパにも行ったし、全部経験したぜ！";
			link.l1 = "お前はワインを飲みすぎだぜ、親分。お前がヨーロッパへ行ける切符なんざ、 鎖につながれてバチカンや大道芸人どもが大喜びするだけさ。お前の言ってることなんて、この世じゃ絶対に無理だ。";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "それが俺たちの生きる世界だ、船長。もうすでに、この世界は間違っていて、幻想で、 何でもあり得るって言われたことがあるんだ。";
			link.l1 = "「で、そんなことを教えたのはどこの利口ぶった野郎だ？どうやら売春宿だけじゃなくて、 狂人院にもお前みたいなのを入れてくれるらしいな！」";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "さて、ここからが俺の話の核心だ。ここでどういう仕組みになってるか、あんたも知ってるだろう？ スペイン人もイギリス人も、捕虜のために銃や道具、火薬を払ってくる。俺は自分の部族の仲間を、 あんたの金で買い戻したんだ。なぜだと思う？";
			link.l1 = "俺に何か教えてくれそうな気がするぜ。";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "我々の最も深く、最も恥ずべき願いを叶えられるのは神々だけだ。自分の望む人生を生きられないなら、 運命に介入してくれるよう神々に頼むしかない。最も深く、最も恥ずべき願いを叶えられるのは彼らだけだ。これが道だ。 だが困ったことに、我々の神々のほとんどはすでに死んでいるし、たとえ生きていたとしても、 もともと金には興味がなかった。幸いなことに、自然は空白を嫌うもので、古いピラミッドの一つに新しい神が現れた。 その神はお前が誰だろうと気にしない――現地人でもヨーロッパ人でも、悪党でも英雄でも、金さえ払えば望みを叶えてくれる！ それはすべての部族が知っているし、お前たちの仲間の何人かも知っている。俺は金で代償を払い、 お前たちの一人のように生きてきた。明日でちょうど一年になる。";
			link.l1 = "何の神様だ？一年でヨーロッパまで行って帰ってきたって？しかも旅のハイライトがカリブのしけた売春宿だと？ああ、 もうどうでもいいや。酔っ払いの与太話みたいだな、そう思って聞いてやるよ。さあ、一杯やって、 その話の続きを聞かせてくれ。";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "俺が話したことは全部本当だぜ。もう話すことは何もねえ。";
			link.l1 = "お前はまだ俺たちの世界に長く生きてねえな、アグエイバナ。酒が入ったやつの与太話、 特に娼館で酔っ払って語られる話には、必ず教訓がつきものだぜ。\nちゃんとサロンを締めくくる前に、しっかり哲学でも語ろうじゃねえか。";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "「普通はどう終わるんだ？」";
			link.l1 = "知らねえのか？もちろん参加者の性別によるんだぜ！男なら殴り合い、女ならベッドに連れ込むってわけさ。まあ、 時には流行りで逆になることもあるがな。\nで、お前の寓話の教訓は何だ？金で幸せは買えねえってか？つまんねえな！";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "それはお前が言うような俺の寓話の教訓じゃねえ。だが、お前が話を始めたからには、俺の考えも言わせてもらうぜ。 お前の意見には賛成できねえ。逆に、金こそが幸せを買い、人を良くするもんだと俺は思ってる。";
			link.l1 = "馬鹿なことを言うな！今や自分の言っていることが矛盾しているようだぜ。自分の同胞を売り飛ばして、 かなりの財産を築いたじゃねえか。どれだけの利益を得たか覚えているか？三万枚近い金貨だったよな？ 少しは考えてみろよ。だが、俺にははっきり分かる――金で幸せは買えなかったんだろう。ただし、この立派な部屋は手に入れたようだがな。\n";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "よし、最初の意見を修正しよう。金は人生も人も良くするんだ。";
			link.l1 = "そりゃあマシだが、それで人が良くなるとどうして思うんだ？今やお前は美徳の模範ってわけか？ それに金のない連中はどうなる？そいつらを悪人呼ばわりするつもりか？";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "なあ、船長、この会話には本当に感謝してるぜ。もう一度はっきり言わせてくれ。金は人生も人も良くするが、 それはもともと徳の火花を持ってる奴だけさ。";
			link.l1 = "聞け聞け！お前には火花がないってわけか？";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "いいや。俺は自分の民の長だったが、金とは違って権力は確実に人間を堕落させるんだ。\nなあ、船長？今のお前を見ていると、いつか同じ葛藤に直面することになると気づくぜ。";
			link.l1 = "お前の神様も予知の力を授けてくれたのか？それならサンティアゴへ行くといい、 あそこじゃ霊媒師や占い師に特に興味があるらしいぜ。";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "俺たちの……ええと、サロンは殴り合いや寝床の話抜きで終わらせようじゃねえか。\n話に教訓は見つからなかったから、代わりに乾杯を提案したいぜ。";
			link.l1 = "お前はまったく迷子だな、親分。でも一つだけ正しいぜ。まあ、とりあえず飲もうじゃねえか！";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "俺たちの欲望が常に必要と一致することを祈って乾杯だ。ありがとう、船長、今夜の締めくくりにふさわしいな。 もし俺の話の真偽を確かめたくなったら、大陸へ行って、そこにある古代の神殿を探してみな。 百十三個のトゥウニチ・カアネを持っていくんだ。俺には九十九個残ってる――これを持っていけ、じゃあな！";
			link.l1 = "穴の開いた石の山か？この場所にはぴったりだな。今夜はありがとう、アグエイバナ。また会えるか？";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "いや、そうはさせないぜ。じゃあな、船長。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "わかったぜ、船長。良くも悪くも、お宝についてのヒントを教えてやるよ。なんせ、 あんたのおかげで俺の余生が少し明るくなったからな……この娼館での話だけどな。\n本土にある古代の神殿を探して、そこに大量のトゥーニチ・カアネを持っていくんだ。ほら、これを一つやるよ。";
			link.l1 = "アダー・ストーン？なんて素敵なの、しかも穴の開いた石ならこの場所にぴったりだわ。 もうあなたの扱いにはうんざりよ！";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "怒ってるのは分かるぜ、船長。良くも悪くも、お宝のヒントを教えてやるよ。なんたって、 お前さんは俺の余生を明るくしてくれたからな……この娼館で、って意味だがな。大地にある古代の神殿を探して、そこに山ほどのトゥウニチ・カーネを持っていけ。ほら、 一つやるよ。";
			link.l1 = "アダー・ストーン？なんて素敵なの、しかも穴の開いた石ならこの場所にぴったりだわ。 もうあなたの扱いにはうんざりよ！";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "さようなら、船長。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "またかよ？くそったれ、もうお前らにはうんざりだぜ！";
			link.l1 = "ああっ！消え失せろ！";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "え？ああ、そうだ。ひれ伏せ、凡人ども！俺のピラミッドの力を見よ！";
			link.l1 = "（必死に叫ぶ）";
			link.l1.go = "joruba_2";
			link.l2 = "（化け物を倒せ）";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "そうだ。その通りだ。俺のささやかなファクトリーへようこそ、船長。";
			link.l1 = "お、お前は何者だ？";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "粘り強さには感心するよ。次はどうするんだ、船長？取引でもしてみる気はあるか？";
			link.l1 = "お、お前は何者だ？";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "俺が何者かなんてどうでもいいんだ、大事なのは俺が果たす役割だぜ。今この時点で、 俺はこのボロ小屋の住人たちと互いの利益のために取引をしてるってわけさ。";
			link.l1 = "ネズミの巣穴だと？この寺院のことか？";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "最初で最後の警告だぞ、船長！だが、このピラミッドは確かに窮屈だな。どうやら俺にはもう狭すぎるらしい。";
			link.l1 = "取引について言っていたな。どんな取引のことだ？";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "俺は人々に一番必要なものを与えてやるんだ。";
			link.l1 = "願いを叶えてくれるのか？おとぎ話の魔人みたいに？なんてこった、ここで一体何が起きてるんだ！？";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "馬鹿なことを言うな！俺はただ、人がこの世に求めてきたものを、最も早く、 そして心地よく手に入れられるよう手助けしているだけだ。";
			link.l1 = "お前はシャーマンか何かか？";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "ああ、アグエイバナに会ったんだろう、それで何か思いつくだろう。";
			link.l1 = "あの哀れで迷子になって酔っ払ってたインディアンはお前の仕業か？";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "部族を数千ポンドの金で売り飛ばしたのは俺じゃねえし、酒を樽ごと飲ませたのも俺じゃねえ。それに、 何百人もの娼婦からありとあらゆる病気をもらうように強制した覚えもねえ。あいつが俺に「白人の貴族にしてくれ」 と頼んだから、俺はそうしたまでだ。運命がそう命じたんだよ。";
			link.l1 = "願いを叶えるって？おとぎ話の魔神みたいにか？なんてこった、ここで一体何が起きてるんだ！？";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "馬鹿なことを言うな！俺はただ、人間がこの世に来た目的を、最も早く、 そして気持ちよく果たせるよう手助けしてやってるだけだぜ。アグエイバナは本来、 ヨーロッパからの侵略者のくびきから自分の民を救うはずだったが、 結局は司令官の娘のコルセットにばかりよだれを垂らして、自分の魂を質に入れることに決めちまったんだ。\nそれからは、自分の過ちの深さを思い知り、早くやり直すことだけが生きる意味になった。ヨーロッパでの一年、肝硬変、 そしてお前たち二人が娼館で過ごした時間も役に立っただろうさ。まあ認めるが、奴は最高のバカンスを楽しんだな、 ははっ！";
			link.l1 = "「シロ…なんだって？お前は呪術師か何かか？」";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "まあ、そんなところだ。だが、俺の提案は気に入るはずだぜ。たまには本気で助けてやるのも悪くねえからな。";
			link.l1 = "ああ、いくらだ？";
			link.l1.go = "joruba_9A";
			link.l2 = "「なぜだ？俺は特別なのか？」";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "悪くねえな、船長。お前は頭が切れるか、それともロバ並みに間抜けか、どっちかだが、運はちょっと上向いたぜ。 値段のことは気にすんな。";
			link.l1 = "誰かを殺してほしいのか？俺はそんなことはやらねえ。";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "「お前のこの世での目的は、俺の親友に穴を開けることだからな、はは！」";
			link.l1 = "誰かを殺してほしいのか？俺はそういう仕事はしねえ。";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "まずは、お前がやるんだ。次に、俺たちは四つの大きな取引と、さらに四つの小さな取引を行う。 それぞれの取引でお前はもっと強くなり、この残酷で奇妙な世界で生き残る可能性が高まるぜ。 すべての取引をやり遂げれば、いつか神々と互角に戦えるようになることを俺が保証する。 ましてや普通の人間相手なら言うまでもねえさ。";
			link.l1 = "面白そうだな。詳しく聞かせてくれ。";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "賢い選択だな！普通なら俺の話が終わる頃には、誰かが心臓発作でブルーウェルドに運ばれていくもんだが、 お前はなかなかしぶといじゃねえか。\nさて、これが仕事のリストだ。いくつか物々交換絡みの用事があるから、しっかりやってもらうぜ。期限はねえ、へへ。";
			link.l1 = "妙だな。リストは後で読むとしよう。他に何かあるか？";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "ああ、最初の大きな取引だ。値段は二千ドゥブロンだぜ。";
			link.l1 = "もしかしたら乗ってやってもいいが……でも、それは大金じゃねえか！なんでそんなに必要なんだ？ペソで払ってもいいか？";
			link.l1.go = "joruba_13";
			link.l2 = "気は確かか？その金があればフリゲート艦が買えるじゃねえか！";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "ピラミッドは修理が必要なんだ――時々石材が客の頭に落ちてきて、商売にとっちゃ最悪だ。俺の手下どもが毎日応急処置してるが、 うちの組織には外部からの資金注入が急務で、この状況を根本的に解決する必要がある。\nペソについてはあまり好かん、為替が不安定すぎるからな。";
			link.l1 = "お前は正直なペソにずいぶん不公平じゃねえか……待てよ、ここに一人じゃねえのか？";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "いや、俺はただの真面目な組織の看板にすぎねえんだ。\nで、乗る気はあるか？";
			link.l1 = "考えてみるが、まずはそんな大金で何が手に入るのか知りたいんだ。";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "なぜサプライズを台無しにするんだ？それに、その金は税金だと思っておけ。お前にとって一番価値のあるのは、 次の取引を解放することだぜ。報酬は神がかり的だし、しかも唯一無二だ。どこにも手に入らねえからな！";
			link.l1 = "いいだろう。名前をもう一度聞かせてくれ。";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "偉大なるアルバ。最後にもう一つ、 "+pchar.name+"「ピラミッドへの入場は一日一回だけ許可されている。他の客を待たせるな、そして理由もなく俺にちょっかいを出すな。 」";
			link.l1 = "行列ができているようには見えませんね……それでは、ごきげんよう、陛下。";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "ああ、船長。俺に何の用だ？";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Here are your doubloons. It's hard enough to carry that damned metal around... but it is even harder to part with it!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "I kept my end of the bargain. Here's your herb, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' is all yours!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Pink '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "I am bringing you a bride and troubles with the Spanish authorities, sir. The lady is taking a stroll outside, well protected by my men. I will not give her to you until you convince me of the nobility of your intentions.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Here's your armor, Aruba. Make sure my reward will make up for it.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "I have the prisoners you asked for.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "I brought you your junk. Here, a hundred and thirteen stones, just like you asked for.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec character's stats)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "I am just passing by.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "では、次の機会に。";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "悪くねえな、その金は有効に使わせてもらうぜ。ほら、これは昔、 とても徳の高いタイノ族の酋長が持ってた小さな飾りだ。金貨の山を運ぶのに役立つんだ。 あいつにもきっと役立ったんだろうな、へっへっ…";
			link.l1 = "ありがとうございます、後悔しないといいが。次の取引は何だ？";
			link.l1.go = "joruba_p1_1";
			link.l2 = "ちょっと待てよ。俺は山ほどの金を渡したのに、代わりに土の塊を受け取ったってのか？返金してもらうぜ！";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "え？ああ、次の取引だな。この金で今は十分だが、そろそろ精神的な品にも目を向ける時だ。 自分の治療法を見つけなきゃな。";
			link.l1 = "「どうした、具合でも悪いのか？」";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "俺の魂はな。見ての通り、あの異端審問の一件以来、神父たちはこのつつましいピラミッドを避けているんだ。だから、 もっと伝統的な手段に頼るしかない。俺が――いや、うちのファクトリーが稼働し続けるには、マガローサの草が十五本必要なんだ。";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "それは薬草か？";
			} else {
				link.l1 = "俺はそれが何か知ってるぜ、へっへっ。";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "正直に言うと、それは非常に貴重な珍しい薬草だ。\n本当に諸島中を何年もかけて集めるつもりか、よく考えたほうがいいぜ。";
			link.l1 = "約束はできねえが、あんたの健康を祈るぜ。それと、この薬草の報酬がちゃんと価値あるもんだといいんだがな。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "よし、今日は正式に俺の休みだと宣言するぜ！こんな掘り出し物は本物の財宝に値するからな。見てくれ！\nこのマチェーテは、かつてあの間抜けなカネクの頭を真っ二つにしかけたんだ！だから俺にとってはとても大切な品だ。 どうか大事にしてくれよ。古いが、作りは抜群だ。今じゃこんな鋼はもう手に入らねえぜ。";
			link.l1 = "「カネク？誰だそいつ？」";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "おう、お前ら二人は会うことになるぜ。さて、お前はまさか手作業を見下すような偉そうな野郎じゃねえだろうな？ もしそうなら運が悪いな、報酬の後半は二重装填弾の設計図だからな。";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "ああ、それは大好きだよ。でも、それの何が特別なんだ？二重火薬装填なんて珍しくもねえし、 つまりお前さんは博物館のマチェーテがあった時代からピラミッドの外に出たことがねえんだろうな。";
			} else {
				link.l1 = "それだけか？おい……";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "利口ぶるんじゃねえ、ちゃんと聞け！どんな馬鹿でも火薬を二山樽にぶち込んで、目が見えなくなったり、顔を焼いたり、 鼻を折ったりする危険を冒せるさ。だが俺が教えてやるのはちょっとした魔法の技だぜ。火薬の質をしっかり確かめて、 ちょうどいい粗さに挽き、弾丸か散弾を込めて、刻んだドゥブロン金貨を一振り加えるんだ。そうすりゃ、 その爆発はキュイラスだって木っ端みじんにしちまうぜ！";
			link.l1 = "金をぶっ放すとはな。まったくお前らしいぜ。";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "お前は本当に手に負えねえ奴だな！いいだろう、手持ち臼砲と、それ用の手榴弾を十発持っていけ。 そんなに頭が切れるってんなら、手榴弾の設計図くらい自分でさっさと手に入れられるだろうよ！";
			link.l1 = "ありがとうございます、旦那様。次はどうなさいますか？";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "気に入らねえだろうが……俺には船が必要なんだ……いや、「その」船が必要なんだ。わかるだろ、何か曰く付きの船さ。";
			link.l1 = "なぜだ？お前は船長ですらないじゃねえか。";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "余計なお世話だ！報酬のことだけ考えてろよ。俺がその気になりゃ、 このピラミッドを上から下まで掃除させることだってできるんだぜ。それでもまだ借りが残るくらいにな！";
			link.l1 = "お前は絶対に船長じゃねえな。船を停泊させるには桟橋か湾が必要だってことくらい知ってるはずだ。\n一体どうやって俺にお前のピラミッドに船を入れろってんだよ！？";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "俺のピラミッドの裏に巨大な湖があるのに気づいたか？そうだ、その通りだ。近くの艦隊に適切な船を停泊させれば、 あとは俺の部下がやる。さあ、もう行け。後ろがつかえてるんだよ。";
			link.l1 = "もちろんだとも。じゃあな！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "いいぞ！わかった！";
			link.l1 = "偉そうな口をきくのはやめて、さっさと報酬をよこせ！";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "他の二人はどうした？自分のために助けておけなかったのか？へっへっ。";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "他の二人はどうした？自分のために助けておけなかったのか？へっへっ。";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "他の二人はどうした？自分のために助けておけなかったのか？へっへっ。";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "くそっ、お前があの女を自分のものにしようとしなかったのには驚いたぜ。あれこそまさに物語を持つ船ってやつだな！ ちくしょう、ウィリアム……本当にお前には、いつも夢見てたみたいに故郷に帰って立派な銀行を作ってほしいもんだ。";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "見てみろよ！お前は自分の任務に泥を塗ってるじゃねえか。 "+sTemp+"!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "チャーリー・プリンスが俺の古いピラミッドにあった自分に不利な証拠を処分することにしたのか？俺は賛成だぜ！";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "旗艦を失ったことを上官にどう説明するか、幸運を祈るぜ、提督。あっと、失礼、総督閣下。";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "お前は迷信深い馬鹿か、それともただの馬鹿か？あの女は大金の価値があるんだぜ！ 割に合う取引かどうかは分からねえが、まあいいさ。";
				break;
				
				case SHIP_FDM:
					dialog.text = "お前は迷信深い馬鹿か、それともただの馬鹿か？あの女は財宝にも匹敵する価値があるんだぜ！ 公平な取引かどうかはわからねえが、まあいいさ。";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "お前は迷信深い馬鹿か、それともただの馬鹿か？あの女は大金の価値があるんだぜ！公平な取引かどうかは分からねえが、 まあいいさ。";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "いい判断だな！俺はカスティーリャ人が大好きなんだぜ。用が済んだら、あの娘をあいつらに返してやるかもな。";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "本当に、あんたには情けってもんがねえな、船長。この船は裏切りの臭いがぷんぷんするぜ。俺がいただく。";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "ああ、この船には歴史があるかもしれねえ……だが、手に入れるのが簡単すぎたんじゃねえか？\nまあ、いいさ。お前の場合は特別だ、俺の可愛い人よ、引き受けてやる。少なくとも若い頃を思い出させてくれるぜ。";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "ああ、この船にも歴史があるかもしれねえが……手に入れるのがちょっと簡単すぎたんじゃねえか？まあ、いいさ。よし、船長、今回は大目に見てやるぜ。 お前が俺のリストの仕事をちゃんと片付けてくれたからな。受け取っておくぜ。 少なくとも若い頃の思い出が蘇るってもんだ。";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "神父を見たか？まあ、そのうち会うだろう。\nそれから二連発ピストルの弾をしっかり用意しておけよ。\nそれでもダメなら木の杭を試してみな。";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "神父を見かけたか？まあ、そのうち会うだろう。\nそれと二連発ピストルの弾をしっかり用意しておけよ。\nそれでもダメなら、木の杭を使ってみな。";
				break;
				
				case SHIP_MEMENTO:
					dialog.text = "神父を見たか？まあ、そのうち会うことになるさ。二連発のピストル弾をしっかり用意しておくんだな。 それでも駄目なら――木の杭を試してみろ。";
				break;
			}
		break;
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "ああ、この船には歴史があるかもしれねえが……手に入れるのが簡単すぎたんじゃねえか？そんなわけねえ！まだやるべきことが山ほど残ってるだろう。 全部片付けてから、もう一度この犠牲について話そうじゃねえか。";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "「お前に祝福を授ける」 "+GetFullName(pchar)+"。海があなたに味方しますように。さて、次の取引について話しましょう…";
			link.l1 = "待て、なんだと？理性の時代の今、田舎者の馬鹿だってそんな戯言には騙されねえぞ！ 俺はお前の慈善箱に一銭も入れてねえ、ちゃんとした軍艦をくれてやったんだぜ！";
			link.l1.go = "joruba_insult";
			link.l2 = "ちょっと待て。お前の祝福が俺にとって一体何の意味があるんだ？";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "これからお前が指揮するどんな船も船体がより頑丈になる祝福を受けるが、敵どもは逆に弱くなるだろう。\nさらに、海上での時間もお前にはゆっくり流れるぜ。\nそれでもこのクソみたいな世界を跪かせるのに足りねえってんなら、 とっとと親父のところへ行って金返せって言ってこいよ！";
			link.l1 = "もしうまくいかなかったら、今夜ここに戻ってきてお前のピラミッドを燃やしてやると誓うぜ！さあ、 次の取引について話せ！";
			link.l1.go = "joruba_p3_3";
			notification("+10% hull defence", "None");
			notification("+10% damage to enemy ships hull", "None");
			notification("+5% speed on the Global Map", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "気に入ってきたのかい、船長？残念だが、俺も同じさ。俺がこのピラミッドを仕事場に選んだ理由、わかるか？";
			link.l1 = "多分、まだ魔女狩りが続いてるからじゃねえか？";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "へっへっ、いや、ちょっと違うな。俺がここで商売してるのは、最高の取引には血が必要だからだ。 このピラミッドも血を求めている。俺も血を求めている。昔からそうだし、これからもそうだぜ。";
			link.l1 = "考えるんじゃねえぞ、この化け物め。お前のために犠牲者を差し出すなんて絶対にしないからな！";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "「で、今まで何人殺したんだ、え？待てよ、正確な数まで教えてやるぜ。お前が自分の手で殺したのは」 "+(Statistic_AddValue(pchar,"Solder_s",0)+Statistic_AddValue(pchar,"Citizen_s",0)+Statistic_AddValue(pchar,"Warrior_s",0)+Statistic_AddValue(pchar,"Solder_g",0)+Statistic_AddValue(pchar,"Citizen_g",0)+Statistic_AddValue(pchar,"Warrior_g",0))+" 人々よ！お前たちは野望と金への欲望の祭壇に死体の山を積み上げたんだ！ ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+"お前の兄貴の借金のせいで、普通のヨーロッパの戦争より多くの人間がもう死んでるんだぞ！ ";
			}
			dialog.text = dialog.text+"ここで俺に説教なんか始めるんじゃねえぞ、特に俺がお前を裁くつもりもねえんだからな。誰かの成功は、 いつだって他の誰かの悲劇の上に成り立つもんだ。そして神々は――ああ、神々は、ちゃんと見てやがるし、自分たちの取り分をしっかり回収するのさ！";
			link.l1 = "今は答えられねえ……ここから出なきゃならねえんだ。";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "頭を冷やしたいほど切羽詰まっているのか？よし、だがまずは俺の話を聞け。お前に力と、 肉体と精神を完全に支配する力を授けてやろう。ただし、価値ある男を一人、俺のもとに連れてくるんだ。通行人でも、 顔のない灰色のネズミでも、臭い船底のドブネズミでもない。お前についてきて、 お前の悲喜劇で重要な役割を果たす男を連れてこい。";
			link.l1 = "俺の部下の一人だと？お前も落ちぶれたもんだな、アルバ！この話が広まったら……";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "いつも通り、秘密は俺がしっかり守るぜ。\nそれから、また文句を言い出す前に教えてやるが、もう一つ方法があるんだ。";
			link.l1 = "それはどういう意味だ？つまり、俺が自分の仲間を無理やり祭壇まで引きずっていかなくてもいいってことか？";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "いや、だが他の選択肢は気に入らねえだろう。血で払いたくねえなら、金で払え。三千ドゥブロン払えば、 良心もすっきりだ。金さえあれば何でもできる――俺はそれが大好きなんだよ！";
			link.l1 = "さらばだ、アルバ。もうお前とは話したくねえ。";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "俺がどこにいるか、知ってるだろ。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "スペイン異端審問が来る前に、さっさと片付けようぜ。サングレ・ウ・オロ（血か金か）？";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "金だな。ほら、三千だ。だが、こんな荒野でどうやってそんな大金を使うつもりなのか、俺には想像もつかねえぜ。";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "「血だ。」";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "気にするな。";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "終わったか？俺の報酬について話そうぜ。";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "そうか。名を言え。";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "クロード・デュランは士官ではなく、冷酷な傭兵だ。だから他の獲物を選ぶんだな。";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "貢ぎ物は受け取ったぜ。見てなくてもいいんだ。";
			link.l1 = "いや、知らねえ。報酬をもらいに一時間後に戻ってくるぜ。";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "素晴らしい選択だ。祭壇から血を拭き取るのは大嫌いだからな、だから金の方がありがたい。さあ、この薬を持っていけ――俺の親しい友人からの贈り物だ。";
			link.l1 = "味は全然悪くねえな……";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "終わったか？俺の報酬について話そうぜ。";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "運命を変えたい時は、いつでも俺に話しかけてくれ。";
			link.l1 = "「でも、それは俺にとって一体どういう意味なんだ？」";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "自分自身を制する力だ！一度やってみれば、きっと気に入るぜ。さて、その間に次の取引について話してやろう。 最も重要な取引だ。";
			link.l1 = "もうこれ以上やる価値があるのか分からねえ！";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "さあ、早く言えよ。";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "お前には自分の運命を変えるだけでなく、この時代の天才や神々と肩を並べる機会があるんだ。\nああ、今なら好きなだけ身体も心も変えられるだろうが、自分の限界を超えることはできねえ。 凡人はすべてにおいて卓越することはできないからな。\n俺が言いたいのは、その枠をぶち破れってことだ。";
			link.l1 = "俺に何が必要なんだ？もっと血か？それとも金か？";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "ああ。二万五千ドゥブロンか、お前の仲間の誰か一人を連れてこい。取引が終わったら、もうこれ以上は何もないぜ。";
			link.l1 = "少し考えてみるぜ。";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "俺の居場所はわかってるだろう。運命を変えたくなったら、いつでも遠慮せずに来いよ。";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "ご希望の通りに。";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "まず第一に、あれは俺の妻であって、花嫁じゃねえ。\n第二に、お前が揉めてるのはカスティーリャ人であって、俺じゃねえ。\nそして最後に、俺はもう彼女を連れて行ったし、お前の部下どもも解散させたぜ。\nそれから“高潔な意図”ってやつについてだが……俺のこの姿を見てみろよ、まともな紳士の鑑じゃねえか？\nトラソルテオトルよ、あいつにもいつか本物の女……いや、男でもいいから知る日が来ますように。";
			link.l1 = "くたばれ、アルバ！";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "悪くないな、ありがとう。正直言って、あまり必要じゃないけど、まあサロンかどこかで身につけるかもな。 イシュタルの名において、お前に祝福を授けよう。さあ、行って罪を犯せ。";
			link.l1 = "なんだか妙な感じだな……";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "俺が引き取るぜ。なんだと？俺だってお前と同じように死んだ奴らが必要なんだが、 あいにくお前みたいに酒場を回って仲間を集めることはできねえんだよ。さて、バストよ、 この英雄のこれからの活躍を祝福してくれ。";
			link.l1 = "なんだか妙な感じだな……";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "ああ、また石をばらまかないといけねえな。みんなすぐになくしちまうし、客も必要だからな。フレイヤ、 この偉大な石集め野郎を守ってやれ。";
			link.l1 = "なんだか妙な感じだな……";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "スペイン異端審問が来る前に、さっさと片付けようぜ。サングレ・ウ・オロか？";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Here's your gold, you greedy bastard.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "気にするな。";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "名前を言え。";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "それはなかなか魅力的だが、今回は特別に例外を認めてやる――お前の犠牲は受け取らねえ。これをお前の\n "+sTemp+"、本当はそうすべきかもしれねえがな。あいつがいなきゃお前なんて何者でもねえってことを忘れるな。さあ、消えろ、 今日は俺にかまうなよ。";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "クロード・デュランは士官じゃなくて、冷酷な傭兵だ。だから他の獲物を選ぶんだな。";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "そうか。これを持っていけ――俺の親しい友からの贈り物の薬だ。";
			link.l1 = "味は全然悪くねえな……";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "また今度だな、船長。";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "おうおう！やっと、すべて終わったぜ！";
			link.l1 = "「え？」";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "ここでの用は済んだぜ、船長。取引はすべて成立、みんな満足してるし、返金の余地なんてない。 うちの事務所はこれで閉鎖して移転するんだ。";
			link.l1 = "ちょっと待て、アルバ。俺はたっぷりと金をやったし、血で払ったし、女や囚人もこの悪魔の巣窟に連れてきたぜ。 カリブで起きるらしい超常現象だって、俺は対処できる。だが、お前との「取引」だけはまったく理屈が通らねえ。 説明してくれ。\n";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "なあ、教えてやろうか。\nもうこの世界にはうんざりなんだ、俺は抜け出したい。毎日が同じ繰り返しさ――崩れかけた天井の古代ピラミッド、見分けのつかねえヤシの木ばかり、そして次から次へと現れる船長ども、 それぞれが妙ちきりんなアイデアを持ち込んでくる。そうさ、俺は人が望むものを与えてやってる。それが俺の役目だし、 誇りも持ってる。だが神に誓って、お前ら全員が大嫌いだ！";
			link.l1 = "誰かにここに引き留められてるのか？出口はそこだぜ、天才さん！";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "おっしゃる通りだ、今はもう誰にもここに縛られていない。\nそれもこれも、全部お前のおかげだ、相棒。";
			link.l1 = "それは急な心変わりだな。話を期待していたが、今のところ俺が聞いたのは、 埃まみれのピラミッドにいる卑劣な小神のくだらない戯言だけだぜ。";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "まあ、誰だってたまには愚痴を言いたくなるもんだろう？\nお前がここに来てくれて本当に嬉しいぜ。おかげでようやくこの世から旅立てるんだ。\n金、仲間、装備、そして船――相棒よ。覚えてるか？聞き覚えがあるだろ？それだけが俺に必要だったんだが、お前は全部そろえてくれた。";
			link.l1 = "どういたしまして。しかし、それでもお前の妙な話し方と、ほとんど神がかった力の説明にはならねえな。 そんなに全能なら、とっくに自分の船も乗組員も金も魔法で出せたはずだろうが！";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "見ての通り、俺はやったぜ。誰にだって自分なりのやり方があるもんさ。";
			link.l1 = "「だが、一体どうやって？お前は一体何者なんだ？」";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "「まあ……それが俺のやり方さ。新世界でまた会おうぜ。」 "+GetPersonaName()+"。次こそは本当に新しいものを期待しているよ。ありがとう、じゃあな。";
			link.l1 = "いや、もう二度とお前の顔なんか見たくねえ。";
			link.l1.go = "exit";
			link.l2 = "じゃあな、アルバ……面白かったぜ。\n";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "取引はすべてご破算になったようだ。行くぞ、船長。";
			link.l1 = "お前の出番だ…";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "スペイン異端審問の名のもとに、名を名乗れ！";
			link.l1 = "Captain "+GetFullName(pchar)+"。そして、よく言われている通り、誰もスペイン異端審問を予想していなかったんだよ……";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "…この冗談はいつも的を射ているが、そのせいで何人もの無実のキリスト教徒が火刑台に送られたんだ。";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "冗談だよ、船長。あんたが冗談を言ったから、俺も冗談を返しただけさ。俺の名はパドレ・エミリオ・ボカネグラ、 そしてこのキリストの兵士たちは俺の武装護衛だ。";
			link.l1 = "「どうなさいましたか、神父？」";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "「旦那アルバという人物を知っているか？」";
			link.l1 = "ああ、彼は最近までこの古いピラミッドに住んでいたんだ。";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "「彼がそこに住んでいたってどういう意味だ？そこに住むなんて本当にできるのか？それに、どうして『つい最近まで』 なんだ？」";
			link.l1 = "この旦那はほんの数分前に俺たちを船に置いて行きやがったんだ。";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "どうしてそれを知っているんだ？一番近い湾でもここから何日もかかるんだぞ！";
			link.l1 = "この湖は見た目よりもずっと大きいに違いありません。他に説明のしようがありませんよ、神父。";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "副王領の地で奇妙なことが起きている。";
			link.l1 = "「ここはイングランドの領土だぜ、神父。」";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "異端者どもにはそう思わせておけばいい。我々は必ず取り戻すことができる。すまない、息子よ、 あれこれと質問してしまって。サンティアゴからこのピラミッド……そしてその元の住人について正式な調査を行うよう指示されているのだ。";
			link.l1 = "「一体何があったんだ、神父？」";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "事件はおそらくこれで終結するだろうから、ちょっとした話を聞かせてやろう。\nこの場所の噂はしばらく前から本土中に広まっていた。我々は、この地域の歴史に大きな足跡を残した何人かの人物が、 かつて定期的にここを訪れていたという信頼できる報告も受け取っていた。\nしかし、サンティアゴが本格的にこれらの噂に注目し始めたのは、パナマ事件の後だった。\nあるインディオがあの栄光の都で大騒ぎを起こし、しかもかなり哲学的な説教を何度か行ったのだ。残念ながら、 パナマの住民たちは表面的な結論しか出せず、このピラミッドには莫大な財宝が眠り、 どんな願いも叶うと信じ込んでしまった。\nまさに純粋な異端だ……だから我々は、何人かのパナマ住民とこのインディオ、アグエバナに対して訴追手続きを開始せざるを得なかったのだ。";
			link.l1 = "なぜパナマ当局はこれを取り締まらなかったんだ？";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "こういう場合によくあることだが、連中は自分たちが魔法にかけられたと主張した。\nもしアグエバナを尋問できていれば、この法の抜け穴も塞げたのだが、奴は突然死んでしまった。";
			link.l1 = "「どうやって死んだんだ？」";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "酒に溺れて彼は死んだ。しかし、彼の死で我々の問題は解決しなかった。なぜなら、異端が群島全体に根付いてしまい、 何百人もの人々がこの古代の神殿へと一種の巡礼に出かけていったからだ。\n";
			link.l1 = "ここでこんなに人が集まってるのは初めて見たぜ…で、どうするつもりだったんだ？アルバを侵略して、あいつを裁判にかけるつもりだったのか？";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "もちろんだ、息子よ。異端審問の裁きは厳しいが公正だ。裁判にはきっと正当な理由があるはずだ。いや、 俺はただアルバ旦那の証言を集めてサンティアゴに届けるつもりだっただけだ。";
			link.l1 = "そりゃあ、お前さんには運が悪かったな。";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "何が起こるか分からん、息子よ。すべては神の御心だ。";
			link.l1 = "「さようなら、神父。」";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,    0.0,  0, 0,  20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,      0.0,  1, 0,  20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,    0.0,  1, 2,  20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,     0.0,  0, 2,  30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,     0.0,  0, 0,  20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,    5.0,   1, 0,  20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0,    0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,   40.0,   0, 0, 100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,    0.0,   0, 0,  20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  15.0,    0, 0,  30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,   5.0,    1, 0,  30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,   0.0,    0, 4,  34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		InitGunExt(		"mushket1", "t3",    "bullet_double",      			"", 240.0, 440.0,  0.0,    0, 0,  20, 0);
		InitGunExt(		"mushket2", "t3", 	 "bullet_double",      			"", 270.0, 470.0,  0.0,    0, 0,  15, 0);
		InitGunExt(		"mushket5", "t3", 	 "bullet_double",      			"", 400.0, 600.0,  15.0,   0, 0,  15, 0);
		InitGunExt(		"mushket7", "t3", 	 "bullet_double",      			"", 300.0, 440.0,   0.0,   0, 0,  18, 0); // Качественный мушкет cle
		InitGunExt(		"mushket8", "t3", 	 "bullet_double",      			"", 200.0, 400.0,  0.0,    0, 0,  20, 0); // Четырехзарядный штуцер cle
		InitGunExt(	  "mushket2x2", "t3", 	 "bullet_double",      			"", 360.0, 560.0,  15.0,   0, 0,  15, 0);
		
		InitGunExt(		"mushket3", "t2", "grapeshot_double",	            "", 140.0, 240.0,    0.0,    1, 0,  13, 0);
		InitGunExt(		"mushket6", "t3", "grapeshot_double",	            "", 180.0, 310.0,  20.0,   1, 0,  15, 0);
		InitGunExt(		"mushket9", "t3", "grapeshot_double",	            "", 140.0, 240.0,   0.0,   1, 0,  23, 0);
		InitGunExt(	  "mushket10",  "t3", 	 "bullet_double",      			"", 360.0, 440.0,   0.0,   0, 0,  21, 0);
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
	
	ref itm;
	
	makeref(itm, items[FindItem("mushket9")]);
	
	itm.type.t3.basedmg  = 3;
	itm.type.t3.shards  = 110;
	itm.type.t3.width   = 8.5;
	itm.type.t3.height  = 7.85;
	itm.type.t3.area    = XI_ConvertString("grapes_area_4");
		
	if(CheckAttribute(itm, "UpgradeStage"))
	{
		int iUpgradeStage = sti(itm.UpgradeStage);
		
		switch (iUpgradeStage)
		{
			case 2:	
				itm.type.t3.basedmg  = 3;
				itm.type.t3.shards  = 120;
				itm.type.t3.width   = 7.0;
				itm.type.t3.height  = 5.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_4");
			break;
			
			case 3:	
				itm.type.t3.basedmg  = 4;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 5.5;
				itm.type.t3.height  = 4.5;
				itm.type.t3.area    = XI_ConvertString("grapes_area_3");
			break;
			
			case 4:	
				itm.type.t3.basedmg  = 5;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 4.5;
				itm.type.t3.height  = 3.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_2");
				itm.type.t3.ChargeSpeed = 18;
			break;
		}
	}
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
