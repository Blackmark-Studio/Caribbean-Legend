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
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

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
		
		case "BM_Contra_1":
			dialog.text = "お前は何者だ、そして一体ここで何をしてやがるんだ！？";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "落ち着けよ、相棒。俺はただ通りかかっただけだ。お前らの……なんだか知らねえが、邪魔するつもりはねえよ。";
			}
			else
			{
				link.l1 = "え？この灯台はお前のか？次からはヤシの木に名前でも書いた札をぶら下げるか、血まみれの柵でも作っとけよ。";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "出て行け！客を怖がらせて取引を台無しにしたら、俺は……";
			}
			else
			{
				dialog.text = "聞けよ、坊主、俺と仲間たちにお前の剣がその口ほど切れるか試させるなよ。さっさと消え失せろ、そして…";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "「さて、フランキー、どっちなんだ？」";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "いや……くそっ、どの面も見覚えがねえな。";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "「なんだと！？本当か？」";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "俺が盲目だと思ってるのか！？言ってるだろ、な…";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "なんだと！？";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "「誰が撃ったんだ！？」";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "俺たちをバカにしてんのか、このクズ野郎ども！全員、銃を地面に置け！お前もだ！";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "落ち着けよ、役人。俺たちじゃねえだろ、見りゃわかるだろ？俺たちの大砲は元の場所にあるんだ。 それにお前の銃には手を出すなよ！";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "俺に命令してるつもりか、この野郎！？全員を今すぐ捕まえろ！";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "ふざけんな！そんなことはさせねえ。野郎ども、武器を取れ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "おいおい、気をつけろよ！そんなに鉄を振り回してたら、誰か死ぬかもしれねえぞ。";
			link.l1 = "は？誰だ？";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "もちろん俺だ。";
			link.l1 = "なんだと…？てめえ、何者だ！？";
			link.l1.go = "BM_Irons_4";
			link.l2 = "まさにそれをやろうとしているんだ。行こうか？";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_DlgExit_1");
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "俺はトミーだ！トミー・アイアンズ。たぶんな。お前は誰だ？あんた、なかなか度胸のある女だぜ、 そんな格好で歩き回ってるなんて、へへへ。";
				link.l1 = "勇敢だな、確かに。でも、必要ならお前の口を黙らせることもできるぜ。ここは暑いから軽装なんだ――お前やお前の仲間を喜ばせるためじゃない。名前はヘレン・マッカーサー。友達はあたしをルンバって呼ぶけど、 お前は違うよ。それとさっきの「たぶん」ってのは何だい？";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "俺はトミーだ！トミー・アイアンズ。たぶんな。で、お前は？";
				link.l1 = ""+GetFullName(pchar)+"。で、「たぶん」って一体どういう意味だ？";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "それは文字通りの意味だ。俺は記憶をなくした――戦いでひどくやられてな。時には全部失うこともあるんだ。だが、俺は運が良かった。名前だけしか忘れなかったんだ。 首にかけてるペンダントに「トーマス」って書いてあったおかげでな。でも俺は「トミー」の方が好きだ。それと 「アイアンズ」もな。クロムウェルのためにアイアンサイドで戦ったんだ、それは覚えておけよ。でも「アイアンサイド」 じゃ長ったらしいだろ。「アイアンズ」の方がずっといいさ。";
			link.l1 = "なるほど、トミー、お前の様子は分かったぜ。で、どうしたんだ？誰か特定の奴を狙ってたのか？ちゃんと当てたのか？ それともただの遊びで撃ってたのか？まあ、驚きはしねえけどな。";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "ぶん殴ってやったぜ、しかも思いっきりな！あらゆる意味でな。あの気取った野郎を覚えてるか？俺の跡を追ってきて、 兵隊まで連れてきやがった。俺があいつの女房と寝ただけで、わざわざ部隊まるごと引き連れてきたんだぜ。";
			link.l1 = "確かに当てたな、へっ。あいつに二人の現場を見られたんじゃねえか？";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "はっ！信じられねえだろうが、いや、違うんだ。あの女は後で自分から白状したんだよ。良心の呵責か、 それとも俺ほど楽しめなかったのか、へへ。女の頭の中なんて誰にも分からねえさ。俺は気にしちゃいねえけどな、 ははは！";
			link.l1 = ""+GetSexPhrase("ふむ、あいつは変わった女だな。","男ってやつは……さっきまで俺たちの考えを知ろうとしてたくせに、次の瞬間には「どうでもいい」なんて言いやがる。\nでも一つだけ正しいことがある――あいつのやったことは変だったな。さっさと立ち去って、悪い夢みたいに忘れちまえばよかったんだ。\nもし俺だったら、そうするぜ。")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "その通りだ！俺のことをどこかおかしいって言う奴もいるがな。死んだ兵士たちには同情するぜ。俺にもわかるさ、 昔は俺もただの下っ端だったからな。言わなかったか？";
			link.l1 = "ああ、そうだ。アイアンサイドから来たんだ。クロムウェルの部下だな。";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "へえ、そうかい？俺がやったかどうか覚えてねえな。どうして俺が新世界に来ることになったか知ってるか？ 話してやろうか？";
			link.l1 = "いや、興味もねえよ、トミー。";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "そうだ、そうだ。話してやるよ。";
			link.l1 = "よし、もうどうでもいい、撃てよ。いや、好きにしろ。";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "じゃあ、俺の話を邪魔すんなよ！どこまで話したっけ？ああ、そうだ、俺は負傷したんだよ、わかるか？ 勝ち組だったから正式に辞職させられたんだ。だがな、あの机にかじりついてる連中のツラ、見せてやりたかったぜ！ 俺が怪我を装って記憶喪失のフリしてると思ってやがった。家族のことをしつこく聞いてきやがったんだ。";
			link.l1 = "「で、あんたは奴らに何て言ったんだ？」";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "俺は何て言ったか？覚えてないって言ったんだ。本当のことさ――親なんて知らねえ。俺を育てたのは街の路地裏、スラムの労働者や召使いたちだ。 あいつらのために革命に参加したんだぜ。だが、人間の恩知らずっぷりには驚かされるな――もし腕や足を失ってたら、英雄の俺はすぐに引退させられてただろうよ。ちなみに、首を飛ばされかけたこともあるんだ、 文字通りにな！\n";
			link.l1 = "さて、どうして新世界に来ることになったんだ、戦争の英雄よ？";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "疑ってるのか？庶民のために戦う――それが英雄じゃなくてなんだってんだ？いつかお前みたいな腰抜けにも、本当の自由ってものがわかる日が来るといいな！ ";
			link.l1 = "自由は素晴らしいものだけど、なんだか脅しのように聞こえたぜ。よし、トミー、続けろ。";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "ああ。革命が勝利した後に辞職を手に入れたんだが、その時気づいたのさ、 俺には撃つことと人の顔を殴ることしかできねえってな。軍に戻るなんてできやしねえ――笑いものにされるだけさ、特にあれだけ必死に辞職を勝ち取った後じゃな。へっ、仮に本当に腕や脚を失ってたとしても、 あの机にかじりついてる連中は、俺が退役証明を手に入れた後でどこかに隠しておいて、 また縫い付けるつもりだとでも思ってたんだろうな、ははは！";
			link.l1 = "それはおかしいな。でも、どうしてここに来たのかまだ話してくれてないぜ。";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "「ああ、つまらない奴だな。辛抱ってものを教わらなかったのか」 "+GetSexPhrase("若造","あたしの娘")+"？故郷ではカモやシカを撃つくらいしかやることがなかったから、新世界へ行ったんだ。 しばらくは面白半分で海賊と一緒に航海してたが、無法ぶりに飽きて傭兵になったんだ。";
			link.l1 = "あまり独創的な話じゃねえな。";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "もしかして、もっといい案があるのか？まさか用心棒が必要ってわけじゃねえだろうな？だってお前……弱そうに見えるぜ。心配だな、遠くまで行けそうにねえ、へへ。覚えとけよ、王を王たらしめるのは取り巻きだ。 悪い連中をそろえりゃ、王様だって転落するもんさ。";
			link.l1 = "「どんな」 "+GetSexPhrase("王","女王")+" 「お前みたいな取り巻きを連れて俺がいると思うか？」 "+GetSexPhrase("King","Queen")+" 肥溜めのことか？";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "いや、違う！俺は本気の提案をしてるんだ、なのにお前は…";
			link.l1 = "まだ何の申し出も受けていない。お前の仕事の報酬はいくらだ、トミー？";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "まずは前金で150ドゥブロンだ！お前が本気か、それともただの詐欺師じゃねえか確かめるためにな。\nその後は毎月の手数料ももらうぜ。\n取引は成立しそうだな。";
			link.l1 = "「それにお前は……」";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "……お前、自信があるつもりか？へっ、俺は口論なんざしねえよ――灯台であの間男を撃ったの、見ただろ？一発で仕留めたぜ！値切りもなしだ、もしそれを考えてるならな。 俺みたいなプロを雇うなら、その覚悟と金を見せてもらわねえとな。";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "ああ、できるぜ！150枚の金貨だ。ほら、持ってけ。";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "その一発は運が良かっただけだろう。今度は自慢して自分の価値を釣り上げようってのか。 お前みたいなプロはいなくても困らねえよ。そんなに名誉も金もいらねえんだ。";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "今はそんな大金は持ってないんだ。ポケットにもそれほど入ってないからな。ここで待ってろ、どこにも行くなよ――船から金貨を取って戻ってくるぜ。";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(150);
			
			dialog.text = "思ったより悪くねえな！でも、俺を退屈させるんじゃねえぞ。俺の才能がもったいねえだろ？トミーと\n "+pchar.name+"！カリブを揺るがせようぜ！";
			link.l1 = "指揮系統をちゃんと守れ、トミー。\nそれから、俺は「船長」だ。わかったか？";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "へっ、そうだよ、退屈な"+pchar.lastname+"船長。 "+GetSexPhrase("旦那","お嬢さん")+".";
			link.l1 = "ああ、もうこれを後悔し始めてるぜ……";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_Hire");
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "おい、お前はバカだな、若造 "+GetSexPhrase("男","女")+"！それにまったく判断力がないな。そのままじゃ長くは生き残れねえぜ。特にこの諸島ではな。";
			link.l1 = "お前がいなくても俺はやっていける、トミー。じゃあな。";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "本気か？ここで何人もの兵隊が死んだんだぜ、天才さんよ！たぶんすぐに別の部隊が来るだろうな。いや、 灯台の扉を閉めて防衛を組織することもできるが、やりたいかって？やる気はねえな。";
			link.l1 = "それで、どうするつもりだ？";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "ジャングルの洞窟で俺と会え。お前に俺の手間賃を稼ぐための猶予を二、三日やる――剣の扱いは分かってるだろうし、何とかできるかもしれねえな。";
			link.l1 = "本気か？そこじゃまるで袋の鼠だぜ。";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "俺を狙って大部隊で捜索された場合だけだな。だから大丈夫だと思うぜ。さて、もう行かないと――やつらがすぐ来る。じゃあ、またな。";
			link.l1 = "ああ、俺も念のために行かねえとな。";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "おう、そこにいたか！お前が金を稼げる奴じゃないんじゃねえかと思い始めてたぜ。時々思うんだが、 お前みたいな奴は生まれつきそういう才覚があるんだろうな。もしなけりゃ、 真面目な連中みたいに一日も働かずに貧乏のままくたばるだけさ。";
			link.l1 = "ほう、ほう、トミー。俺の船に入りたくねえなら、無理に誘わねえさ。 どうやらこの穴倉で巣作りするのが気に入ってるみてえだな。";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "「お前、アイルランドの雨季に穴に隠れたことなんてねえだろうな」 "+GetSexPhrase("若造","あたしの娘")+"！でも、ここに隠れているよりお前と一緒に行く方がマシだ。さて、その金の話だが…";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "「ほら、金貨だ。」";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "まだ手に入れてねえんだ。お前がどっかに逃げちまったかと思って確認しに来たのさ。";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(150);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "いいぞ、話が早いな！次はどうするんだ…船長？";
			link.l1 = "まずはこのじめじめした場所から出ようぜ、じゃねえと俺、くしゃみが出ちまう。";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "おい、戦争をやってみるといいぜ。こういう場所じゃ、まるで自分の家にいるみてえな気分になるんだ。";
			link.l1 = "なるほどな、辞職したからって、礼儀も上下関係も忘れちまったのか、トミー？心配すんな、 必要ならまた痛い目にあわせてやるぜ。さあ、行くぞ。";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "へっ、トミー・アイアンズは決して逃げねえぜ！約束は守る男だ。お前も自分の約束を守るつもりか？";
			link.l1 = "作業中だ。";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "金貨は持ってきたか？";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "「ほらよ、金貨だ。」";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "まだ手に入れてねえんだ。お前がどっかに逃げちまったかと思って様子を見に来たんだぜ。";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsJungleUhodit");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "聞いてくれ、船長…";
			link.l1 = "どうした、トミー？";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "弾薬を余分に持ってたりしねえか？ただの弾じゃなくて、ちゃんと紙で包んだ火薬包が欲しいんだ。";
			link.l1 = "またお前の冗談か？俺はいつもお前に弾丸やカートリッジを必要なだけ渡してるだろう。で、なんで一発だけなんだ？ 一握りじゃなくてよ。";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "なんでそんなに俺の頼みを嫌がるんだ？血の涙が出るような真珠をくれって言ってるわけじゃねえ、 ただ弾薬が欲しいだけだ。ちゃんとタイミングも見計らって、あんたの邪魔にならないように気を遣ったんだぜ、 狂人みたいに押しかけたりもしなかったし、へへ。\nで……弾、持ってるか？";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "ああ、一杯用意したぜ。ほらよ。その弾でくだらねえ悪ふざけはやめてくれよ。わかったな、トミー？";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "今は持ってないぜ。トミーが弾をくれって言うかもしれねえって思って、 ポケットに一発だけ入れて歩いてるわけじゃねえからな……";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "なるほど、いいところに気がついたな、さすがだぜ、へへ。しかし、ここでお別れってわけだな。";
			link.l1 = "本気か？弾一発で怒ってるのか？まあいい、船に行って手に入れようぜ。そんなに急ぎなら、俺が一発でも十発でも、 欲しいだけ用意してやるよ。";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "いや、結局お前には特別なところなんてないさ。いい船長なら、いつだって乗組員に必要なものを用意できるもんだ。 だから俺は行くぜ。";
			link.l1 = "もし俺たちが海の上でラム酒が切れて、お前がもっと欲しくなったらどうする？小舟の縄を解いて一人で漕ぎ出すか？ それとも海に飛び込むのか？";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "ハハハ！笑ったが、この悲しい時には、どんな冗談も役に立たねえ。さよならだ、退屈な船長。";
			link.l1 = "ちぇっ、もういいさ、トミー。じゃあな。";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "何も約束はできねえな、へっへっ。いい冗談は場を和ませるもんだぜ。だが、もちろん礼は言うぜ。";
			link.l1 = "よし、行くぞ、この野郎。";
			link.l1.go = "BM_IronsFirstJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
    			TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsFirstJungle");
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "おい、船長！";
			link.l1 = "「ああ、トミーか？」";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "もう一つ紙薬包はあるか？";
			link.l1 = "前の奴に何があったんだ？それと、カートリッジの冗談って何だったんだよ？ お前からくだらねえ冗談を二週間も待ってたのに、何もねえじゃねえか。";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "ああ、これは最高にウケる冗談になるぜ、信じてくれ。絶対に気に入るって、へへ。まだ全部まとめきれてねえんだよ。 で、火薬筒のほうはどうする？";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "ほらよ。次の悪ふざけ、心から楽しませてもらえるといいがな。で、最後の弾はどこにやった？ たっぷり渡してやったはずだぜ。まさか戦う用の弾と冗談用の弾を別々にしまってるのか？";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "お前のくだらねえ冗談のための弾薬なんか持ってねえぞ、トミー！二週間前にたった一発じゃなくて、 まとめて頼めばよかっただろうが！";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "やったぜ！俺の船長だと名乗る奴は、いつだって乗組員に必要なものを用意してくれると思ってたからな。";
			link.l1 = "俺は何かを装ってるわけじゃねえよ、トミー。ずっと前に自分らしく生きるって決めたんだ。 俺といて居心地がいい奴はそれでいいし、そうじゃなくても別にかまわねえさ。";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "へっ、そういう点じゃお前と俺は似た者同士だな。だが、俺の船長にはいくつか条件があるんだよ。そしてお前はもう、 その条件を満たしてねえ、若造。ここでお別れだぜ。";
			link.l1 = "本気か？俺がクソったれな紙薬莢を持ってなかっただけでってのか？";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "それは論外だ。俺は普段、人には好きなように生きて、欲しいものを手に入れろって言うんだがな。だが、 お前はこれからは自分の仲間のことをもっと考えた方がいいぜ。じゃあな。";
			link.l1 = "それと、自分の頭には気をつけた方がいいぜ――思ってるよりもひどくやられてるからな。じゃあな、トミー。";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "そのうち分かるさ。時が来ればな、へへ。";
			link.l1 = "ああ、嫌な予感がするぜ、トミー…";
			link.l1.go = "BM_IronsSecondJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
    			TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsSecondJungle");
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "お前に聞きたいことがあるんだ、船長。";
			link.l1 = "ああ、トミー、どうした？";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "分からなかったのか？推測するのは役に立つ技術だぜ、へへ。お前と俺、そしてこのジャングル……二週間ほど前にも同じ話をしただろう。もう一つ紙薬莢が必要なんだ。";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "これはすっかり恒例になってきたな、そうじゃねえか？もう二週間だ――トミーが弾薬をくれって言う。ほらよ。お前のその冗談のために、あと何発必要なんだ？";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "「あとどれくらいかかるんだ、トミー！？いつまで続くんだよ？ お前らアイアンサイドは戦いのたびに弾一発しかもらえねえのか！？お前の変なこだわりのために、 俺がいつも弾を持ち歩かなきゃならねえ理由なんてねえんだぞ、わかってんのか！」";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "実は、俺の船長なんだから、戦いに必要なものはもちろん、それ以上のものも全部用意するのがあんたの務めだぜ。";
			link.l1 = "トミー、お前は混乱してるぜ。船長の命令に従うのが義務だろう。俺はいつだってお前ら全員に必要なもの――薬も弾薬もラム酒も――全部用意してやってる。必要な時に自分で取りに来ず、あとで物乞いみたいな態度を取るのは完全にお前自身の責任だ！";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "お前は頭が切れるくせに、ここで今まで何も成し遂げてねえのはなぜだ？教えてやろうか。先のことを考えねえし、 何にも備えてねえからだ。自分が何してるかも分かっちゃいねえ、退屈な奴だ。 そんな奴を俺の指揮官だなんて認めねえからな、じゃあな。";
			link.l1 = "全く頭を使わねえな！せいせいするぜ、このクソ間抜け野郎！";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "これでいいな、へへ。";
			link.l1 = "やっと落ち着いたのか？だが、それが何のためだ？";
			link.l1.go = "BM_IronsThirdJungle_6";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
   				TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "ちょっとからかってみただけさ、お前がまた不機嫌な奴に戻るかどうか見てたんだ。へへ。まあ、弾薬はありがとな。";
			link.l1 = "トミー、お前の冗談は変だな。";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "それも冗談さ。集めてたんじゃねえ、選んでたんだ。ほぼ完璧な弾薬が必要だったんだよ。これで十分だ。ああ、 この弾なら、弾丸は遠くまで真っ直ぐ飛ぶぜ。昔、リアズリーの頭を吹き飛ばした時みたいにな、ははは！";
			link.l1 = "「老いぼれリーズリーって言ったな……フランキーの寝取られ野郎だろ？灯台で撃ったやつじゃねえか？じゃあ、お前らはずいぶん前からの知り合いってわけか？ 」";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "何だと？ああ、くそ、つい口が滑っちまった。でも気にしねえ――俺は嘘をついたり秘密を守ったりするのが昔から苦手なんだよ。";
			link.l1 = "二発目の弾は誰か特定の奴に向けたものだったんだろう、トミー？";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "そうだな、天才さんよ。俺は自分自身と自分の目的をちゃんとわかってるし、恥じることなんてねえ。 だからお前がどう思おうが気にしねえ――全部話してやるさ、どうせならな。";
			link.l1 = "さて、話してみろよ。お前が何を企んでるか知っても損はねえからな。";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "さて、いつものように口を挟むなよ。俺と一緒にいたのは二人のろくでなし――フランシス・リーズリーとガブリエル・キャロウだ。まったく、あいつらは本物のクズ野郎さ！ 俺の辞表をなかなか受け取らなかった机の上のネズミどもよりも、もっとタチが悪いぜ。";
			link.l1 = "それで、あいつらは何をしたんだ？特に二人目のカロウはどうだ。お前、あいつの女房とも寝たのか？それで、 あいつも兵隊を差し向けてきたのか？";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "黙ってろよ、いいな？まあ…別に構わねえけどな、へへ。でも駄目だ。あの日は王党派が俺たちを襲ってきたんだ。騎兵もいたぜ。 奴らの方がずっと多かった。ゲイブとフランキーは怯えたウサギみてえに逃げやがった。 でも俺は仲間と一緒に残ったんだ。生き残ったのは俺だけさ。子供の頃や若い頃のことはほとんど忘れちまったが、 あれだけは忘れねえ。";
			link.l1 = "「それで復讐したいってのか？逃げたからってよ。誰もが理想のために戦うわけじゃねえ。みんな生き延びたいんだ。 いや、ほとんどの奴はな。たとえ革命のために戦ってる奴でも、たまたま巻き込まれて後悔してるかもしれねえぜ。」\n";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "はっ、もし臆病者を全部狩ってたら、この世の全員を撃たなきゃならねえ。臆病者なんざ、くたばっちまえだ。だが、 奴らは俺を裏切った。俺が革命を裏切り、王党派の命令で仲間全員を皆殺しにしたって、 みんなに言いふらしやがったんだ。船長、一つだけお前に嘘をついてたことがある。";
			link.l1 = "何だ？フランキーがあんたを追ってるのは、あんたが奴の女房に手を出したからだって嘘ついたこと以外に何かあるのか？ ";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "いや、違う！嘘はついてねえ、全部を話さなかっただけだ。そこには違いがあるんだぜ。 俺が嘘をついたのは辞職のことだけさ。辞職なんてなかった。裁判があったんだ。そして運のいいトミーは――絞首刑にはされず、南方の植民地の採石場送りになったんだ。正確にはバルバドスさ。";
			link.l1 = "ああ、運が良かったな。何年そこで働いてたんだ？";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "なし。あのネズミどものせいで地上の法廷に裁かれたが、天の法廷は俺を見逃してくれたんだ。\n群島に入った途端、その空気を感じた――俺たちの船は海賊に乗り込まれたんだ。";
			link.l1 = "「じゃあ、バルバドスの採石場やプランテーションじゃなくて、海賊に奴隷として売られたってわけか？でも、 お前は採石場で働いたことはないって言ってたよな。」";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "俺が言った通りさ――誰かが天の上で俺を助けるって決めたんだ。まあ、すごい救出劇だったぜ、へへ！その通りだ――海賊たちが、縛られて鎖につながれた男たちを虐げるのが好きな連中をやっつけたんだ。でもな、戦いは激しかったぜ、 この太陽みたいに熱かった。しかも俺たちの救い主も犠牲を出した。だから、 望む者にはみんな仲間に入るよう声をかけてくれたんだ。";
			link.l1 = "それで、お前も奴らに加わったのか？海賊と一緒に航海したって言ってたじゃねえか。";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "ああ、もちろんだぜ！人生で最高の時期だった。ジャック・ミルズは本物の「船長」だったよ――いつかお前もああなれるといいな。俺はあいつの『クレーン号』で二年ほど航海してたんだ、あの時までは……";
			link.l1 = "…お前が言った通り、無法な生活に飽きるまでか？なぜそれが人生で一番良い時期だったと言うんだ？";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "ええ…あの二人の裏切り者も結局諸島に流れ着いたって話を聞くまではな。ああ、分かってるさ、 俺はお前に大海賊稼業にはもううんざりだって言ったし、他にもいろいろ言った。 お前がどう思おうと俺は気にしねえとも言ったな。それは今も変わっちゃいねえが、 最初に会ったときはお前のことをよく知らなかったんだ。どう反応するかも分からなかった。 だから違うことを言ったってわけさ。";
			link.l1 = "お前は嘘つきだな、トミー！まあいい、で、なぜ『クレーン』を離れたんだ？";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "ジャックは本物のリーダーだったから、たった一人のために遠回りもしないし、待ったりもしないし、復讐もしないし、 太った商船を襲う代わりにイギリス海軍の偉い将校と揉めたりもしないって言ったんだ。";
			link.l1 = "著名な士官たち？フランクは民間人だったと思うぜ。";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "ええ、あいつは最初からそういう奴じゃなかったんだ。ただ、なんていうか、昔からちょっと胡散臭かったんだよ。 それで誰かをハメようとして、恥をかいて追い出されたんだ。商船で働こうとしたけど、 真面目な仕事は性に合わなかったみたいだな。結局ここに落ち着いたってわけさ。";
			link.l1 = "あいつを立派な士官とはまだ呼べねえな。";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "ゲイブのことを忘れるなよ。あいつは故郷で中尉になったんだ。それにここポートロイヤルで『プリンシピオ』 号の船長として任命されたんだぜ。";
			link.l1 = "あまりイギリスらしく聞こえねえな。";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "いいところに気がついたな！この船は港の女みたいに持ち主が何度も変わって、いろんなことを見てきたんだぜ。だが、 今でもちゃんと航海できる。しかもゲイブのやつ、くそっ、腕の立つ船長だ。";
			link.l1 = "「それでジャックはあいつと関わるのを怖がったのか？本当にお前の言う通りすごい奴なのか？」";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "わかった、わかったよ！むしろ、あいつは俺のために時間を無駄にしたくなかったんだろうな。\nそういえばジャックのことで思い出したが、あいつから初めて見た伝統がいくつか気に入ったんだ――板渡りとブラックマークの配布さ。あの時、妙なアイデアが頭に浮かんだもんだぜ。";
			link.l1 = "黒い…印だと？黒い点（ブラックスポット）のことか？それで、どうしたんだ、トミー？ お前がブラックスポットを渡したとしても、あいつはどうしていいかわからなかったんじゃないか。そういうことか？ お前がそれを渡そうとしたら、あいつはお前の姿を見た途端に襲いかかってきた。だからお前は灯台まで逃げて、 あいつは兵士たちを引き連れて「お前は海賊だ」と言いながら追いかけてきたってわけか？";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "俺は「黒い印」と呼ぶ方が好きだな。その方が響きがいいだろう。\nただの黒い印じゃ、あいつも何も気づかなかったはずさ。だが、 俺たちの会社の特徴だった絹のハンカチで作った黒い印なら――あいつも分かるだろう。\nそいつをさりげなくあいつのポケットに忍ばせたんだ。それから、灯台へ向かうところをちゃんと見せてやった。\nあとのことは、もう知ってるだろう。";
			link.l1 = "「密輸業者たちは？」";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "間が悪かったな。ちょっとだけ同情しちまったぜ。まあ、ほんのちょっとだけだが、へへ。";
			link.l1 = "「フランキーには？」";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "今さらどうでもいいだろ？もっと大事なことがあるんだ。残るはゲイブだな。そいつが厄介だぜ。俺たちは……";
			link.l1 = "俺たちか？";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "まあ、面白い話を聞くのと、自分で物語を作るのは全く別物だぜ！\nだから、こうするぞ。ゲイブにもう一つ特別な黒印を残す必要がある――もう用意してあるんだ。\nそれから奴の足取りを追ってポートランド・コーブへ行き、跡を残さず片をつけるってわけだ。";
			link.l1 = "「で、俺たちはどこにそれを植えるんだ？」";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "ははは、だからこそ俺はジャックみたいになってほしいって言ったんだぜ、船長。さあ、つまらねえ顔すんなよ、 お前の目がギラギラしてるのは見えてるぜ！";
			link.l1 = "実は、あなたの話にけっこう興味があったんだ。";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "もちろん、あいつの家だよ！そんなの聞くまでもねえだろ？やつはポートロイヤルに腰を落ち着けてるんだ。 だから俺たちは入り江に船をつけて、もし何かあったらすぐ島を出られるようにしておくぜ。";
			link.l1 = "奴の家がどこにあるか知ってるか？";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "いや、知らねえよ。でも調べるのは簡単だぜ。酔っ払いどもに聞けばいい、 酒を一杯か二杯おごれば自分の母親だって売る連中さ。\nさて、俺の作戦はどう思う？";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "もし奴がジャマイカ行きの船の船長なら、島の海域で常に巡回しているはずだ。\n偽旗で襲う方が、町の中で何か仕掛けるよりずっとマシだぜ。";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "欠点がないわけじゃねえし、かなり運任せなところもある。だが、全体的にはやれそうだぜ。俺はお前の味方だ、トミー。 一人は片付けたんだ、もう一人も逃がせねえよな？";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "俺はお前の復讐には関わらねえし、こんな運任せの冒険のためにイングランドとの関係を危険にさらすつもりもねえぞ、 トミー。";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "お前は大胆な奴だな、船長！俺はお前のことが気に入り始めてるぜ。\nだが、あの古い『プリンシピオ』のゲイブは簡単な獲物じゃねえ――あいつはああいう船の他の船長なんかよりずっと危険だぜ。";
			link.l1 = "俺を何だと思ってるんだ、臆病者かよ、トミー？俺たちであいつの船に乗り込むぜ、お前がじっくり話してやれ。 奴が引きずり下ろされる直前に、ブラックスポットを渡してやれよ。";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "へっ、お前は腰抜けじゃねえかもしれねえが、あいつはそうさ。ただし頭は切れる野郎だ。 兵士や自分よりでかい船を持つ海賊には絶対に手を出さねえ。そんなのが地平線に見えたら、砦の陰に隠れやがるんだ。";
			link.l1 = "ふむ、商船はどうだ？";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "ああ、それならうまくいくかもしれねえ！だが、もう一度言うが、バークやバーケンティンよりでかい船はダメだぜ！ ゲイブはただの腰抜けじゃねえ――あいつは用心深さを犠牲にするほど欲深くなったことは一度もねえんだ。";
			link.l1 = "うまくいくといいな、トミー。さて、五等級のバークかバーケンティンで、スペインかオランダの旗を掲げている船だ。 昔の戦友に会う準備をしろよ！";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "お前なら頼りになると思ってたぜ！いつかジャックよりもいい船長になるかもしれねえな。それに俺の運も…ここまで来れたんだ、今回も信じるさ。\nじゃあ、行くとするか？";
			link.l1 = "ああ、あまり長引かせるのはやめようぜ。早く終わった方がいいからな。";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "へっ、俺は違うことを期待してたが、やっぱりな――こういうことをやる度胸はお前にはねえんだよ。 "+GetSexPhrase("若造","あたしの娘")+"。本物の船長なら、そういうネズミどもをこっそり始末した経験が何度かはあるもんだぜ。 時には自分の仲間のネズミさえもな。";
			link.l1 = "俺にその挑発に乗って、「気が変わった、本物の船長だって証明してやる」って言わせたいんだろう、トミー？でも、 お前の復讐心は分かるぜ。ジャックみたいに無理やりお前をクルーから追い出したりはしねえよ。 それにはどれくらい時間が必要なんだ？それまでに俺はジャマイカに着くからな。";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "ははは、お前も成長したな。まんまと引っかからなかったのは、ちょっと感心するぜ。だが、 もう待って俺を拾う必要はねえ――この件は自分でケリをつけるさ。結局、俺がずっと望んでたのは、自分のために何かしてくれる船長だけだったんだ。 じゃあな。イングランドのこと、頼んだぜ、ははっ。";
			link.l1 = "お前は本当に変わってるな。まあ、好きにしろ。じゃあな！復讐、うまくいくといいな、トミー。";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsThirdJungle_Otkaz");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "よし、ここからなら必要になった時すぐに退却できるぜ。これを持っていけ――ゲイブの住処と在宅時間が分かったら、この手紙と黒印を渡してくれ。";
			link.l1 = "おいおい、今度はお前が仕切るってわけか、トミー。でもな、俺はまだお前の船長だぜ。俺が町にいる間、 お前はどうするつもりだ？";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "へっ、そんなこと忘れるわけねえだろ、退屈船長。もしガブが俺を町で見かけたら、あの臆病者め、 警報を鳴らすか島から逃げ出すかどっちかだろうよ。心配すんな、ここで待ち伏せしてやるぜ、へへへ。";
			link.l1 = "待ち伏せだと？よし、トミー。お前の昔の戦友にふさわしい再会をしてやろうじゃねえか、はははは！";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "ひっく！こいつは最高のラムだな！ひっく……乾杯！";
				link.l1 = "聞けよ、相棒、この町でガブリエル・キャロウ船長について何か噂はあるか？";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "「ゲイブじいさん！？いい話しかねえよ！おっと、ひっく、なんだそりゃ？」";
			link.l1 = "「おお、本当か？それは良かった。さて、海賊絡みの厄介事があってな。司令官殿は主に陸のことを担当しているし、 旦那様にご迷惑はかけたくないんだ。」";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "だったら、すぐにゲイブのところへ行けって言ってるだろう！この町でゲイブほど正直で勇敢な船長はいないぜ。 ドイリー大佐でさえ、あいつを高く評価してるんだ。 ゲイブはかつてニコラス・シャープ本人が所有していた船に乗ってるんだぜ、信じられるか？";
			link.l1 = " 「まだそんなこと信じるほど酔っちゃいねえぜ、相棒。」";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "あ、ああ、そうだぜ！お前さんがそうだ！プリンシピオ号だ！ピンと来ねえか？";
			link.l1 = "スペインの戦利品の船か？なぜだ？";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "最後に自分の目でピンクのやつを見たのはいつだ、え？俺は本当のことを言ってるんだぜ、ひゃー！";
			link.l1 = "そうだなあ、その船の設計がそんなに珍しいものかどうかは俺には分からねえな。";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "でも本当なんだ！今じゃ、こんなガラクタを指揮する奴なんていねえよ、新しい設計の船が山ほどあるんだからな！ 造船所でも、もう三十年近く前に建造が止まったんだ！ニックが自分であの船を操ってたんだぜ、俺は断言するよ。";
			link.l1 = "よし、買おう。で、こいつがその船か。どうしてこんなボロ船がまだ壊れてねえんだ？";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "まあ、あの船も全盛期ほど速くはねえな――俺も酒をもう一杯やった後みてえによ、ははは！だが、 腕のいい船長ならこの婆さんからまだまだ引き出せるもんがあるぜ。 ゲイブも無理に危険な目には遭わせねえようにしてるさ。";
			link.l1 = "それで、なぜ船の名前が変わっていないんだ？例えば「陛下の軍艦スラッシング」とか、\n "+sStr+" 旧体制か？";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "伝…伝、伝、伝統だ、ひいっ！ニック本人はキューバのスペイン人プランテーションから逃げ出した後も、 あの船の名前を変えなかったんだ。あの体験を決して忘れたくなかったんだよ――スペイン野郎どもも同じさ！聞いてくれよ、テンダレス沖でのあの戦いはさ…";
			if (startHeroType == 4)
			{
				link.l1 = "テンデールズ、だろ？ふん、その名前を最後に聞いたのは俺がガキの頃だったぜ。 今じゃ誰もあの見捨てられた岩山のことなんて覚えちゃいねえと思ってたがな。";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "テンデールズ？それはどこだ？";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "それとも、ひぃ、高岩だったか？い、いや、絶対にそこじゃねえ……まあ、どっちでもいい！ニックはあのピンク色の船で戦い、勝ったんだ、信じられねえ勝利だったぜ。 相手はデズモンド・レイ・ベルトロップって海賊男爵が差し向けたブリッグ船カトルフィッシュだ。 長いこと血を流し合って、最後はニック自身がデズモンドを斬り倒したんだ。\n";
			if (startHeroType == 4)
			{
				link.l1 = "おったまげたぜ、こりゃすげえな！まあ、ニコラスならこれくらいやるだろうけどな。ええと、 シャープ家とベルトロップ家はいつも一緒だったり離れたり――どうやら歴史は時々繰り返すもんだな。\n";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "見事だな。で、シャープはどうやってその船と別れたんだ？造船所で売ったのか？";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "いや、違うぜ。あの拿捕の後で船が浸水し始めたから、ニックは見捨てたんだ。それで大潮の時に、 そのピンク船は町のすぐそばの岸に打ち上げられたんだよ。\n";
			link.l1 = "誰もあの難破船になんか興味なかっただろう。";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "おお、だが海軍は興味を持ったんだ！実利的な連中さ。イギリスの旗を掲げてるのにスペイン語の名前の船を見て、 不審に思ったんだよ。ニックは数年後に死んじまったが、あいつの船はその後も動き続けて、 持ち主が変わるたびに血なまぐさいやり方だったぜ。\n";
			link.l1 = "これはただの幽霊船の噂話さ。でもゲイブの船長ぶりは本物だぜ。だから、俺は彼に会いに行こうと思うんだ。あんた、 彼がどこに住んでるか知ってるか？";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "ははは！もちろん、ひっく、知ってるさ！みんな知ってるぜ！ガブじいさんは古い風車のそばに住んでるんだ。 酒場を回って上を見上げりゃ……ひっく！";
			link.l1 = "彼はいつ家にいるんだ？忙しい男みたいだな。";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "そうだぜ、相棒！あいつはやることが山ほどあるんだ。家にいるのは夜だけ、十時からだ。 それに毎日きっかり六時に自分で起きるんだぜ。鉄の規律ってやつさ！";
			link.l1 = "ありがとうございます！もう当分はこんな海賊話はたくさんだよ。";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "お前が本当に……ルンバなのか？噂は聞いたことがある……だが、自分の仲間に刃を向けたことは一度もなかったはずだ！";
				link.l1 = "俺はそんなことしてねえ。俺の恨みは祖国にあるんじゃねえ。お前だ、ゲイブ。";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "お前は商人じゃねえな……";
				link.l1 = "驚いたか、ゲイブ！お前は用心深い、いや臆病だと聞いていたぜ。強欲さで判断が鈍ったんじゃねえか？ 商人なら俺みたいに自分から白兵戦を仕掛けたりしねえよ。";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "俺と一緒に？何の用だ？俺の部屋でも、お前の部屋でも、ちゃんと話し合えるだろう、船長同士としてさ……って、お前、ここで何してやがるんだ！？";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "確かに。で、お前は誰だ？いや、くそ、どうでもいい。あれは誰だ……";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "「トーマス、お前か…？」";
			link.l1 = "ああ、そうだよ、ゲイブ。あの日お前が俺にしたことの報いを与えに来たんだ。";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "俺を罰するだと！？口の利き方に気をつけろ、トーマス！罰を受けるべきなのはお前だろうが！ 援軍を連れてくるって言ったのはお前だ！それなのに俺たちは、 王の騎兵の銃弾と剣の下で死にかけながら待ってたんだぞ！\n";
			link.l1 = "俺は必死で助けを呼びに走ったんだ！だが、別の忌々しい連中に追いつかれちまった！ チャールズのろくでもねえ手下どもがそこら中にいたんだ！奴らに囲まれて、危うく死ぬところだったぜ！ 俺が死んだと思われたのが幸いだったがな。だがな、ゲイブ、お前に言いたいことがあるんだ、俺が何を見たか分かるか！ ？";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "どうした、トム？この男に信じ込ませるためなら、どんな作り話でもするつもりか！？";
			link.l1 = "へっ、あいつはどうせ俺を裏切らねえよ。あんな奴らみたいなネズミじゃねえからな。";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "奴には選択肢がねえ！イギリス海軍の船を襲うなんてよ！";
			link.l1 = "ああ、最初から彼には選択肢があったんだ。そして、彼は俺を助ける道を選んだ。お前とフランキーにも選択肢はあった。 お前たちは死にたくなくて逃げることを選んだんだ。\nそれから戻ってきて、瀕死の俺を見つけた。\nそして裁判で卑劣な嘘をついた。俺が頭を殴られて記憶を失っていたから、 誰も俺の話なんて聞かないって分かってたくせに！";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "どうせ誰もお前の話なんか聞きやしなかったさ。お前は昔から……ダメな奴だったよ、トーマス。";
			link.l1 = "おお、あの日お前がやったことを隠す気はねえんだな。ガブ、お前に渡すものがあるぜ。黒い印だ。でもよ、 今さら渡しても意味ねえか。船は奪われちまったし、これからお前の腹をぶちまけるところだからな、ひひひひひひひ…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("BM_IronsClone5_function"); // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone8":
			dialog.text = "さて、ゲイブは追い落とされたぜ、へへへ。ずっと前から言いたかったんだよな。もうお前には聞こえねえのが残念だな、 相棒。あ、待てよ！地獄からなら聞こえるかもな。";
			link.l1 = "さあ、トミー。たとえ彼が聞いていなくても、見てわかってたはずだぜ――これがまさにお前の企みであり、復讐だってな。そして、奴にはどうすることもできなかったんだ。";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "へっ、あんたの言う通りだぜ！まったくだ！今回は助けてくれてありがとな。正直、 最初は派手な格好したお嬢ちゃんが遊び半分で船を手に入れたのかと思ってたんだ。でも、 あんたはすげえ船長じゃねえか！ジャックだってあんたには手こずるだろうよ。";
			}
			else
			{
				dialog.text = "へっ、あんたの言う通りだ！まったくその通りだぜ！今回助けてくれてありがとな。あんた、 ジャックと同じくらい腕のいい船長だと思うぜ。いや、もしかしたらそれ以上かもな！";
			}
			link.l1 = "おや、今のはお世辞だな。ありがとう。まあ、そういうことにしておくよ。";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "全然そんなことねえよ。お世辞なんか一切言ってねえ。見りゃ分かるだろ、 俺はめったに誰かをそんなふうに褒めたりしねえんだ。だから黙って、 俺がそこまで評価してるってことをありがたく思えよ。";
			link.l1 = "お前の言い方はあまり気に入らねえが、俺のことをいい船長だと思ってくれてるのは嬉しいぜ。だがな……指揮系統だ、トミー、指揮系統ってやつを忘れるなよ。";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "おい、頼むぜ！これまで一緒に乗り越えてきたことが、俺たちをもっと近づけた気がするんだ、エリー。 俺たちはただの船長と士官以上の関係になれるかもしれない。認めてくれよ――たとえ自分だけにでも、お前も感じてるだろう。";
				link.l1 = "お前の妄想の中だけだぜ、トミー。それに、私はエリーじゃなくてヘレンだ。でも今は「ルンバ」と呼んでもいいぜ。";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "おいおい、つまんねえ野郎だな！もう俺たちはただの船長と士官じゃなくて、本当の友だちになったと思わねえか！？";
				link.l1 = "へっ。まあな。お前の敵になるより、味方でいた方がマシだぜ。それに礼儀なんてお前には無縁みたいだし、 俺も慣れるしかねえってことだな。";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "「お前に……プレゼントがあるんだ、船長。」";
			link.l1 = "おい、見ろよ！黒い印か？お前も俺を船長の座から引きずり下ろしたいのか、トミー？自分が船長になりたいってか？ はははは！仲間だって言ってたじゃねえか。";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "それは黒い印だぜ、この野郎。なあ、俺はな、 このスカーフにドクロと骨を刺繍した途端に運が向いてきた気がしてるんだ。説明はできねえけどな。持ってけ。あとよ……もし欲しけりゃ、俺の頼りになる剣と鎧も貸してやるぜ……残ってる分だけだけどな、はは！役に立つはずだ！お前はきっと大物になる。俺はその目撃者になりてえんだ。 流れ弾なんかで死ぬんじゃねえぞ。";
			link.l1 = "ありがとう、相棒！俺も全力を尽くすぜ。お前も見てて感心しな、ははは！";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "感心するのか、ははは。ああ。で、この船をどうするつもりだ？一方では、もうあまり役に立たねえ。だが、 他にこんな船はもうねえんだ。今後も二度と現れねえだろうよ。";
			if (startHeroType == 4) 
			{
				link.l1 = "まだ決めてねえ……なあ、トミー、この船には何か縁を感じるんだ。うまく説明できねえけどよ。だから、 まずはこの腐った死体を片付けようぜ。船倉に浸水がなけりゃ、多分この娘は俺がもらうつもりだ。";
			}
			else
			{
				link.l1 = "わからねえよ、トミー。まだ決めてねえんだ。その間に、ゲイブの死体を片付けようぜ。 船を手元に残すことになった時のためにな。";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "よくやったな、その古びた船での働きは見事だったぜ、船長！ガブをこの手で始末したかったが、 この勝利を貶めて創造主を怒らせるわけにはいかねえ。";
			link.l1 = "それは必要ないさ、トミー。今はお前の魂が安らかであることを願うぜ。";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "俺たちがこれまで経験してきたことが、エリー、お前と俺をもっと近づけた気がするんだ。\n俺たちはただの船長と士官以上の関係になれるかもしれない。\n認めてくれ――たとえ自分の心の中だけでも、お前も感じてるはずだろ。";
				link.l1 = "夢の中だけだぜ、トミー。それに、私はエリーじゃなくてヘレンだ。でも、お世辞をやめてくれるなら、 今はルンバと呼んでもいいわよ。";
			}
			else
			{
				dialog.text = "こんなに幸せだったことは今までないよ！助けてくれて本当にありがとう。\nねえ、君はジャックと同じくらい立派な船長だと思うよ。いや、それ以上かもしれない！";
				link.l1 = "おや、お世辞を言ってくれるんですね。比べてくれたことにも一応感謝しますよ。";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "全然そんなことはない。お世辞なんかじゃねえよ。もう気づいてるかもしれねえが、 俺はめったに誰かをそんなふうに褒めたりしねえんだ。だから黙って、俺がそこまでお前を評価してることを喜んでおけ。 ";
				link.l1 = "お前の言い方は好きじゃねえが、俺のことをいい船長だと思ってくれてるのは嬉しいぜ。だがな……指揮系統だ、トミー、指揮系統ってやつを忘れるなよ。";
			}
			else
			{
				dialog.text = "全然違うぜ。お世辞なんかじゃねえ。もう気づいてるだろうが、俺はめったに誰かをそんなふうに褒めたりしねえんだ。 だから黙って、俺がそこまでお前を評価してることを喜んでおけ。";
				link.l1 = "お前の言い方は気に入らねえが、俺のことをいい船長だと思ってくれてるのは嬉しいぜ。だがな……指揮系統だ、トミー、指揮系統ってやつを忘れるなよ。";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "おいおい、つまんねえ野郎だな！俺たち、もうただの船長と士官じゃなくて、本当の友達だと思わねえか！？";
				link.l1 = "へっ。まあな。お前の敵になるより味方でいた方がマシだぜ。それに礼儀なんてお前には無縁みてえだし、 俺も慣れるしかねえな。";
			}
			else
			{
				dialog.text = "おいおい、つまんねえやつだな！俺たちはもう単なる船長と士官じゃなくて、本当の友達だと思うぜ。そう思わねえか！？ ";
				link.l1 = "へっ。まあな。お前の敵になるより、味方でいた方がマシだぜ。それに礼儀作法なんてお前には無縁みたいだし、 俺も慣れるしかねえな。";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "「お前に……プレゼントがあるんだ、船長。」";
			}
			else
			{
				dialog.text = "「俺からの……プレゼントがあるぜ、船長。」";
			}
			link.l1 = "おい、見ろよ！黒い印か？お前も俺を引きずり下ろしたいのか、トミー？自分が船長になりたいってわけか？はははは！ 仲間だって言ってたじゃねえか。";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "それはブラックマークだぜ、この野郎。なあ、俺はな、このスカーフにドクロと骨を刺繍した途端、 運が向いてきた気がしてるんだ。説明はできねえけどな。持っていけ。\nそれと…もし欲しけりゃ、俺の頼りになる剣と鎧も貸してやるぜ…残ってる分だけだけどな、ハハッ！役に立つはずだ！お前はきっと大物になる。俺はその目撃者になりてえんだ。 流れ弾なんかで死ぬんじゃねえぞ。";
			link.l1 = "ありがとう、相棒！俺も全力を尽くすぜ。お前も見てて、感心しろよ、ははは！";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			Notification_Reputation(true, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "そんなものを信じる奴なんているかよ……すまねえ、お嬢さん。 "+TimeGreeting()+"。どうされましたか？とても心配そうですね。";
			}
			else
			{
				dialog.text = "何だ？こんな夜更けに誰が来たんだ？ずいぶん心配そうな顔をしてるな、旦那。どうしたらいいんだ？";
			}
			link.l1 = "お休みのところ失礼します、Callow船長。私の名は "+GetFullName(pchar)+"、そして俺はあんたのかつての戦友の代理で来たんだ。";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "どの仲間のことだ？俺には旧世界にも新世界にもたくさん仲間がいたんだ。";
			link.l1 = "最初は、あんたのトランクのひとつに何かを残すつもりだったんだ。\nあるいは、もっと早く気づくようにテーブルの上に置こうかとも思った。\nあんたの過去に関わる男のことだ。\nほら、自分で見て読んでみな。";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "黒い印だと？俺の仲間に海賊なんていた覚えはねえな。もしかして、誰かがそんな道に落ちちまったのか？黒い絹だと？ まさか……ああ、トマス。あんたみたいな男があの悪党と関わりがあるなんて、驚いたぜ。";
			link.l1 = "申し訳ないが、あいつを悪党呼ばわりする資格はお前にはないぜ。お前は戦場から逃げ出して、トムを中傷したんだ。 あとで悔い改めて、この群島で模範的な士官になったかもしれねえが、過去は変わらねえよ。";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "あいつがそんなことを言ったのか？別に驚きゃしねえ――あいつはいつだって話をでっち上げるのに都合のいい奴を見つけるのが上手かったからな。トマスは口が達者だったんだ。 お前はあいつのことも、本当の話も、これから自分が何に巻き込まれるのかも知らねえだろう。教えてやるよ――どうせもう眠れそうにねえしな。";
			link.l1 = "耳を傾けるのは悪くないことだ。続けてくれ、Callow船長。";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "それで、トーマスは俺が逃げて、さらに奴を中傷したって言ってるのか？いや、実際は逆だったんだぜ！ 王の騎兵隊が近づいてきたとき、トムは「援軍を呼んでくる」と言いやがった。それで俺たちは退却せずに待ったんだ。 結果、俺たちの部隊は全滅した！あいつが約束した援軍を待たずに撤退していれば、生き残れたかもしれねえ！結局、 生き残ったのは俺とフランキー、そして忌々しいトーマスだけだったんだ。";
			link.l1 = "「つまり、お前の言いたいことは……」";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "俺が言いたいのは、うちの仲間の血はトムの手にもロイヤリストどもの手にも等しく付いてるってことだ。\nあいつが流刑で済んで、首吊りにならなかっただけでも運が良かったんだぜ！\nそれなのに、恨みを抱いて俺に決闘を挑むとはな！\nあんな奴にそんな価値はねえよ！";
			link.l1 = "行かないつもりか？それが何を意味するかわかっているだろう。名誉の掟は誰にでも適用されるんだ。";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "もちろんだ。だからこそ俺が行くんだよ。トムのかつての軍での功績のせいで、我々 の共和国の法廷がやり遂げられなかったことを終わらせる必要があるんだ。\nそれに……お前はまともな奴に見えるぜ。忠告しておくが、付き合う相手はもっと慎重に選んだほうがいい。 トムやああいう連中には関わるなよ。";
			link.l1 = "だが、トマスは今や俺の部下で、俺の船の士官なんだ。 "+GetSexPhrase("俺があいつを見張っておくぜ。もしお前とのやり取りで生き延びたら、これ以上恥をかかせねえようにするさ。","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "俺の立場だったらどうする、キャロウ船長？";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "ええ、もしトムの話でお前が納得したんなら、あいつはまた同じことをやってのけるだろうよ。";
			link.l1 = ""+GetSexPhrase("しかし名誉の掟により、俺はあいつを裏切ることはできねえ。俺は","俺は")+" 俺の部下たちの責任は俺にある……あいつのようにはならねえ。これからは、もしあいつが生き残ったら、もっと注意深く、そして厳しく接するぜ。";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "難しい決断だな。しかし、お前の考えを変えようとはしないぜ。じゃあ、さらばだ。 "+GetSexPhrase("旦那","お嬢さん")+" - まだトムに会う準備をしなきゃならないんだ。";
			link.l1 = "さようなら、Callow船長。";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "正義を成し遂げよう！トマスを倒すのを手伝ってくれ、 "+pchar.lastname+"。奴は稀に見る悪党で臆病者だが、射撃の腕は一流だ――簡単にはいかねえ。だが、俺たちが力を合わせれば…";
			link.l1 = "ふむ、トマスを倒すのを手伝えって？そんな決闘に大した名誉があるのか？お前たちで決着をつけろよ、 俺は口出ししねえ。";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "あいつのことを考えれば、公平な決闘なんて望めそうにねえな。中立を貫くってのは、不正を黙認するのと同じだぜ。 違うか？";
			link.l1 = "どうやらお前の方が俺よりトムのことをよく知っているようだな、そしてあいつの本性もな。お前の言う通りだ――あいつはすでにポートランド湾で待ち伏せの準備をしていて、俺の協力を当てにしている――今のお前と同じようにな。";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "それなら決闘じゃなくて、ただの乱闘だ。しかし俺たちが自分でトマスを殺すつもりはない。逮捕するんだ！ 俺が兵士を連れてきて、旧世界で果たせなかったことをここで終わらせる。もしまた奴を無罪にしようとするなら、 大佐に手紙を書くか、いっそここに呼んで裁判させるさ。トマスが武器を捨てないなら、それは自業自得だ。";
			link.l1 = "そっちのほうがずっといいな。";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "「それは良かった」 "+pchar.lastname+"！このような決断を下すのは簡単ではないかもしれないが、安心してくれ、君は正しい選択をしたんだ。\nそしてその確信のために、俺がもう一つ手助けしてやろう。";
			link.l1 = "どうしたんだ、Callow船長？";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "ほら、これを持っていけ。ただの贈り物じゃなくて貸しだぞ――トマスは言った通り、腕の立つ戦士だからな。まともな武器で相手した方がいい、錆びた鉄くずじゃなくてな。 この逸品はドイリー大佐本人からもらったんだが、本気の戦いなら俺はいつだってブロードソードを選ぶぜ。";
			link.l1 = "確かに、素晴らしいレイピアだ。ありがとう。";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "礼なんていらねえ――貸してやるだけで、くれてやるわけじゃねえのを忘れるなよ？さあ、入り江へ行って、 トムと一緒にお前の役目を果たしてこい。俺は増援を集めてから向かうぜ。そこで会おう。";
			link.l1 = "そこで会おう、Callow船長。";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			Notification_Reputation(false, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "あんた誰だい、お嬢さん？住所を間違えてるんじゃないか。俺は、えっと、泊まりのサービスなんて頼んでねえぞ。";
				link.l1 = "ヘレン・マッカーサーよ。それから、欲望は抑えてちょうだい、カロウさん。私は真面目な娘なの。ここの気候のせいで、 夜でも暑く感じるわ。見知らぬ娘にそんなことを言って、恥ずかしくなかったの？ あなたは模範的な士官だって聞いているのよ。";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "お前は誰だ、何の用だ？そのニヤついた顔が気に入らねえぞ、旦那。";
				link.l1 = ""+GetFullName(pchar)+"。しかも、お前はあまり親切じゃねえな、カロウ旦那。";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "この時間に見知らぬ者への挨拶の仕方が違うのか？";
			link.l1 = "他の時には家にいないと聞いた。";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "もちろん私は違う――私には仕えるべき主も、義務も、正直な労働もある。君の身なりを見る限り、そういった言葉は君には縁がなさそうだな。 ";
			link.l1 = "なんて自信満々なんだ！まあ、 そうじゃなきゃドイリー大佐や他の連中に誠実さを信じさせることもできなかっただろうな。俺はお前に用はねえが、 お前の古い知り合いが用があるらしい。ほら、これだ。";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "納得したか？ゲイブ？おい！黒い印だと？ってことは、お前は海賊か？ちょっと待て……黒い絹……まさか……ああ、そういうことか。トーマス、この野郎、まだ俺とフランクがチクったことを根に持ってやがるな、はははは！";
			link.l1 = "おい！トムは俺の船の士官で、敬意を払うべき男だ。奴はこの諸島でも屈指の射撃手なんだぜ。";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "あいつが下手な射手だなんて言ってねえよ。だが、お前はトーマスのことをよく知らねえみたいだな。あいつこそ、 俺たち全員を裏切った張本人だぜ。だが、お前と話しても無駄みてえだな――どうやらお似合いの二人ってわけだ。";
			link.l1 = "俺は興味ねえ。お前の話なんざドイリーやあの世間知らずどもにでも聞かせてやれ。噂通り勇敢で誇り高いってんなら、 この挑戦を受けて今すぐ来いよ。どうだ、受けるのか？";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "ああ、そうだそうだ。さっさと俺の家から出ていけ、衛兵を呼ぶ前にな。";
			link.l1 = "喜んでやらせてもらうよ、Gabe。";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "なんでそんなにビクビクしてるんだ？怖いのか、それともどうした？";
				link.l1 = "誰だってマスケット銃を持った男が突っ込んできたらビビるさ――最初はお前だと気づかなかったぜ。ここで何してるんだ、トミー？";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "どうだったんだ？おいおい、なんでそんな目で俺を見るんだよ？びっくりしたぜ、へへへ。";
				link.l1 = "誰が誰を脅かしてるんだ！誰があんなふうに逃げていくんだよ！？入り江で客人を迎えるって約束しただろうが！";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "へっ、まあ、そうかもな。俺は待つのに飽きちまったんだ――あんたと、そしてご親切な客人たちをな。だから、ここが本物の待ち伏せにはうってつけだと判断したのさ。結局、 俺は狩人であって、決闘士じゃねえからな。";
			link.l1 = "なるほど。";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "ああ。で、俺の贈り物はゲイブの家に置いてきたのか？ずいぶん時間がかかったじゃねえか。 俺なら町に入れりゃもっと早かったぜ。どうした、船長？何をキョロキョロしてやがる？何かあったのか？";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "（信頼できる）俺は不安だ。ゲイブは臆病者だが、馬鹿じゃねえ。 もし奴の代わりに兵士の小隊が丸ごとここに来たらどうする？それとも、 入り江に近づいて先に俺たちの船を沈めるかもしれねえじゃねえか？\n";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				Notification_Perk(true, "Trustworthy");
			}
			else
			{
				link.l2 = "ゲイブに見られた。俺は逃げなきゃならなかった。";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				Notification_Perk(false, "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "へっ、わかってるさ――俺だって正直うまくいくか自信ねえよ。こんな大事があんたに起きるのは初めてだろ？大丈夫だ、よくあることさ。 全部俺が考えてある。兵隊がゲイブ抜きで来たら、俺たちはさっさと逃げる。ゲイブを連れて来たら、 俺があいつの眉間に鉛玉ぶち込んで、やっぱり逃げる。それに、もし船が湾に来たら、マルーンタウンまで走る――あそこには奴らも手出しできねえし、それから次の手を考えるってわけだ。";
			link.l1 = "トミー、お前は本当に何もかも考えてあるんだな。";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "もちろんだ。さあ、客人を待とうじゃねえか…";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "はは、お前が盗賊として優秀なのは、俺が王党派であるのと同じくらいだな。だが、なぜ俺の目を見ようとしねえんだ……船長？ガブと話してたんじゃねえのか？";
			link.l1 = "いや、何を言ってるんだ？俺があいつに話しかける理由なんてあるか？";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "お前らは口だけだからな。口ばっかりで行動しねえ。で、俺たちの親愛なるゲイブが何を話したんだ？";
			link.l1 = "トミー、それが重要か？";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "正直に言うと、違うな。裏切らなければ話は別だが、どうやらもう裏切ったみたいだな。あいつに言いくるめられて、 そっちの味方になったんだろう？";
			link.l1 = "いや、違う。トミー、銃を下ろせ。約束する、取り返しのつかないことにはならない。 お前は採石場で働くことになるかもしれないが、ガブに情けをかけてくれるよう頼んでみる。 必要ならドイリー大佐にも頼んでみるさ。";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "なんて親切な奴だ。石切場で何年も働かされた挙句、今さら情けをかけてくれるってか？ 俺はもう二度と監獄船には戻らねえ。絶対にな。 そしてお前……やっぱりただのネズミ野郎だったか。お前の面構えで分かったよ。まずはお前から片付けてやる。そうすりゃ、 後でゲイブの始末も楽になるからな。";
			link.l1 = "お前のせいで他に選択肢がねえんだ！";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "「ほう、もうやってしまったんだな。」 "+GetSexPhrase("旦那","お嬢さん")+"。それで俺は仲間を集めていたんだ、数で優位に立てばトムも考え直して武器を捨てると思ってな。";
			link.l1 = "「ずいぶん時間がかかったな、Callow船長。」";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "言っただろう、俺は人を集めてたんだ。うちの守備隊の中でも腕利きばかりだぜ。トムは何しろベテラン兵士だからな。……だが、こんな話を誰にしてるんだ俺は？よくやったな。 "+GetSexPhrase("旦那","お嬢さん")+" "+pchar.lastname+". "+GetSexPhrase("俺はお前を誇りに思うぜ、若造","正直に言うと、あなたは美しさ、知性、そして腕前を兼ね備えているね、お嬢さん")+"。最初に会ったときにも言ったが、お前は正しい決断をしたんだ。これで正義が果たされたな。";
			link.l1 = "うまくいったな。誇らしい気分か？";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "俺はベテランの兵士じゃねえが、戦うことはできるんだ、今見てわかっただろう？だが、ありがとう、旦那。 俺にとって正義ってのは口先だけの言葉じゃねえんだ。";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "「それは立派なことだ」 "+GetSexPhrase("若者","お嬢ちゃん")+"。しかし、この素晴らしい一日を締めくくるために、もう一つやるべきことが残っているんだ。";
			link.l1 = "ふむ、それは何だ？トムはもう倒されたんだぜ。";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "俺の物を持ってるな。俺の美しいイタリア製レイピアを返してくれ、頼むぜ。\nただのつまようじじゃねえんだ、これは思い出の品――ドイリー大佐本人からの贈り物なんだよ。";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "ええと……そのことなんだが、カロー船長……レイピアはもうないんだ。失くしちまった。すまねえ。";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "ああ、もちろんです。どうぞ。盗むつもりはなかったんです。ただ、正直に言うと手元に置いておきたかった。でも、 はい、カロー船長。";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "もっといい提案があるんだ、船長。";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "「でもお前はさっきそれを楊枝って呼んだじゃねえか。それに、レイピアなんて好きじゃねえって言ってたろ。 俺は逆にご褒美もらうに値するぜ。」";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "誰だってこんな美人を手元に置いておきたかったはずだ！返してくれてありがとう。 君の立場なら意地を張る奴も多かっただろうな。";
			link.l1 = "お前のものだ。これで終わりだな？";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "興味はねえ。ただレイピアを返してくれりゃ、それで円満に別れようじゃねえか。 "+GetSexPhrase("旦那","お嬢さん")+" "+pchar.lastname+".";
			link.l1 = "このレイピアがあんたにとって大事なのは、歴史ある武器が好きだからだろう？違うか？俺も同じものを持ってるが、 これは引き出しにしまっておくより、身につけていたい一本だよな。";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "そうかい？まあ、話がまとまるとは約束できねえが、聞いてやるぜ。俺は確かに歴史ある武器には興味があるんだ。だが、 このレイピアは大佐からの贈り物なんだ。だからこそ、俺にとっては特別なんだよ。";
			link.l1 = "お前は幅広の剣が好きだと言ってたな。ほらよ。これは俺たちの親友トミーのものだったんだ。何年もの間、 この武器がどんな修羅場をくぐってきたか想像してみろよ。そして、 お前の手でこれからもどんな冒険を重ねていくのかもな。";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "お前はなかなか説得力があるな、若造！トマスの剣を振るうとは……皮肉なもんだ。まあいい、レイピアを持っていけ。ただし、そう簡単に手放すわけじゃねえぞ。";
			link.l1 = "合意に至れて嬉しいです。これでお別れですね、Callow船長？";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "何だと！？どうやって……どうやって丸ごと一本のレイピアを失くすんだよ！？お前はバカか！";
			link.l1 = "落ち着けよ！ただのレイピアだろ。どうせお前は使わねえさ。トムは死んじまった――今はそれだけが重要なんじゃねえか？";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "レイピアだけだと！？あれは俺の宝だったんだ！ドイリー大佐ご本人からの贈り物だぞ！使ったことがなくても関係ねえ！ ";
			link.l1 = "「だったら俺に渡すんじゃなかったんじゃねえか？」";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "今は黙っていたほうがいいぜ。 "+GetSexPhrase("旦那","お嬢さん")+" "+pchar.lastname+"。穏便に別れることもできたんだ。しかし今となっては……今こそお前に思い知らせてやりたいぜ、 "+GetSexPhrase("若者","お嬢ちゃん")+".";
			link.l1 = "墓場にはあんたみたいな教師が山ほど埋まってるぜ。";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "もちろんだ。しかし、手を貸したからといって士官の私物である武器を勝手に持っていくわけにはいかねえだろう？";
			link.l1 = "俺も同意したいが、お前はどうせ使わねえだろう？部屋の釘にぶら下げておくだけさ。だが俺なら、 ちゃんと役に立ててやるぜ。ドイリー大佐がそれをなくしたかどうかなんて、いちいち調べたりしねえだろ？";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "これは議論の余地はないぞ、若造。最初から言ったはずだ、これは贈り物じゃない。レイピアを渡せ。今すぐだ。";
			link.l1 = ""+GetSexPhrase("俺はお前のおもちゃの兵隊じゃねえ","俺はお前らの港の売女じゃねえ")+"、お前の命令なんか聞く気はねえ。俺もお前と同じ船長だ。このレイピアは俺のもんだ、気に入ろうが気に入るまいがな。 ";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "トマスにずいぶん影響されたようだな。そんなに欲しいなら、そのために死ねよ。";
			link.l1 = "俺もまったく同じ考えだぜ！";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "ほら、これを持っていけ。俺には全く必要ねえ。今日の記念にしな。これからはもう少し騙されやすいのを直せよ。 それから、トマスみたいな悪党に汚い仕事へ巻き込まれるんじゃねえぞ。";
			link.l1 = "へっ、俺に黒い印を渡すつもりか、Callow船長？";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "「まあ、俺たち二人とも海賊じゃねえよな」 "+pchar.name+"？これを教訓にしろ。気をつけろよ、この群島にはお前のような男が必要なんだ。 "+GetSexPhrase("もしかしたら、海軍に入隊することを勧めて、ドイリー大佐への推薦状を書いてやってもいいかもな……","")+"";
			link.l1 = "申し訳ありませんが、お申し出はお受けできません、船長。";
			if (startHeroType == 3)
			{
				link.l1 = "ふむ。よく考えてみるとしよう。じっくりとな。";
			}
			if (startHeroType == 4)
			{
				link.l1 = "さらばだ、旦那。";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "好きにしな。じゃあ、さらばだ。 "+GetSexPhrase("旦那","お嬢さん")+" "+pchar.lastname+"。お前にはアイアンサイド号の残骸を持つ資格がある。さらばだ。";
			link.l1 = "さらばだ、旦那。";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "「その口のきき方、気に入らねえな」 "+GetSexPhrase("旦那","お嬢さん")+"。で、何が言いたいんだ？";
			link.l1 = "わざと時間を稼いで「精鋭」を集めていたんだな。何のためだ？たった一人を捕まえるためか？ 街を巡回している兵士を何人か連れて、すぐに俺の助けに来ればよかったんだ！";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "雑兵を連れてくるだと！？トムはあいつらみたいなただの市警じゃねえ。全く違う訓練と経験を積んでる――あいつは俺と同じく血塗られたアイアンクラッドなんだぜ！どうしてそれが分からねえんだ？";
			link.l1 = "ああ、逆にちゃんと分かってるさ。だからこそ、俺とお前はここにいたんだ――トムと刃を交えて、奴を生け捕りにするためにな。しかも、お前もアイアンクラッドだろ。同じ仲間じゃねえか。まさか、 奴と直接やり合うのが怖かったのか？";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "俺を臆病者呼ばわりするとは、若造め "+GetSexPhrase("男","お嬢さん")+"！誰に聞いても、この街のために俺が成し遂げた偉業について詳しく話してくれるぜ。";
			link.l1 = "俺はまだ終わっちゃいねえ。そもそも、その“武勇”とやらが本当にお前自身の手で成し遂げられたのか疑い始めてるんだ。お前はトムと俺を殺し合わせて、 全部の手柄を独り占めしたかったんだろう。前にもそうしたことがあるんじゃねえか？";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "「お前の非難はもううんざりだ」 "+GetSexPhrase("旦那","お嬢さん")+" "+pchar.lastname+"。争いが欲しいのか？今すぐにでも相手してやるぜ。";
			link.l1 = "真実は辛いよな、ゲイブ？";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "ゲイブ！久しぶりだな、何度も寒くて暗い冬を越えてきたじゃねえか！それにお前、 相変わらずその生意気な面してやがるな、くそっ！";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "トマス！今日はついに俺自身の手で、長年司法が果たせなかったことを成し遂げられると思うと嬉しいぜ。\nそれに、今日は機嫌がいいから、武器を捨てて俺たちと一緒に来ることを許してやる。\nもしかしたらお前は強制労働に送り返されるかもしれねえ。その時は、俺が直々に送り届けてやるよ。";
			link.l1 = "へっ、やれるもんならやってみろよ！お前の隣にいる二、三人の野郎どもが俺を止められると思ってんのか！！！";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "「俺と一緒にいるのがあいつらだけだなんて、誰が言ったんだ？今まさにお前の隣に立ってる奴のことを言ってるんだぜ。 」";
			link.l1 = "何だって？";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "トマス、トマス、トマス……お前はいつも通り、この世でひとりぼっちだな。ちょっと同情しちまうぜ！";
			link.l1 = "ちくしょう、クソ野郎どもめ！";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "それはどういう意味だ！？あいつは何を言いたかったんだ！？";
			link.l1 = "トミー、聞いてくれ……";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "まさにその通りだ！あいつが嘘をついてるって言ってくれ！";
			link.l1 = "残念だが、彼の言う通りだ。武器を捨てろ。今日は誰も死ぬ必要はない。俺が直々に口添えしてやるから、 絞首刑にはならねえよ。いつか真っ当な人生に戻ることもできるさ。";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "それを決めるのはお前じゃねえ！ましてやお前でもねえ！あんな指揮官がいりゃ、敵なんか必要ねえだろ！ またしても血塗れのクソ野郎だ。";
			link.l1 = "行くぞ、トミー。お前みたいな奴にきれいな逃げ道なんてねえんだよ。";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " お前の船の乗組員の一員として居場所をもらえれば、それが始まりだったんだ。だがな、 お前が仲間のために立ち上がる気があればの話だ！だがもうどうでもいい。くたばれ、全員！ この臆病者どもの腹をぶちまけてやる、てめえみたいな小賢しいネズミもな。それからお前もだ、ゲイブ、 道連れにしてやるぜ……";
			link.l1 = "待て、トミー、やめろ！";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "「おめでとうございます。」 "+GetSexPhrase("若者","お嬢ちゃん")+"！お前がトマスにすべてが自分の計画通りだと思わせたとは感心したぜ。あいつは裏切りの気配には敏感だったからな。";
			link.l1 = "ああ、ありがとうございます、Callow船長。";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "「何か悩み事でもあるのか、 "+GetSexPhrase("旦那","お嬢さん")+" "+pchar.lastname+"?";
			link.l1 = "トムは……俺があんたの味方だったことにただ怒っていただけじゃねえ。 あいつの声には本物の絶望と理解できねえって気持ちがにじんでた、まるで……";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "…まるで自分が被害者であるかのような態度だな。予想通りだ。覚えておけ、チャールズ、 怪物だって痛みを感じることはある。だが、それで怪物でなくなるわけじゃない。多くの犯罪者は、 自分が正しいと本気で信じているし、無実だと思い込んでいるものさ。";
			link.l1 = "それを覚えておくようにするよ。ここで話は終わりだと思うが、どうだい、船長？";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "概ねそうだが、この素晴らしい一日を締めくくるために、もう一つやるべきことが残っているんだ。";
			link.l1 = "おや？何だ？";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "ずいぶん時間がかかったな。だから俺がちょっと偵察しておいたぜ。\nまあ、浜辺で気取った決闘ごっこをするより、ここで待ち伏せした方がいいと思うんだ。\nちゃんとゲイブの家を見つけて、全部目立つように置いてきたんだろうな？";
			link.l1 = "もちろんやったさ、俺を何だと思ってるんだ、バカか？実は俺がお前の船長なんだぜ、トミー。もしバカに仕えてるなら、 お前は何になるんだ？";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "ハハハハ、俺が任務でそんなくだらねえことにどれだけ付き合わされたか、信じられねえだろう！だが、 今回は幸いそんな状況じゃねえ。さてと、客が来るぞ。準備はいいか？";
			link.l1 = "まあ、ポートロイヤルの艦隊全体か守備隊がここに現れない限り、俺は準備万端だぜ。";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "トーマス？やっぱりお前だったのか……";
			link.l1 = "もちろん俺だよ、他の誰かを期待してたのか、ゲイブ？へっ、お前、まるで幽霊でも見たみたいに顔色が悪いぜ。 イングランドにいた頃よりも太ったんじゃねえか。";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "やっとお前だと確信できたぜ。相変わらず無礼な野郎だな。だが構わねえ、 すぐにその汚ねえ口を永遠に塞いでやるからな、この野郎。";
			link.l1 = "ハハハ、やっと面白くなってきたじゃねえか！なあ、ガブ、正直言ってお前にはまたガッカリだぜ。 俺一人相手にするのに、もっと仲間を連れてくるべきだったんじゃねえのか？しかもこっちは二人だぜ！それとも、 それしか回してもらえなかったのかよ、この腰抜けが？";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "もういい！これ以上話しても意味がねえだろ。";
			link.l1 = "それには俺も同感だぜ！ "+pchar.name+"「戦闘だ、船長！」";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "へっ、これで終わりだ！安らかに眠れ、この野郎。";
			link.l1 = "さて、満足したか、トミー？復讐を果たした後、かえって悪くなる奴も多いんだぜ。";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "はっ、どこかでそんなこと読んだのか？俺にはああいう腑抜けどもが理解できねえんだよ。ちっ！満足かって？ 嬉しすぎて小便漏らしそうだぜ！あいつらこそ、俺の最大の不幸の元凶だったんだ！";
			link.l1 = "お前のことを嬉しく思うぜ。他に復讐したい奴はいねえのか？まだ紙薬莢の冗談を聞かされることになるのか？";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "落ち着け、ゲイブが最後だったんだ。それと冗談については――心配するな、お前に関してはもうこれ以上言わねえよ、少なくともな。";
			link.l1 = "じゃあ、船に戻るか？";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "どうせ俺たちはあの船に戻ることになるんだ、復讐すべき相手がまだいるかどうかに関係なくな。だが、ちょっと待てよ……";
			link.l1 = "「ああ、まだ終わっちゃいねえのか……」";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "そうだ、そうだよ。お前に伝えたいことがあるんだ。これはごくわずかな人間にしか言わないことだ。 そしてもう二度と言わない。もし笑ったら、俺は本気で怒るからな。";
			link.l1 = "笑わないと約束するよ。\nそれにしても、お前の冗談は面白いというより、むしろ緊張感があるな。";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "よし。さて……ジャックがやったことをせずに、俺を助けてくれると決めてくれて本当に感謝してるぜ。あんたは本物の友だ、船長。 ありがとうな。\nそれと……もしよけりゃ、俺の頼りになる剣と鎧――残ってる分だけどな、ははっ！――を貸してやるぜ。";
			link.l1 = "そう言ってくれてありがとな。そんなことを部下から聞けるなんて、そうそうあるもんじゃねえ。さあ、行こうぜ、相棒。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "アイアイサー、船長？";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				Link.l1 = "トミー、どうやらここで俺たちの道は分かれるようだな。";
				Link.l1.go = "SharlieEpilog_Irons_1";
				break;
			}
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "さて、ルンバよ、今夜は誰の骨の上で踊るんだ？";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "「はい、エリー？」";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "聞いてるぜ、船長。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "トミー、ちょっと真剣な話をしたいんだ。実はな……レッドスキンズの石像があるんだ。俺には助けが必要だぜ。こんな頼みは、お前みたいな親しい仲間にしかできねえ。 新参者や、まだ信用しきれねえ奴らには任せられないんだ。";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "トミー、カモメの数を数えるのはやめろ。積荷は全部確認したのか？全体の報告と今後の見通しを教えてくれ。";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "トミー、今日から港で特定の品を仕入れてほしいんだ。";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "トミー、船についてすべて報告してくれないか？";
					Link.l12 = "トミー、俺はちょっと疲れてきたぜ。各港で特定の品を補充してきてくれないか？";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "「船と積荷の状態について報告をまとめてくれ、トミー。」";
					Link.l12 = "寄港中に特定の品を補充してくれねえか？";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "船にある物をすべて数えて、全体の状態を報告しろ。";
					Link.l12 = "俺たちが各港に寄港するたびに、この品物を買ってきてほしいんだ。";
				}
			}
			//////
			Link.l1 = "俺の命令をよく聞け！";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "誰かがそうしているのは間違いねえ。だが今は、俺の命令を聞け。";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "俺の命令を聞け……トミー。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "それはいいな、トミー。新しい指令があるんだ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "トム、俺の命令を聞け。";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "何もない、トミー。楽にしていいぞ。";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "どうなるか見てみようぜ、トミー。";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "いや、トム、何もない。";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "いや、何もない。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "何でもない、大丈夫だ。";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "まだ在庫の確認すら始めてないんだぜ。利益と損失を数えてやってるだけでも感謝してほしいもんだ、 あの欲張りな商人どもと値切り交渉なんてとんでもねえ。\n在庫管理なんざ俺の仕事じゃねえし、軍隊時代にもやったことねえ。今さら始める気もねえよ。";
			Link.l1 = "ここは軍隊じゃねえぞ、トミー。まあ、わかったよ、無理強いはしねえ。";
			if (startHeroType == 4)
			{
				dialog.Text = "俺は書記なんかじゃねえよ、エリー。昔、ダニエル・クリムゾンって野郎を知ってたが、 あいつは自分をいつも書記だって言い張ってたくせに、戦場なんてほとんど見たことがなかったんだ。だが、 戦いになると化け物みたいに強かった。俺はそうじゃねえし、嘘もつかねえ。帳簿なんて性に合わねえよ。 お前のために会計をやってやってるだけだ。これ以上無理を言うな。";
				Link.l1 = "わかったよ、Tommy、やめておくぜ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "見ろよ、俺は書記じゃねえんだ。こんなことは、俺みたいな普通の兵士には誰も求めたことがねえ、軍隊でもな。 そいつは変えないでおこうぜ。";
				Link.l1 = "よし、やめておこう。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "俺が数えられるのは、ぶっ倒した敵の数だけだぜ、ははは。しかも途中で数えきれなくなるんだよ。俺はただの兵隊さ、 分かるだろ。船のことなんざ知るかってんだ――ほとんど陸の上で生きてきたんだからな。";
				Link.l1 = "どうやら俺が自分でやるしかなさそうだな。";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "俺をなんだと思ってやがる、裏路地の下っ端軍需係か？俺たちは、あんな腑抜けの腰抜けどもなんざ、 故郷じゃ鼻にもかけなかったぜ。貴族じゃねえが、俺にも誇りってもんがあるんだ。";
			link.l1 = "わかった、わかった、やらないなら仕方ねえな。";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "聞いてくれ、あたしはただの素直な兵士だったんだ、補給係なんかじゃないよ、お嬢ちゃん。 そういうことはよく知らないし、これから覚える気もないよ。 君に火縄銃の分解と組み立てを時間内にやれって頼むようなもんさ。";
				Link.l1 = "そうだな、この船の索具の一本一本まで全部暗記してるぜ。だが、お前の望み通りにしよう、トム。 もうこの話は終わりだ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "いいえ、できませんでした。もしかすると、あなたは忘れているか、そもそも知らないかもしれませんので、説明します。 あなたにとっては日常的な任務でしょうが、我々の軍では補給や後方支援の者たちはあまり良く扱われていません。 どうか私を彼らと一緒にしないでください。";
				Link.l1 = "ははは、いいぞ、いいぞ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "見てくれよ、もちろんあんたのことは尊敬してるが、俺は自分に逆らってできねえことや我慢できねえことはやらねえぜ。 当時はやっと数を数えられるようになったばかりだし、今さらちゃんとした納入業者になれって言うのかよ。\nそれに、あいつらのことは好きじゃなかった――弾薬も水も食い物もケチるし、新鮮さもないんだ。";
				Link.l1 = "ふむ、まあいい、忘れようぜ。";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("おっと、命令かい？お前さんは訓練とか軍隊のやり方が好きなんだな。俺としては、 何をすればいいかだけ教えてくれりゃ十分だぜ。","お前は軍曹か何かみたいだな。でもそんなの似合わねえよ――お前は美しすぎるからな。軍隊じゃ一日も生き残れなかっただろうさ。だが、話は聞いてやるぜ。")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "どうやらお前は本当に制服や訓練、そういうのが大好きなんだな。まあいい、続けてくれ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "「どれだ？」";
			}
			
            Link.l1 = ""+GetSexPhrase("どこにも行くな、何もするな――ただ見てろ、わかったか？お前のことはよく知ってるんだ。","そのまま動くな、わかったか？")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "ここに立ってろ、どこにも行くな、何にも触るんじゃねえぞ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "ここで待機して、誰も通すな。";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("俺について来いよ、どんなことにも気を取られるな――迷い妻や急に現れる昔の戦友も含めてな。","そばにいてくれ、いいな？俺の背中を頼むぜ。")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "ついて来い。考え事をしているのが見て取れるぜ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "理由があって立ち止まったのでなければ、俺について来い。";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "今回は違うものを撃ってほしいんだ。";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "次の戦いでは別の弾薬を使ってほしいんだ。";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "次の戦いでは別の弾薬を使うことになるぜ。";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "マスケット銃の弾薬の種類を変更しろ。";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "戦闘用の主武器を変更しろ。";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "お前には敵との間に一定の距離を保ってほしいんだ。";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "敵からある程度距離を取ってほしいんだ、トミー。";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "「敵との間に一定の距離を保て、トミー。」";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("どんな弾を使うんだ？一発一発、ちゃんと作ったんだろうな。どこに飛んでいくかわからねえからな、へへ。","あんたのためなら何でも撃ってやるぜ。どんなもんでもな、でも空砲だけはごめんだ、へへ。 ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "面白いことが起こりそうな気がするぜ！よし、どんな話だ？";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "また戦うのか……よし、どんな戦いだ？";
			}
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "弾薬の種類を選択してください：";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "戦闘開始時に使うのは：";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("そこでぶん殴られても、へへ？わかった、俺は見てるだけだぜ。","俺を用心棒にしようってのか？お前がボコボコにされたらどうすんだよ？")+"";
            Link.l1 = ""+GetSexPhrase("おい、気をつけろよ！もしそうなったら何とかするさ。","おい、まさかそこで突っ立って見てるだけじゃねえだろ？自分の船長がそんなに素晴らしいって言うなら、 何かしてみろよ。")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "頭を狙うのもアリか？わかった、わかった、そんな目で見るなよ、理解したってば。";
				Link.l1 = "そうだといいんだが。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "怖がるな、誰も突破できやしねえ。";
				Link.l1 = "誰かを置き去りにしていなければ、もちろんだ。だが、よし。";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("おもしろいじゃねえか。だが、言いたいことはわかったぜ。","おいおい、心配すんなよ、俺はいつだってお前の味方だぜ、へへっ。")+"";
            Link.l1 = ""+GetSexPhrase("「よし。」","「まったく、お前は本当に手に負えないな、トム。」")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "うーん、とても大事なことを思い出そうとしてるんだ。でも、その時に記憶を失ったせいで、 何を思い出そうとしてるのかすら分からなくて、結局どうにもならねえ。\nまあ、行こうぜ。";
				Link.l1 = "気が利いてるな、そう言わざるを得ないぜ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "「おい、俺がここに立ってるのは、あんた自身がさっきそう命じたからだぜ。今行く、今行くよ。」";
				Link.l1 = "ふむ、わかった、わかった。";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("どれくらいの距離だ？二十ヤードを超えると、正確に狙うのは無理だぜ。もちろん、 別に当てなくてもいいってんなら話は別だけどな、へへ。","お前みたいな臭い野郎のそばにいた後で、他の男どもに近づきたいわけないでしょ。\nそれで、距離はどれくらい？でも覚えておいて、あたしの火縄銃は二十ヤード以上じゃ本当に狙えないのよ。 誰だってそうよ。")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "よし、どのくらいの距離だ？だがな、戦闘の最中に二十メートル以上離れると、 正確にゆっくり撃つなんて無理だってことは覚えておけよ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "わかった。何だって？あの先のことを覚えてるか…まあ、俺たちはもう子供じゃねえって、お前も俺も分かってるだろう。";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("ユーモアを試みるべきじゃねえ。","ユーモアについては、まだまだ俺から学ぶことが多いぞ、お嬢ちゃん。だが、成長してきてるじゃねえか！")+"";
				link.l1 = ""+GetSexPhrase("それはおかしいな。俺はずっと逆のことを聞かされてきたぜ。","「おもしろいな、トミー。」")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "悪くない冗談だな。いつかはその仏頂面もやめる日が来るかもな、へっへっ。";
					Link.l1 = "まあ、仕方ねえな。";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "ははは、いい冗談だな。";
					Link.l1 = "実は、俺はただ……わかったよ。";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "じゃあ、俺はここでじっとして踏ん張るだけだ。あいつらと遠くから戦うなら、お前の首が危ないぜ、へへ。";
				link.l1 = "皮肉を言うな。これからは踏ん張ってくれるのがまさに俺の望みだぜ。";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "へっ、距離や数字の話なんかせずに、「ここを守れ」って一言言えばよかったんだぜ。";
					Link.l1 = "まあ、大事なのはお前が俺の言いたいことを分かってくれたってことだ。";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "了解だ、ここで踏ん張るぜ。そしたら、奴らをもっと近くに連れてきてくれ、撃てるようにな。";
					Link.l1 = "かしこまりました。";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "見ろよ、灯台での一発みたいな完璧な射撃を毎回期待してるのは分かるが、そんなの無理だぜ。あそこはいい場所だった。 落ち着いて、しっかり狙えた。戦いの最中じゃ、あんな状況は再現できねえんだよ。";
				link.l1 = "ふむ。それなら二十ヤード離れていろ。";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "それはお前も好きだろうし、みんなも好きだろうが、あの灯台の時みたいにはもういかねえんだ。\n今度はちゃんとした場所が必要だし、誰にも邪魔されないようにしねえと、俺の神経が持たねえよ。";
					Link.l1 = "ふむ、わかった。";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "あれから確かに腕は磨いたが、不可能なものはやはり不可能だ――戦いの最中に、灯台からのあの一撃をもう一度決めるなんて絶対に無理だ。 たとえホイールロック式ライフルを使ってもな。";
					Link.l1 = "不可能も可能になるんだぜ、トミー。\nだがまあ、ダメなものはダメだ。";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("よし、わかった。その距離はきっちり守るぜ。ただし、酒場や洞窟の中で戦うときは、 距離を保つために外に出ることにするさ、へへ。","やってみるぜ。しかし、甲板や狭い場所じゃ、向こうの都合で動くことになるかもしれねえな。");
			link.l1 = ""+GetSexPhrase("面白くねえぞ、トミー。ちゃんとしろ、冗談やくだらねえ悪ふざけはやめろ。","分かってるさ、Thomas。俺はバカじゃねえ。")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "覚えておくようにするぜ。";
				Link.l1 = "よし、頼んだぜ。";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "「はい、船長。」";
				Link.l1 = "楽にしろ、Tommy。";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "何を手伝うって、盗めってことか？でも、なぜだ？まあ、お世辞は嬉しいが、 そんなこと最初から言えばよかったんじゃねえか。さあ、はっきり言えよ。";
			link.l1 = "口の利き方に気をつけろよ、あ？まあ、くそ、どう言おうが俺の味方でいてくれりゃ気にしねえよ。で、その偶像だがな。 あれを使えば……魔法みてえに別の場所へ移動できるんだ。そんな目で見るなよ――自分でもどう聞こえるか分かってる。でもな、俺はこれを体験して、全部この目で見たんだ。……ひとつエリクサーを飲めば安全だぜ。";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "もう何杯か飲んだようだな。いや、でも、酔ってるようには見えねえな。 いつも俺がでたらめばかり言ってるって言われるが……";
			link.l1 = "俺と一緒に来るのか、それとも来ないのか？その偶像が俺たちを古代マヤの都市へ導くらしいが、 そこで何が待っているかなんて誰にもわからねえ。お前は、いざという時に頼れる数少ない仲間の一人だ。 今がまさにその時なんだぜ。";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "俺はどうも嫌な予感がするぜ。あんたが俺の船長じゃなきゃ、精神病院に入るべきだって言ってるところだ。 次は神様がいるなんて言い出すんじゃねえだろうな。";
			link.l1 = "ああ、トミー、そうだ。しかも、この諸島で俺が驚いたのは、俺たちだけじゃないってことさ。 ここでどんな悪事が渦巻いてるか、自分の目で見ただろう？それに、 祝福されたのか呪われたのか分からねえ小物の影響も、きっと気づいてるはずだ。";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "悪魔の仕業なんて家でもあるもんさ。だが、いつだって普通の理由があったんだ。悪いな、船長、 だが石像のまわりでお前と踊る気はねえよ。敵を撃つのは大歓迎だがな。記憶は失ったかもしれねえが、 正気は失っちゃいねえ。少なくとも、そう思ってるぜ。";
			link.l1 = "まあ、無理強いはできねえな。じゃあ……好きにしろよ、トミー。";
			link.l1.go = "tieyasal_5";
			link.l2 = "お前みたいな大胆な奴でも、あの偶像に近づくのが怖いなら、どうせ撃つ度胸なんてねえだろうよ。";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "おっと、まあまあ、そんなにふくれっ面するなよ。よし、あの偶像の周りで踊ってから戻ってきたら、次は考えてやるぜ。 ";
			link.l1 = "次はないかもしれねえ。船に戻れ、トム。";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "俺は怖がっちゃいねえ、誤解すんなよ。だがな、俺はずっと自分の勘を信じて生きてきたんだ。その勘が今、 これはろくなことにならねえって言ってるんだよ。\nそれに……まあ、いいさ、お前は気を悪くするだろうしな。";
			link.l1 = "さあ、話してくれ。";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "そうかい、そういうことなら！俺はお前と肩を並べて戦うって約束したぜ。\nだが、もしだ、仮にこの代物が本当に動いたらどうする？呪われてたらどうするんだ？\n誰かのために死ぬつもりはねえ、悪いがな。";
			link.l1 = "これでお前の実力は分かったぜ、トミー。俺が欲しかったのは一番忠実な奴らだけだ。だが今、 お前はその一人じゃねえって分かった。俺はこれから行く。お前は……好きにしろ。";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "見てみろ。結局、あいつは気分を害してるじゃねえか。";
			link.l1 = "黙れ。そんなに俺たちが気に入らねえなら、船に戻ってこなくていいんだぜ。";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "なんてこった！本気か？まあ、そっちの方がいいかもな。冗談も通じねえ湿っぽい連中と一緒にいたくねえしな。 そういうことなら……さらばだ、閣下。";
			link.l1 = "さらばだ、トミー。地獄へ落ちろ。";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_tieyasal_otkaz");
		break;
		
		// Эпилог
		case "SharlieEpilog_Irons_1":
			dialog.text = "はは。冗談も言えるようになったのか。俺みたいに。だがその手には乗らん、諦めろ。";
			link.l1 = "違う、冗談じゃない。本気だ。俺はヨーロッパへ行く、親父のところへ。お前がここに残って待つのもいいが…どれくらいかかるかは分からない。";
			link.l1.go = "SharlieEpilog_Irons_2";
		break;
		
		case "SharlieEpilog_Irons_2":
			dialog.text = "そんなツラで冗談言えるほど面白くないぞ。つまり、俺を蹴っ飛ばすってわけか？俺が命張ってお前を助けた後で？お前のためにここまでしてきたのに？";
			link.l1 = "大げさに言うなよ、トミー。お前は仕事をしてた、それで給料をもらってただけだ。認めるよ、お前は腕がいい。もし待つ気があるなら、また乗組員として迎えるさ。だが今は…";
			link.l1.go = "SharlieEpilog_Irons_3";
		break;
		
		case "SharlieEpilog_Irons_3":
			dialog.text = "気前がいいな、クソが。ありがとな、裏切り者の船長殿よ。じゃあこう書いておくか―『忠犬はご主人を待てる、退屈で死ななければな』。";
			link.l1 = "気にするな。こうなる運命だったんだ。";
			link.l1.go = "SharlieEpilog_Irons_nothing";
			link.l2 = "怒るのも無理はない。俺だって同じ立場なら腹が立つさ。だから、今のお前の取り分に加えて、さらに一か月分の給料を払う。恨まないでくれよ。";
			link.l2.go = "SharlieEpilog_Irons_salary";
			link.l3 = "突然の話で驚いたろうし、怒るのも当然だ。だから、今のお前の取り分に加えて、三か月分の給料を払うつもりだ。";
			link.l3.go = "SharlieEpilog_Irons_salary_X3";
		break;
		
		case "SharlieEpilog_Irons_nothing":
			dialog.text = "運命なんかクソくらえだ。お前もだ。お前なんかに関わったことを後悔してる。いいか、追い出されるんじゃねえ。俺が自分の意思で去るんだよ。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
		break;
		
		case "SharlieEpilog_Irons_salary":
			dialog.text = "その小銭は乞食にでもくれてやれ。俺はお前の施しなんかいらねえ。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
			//
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Irons_salary_X3":
			dialog.text = "三か月分の給料？そりゃ太っ腹だな…泣けてくるぜ。よし、ありがたくもらっておく。酒場で野郎どもに一杯おごってやるさ―シャルル・ド・モール船長に乾杯。忠誠の鑑、友情の象徴、見習うべき男に。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
			//
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Irons_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Irons_exit");
		break;
	}
} 