void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "それは間違いなくバグだ。いつ、どうやってそれが起きたのか、ジェイソンに知らせてくれないか。";
			link.l1 = "承知した。";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "なぜ俺の小屋に来たんだ、白い肌の男よ？トゥットゥアタパクはお前を大事な客とは思っていないぞ。";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "ごきげんよう、偉大なるトゥットゥアタパク呪術師。私はあなたの助力と助言を求めて参りました。 どうかこのマスケット銃を私の善意のしるしとしてお受け取りください。";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "ごきげんよう、偉大なるトゥットゥアタパク呪術師よ。あなたの助力と助言を求めて参りました。";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "トゥットゥアタパクは白人を助けない。白人は悪い奴らだ。インディアンを殺し、征服し、奴隷にする。 トゥットゥアタパクは白人に何も教えない。今すぐ立ち去れ。";
			link.l1 = "ふむ……";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have given: "+XI_ConvertString(sTemp)+"");
			dialog.text = "お前はトゥットゥアタパクに何を渡すべきか知っているな、白人よ。トゥットゥアタパクはお前の贈り物を受け取る。 話そう。\nどんな助言を求めているのだ？";
			link.l1 = "南の遠い土地から来たと聞いたぜ。俺はインディアンのお守りを持ってるんだが、物知りの男が、 あんたならその使い方を知ってるかもしれねえって言ってたんだ。";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "アミュレットを見せろ。";
			link.l1 = "どうぞ、偉大なるシャーマン。";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "（アミュレットを見ながら）…お前の友は真実を語っている、白人よ。このアミュレットは我が民族、偉大なるインディアンのものだ。チャビン、 それが我らの名だ。呪われし、冒涜せる白き顔の犬が聖堂を汚し、これをここへ持ち込んだ。 トゥットゥアタパクがその犬を罰したのだ。";
			link.l1 = "あんたが奴の正気を奪ったってことか？";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "白人はその知識でトゥットゥアタパクを驚かせる。\nああ、俺はあの卑劣な野郎の心を喰らったんだ。奴とその汚い手下どもは報いを受けたぜ。";
			link.l1 = "なるほど……教えてくれ、シャーマン、このお守りは何に使うんだ？もしかして戦いで身を守ったり、 邪悪な魔法を退けたりできるのか？";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "このお守りはお前には役に立たん、白人の船長よ。\nその力を使うことはできぬ。\n我らの部族の偉大なシャーマンだけが、その力を目覚めさせる方法を知っているのだ。";
			link.l1 = "ふむ……つまり、俺はこんなに長い旅を無駄にしたってことか。だが、もしかしてあんたなら、 このアミュレットの力を目覚めさせられるんじゃないか、大シャーマンよ？きっと俺たち、話し合えばうまくいくはずだ……";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "たとえ俺がこの護符を目覚めさせても、お前がその力を長く持つことはできねえ。だが、取引を持ちかけてやるぜ、 白人よ。";
			link.l1 = "「どんな取引だ？」";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "このような護符が三つ、我々の聖堂から奪われたのだ。それぞれ異なる力を持っているが、三つを揃えると、 とてつもない力になる。三つすべての護符を見つけて私の元へ持ってきてくれれば、褒美をやろう。 永遠に手にできる力を授けてやるぞ。";
			link.l1 = "俺にはよくわからねえ……どんな力のことを言ってるんだ？";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "いずれ時が来ればすべて分かるだろう。三つのアミュレットをすべて見つけて、私のところに持ってくるのだ。 それらはカリブ海にある。探し出して見つけるのだ。すぐに分かるはずだ――見た目がよく似ているからな。行け、白人よ。トゥットゥアタパクが待っている、 精霊たちにお前を助けるよう頼んでいるぞ。\n";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "行け、白人。あと二つのお守りを見つけてこい。";
				link.l1 = "もう見つけたぞ、大シャーマン。ほら、見てくれ。";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "行け、白人よ。残りの二つの護符を探せ。";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "また来たのか、白人野郎？ジャングルで凶暴なジャガーにでも出くわした顔してるぜ。";
			link.l1 = "さらに悪いことに、大シャーマン。俺が海に足を踏み入れた途端、どこからともなく巨大な嵐が現れ、 不死者どもが操る船に襲われたんだ！あいつらの船長はまったく無敵だった。最初に俺からアミュレットを奪い、 殺されかけた――かろうじて生き延びたんだ。それから奴らは俺の船を沈めかけて、乗組員もほんのわずかしか生き残らなかった。\n";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "悪い知らせだ、白人。カレウチェがまたとどめを刺しに来るぞ。";
			link.l1 = "カレウチェだと？あの不死の船長は自分の船をフライング・ハートと呼んでいた。つまり、 お前は幽霊船のことを知っていて、俺には警告しなかったのか？ もしあの航海する悪夢がアミュレットを狙っていると知っていたら、俺は絶対に……";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "トゥットゥアタパクは白人の船長が動揺しているのを見ている。\n白人の船長は落ち着かねばならん。";
			link.l1 = "落ち着けだと！？正気かよ？あんなもの相手にどうやって生き残れってんだよ！";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "ああ。落ち着いて、叫ぶな。教えてくれ――お前はまだ、俺から永遠に残る大いなる力を受け取りたいと思っているのか？";
			link.l1 = "もちろん持っていたさ。でも、もうそのお守りは手元にないんだ。";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "カレウチェ号の船長からアミュレットを奪う方法を教えてやるぜ。簡単にはいかねえぞ。\nだが、やり遂げればあいつの船を戦利品として手に入れ、貴重な財宝を見つけ、仲間の間で名声を得て、 俺からも報酬を受け取れるんだ。";
			link.l1 = "くそっ！あの干からびた化け物なんざ喜んでぶっ潰してやるぜ！\nだが、剣でも弾でも傷つかねえ奴をどうやって倒せってんだ！？";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "俺の話を聞く準備はできてるか、白い船長？";
			link.l1 = "ああ、そうだ、大シャーマン。";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "俺の父が若き戦士だった頃、白人たちが「フライング・ハート」と呼ばれる船で俺たちの土地にやって来た。 奴らは山へ向かった。伝説によれば、そこには俺たちの祖先の祠が隠されているという。ジャガー戦士たちの祠だ。 白人たちはその祠と黄金を見つけ、古の聖なるものを汚した。奴らはチャビン族の偉大な宝――死の神でありジャガーの民の守護者ユム・シミルの翡翠の髑髏――を奪い去った。\n白人たちは自分たちの船に戻った。さらに黄金を求めて戻ることを決めたが、仲間の一人が陸地に足を踏み入れた瞬間、 恐ろしい苦しみの中で死んだ。ユム・シミルが船長とその乗組員に呪いをかけたのだ。奴らは不死となったが、 二度と陸に足を踏み入れることはできなくなった。奴らは何十もの冬、つまりお前たちの暦で半世紀もの間、 海をさまよい続けた。こうしてカレウチェが生まれたのだ。\n奴らの体はしおれ、肉は腐っても、なお生きている。腕や脚を切り落としても、また生えてくる。真っ二つにしても、 元通りになる。船が沈んでも、水中で修理して再び航海を続けるのさ。";
			link.l1 = "まったく、最高だな……";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " カレウチェ号は船乗りたちを恐怖に陥れる。理由もなく襲いかかり、必ず死をもたらすのだ。 カリブ海にはあまり現れない。俺の母国の沿岸を航海するのを好むらしい。呪いを解こうとしているのだろうが、 決して解けはしないさ。";
			link.l1 = "なぜだ？呪いを解くには何をすればいいんだ？";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "翡翠の髑髏だ。これはユム・シミルの神殿、ジャガー戦士の寺院に戻さねばならない。寺院はいくつかある。 俺の部族の長老たちは、カリブ海の小さな島に一つあると言っている。だからカレウチェ号はそこへ航海したんだ。 髑髏が寺院に戻れば、ユム・シミルの呪いは解け、奴らは死すべき者となり、もはや傷を癒すことはできなくなる。";
			link.l1 = "はっ！むしろ、奴らがドクロを返す気なんてねえだろう！不死身で無敵なら、返す理由があるか？それにさ、 陸に上がることが許されてねえなら、そもそも持って来ることもできねえじゃねえか？\n";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "奴らはその頭蓋骨を持っていない。船長はジャガーの民の聖堂から戻ったとき、俺の祖先の土地にそれを捨てたんだ。 翡翠は金じゃねえ、白人には必要なかった、美しい緑の宝石を頭蓋骨の目から取り出すこともできなかった。 だから捨てたのさ。ある水夫がそれを拾ったが、呪いには触れなかった\nその水夫はカレウチェ号の乗組員がどうなったかを見て、逃げ出した。奴は俺たちの村に来た。 親父はその水夫とユム・シミルの頭蓋骨を見たんだ。そして白人は海岸沿いを北へ行き、頭蓋骨を持っていった。";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "緑色の石が目に埋め込まれた翡翠の髑髏か？俺はそれをこの手で持ったんだ、想像できるか？ ソロモンに自分で渡したんだよ。だが、あいつは娘を連れてヨーロッパへ行っちまってな、 どうやら髑髏も一緒に持っていったらしい。";
				}
				else
				{
					link.l1 = "緑色の宝石が目に埋め込まれた翡翠の頭蓋骨だと？くそっ……俺は……俺はそれをこの手で持ったんだ！それで、ポルトガル人に売っちまった……メリマンとか、そんな名前だったな……そうだ、やつはそう呼んでた――ユム・シミルの頭蓋骨って！あいつはどうしても欲しかったんだ！五十万ペソも払いやがった！";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "緑色の宝石が目に埋め込まれた翡翠の髑髏だと？それを探せばいいんだな？\nだが、その水夫は五十年前にジャングルで死んだかもしれねえし、髑髏も永遠に失われたかもしれねえじゃねえか！";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "ドクロがカリブ海にあるのは知っている。カレウチェ号がここにいるのも偶然じゃねえ。\nこの六つの月の間、あの島でよく目撃されているんだ。昔は何年もあそこには現れなかった。\nカレウチェ号の船長はジャガー族の秘宝を感じ取れる。だからお前とお前の船を見つけたのさ。";
			link.l1 = "つまり、俺はまたこの髑髏を探さなきゃならねえってことか？\nそれで、見つけたらどうすりゃいいんだ？";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "ドクロはここ、カリブ海にいるはずだ。カレウチェ号がここにいるのも偶然じゃねえ。過去六つの月の間、 あの島でよく目撃されている。それ以前は何年もの冬の間、姿を見せなかったんだ。 カレウチェ号の船長はジャガー族の秘宝を感じ取ることができる。だからこそ、あいつはお前とお前の船を見つけたんだ。 \n";
			link.l1 = "つまり、俺はもう一度このドクロを探さなきゃならねえってことか？\nそれで、見つけたらどうすりゃいいんだ？";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "まず、俺たちが話した二つの護符を見つけなければならない。\nそれがなければ、何もできねえぞ。\n護符があれば、ジャガーの戦士どもや出会う敵に立ち向かう力を得られるんだ。";
			link.l1 = "ジャガーの戦士たちに立ち向かうだと？何の話だ？";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "お前が翡翠の髑髏を持っていかなければならない寺院は、カリブの無人島にある。 そこはジャガー人間たちに守られている。やつらは皆死んでいたが、今は再び生きている。護符がなければ、 やつらを通り抜けることはできない。生前、ジャガー人間たちは猛々しい戦士だったが、死後はほとんど無敵になった。 ユム・シミル自身がやつらに力を与えているのだ。";
			link.l1 = "アンデッドか？またかよ……ついてねえな……";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "なぜそんなに驚いている、白い船長？ユム・シミルは死の神だ。翡翠の髑髏は死者と生者を支配する力を持つ。 カリブ海だ。ジャガーの戦士たちがそれを守っている。護符がなければ奴らを通り抜けることはできない。 護符があれば神殿に入って生き延び、そこで髑髏を置き、カレウチェを探し出し、そいつの船長を倒して、 お前から奪われた護符を取り戻せるのだ。";
			link.l1 = "「それで、カレウチェ号の船長はなぜこの護符が必要なんだ？」";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "あいつはジャガーの民の神殿に行きたがっていて、アミュレットが役に立つと思ってるんじゃねえかと俺は思う。だが、 間違ってるかもしれねえ。\nそれでも、カレウチェはいつも俺の故郷の遺物に惹かれるんだ。ジャガーの民の神殿がある島の近くを航海し、 俺の母国の岸辺沿いも航海したんだ。";
			link.l1 = "「で、その島はどこだ？」";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "まずはユム・シミルの頭蓋骨と護符を見つけろ。\nそれから島の話をしよう。";
			link.l1 = "いいだろう。翡翠の髑髏を探す手がかりを教えてくれないか？";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "知らねえ。でもここ、カリブにあるんだ。お守りもな。聞け。探せ。見つけろ。";
			link.l1 = "へっ…よし、やってみるぜ。";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "気をつけろよ、白い船長。カレウチェはチャビンの品を感じ取る。お前がアミュレットを手に入れたら、 あいつはお前を探しに来るぞ。見つかったら、すぐに逃げろ。捕まったら、お前はもう死んだも同然だ。";
			link.l1 = "この呪われた船はとんでもなく速いぜ！今まで見たどんな船の倍は速い。\nだが、風上に向かうときは苦戦しているのに気づいたんだ。";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "カレウチェ号は呪われている――だからあんなに速いんだ。逃げるのは難しいぜ。カレウチェ号より速い船を持ってなきゃ、死ぬ羽目になるぞ。\n護符を見つけたら、俺のところに持って来い。\n護符は船に置いておくなよ。";
			link.l1 = "もう手に入れた。話をありがとう、大シャーマン。そろそろ俺は行く時間だ。";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "俺は精霊たちに、お前を助けてカレウチェから救ってくれるよう頼んでいるんだ。";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "Santiago_Lightman") {AddLandQuestMark(characterFromId("Santiago_Lightman"), "questmarkmain");}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "BasTer_Lightman") {AddLandQuestMark(characterFromId("BasTer_Lightman"), "questmarkmain");}
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "（見ている）ああ、それだ。二つ目のチャビンの護符だな。やるじゃねえか。だが、 もう一つ護符を見つける必要があるぜ。";
			link.l1 = "覚えているぞ、シャーマン。すぐにお前のものになる。";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "行け、白人。もう一つ護符を見つけてこい。";
				link.l1 = "もう持ってるぜ、大シャーマン。ほら、見てみな。";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "行け、白人。もう一つ護符を見つけてこい。";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "（見ている）ああ、それだ。三つ目のチャビンズのアミュレットだ。やるじゃねえか。 ユム・シミルのしもべである死んだジャガー戦士たちを通り抜けるためのアミュレットを全部見つけたんだな。";
			link.l1 = "さて、俺の理解では、翡翠の髑髏が必要になるんだな？";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "お前の言う通りだ。ユム・シミルの翡翠の髑髏だ。それをチャビンの神殿へ持って行かねばならん。 そうすればカレウチェの力は永遠に失われるだろう。";
			link.l1 = "トゥットゥアタパク、頼む、どこを探せばいい？何か心当たりはあるか？";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "いいや。最後に翡翠の髑髏を見た場所を思い出せ。誰に渡したかもな。そこから探し始めるんだ。";
				link.l1 = "わかったぜ、大シャーマン。できる限りのことはやる。";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "ユム・シミルの頭蓋骨に興味を持つ白人の魔術師だ。あいつはそれを探している。うちの村にもやって来たらしい。 魔術師はオランダの島の家に住んでいると聞いた。オランダの島でその魔術師を探せば、何か分かるかもしれない。";
				link.l1 = "わかったぜ、大シャーマン。できる限りのことはやる。";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "I'll start with Curacao, where I handed it over to Solomon. Maybe I'll find some clue - to find out what happened to the skull.";
				else sTemp = "I'll start with visiting Curacao - there I've sold the jade skull to Joachim Merriman.";
			}
			else sTemp = "Tuttuathapak told me, that a 'white warlock' showed interest in the jade skull, and adviced seeking for him on Dutch islands. Who might that be?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "行け、白人よ。ユム・シミルの翡翠の髑髏を探せ。";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "ここにありますぞ、大シャーマン、見てください。";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "行け、白人よ。ユム・シミルの翡翠の髑髏を探せ。";
			link.l1 = "申し訳ないが、俺にはできそうにない。魔術師は見つけたんだが、土壇場で奴は頭蓋骨を持って逃げちまった。 今どこにいるのか、まったく見当もつかねえ。";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "これはとても悪いことだ、白人よ。これでお前は寺院を通れず、カレウチェを倒すこともできん。贈り物はやらん。さあ、 出て行け。";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "今すぐ出ていけ、白人。";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "（見ている）ああ、それだ。とても美しい。だが、とても恐ろしい。";
			link.l1 = "ああ……でも、もっと興味深いのはな、俺はこの髑髏を持ってキューバからドミニカまでカリブ海を横断したが、 その間カレウチェは一度も俺を襲おうとしなかったし、姿すら見なかったんだ。\nだが、お前にお守りを運んでいた時は、あいつは執拗に俺を追い回してきた――出航した途端、数時間以内に見つけられたんだぜ。";
			link.l1.go = "Tuttuat_46a";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_46a":
			dialog.text = "カレウチェ号はドクロを恐れているか、あるいはそれを感知できないのだと思う。他に説明のしようがない。 もしかするとユム・シミルが翡翠のドクロを、 呪いに加えてカレウチェ号にとって非常に危険なものにしたのかもしれない。だからこそ船長は、 私の民の三つの護符をどうしても手に入れたかったのだろう。ユム・シミルの呪文を制御する知恵を得るために。";
			link.l1 = "つまり、俺の船に翡翠の髑髏が積んである限り、カレウチェの襲撃を恐れる必要はないってことか？";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "その通りだ、色白野郎。自分の目で見てみろよ。";
			link.l1 = "よし！これで俺は大型船の指揮を執り、まともな船員を雇って、 あの死人が呪いから解放された時にしっかり歓迎してやれるってわけだ。しかも、あいつが先に俺を捕まえる心配もねえ……";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "…ところで、その呪文のことだが――翡翠の髑髏はどこに持っていけばいい？";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "それをチャビンの神殿に持って行き、旅を終えなければならん。\n話を聞かせてやろう。準備はいいか、白人よ？";
			link.l1 = "俺の耳はいつでもお前の知恵を聞く準備ができてるぜ、Tuttuathapak。";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "我が祖先の伝説によれば、遥か昔、白い顔の男たちがまだ我らの地に来ていなかった頃、 チャビン族の偉大なる酋長が非常に非常に大きなカヌーを作り、戦士たちと共に多くの島々の地へ送り出した。 その先頭に立ったのは偉大なる酋長の息子であり、彼らの中には高位のシャーマンもいた。多くの島々 の地で彼らは無人の場所を見つけ、集落を築き、ユム・シミルのために偉大な神殿を建てた。 それは我らの偉大なる祖先だけが成し得たことだった\n使者たちは良い知らせを持ち帰ったが、酋長の息子も、シャーマンも、戦士たちも二度と誰も見ることはなかった。 伝説では、彼らはそこで暮らすことにしたと言われているが、最も賢いシャーマンが精霊と語り、 「もはやそこには人は住んでおらず、ユム・シミルがその地を支配している」と告げたという\n多くの島々の地とはカリブ海のことだ、白人よ。ユム・シミルの神殿は、白人もインディオも住まぬ島にある。今もなお、 ユム・シミルに仕えるチャビナヴィだけが神殿の回廊を守っているのだ。";
			link.l1 = "「で、その島はどこだ？」";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "話から察するに、それはこの村のある島から、白い顔の者たちが「北」と呼ぶ方角に位置する小さな島で、 三つの島に囲まれ、四つ目の側には大いなる水――つまり大洋が広がっているのだ。";
			link.l1 = "ふむ……ドミニカの北、島々が三角形に並ぶ場所で、ちょうど海の果てか？くそっ、そりゃあ広い海域じゃねえか！ そんな誰も聞いたこともねえ小島を、どうやって見つけろってんだ？";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "はっきりとは言えない。しかし、もう一つの話を知っている。お前の兄弟たちからも聞いたことがあるかもしれない。 二十冬ほど前、白い肌の男があの島を見つけた。女と老人と共にユム・シミルの神殿に入り、強力な秘宝――昇る太陽のオーブを持ち去った。島の岸辺で、その青白い顔の船長はカレウチェに襲われた\nだが、その青白い男は賢かった。昇る太陽の光でカレウチェの船長と乗組員の目をくらませたのだ。 カレウチェの呪いは弱まり、船長はそれを沈めたが、昇る太陽のオーブは消えてしまった。 もしその青白い男を見つければ、島の在り処を教えてくれるだろう。";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "はっ！俺はその「青白い顔の男」を知ってる気がするぜ……話があまりにも似すぎてる。で、カレウチェ号は沈められたのか？";
			else link.l1 = "ふむ……カレウチェ号は沈められたのか？";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "ああ、だが呪いが奴らを死から守っているんだ。奴らはそれを直して、永遠の航海を続けているのさ。";
			link.l1 = "わかった、了解だ。だが、寺院では何をすればいい？頭蓋骨はどこに置けばいいんだ？ それを守っているジャガー戦士たちをどうやって倒せばいい？ もしあいつらがメリマンっていう呪術師が呼び出したチャビナビみたいな連中なら、一人で行くのは無謀だぜ――奴ら一人一人が十人の兵士並みに強いんだからな。";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "奴らは違う。頭蓋骨を持つ白い魔術師が呼び出したチャビナビは弱い。 ユム・シミル自身が召喚したものよりはるかに弱いんだ。お前は奴らに傷一つつけられねえし、 奴らの武器に触れられたら一撃で殺されるぞ。";
			link.l1 = "待てよ――それじゃあ、その「青白い顔の男」はどうやって寺院に入り、秘宝を盗んだんだ？";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "最初の青白い顔の男が寺院に入る前は、死んだ祖先たちの霊が寺院を守っていたんだ。その青白い顔の男は強い戦士で、 霊たちを打ち倒した。そいつが昇る太陽の宝玉を盗んだとき、ユム・シミルは激怒した。 ユム・シミルはその男に火と硫黄を降らせ、寺院をほとんど破壊したが、男はその秘宝を持って逃げおおせた。 今やユム・シミルは無敵のジャガー戦士たちを呼び出し、寺院を守らせているんだ。";
			link.l1 = "素晴らしいじゃねえか！それで、俺はどうやってこっそり入りゃいいんだ？";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "俺はお前を助ける、白人。お前が持ってきたチャビンのお守り二つをやる。俺は祖先の精霊に語りかけて、 お守りに力を与える。お守りを一つ持っていれば、ジャガー戦士たちと普通の兵士のように戦える――お前も奴らの一人のようになれるが、ずっと強い。お守りはお前を守り、 武器に神殿のチャビナビを傷つける力を与えてくれる。";
			link.l1 = "お守りが本当に役に立つのか、確信はあるのか？";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "知っている。俺は祖先と話す。俺は偉大なシャーマンだ。お前は俺を信じている。お前は護符を二つ持っていけ。 一つは守ってくれる。もう一つはお前の武器に力を与える。どちらか一つを使わねばならん。どちらを使うか――お前が選べ。もし護符を身につけなければ、ジャガー戦士どもに殺されるぞ\nそれと覚えておけ、真夜中になるとユム・シミルが、お前が倒した戦士たちをすべて蘇らせる。二度と戦わずに済むよう、 タイミングを考えねばならん。あるいは、もう一度戦ってもいい。精霊たちは、お前ならそれもできると告げている。";
			link.l1 = "なるほど。";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "お前がこの護符を持っていけ。ほら、これだ。だが覚えておけ、その力には限界がある。一つの月が過ぎれば弱まるのだ。 言っただろう、その力をお前が保つことはできないと。我らの部族の偉大なシャーマンだけが使いこなせるのだ。";
			link.l1 = "覚えてるよ。で、俺には月が一つしかないのか？一ヶ月だけか？";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "ああ。ユム・シミルの神殿に来たら、祭壇とその中にある大きなコンドル像を探さねばならぬ。 これが神殿で最も重要な場所だ。ここにユム・シミルの翡翠の髑髏を置けば、 カレウチェにかけられた呪いは解かれるだろう。やつが再びお前を襲ってきても、 今度はただの人間のように倒せるはずだ。その後、やつが奪ったお守りを私のところへ持ってくるのだ。";
			link.l1 = "「コンドル？どうした？」";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "コンドルは俺の故郷の山に住む偉大な鳥だ。\n故郷を偲んで、先祖たちは聖堂の近くにコンドルの像を建てたんだ。";
			link.l1 = "わかった、俺が探してやるよ……";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "気をつけろよ。寺院にはジャガー戦士以外にもたくさんの危険が潜んでるぜ。";
			link.l1 = "「どんな危険だ？」";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "俺にもはっきりとは分からねえ。自分の目で確かめてみな。罠かもしれねえし、ただの混乱かもしれねえ。\n神殿に入るのは難しいぜ。入口は封じられていて、開ける方法を見つけなきゃならねえ。\n俺の先祖たちは偉大な戦士やシャーマンだっただけじゃなく、優れた建築家でもあったんだ。\n開けるには、頭を使う必要があるぜ。";
			link.l1 = "へっ！怖そうに聞こえるが、全員まとめてかかってこい！俺は時間なんか無駄にしねえ。すぐに出航するぜ！";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "行け、白き戦士よ。私は精霊たちを呼び出し、ジャガー戦士たちとカレウチェに立ち向かうお前を助けよう。\n覚えておけ、もしお守りを使うなら私が助けてやるが、使わなければお前は滅びるぞ。";
			link.l1 = "ありがとう、偉大なるシャーマン……必ずやり遂げます。";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("You have received two amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			AddDescriptor(sld, M_AMULET_TYPE, AMULET_PAGAN);
			aref modifier = AddCallback(sld, CT_COMMON, "KaleucheAmuletAttack");
			modifier.arg0 = 0.25;
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			AddDescriptor(sld, M_AMULET_TYPE, AMULET_PAGAN);
			SetModifierFromSource(sld, HAS + M_CANT_BE_POISONED, true, TALISMAN_ITEM_TYPE);
			SetModifier(sld, M_REDUCE_DAMAGE, 0.25);
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "But I have a clue: it seems that white captain, who had visited the temple of the Chavins, is none other than my good friend Nathaniel Hawk. I remember him saying that he had a map of that island in Maroon Town. Guess I will pay Nathan a visit.");
			}
			else AddQuestUserData("Caleuche", "sText", "That's a huge area in the sea, but I have no choice. I'll have to scour it entirely. Shaman said North of Dominica, and not too far so I could steadily move North, it might very well be a bit to the East or West. He also mentioned some Captain that destroyed the undead ship maybe I will be lucky and I might find him one day, alas, he said that I have only one month to hold this power or whatever it is, oh well it is what it is, let the search begin!");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "俺は精霊と話すんだ。お前はあの島、ユム・シミルの神殿にいたな。カレウチェとアミュレットは見つけたか？";
				link.l1 = "おっしゃる通りです、大シャーマン。俺は島を見つけ、神殿に入り、翡翠の髑髏を中に置いてきた。";
				link.l1.go = "Tuttuat_63";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "行け、白き戦士よ。";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "トゥットゥアタパク、聞いてくれ……俺が頭蓋骨を寺院に持って行くのが遅れてしまって、お前の護符は力を失っちまったんだ。";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "お前はカレウチェ号の呪いを解いたんだな。その後、あの船はお前の前に現れたか？";
			link.l1 = "ああ、そうだ。俺たちは島で直接会ったんだ。俺が彼女と戦って勝った。これで三つの護符が全部揃ったぞ。ほら、 持っていけ。";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "お前は素早くて強い戦士だな、色白の者よ。トゥットゥアタパクは白人が好きじゃねえが、 勇敢で腕の立つ戦士は尊敬するぜ。よくやった。カレウチェを海から追い払ったし、三つの護符も持ってきた。 褒美をやろう。";
			link.l1 = "「俺が永遠に手にできる“力”について、何か約束したんじゃねえのか？」";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "お前の言うことは本当だな。その力を授けてやろう。カリブで俺が知っているその植物の秘密を知る者はいない。\nよく聞け、色白の奴よ！俺の故郷には薬草がある。俺たちはそれをマンガ・ローザと呼んでいる。 その植物を聞いたことがあるか？";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "ああ、俺はそれを手に取ったんだ。ジプシーたちはそれに大きな関心を示している。そして、その中の一人、 治療師アメリアは、なんと……";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "さっぱり分からねえ……";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "薬草師アメリアのことは聞いたことがある。多少は知識があるが、大したことはない。マンガローザの秘密は知らない。 マンガローザをここに持ち込んだ私の故郷の偉大なシャーマンだけが、その力を完全に使いこなせるのだ。";
			link.l1 = "「どんな力だ？」";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "この薬草は俺の故郷で育つが、カリブでも見つかるんだ。背が高くて淡い緑色の植物で、 葉っぱは広げた指みたいなヤシの葉に似ていて、いい香りがする。見ればすぐに分かるし、 他のものと間違えることはないさ。俺はこの植物の秘密を知っている。そこから力を引き出すことができるんだ。";
			link.l1 = "わかったが、どんな力なんだ？";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "俺はマンガローザの薬を作れるんだ。とびきり強力な薬さ。カリブ中でこれを作れるのは俺だけだぜ。俺の薬を飲めば、 男は永遠に強く、速く、賢く、目が鋭く、ハンサムになって、運も良くなる。そんな薬を三つ、 お前のために調合してやるよ。";
			link.l1 = "「とても面白い！」";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "お前は偉大な戦士だ、だからまずは体を頑丈にする薬と素早くなる薬が必要だぜ。 最初の二つを作った後で三つ目の薬を選んでもらう。だが、 それらを作るにはマンガ・ロサを持ってきてもらわなきゃならねえ――俺は一つも持ってねえんだ。";
			link.l1 = "マンガ・ロサはどこを探せばいいんだ？";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "マンガ・ローザはカリブ海では珍しい薬草だ。人があまり歩かない場所に生えている。愚かな奴らはそれを摘んで、 乾かして、吸ったりする。まったく愚か者だ。絶対に吸うな！その力を無駄にするだけだ……\nジャングルや入り江、愚か者が足を踏み入れない秘密の場所を探せ。よく注意して探すんだ。 薬を一つ作るにはマンガ・ローザの茎が五本必要だ。";
			link.l1 = "わかったぜ、大シャーマン。マンガローザが十分集まったら、また来るからな。";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "行け、白き戦士よ。マンガ・ローザを持って来い。後悔はさせないぞ。俺の薬は最高だ。 精霊たちにお前の探索を助けるよう頼んでやる。";
			link.l1 = "ありがとう！またな、シャーマン！";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "薬のためにマンガローザの茎を五本持ってきたか？";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "ああ。必要な五つの植物はここにある。";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "まだです、大シャーマン。俺の探索は続いています……";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "よろしい。明日、日が沈んだら来なさい。君の反応と器用さを高める薬を調合してやろう。";
					link.l1 = "わかったぜ、シャーマン。明日の夕方に来るからな。";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "よろしい。明日、日が沈んだら来なさい。お前の持久力を高める薬を調合してやる。";
					link.l1 = "よし、シャーマン。明日の夕方に来るぜ。";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "よし。どの薬を選ぶんだ？力の薬、鋭い視力の薬、知恵の薬、美しさの薬、それとも幸運の薬か？";
					link.l1 = "力のポーション。";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "鋭い視力のポーション。";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "知力のポーション。";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "美貌のポーション。";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "幸運のポーション。";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  It make your movements faster, and you better fight with fine light weapons.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  It make you more hardy in long journeys, and you better fight with sharp sabers.";
				dialog.text = "薬ができたぜ、青白い顔の戦士。持っていけ。"+sTemp+"";
				link.l1 = "ありがとうございます、偉大なるシャーマン。";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "まだできてねえぞ、白人。後でまた来い。俺の邪魔をするな。";
				link.l1 = "……わかったよ……";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "約束した薬は全部調合したぞ。これでお前はもっと強くなる。嬉しいか？";
				link.l1 = "はい、偉大なるシャーマン。その報酬は確かに価値あるものでした。";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "マンガローザの茎をあと五本見つけて持ってきてくれ。\nそしたら、もう一つ薬を作ってやるぜ。";
				link.l1 = "もっと持ってきてやるぜ。またな！";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "明日もいつも通りに来な。お前を強くする薬を作ってやるから、大きな斧でもっと上手く戦えるようになるぜ。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "明日もいつも通りに来な。お前の目が鋭くなって、どんな的も見逃さねえように薬を煎じてやるぜ。それに、 轟く火の武器でもっと上手く斬れるようになるぞ。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "明日もいつも通り来な。お前のために頭が良くなる薬を作ってやるから、敵からはちゃんと身を隠すんだぜ。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "明日もいつも通り来なさい。お前をもっと男前にして、人を説得するのが上手くなる薬を作ってやるよ。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "明日もいつも通りに来なさい。お前のために運が良くなる薬を調合してやるから、きっと幸運が訪れるぞ。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "俺の芸術、偉大なるシャーマンの技を気に入ってくれて嬉しいぜ。";
			link.l1 = "なあ、トゥットゥアタパク、この三つの護符は何に使うつもりだったんだ？ちょっと気になってさ……";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "この二つの護符の力はすでに感じることができる。\n精霊たちが俺に力を貸してくれるから、これらをさらに強めることができるんだ。三つの護符が揃えば、 俺の祖先である偉大なチャビン族のシャーマンの叡智と啓示が授けられるのさ。";
			link.l1 = "なるほど。よし、改めて素晴らしい薬をありがとう。あなたは本当に偉大なシャーマンだ。そろそろ行かねばならない。 さようなら、トゥットゥアタパク、また会えることを願っている。";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "さらばだ、白き戦士よ。もう俺を探す必要はない。これから隠遁し、祖先の知恵を極めるつもりだ。\n旅路に精霊の加護があらんことを！";
			link.l1 = "さて……はは……精霊たちがあなたの道を導いてくれますように、偉大なるシャーマンよ。さらば……";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("You have given amulets");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "お前は俺を悲しませるな、青白い顔のやつ。俺は精霊たちと儀式を行い、このお守りに力を込めたのに、 お前はそれを無駄にした。俺は悲しい。もう行け。トゥットゥアタパクはお前に言うことはもうない。";
			link.l1 = "すまない、ただ本当に運が悪かったんだ……まあ、仕方ない。さようなら、シャーマン。";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "無駄だぜ、水夫。お前が俺に勝つことはできねえ。甲板に倒れてる俺の仲間たちも、 夜明け前には骨を集めて再び立ち上がるだろう。俺たちは殺せねえ。死神は永遠に俺たちを見捨てたのさ。";
			link.l1 = "ちくしょう！お前、生きてるのか死んでるのか？まあ、生きてる方がありそうだな――死んだ奴は普通おとなしく横たわってて、剣なんか振り回さねえからな。で、お前は何者だ？なんで俺の船を襲ったんだ？ ";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "俺はフライング・ハートのバルタザール・デ・コルデスだ。\n俺のことを何も知らねえ哀れな腰抜けどもは、俺をフライング・ダッチマンの船長、ヴァン・デル・デッケンと呼ぶ。\nだが、そんなことはどうでもいい。重要なのは、お前があの護符を持っていることだ――今ここでいただくぜ。\n俺にはそれが必要なんだ！感じるんだよ！チャビン族の偉大なる護符、三つのうちの一つが、ついに俺のものになる！\nひれ伏せ、死すべき者よ！そうすれば、楽に死なせてやるかもしれねえぞ！";
			link.l1 = "地獄へ落ちろ、この死体め！";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "信じられねえ！自分の血を見たり痛みを感じたりするなんて、最後にあったのはいつ以来だ…どうしてなんだ！？";
			link.l1 = "今回はお前の負けだ、バルタザール・デ・コルデス。お前の話は知っている。 翡翠の髑髏はチャビン族の神殿に戻されたし、ユム・シミルの呪いもお前やお前の部下たちにはもう及ばない。 お前はもう船員たちを蘇らせることはできないんだ。";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "おお、つまり自分を救済者だとでも思ってるのか？違う！バルタザール・デ・コルデスは、 残されたわずかな命でも高く売り払ってやるぜ！";
			link.l1 = "フライング・ハート号の最後の航海はここ、カエル・ロアで終わる。\nそして今度は二十五年前のようにお前の船を海底から引き上げることはできねえぞ。";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "ホーク！二十五年が過ぎたが、まるで昨日のことのように今でも覚えているぜ。俺たちを眩ませ、 船を真っ二つに裂いたあの光球の輝き……あれがフライング・ハート号とバルタザール・デ・コルデスの最初で最後の敗北だった。\nだからこそ、最後にもう一度剣を交えようじゃねえか、船長！戦で死ぬのは軽いこと、むしろ歓迎だぜ！";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Caleuche_Alonso_1":
			dialog.text = "船の中の汚れは片付けたぜ、船長。今回は死体もちゃんと沈んだ。でも、この船自体が……どうしてまだ浮かんでるのか、俺にはさっぱりわからねえ。";
			link.l1 = "呪いが彼女を繋ぎ止めていたんだ、アロンソ。だが、それももう終わった。";
			link.l1.go = "Caleuche_Alonso_2";
		break;
		
		case "Caleuche_Alonso_2":
			dialog.text = "ご命令は？火をつけて終わらせちまうか？";
			link.l1 = "考えておくぜ。ボロボロでも「フライング・ハート」は俺たちの船を穴だらけにしかけたからな。";
			link.l1.go = "Caleuche_Alonso_3";
		break;

		case "Caleuche_Alonso_3":
			dialog.text = "この難破船は火力だけはやたらとあるんだ、まったく忌々しいぜ…俺が言いに来たのはこういうことだ――うちの乗組員にジャックって水夫がいるんだが…";
			link.l1 = "ジャック・トルドーか？覚えてるぜ。最近俺たちに加わったんだろ？";
			link.l1.go = "Caleuche_Alonso_4";
		break;

		case "Caleuche_Alonso_4":
			dialog.text = "ああ、船長。実はな、あの野郎は宝の匂いを嗅ぎ分けるのが抜群なんだ――本当にすごいぜ。アンデッドどもが静かになった途端、あいつはすぐに寝台のひとつに飛び乗って、下にもぐり込み――そして箱を引っ張り出したんだ。その箱の中には……五千ドゥブロン金貨が入ってたんだぜ！";
			link.l1 = "五千か？ふむ……バルタザール・デ・コルデスとその手下どもは、本気で呪いから逃れたかったんだろうな。楽な暮らしを夢見て、 金貨で懐をパンパンにしてたんだ……すべてが終わった暁には、ってな。";
			link.l1.go = "Caleuche_Alonso_5";
		break;
		
		case "Caleuche_Alonso_5":
			dialog.text = "俺たちの船員も、そんな暮らしは嫌じゃねえぜ、船長…仲間たちと分け合えば、絶対に忘れねえさ。だが、分け合わなければ、それも忘れねえぞ。";
			link.l1 = "その通りだな、アロンソ。たまには船員たちにご褒美をやるべきだ――よくやってくれたからな。奴らには取り分の半分を配ってやれ。それとジャックには一週間見張りを免除してやれ。 今日はグロッグの代わりにラムを振る舞うことを許す。ただし油断はするな――海は過ちを許さねえってことは分かってるだろう。";
			link.l1.go = "Caleuche_Alonso_6";
			link.l2 = "ふむ……アルフォンソ、お前の言う通りかもしれんな。乗組員たちもたまには羽を伸ばしたほうがいいだろう。 取り分の四分の一をやれ。それと、あの酔っ払いどもがどこかの港に錨を下ろす前に宴を始めやがらねえよう、 しっかり見張っておけよ。\n";
			link.l2.go = "Caleuche_Alonso_7";
			link.l3 = "あいつらが最初の港で酒場や売春宿に散っていくってのか？俺は一人ずつ一ヶ月もかけて集める気はねえ。 払ってる給金で十分だ。それと、ドゥブロンはここに持ってこい。誰にも持ち逃げさせねえためにな。";
			link.l3.go = "Caleuche_Alonso_8";
		break;
		
		case "Caleuche_Alonso_6":
			dialog.text = "承知しました、船長。心配いりません、仲間たちは絶対にあなたを裏切りませんよ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_2");
		break;
		
		case "Caleuche_Alonso_7":
			dialog.text = "ああ、船長。あいつら悪党どもをしっかり抑える方法は心得てるぜ――俺に任せてくれ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_3");
		break;
		
		case "Caleuche_Alonso_8":
			dialog.text = "承知しました、船長。もちろん船員たちはもっと期待していましたが……ここではあなたが船長、決めるのはあなたです。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_4");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "やっと目を覚ましたな、船長…。気分はどうだ？";
			link.l1 = "くそっ、何があったんだ？頭が割れそうに痛ぇ……";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "俺たちが船長室に入ったとき、お前は床に倒れてて、まったく動かなかったんだ。 仲間たちがすぐにお前を抱え上げて俺たちの船まで引きずってきた――ちょうどその時、甲板に転がってた死体どもがまた起き上がり始めたんだ\n聖母様、そしてすべての聖人よ！俺たちは急いで係留索を切って逃げようとしたが、 あいつらの船からの一斉射撃で俺たちのオンボロ船はあっという間に木っ端みじん、操縦不能になっちまった。 それからあいつらは帆を上げて、一瞬で姿を消した\n俺たちの船は座礁して、生き残った奴らはボートで岸までたどり着いた。今日、多くの仲間が死んじまった……もし俺たちが船に残っていれば……だが、あの嵐で船はもう終わりだと誰もが思ってたんだ。";
			link.l1 = "君たちのせいじゃない、諸君。正しい判断だった。感謝する、覚えておくよ。";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "俺たちはお前をボートに引きずり込んで、それから岸まで運んだんだ。お前、ほとんど死にかけてたぜ…";
			link.l1 = "命の恩人だ。俺はどれくらいここで気を失って寝てたんだ？";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "丸一日だ。お前の傷を洗って包帯を巻き、薬を飲ませてラム酒も流し込んだぜ。すぐに良くなるはずだ。";
			link.l1 = "今度こそ絶対に死なねえさ。\nでも、あんまり気分は良くねえな……";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "それは間違いねえな……あれはフライング・ダッチマンだったのかい、船長？なんで奴らは俺たちを襲ったんだ？それに、 なんで乗り込んでくる前に砲撃しなかったくせに、乗り込んだ後で一斉射撃だけで俺たちの船を沈めかけたんだ？\n";
			link.l1 = "奴らの船長は、俺がインディアンのシャーマン、トゥットゥアタパクに話したあの護符を必要としていたんだ。 だからすぐには俺たちを沈めなかったが、奴らの頭が護符を手に入れた途端、あっという間に俺たちは始末された……なんて悪夢だ！死人どもが操る船なんて！信じられねえ……";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "ああ、今度は俺たちがフライング・ダッチマンに遭遇する番だったんだ。機会があれば教会に行って、 奇跡的な救いに感謝してロウソクを灯し、主に祈るつもりだ……";
			link.l1 = "俺も……たぶんな。だが、まずはあの村に戻るぜ。トゥットゥアタパクに全部話さなきゃならねえ。 あの呪われた船が俺たちを襲ったのは、あの護符のせいだ！あの赤い肌の悪魔は、 なぜあの生ける死者どもがそれを欲しがったのか、何か知ってたに違いねえ。";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "わかった。でも気をつけてくれよ、船長。傷はまだ治りきってねえんだ。念のため、誰か連れていってくれよな。";
			link.l1 = "気をつけるよ、約束するぜ。見捨てずにいてくれてありがとう！";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "何言ってんだよ、船長！俺たちはあんたのためなら地の果てまで行くし、何千体ものアンデッドとも戦うぜ！ こんなに失ったのはくそったれだが、この話は伝説として語り継がれるさ。";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "おい！まだ売るほど蛇の皮が集まってねえんだ、さっさと失せろ！";
			link.l1 = "ふむ……お前がファーガス・フーパーか？";
			link.l1.go = "fergus_1";
			DelLandQuestMark(npchar);
		break;
		
		case "fergus_1":
			dialog.text = "いいや、俺の名はトゥットゥアタパクだ。さっさと消えねえと呪ってやるぜ。だから急いだほうがいいぞ、さもないと……";
			link.l1 = "……俺が正気を失って自分の船を燃やし、船員たちに殺されて持ち物を全部奪われるってわけだな。そうだろ？";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "うぐっ…なんだお前は！？どうやってここに…";
			link.l1 = "俺たちには共通の知り合いがいるんだ、ファーガス。あいつは灯台守で、名前は\n "+GetFullName(sld)+"。あんたのことは聞いてるし、探しに来いと頼まれたんだ。ちなみに、 俺はシャーマンのトゥットゥアタパクと個人的に知り合いだから、あんたの冗談は通じなかったぜ、悪いな。聞いてくれ、 俺は揉め事を求めてるわけじゃねえ。あんたから買いたいものがあるんだ、蛇の皮じゃないぞ。";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "おお、俺の古い友人を知ってるのか！あいつは元気か？灯台で退屈死してねえか？まあ座れよ、水夫、俺と一杯やろうぜ！ ";
			link.l1 = "すまない、ファーガス、本当に時間がないんだ。聞いてくれ、あのインディアンのお守りが必要なんだ。 お前の亡くなった船長がトゥトゥアタパクと一緒に本土から持ち帰ったものの一つだよ。いい値で買い取るし、 お前も危険な品から解放されるぞ。";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "「それの何がそんなに危険なんだ？今のところ何の害も見てねえぜ。ただの役立たずな石じゃねえか」";
			link.l1 = "それはお前がもう海を渡っていないからだ。俺もつい最近まで同じようなお守りを持っていたんだ。 幽霊船がこういう物を狙っているんだぜ。";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "冗談だろ、相棒？もしかしてトゥットゥアタパクを知ったせいでおかしくなっちまったのか？気をつけろよ、船長、 あの赤い肌の悪魔はお前の心まで喰らい尽くすぜ…";
			link.l1 = "信じるかどうかは任せるが、俺は本当のことを言ってるんだ。自分の目で見てなけりゃ、俺だって信じなかったさ。 聖書に誓ってもいいし、一緒にいた連中に聞いてみてもいいぜ。あのカレウチェとの遭遇のあと、 俺はかろうじて生き延びたんだ。";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "カレウチェ号か？";
			link.l1 = "まあ、大抵の奴はフライング・ダッチマンって呼ぶが、本当の名はフライング・ハートだ。\nまあ、どうでもいい。とにかくそのお守りを俺に売ってくれ。どうせお前には役に立たねえって、俺は知ってるんだ。";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "その通りだ。これはただの役に立たないガラクタさ、まあ見た目はなかなか綺麗だけどな。聞いてくれ、 本当ならすぐにでもお前に売ってやったんだが、実はもう手元にないんだ。狩りでジャングルに出てる間に、 小屋から他の物と一緒に盗まれちまったんだよ。ごく最近のことでな、だいたい一ヶ月前だ。悪いが、 もうどうにもしてやれねえんだ。";
			link.l1 = "「で、誰がそれを盗んだんだ？」";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "俺が自分の家を荒らした奴を知ってたら、ここでじっと座ってると思うか？ベリーズの外には盗賊や山賊の一味がいて、 町の中にも手引きする奴らがいるんだ。まあ、そう考えてるのは司令官だけどな。だが、 俺はあいつらの仕業だと確信してるぜ。";
			link.l1 = "司令官は盗賊のことを知っていながら、まだ何もしねえのか？";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "あいつが何かしているのかどうかは知らない。ただ一つ確かなのは、俺の持ち物が全部なくなったってことだ。 そしてお前の大事な護符も一緒にな。\nその盗賊どもを探してみろ――もしかしたら奴らの懐にあるかもしれねえ。売りさばくのは難しいだろうしな――商人どもにとっちゃ、そんなものは何の役にも立たねえからな。";
			link.l1 = "よし、司令官に会いに行ってくる。幸運を祈るぜ、ファーガス！";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "おい！何の用だ？客なんて来ると思ってなかったぜ。消え失せろ！";
			link.l1 = "なんでそんなに無礼なんだ、友よ？ちょっと聞きたかっただけなんだが…";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "聞こえなかったのか？さっさと失せろ、じゃねえとぶっ飛ばしてやるぞ！";
			link.l1 = "ふむ……まあ、やっぱりお前が俺の探している人物かもしれねえな。ずいぶんと緊張してるじゃねえか、相棒……";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "自分が賢いつもりか？もう一度言うぞ。今すぐ消え失せるか、衛兵を呼んで牢屋にぶち込ませるか、どっちかだ！";
			link.l1 = "俺を牢屋にぶち込むって？そりゃあ面白い話だな。ふむ、これで俺が探していた相手をほぼ確信できたぜ。よし、 同意しよう。衛兵を呼んで、それから一緒に司令官の執務室まで歩こうじゃねえか、まるで仲良し家族みたいにな。 さっき行ったばかりだから道は覚えてるぜ……衛兵！衛兵ども！";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "くたばれ！ぶっ刺してやるぜ！";
			link.l1 = "おお、ほっほっほ！やれるもんならやってみな！";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "おい、旅人！ようこそ、ようこそ……夕飯も宿も、金さえ払えば何でもあるぜ。さあ、財布の中身を全部出す覚悟をしな！";
			link.l1 = "そんなに急ぐな、旦那。お前に用があるんだ。";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "商売だと？ははっ！お前の唯一の商売は持ってる銀と金を全部渡すことだぜ！";
			link.l1 = "もう黙れよ。お前が待ってたベリーズからの手紙を持ってきたぜ。使者は衛兵を通れなくて、この件を俺に託したんだ。";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "見せてくれ！";
			link.l1 = "「ここに…」";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "（読みながら）ふむ……確かに妙だな……どうやってお前が巻き込まれたんだ？";
			link.l1 = "もう言っただろう、お前の男は捕まったから、俺が代わりに仕事を引き受けたんだ。あいつは金と、 お前からの温かい歓迎を約束してくれたんだよ…";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "温かい歓迎だと？ああ、いいぜ、相棒。お前を温めて、飯も食わせて、金もやるし、そういうのは全部やってやる――だがな、お前も俺たちに、衛兵の犬じゃねえって証明してもらうぜ。今はちょうどケリをつける用事があるんだ\n最近、近くの入り江に商人が来たらしい。どうやら税関をすり抜けて、商品を町に持ち込もうとしてるみたいだが、 俺たちはちゃんと関税を取らせてもらうぜ。俺たちは一応、法を守る連中だからな！お前も一緒に来い。 剣のどっちがどっちか、分かってるか？";
			link.l1 = "「俺にもこの任務の分け前があるのか？」";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "もちろんだぜ！戦いで勇敢に戦って、生き残ればな。ただし、楽な仕事だと思うなよ。商人は一人じゃねえ、 護衛がついてるし、それもかなり大勢だ。さて、そろそろ行くぞ――獲物はすぐそこだ。\n野郎ども！武器を用意しろ、出発するぞ！";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "臆病者じゃねえな。よくやった！お前の取り分だ。どう受け取る？現金か？それとも商品か？ あいつらは酒をたくさん積んでたから、きっといい値で売れるぜ。";
			link.l1 = "現金。";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "「商品。」";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "ほらよ！それと、この財布は手紙を届けてくれた礼だ。";
			link.l1 = "ありがとう！これぞ俺の好みだぜ！";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "ほらよ！死ぬほど飲みすぎるなよ、ははは！それと、この財布は手紙を届けてくれた礼だぜ。";
			link.l1 = "ありがとう！これぞ俺の好みだぜ！";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "俺にはあんたがまともな奴に見えるぜ。もう一つ仕事をどうだ？あんたが届けてくれたあの手紙のことなんだ。";
			link.l1 = "ああ、いいぜ。";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "じゃあ洞窟に来い。奴らは二人いる。前に会った場所までジャングルを進んで、左の道を行け。三日後、 真夜中から一時までの間に洞窟の入口で集まるんだ、いいな？おとなしくしてれば、俺たちの仲間に入れてやる。 ただし覚えとけ――町で何か喋ったら終わりだぞ。俺の手は長いんだ。";
			link.l1 = "もう脅かすのはやめてくれよ。分かったって。魚みたいに静かにしてるからさ。三日後に待ってろ、必ず行くぜ。 楽して稼げる金は大好きだ！";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "よし、相棒。さっさと消えな、衛兵が来る前にな。俺たちもここを出るぜ。";
			link.l1 = "また会おうぜ、相棒……";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "なんだと！俺たちの財産を奪おうってのか？この汚ねえ虫けらめ、ただじゃ済まさねえぞ！";
			link.l1 = "今、誰を虫けら呼ばわりしやがったんだ、このクズ野郎！？";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "やあ、同業者！何の用でここに来たんだ？";
			link.l1 = TimeGreeting()+"、ジャクソン旦那。ようやくお会いできて嬉しいです。";
			link.l1.go = "reginald_1";
			DelLandQuestMark(npchar);
		break;
		
		case "reginald_1":
			dialog.text = "「ジャクソン旦那」だと、ははっ！まあ正直言うと、俺もすぐにそう名乗ることになるだろうな。俺はこの忌々 しい会社のために休みなく働いてるんだ……でも給料はいい、すごくいいんだよ！\nそれで、どうしてここに来たんだ、相棒？";
			link.l1 = "共通の知り合いである灯台守から、あんたが古代インディアンの護符を持っていると聞いたんだ。 どうせ使い道もなかったんだろうし、俺にはどうしても必要なんだ。譲ってもらえないか？";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "「ああ、あの引退した甲板長に頼んだ派手なガラクタのことか？そうだな、旦那、確かに役に立ったことは一度もねえ。 ただ見た目がいいだけさ。」";
			link.l1 = "「それはいくらで売るつもりだ？」";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "実は、ちょっとした問題があってな……説明させてくれ。今はそれを持っていないんだ。使い道がなかったから、 他の荷物と一緒に岸の自分の箱に置いてきたんだよ。";
			link.l1 = "ああ、それでまだ…まあ、いいさ。とにかくお前の宝箱のところへ行こうぜ。そこでお前からお守りを買うだけだ。簡単な話さ。 どこにしまってあるんだ？";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "そんなに単純な話じゃねえんだ。俺の宝箱はバルバドスの灯台の塔にあって、 俺がいない間に誰にも手を出されねえようにしっかり鍵をかけてある。悪いが、バルバドスには一緒に行けねえんだ。 オランダ人との契約で、フィリップスバーグとポートロイヤルの間を航海して、 きっちりスケジュールを守らなきゃならねえ。バルバドスはその航路から大きく外れてるんだよ。";
			link.l1 = "「それで俺たちに何ができるんだ？あのお守りは本当に、心から必要なんだ！」";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "ふむ……まあ、一つだけ手はあるぜ。俺の宝箱の鍵を渡すから、お前が自分でバルバドスまで行くんだ。ただし、 中身の全てを弁償してもらうぜ。それが済んだら、中身は好きにしていい。疑って悪いが……分かってくれよ。お前のことは初めて見るんだ。";
			link.l1 = "いくらだ？";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "五百枚の金貨だ。それ以下は受けねえ。";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "わかったぜ！ほら、金貨だ。";
				link.l1.go = "reginald_10";
			}
			link.l2 = "うーん……そんなに多くのドゥブロン銀貨は持ってねえんだ。";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "じゃあ、金を用意できたらまた俺のところに来な。俺を一度見つけられたなら、また見つけられるはずだ。 しばらくの間はセントマーチンとジャマイカの間を航海してるぜ。";
			link.l1 = "よし、取引成立だ。";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "reginald_9":
			dialog.text = "またお前か、友よ？500枚のコインは持ってるか？";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "ああ。ほら、金貨だ。";
				link.l1.go = "reginald_10";
			}
			link.l2 = "まだだが、今取り組んでいるところだ。";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			RemoveDublonsFromPCharTotal(500);
			DelLandQuestMark(npchar);
			
			dialog.text = "素晴らしい！では、これが鍵だ。お願いが一つだけあるんだ。中身を全部持ち出したら、 鍵は錠前に差したままにしておいてくれ。新しい錠前と鍵を作らせるのは勘弁してほしいからな。";
			link.l1 = "「よし。」";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "それじゃあ、幸運を祈るぜ、友よ！良い航海を！";
			link.l1 = "「あなたにも同じく……よい航海を、ジャクソン旦那！」";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_SpawnItemsInTheChest");
			AddQuestRecord("Caleuche", "20");
		break;
		
		case "Caleuche_Reginald_21":
			dialog.text = "俺たちに何の用だ、悪党め？ここはオランダ西インド会社の船だぞ、こんな真似をしてタダで済むと思うなよ。 貴様もその手下どもも、地の果てまで追い詰められるぞ。\n";
			link.l1 = "オランダ人やあいつらの商会なんざ、俺にはどうでもいい。俺が狙ってるのは古いインディアンの護符だ。 お前がそれを持ってる――いや、持ってたのは知ってるんだ。";
			link.l1.go = "Caleuche_Reginald_22";
		break;

		case "Caleuche_Reginald_22":
			dialog.text = "頭がおかしいのか！？ガラクタ一つのために船を襲うなんて！？";
			link.l1 = "黙ってそれを渡せ。そうすりゃ生きて帰れるかもな。";
			link.l1.go = "Caleuche_Reginald_23";
		break;

		case "Caleuche_Reginald_23":
			dialog.text = "くそっ……持ち歩いてねえよ。バルバドスにあるんだ。";
			link.l1 = "じゃあ、お前のボロ船は今すぐ海の底行きだな。それから、お前は俺の船倉でネズミと一緒に過ごすことになるぜ。 航海の間に、どこにあるかじっくり話してもらうさ。信じろよ――うちの船には、どんな頑固者でも秘密を吐かせる連中がいるんだ……丁寧なやり取りなんて必要ねえからな。";
			link.l1.go = "Caleuche_Reginald_24";
		break;

		case "Caleuche_Reginald_24":
			dialog.text = "そんな必要はねえ。灯台の宝箱に入ってるぜ。鍵がかかってる。これがその鍵だ。";
			link.l1 = "賢い選択だな、相棒。お前みたいな奴がもっと頭を使えばいいんだがな……そうすりゃ俺の手も血で汚れずに済むんだぜ。";
			link.l1.go = "Caleuche_Reginald_24_1";
			link.l2 = "賢い選択だな。しかしな……お前を生かしておくわけにはいかねえ。どうせオランダの商人どもに直行するだろうし、奴らの目を引きたくねえんだよ。 ";
			link.l2.go = "Caleuche_Reginald_24_2";
		break;
		
		case "Caleuche_Reginald_24_1":
			dialog.text = "あの箱には、俺が長年オランダ人に仕えて稼いだものが全部入ってるんだ…";
			link.l1 = "じゃあ、こうしようぜ。宝箱は俺のもん、お前はその大事な命を守れりゃいいだろ。これで文句ねえだろ…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_EndFightWithReginald");
		break;
		
		case "Caleuche_Reginald_24_2":
			dialog.text = "「ううっ……」";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_KillToReginald");
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "やあ、船長 "+GetFullName(pchar)+" ウィレムスタッドへようこそ、お迎えできて嬉しいです。";
			link.l1 = "こんにちは、神父様。あなたのことは覚えていません。私たちは面識がありましたか？";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "お前の船が停泊した後で、お前について調べさせてもらったぜ。\nそれで、ちょっと助けを頼めるんじゃねえかと思ってな。";
			link.l1 = "とても興味深いな。それで、なぜ俺なんだ？";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "あなたは自由州共和国のために多大な貢献をしてくれたからだ。会社とも良好な関係にあり、総督とも親しい。 私はすでに何人かの権威者に頼んだが、断られてしまった。しかし、あなたのような高貴な方なら、 主に仕える者のささやかな願いを断ることはないと信じている。";
			}
			else
			{
				dialog.text = "なぜなら、あなたは我々の総督の配下ではないからです。会社にも雇われていませんし、我々の軍とも関わりがない――もしそうなら、あなたも他の役人たちのように、うるさいハエでも追い払うみたいに私を無視したでしょう。 私はすでに何人もの当局者に訴えましたが、みなに門前払いされましたから。";
			}
			link.l1 = "わかった。それで、依頼の内容は何だ？";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "銀行の裏手に家がある。その家に住んでいたご婦人が、地元の者でもオランダ人でもない、 いかにも怪しい奴に部屋を貸していたんだ。そこで我らが上長、神父様が\n "+sld.name+"、彼を見覚えがあった\nそれはジョアキム・メリマン、異端審問に魔術と邪悪な力との関わりで告発されたポルトガル人だった。 彼は新世界で異端審問から身を隠していたんだ。知ってるだろう、 スペイン人は気に入らない者を異端や魔女として火あぶりにするために告発することが多いが……この場合は本当にそうだった。メリマンは魔術師なんだ\nだから、彼はしばらくウィレムスタッドに住んでいたが、現れた時と同じように突然姿を消した。そしてしばらくして、 彼に部屋を貸していた女が、その家から出てくるのを誰も見なくなった。決して！それ以降、 どこでも彼女を見かけた者はいない\nそして夜になると、市民たちは時折、二階の窓に赤青の光がちらつき、 不気味な叫び声のような奇妙な音が聞こえることがある。神父 "+sld.name+" 司令官に訴えた。彼は兵士四人の巡回隊を派遣し、家を捜索させたが、何も見つからなかった――女将自身も、他の誰も、怪しいものも全くなかった\nだが、奇妙な出来事は続いている。女将は一度も姿を見せず、夜になるとあの地獄のような光が今もそこに見える。 それに、最近は乞食が二人行方不明になった。彼らが教会前で話しているのを聞いたが、家に持ち主がいないと知って、 泊まることに決めたらしい。それ以来、誰も彼らを見ていない。";
			link.l1 = "俺にあの家に入って、本当に何が起きたのか調べてこいってことか？";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "その通りでございます、旦那。どうか聖なる教会をお助けくださいませ。司令官殿は、 巡回隊が何も見つけなかったから我々の思い過ごしだと言っております。政府も同じ考えでございます。 庶民たちは自分たちへの明確な脅威とは思っていないので、まったく気にしておりません。";
			link.l1 = "ふむ……それで、俺は夜にそこへ行かなきゃならねえのか？";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "はい、旦那。昼間はあそこは静かなんだ、だから兵士たちは何も見つけられなかったんだよ。 司令官も自分の部下が心配なんだろう、俺だってそうさ。でも、どうかお願いです。神父様\n "+sld.name+" あなたの働きに感謝し、報酬も渡すだろう。夜にそのアジトへ行ったら、そこで見たことを彼に伝えてほしい。 私が保証するが、我々の不安には十分な根拠があるのだ。";
			link.l1 = "わかった。考えておくぜ。";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "ありがとうございます、船長。私のささやかなお願いをどうか断らないでください。どうか、我らの主と信仰、 そしてすべての聖なるものの名のもとに、この願いを叶えてください。私の祝福とともに行きなさい。";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "visit the house of Joaquim Merriman, where, according to him, strange things happen at night. Remembering that special gleam in Merriman's eyes when he looked at the jade skull, I feel a little creepy. It seems that the old Jew could not resist the sum of half a million pesos. Whatever the case, I don`t feel like going to Merriman former abode at night.";
				else sTemp = "visit the house of my old acquaintance Joachim Merriman, where, allegedly, strange things are happening at nights. I still remember that glitter in Merriman's eyes, when he was looking at the skull, and honestly I feel frightened. I am not really fond of the idea to visit his former abode in the night, who knows what kind of devils lurk there.";
			}
			else sTemp = "visit the house at the back of the bank, where some Joachim Merriman had been renting a room. Apparently it is that warlock, of which Tuttuathapak was talking about. According to the monk, strange things are happening in this house in the night. I really feel uncomfortable about visiting the warlock's former home, who knows what kind of devils lurk there.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "待てよ、相棒。命が惜しいなら、そこには行かない方がいいぜ。";
			link.l1 = "「それで、どういう話だ？」";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "俺を信じろ、お前は知りたくもねえはずだ。だが死神はすぐそこにいるぜ、聖書に誓ってもいいが、 生きて帰れるとは思うなよ。お前の想像を超えるものが待ってるんだ。";
			link.l1 = "そうかい、あんたがそう言うなら、運命を試すのはやめておくぜ。警告してくれてありがとな。";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "どういたしまして。その道には近づくなよ。";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "その道には近寄るなよ、相棒。";
			link.l1 = "ああ、覚えてるぜ…";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "本当にそこへ行くつもりか？";
			link.l1 = "もちろんだ。 "+sld.name+"ハバナの教会の院長が私をここに送った。ここで何が起きているのか調べ、しかるべき措置を取らねばならない。";
			link.l1.go = "cavehunter_6";
			DelLandQuestMark(npchar);
		break;
		
		case "cavehunter_6":
			dialog.text = "ここで何が起きてるんだ？ここで何が起きてるか自分の目で見たら、きっと震え上がるぜ。";
			link.l1 = "「歩く死者のことか？」";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "ああ。俺の言葉を信じたほうがいいぜ。";
			link.l1 = "俺はお前の言葉を信じてるぜ。ウィレムスタッドであの邪悪な化け物にすでに遭遇して、ぶっ潰してきた。\nそして今からこの洞窟に入り、潜んでいる汚物どもを全て叩き潰してやる。";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "お前、一人でそこに行くつもりか？死にに行くようなもんだぜ、相棒。あそこにどれだけあの化け物がいるか、 全然分かってねえだろ。まあ、どうしても行くってんなら勝手にしな。俺は教会に行って、 お前の魂の安らぎのためにろうそくでも灯してやるさ。";
					link.l1 = "俺を早まって埋めるんじゃねえ。もっとひどい目にも遭ってきたんだぜ。";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "二人だけで行くのか？悪いが、それじゃあ到底無理だぜ。あいつらがどれだけいるか、全然分かってねえだろ。 まるで自殺行為だ。";
					link.l1 = "お前はまだ俺たちのことをよく知らねえんだな、友よ。どきな、俺たちがこの穢れた巣窟を清めてやるぜ。";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "たった三人だけか？それだけでやろうってんだから、よほど場数を踏んだ戦士なんだろうな。\nだが、それでも俺はお前たちがやり遂げられるか心配だぜ。\nあの洞窟の中にどれだけあいつらがいるか、お前たちは全然分かってねえんだ。";
					link.l1 = "お前はまだ俺たちのことをよく知らねえんだな、友よ。どきな、俺たちがこの穢れた巣窟を清めてやるぜ。";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "お前ら、臆病者じゃねえな。だが、あいつらがどれだけいるか本当に分かってねえだろう。こういう時は、 一人一人が大事なんだ。くそっ、俺も一緒に行くぜ、あのクズどもをマスケットでぶっ放してやる！";
					link.l1 = "お前は勇敢な奴だな、友よ。助けを断る理由はねえ。行くぜ！";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "行くぞ！汚らわしいアンデッドどもに死を！";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "いやあ、まさに大虐殺だったな！まさかこんなに多くの死者がこの場所に潜んでいたとは思わなかったぜ！まあ、 とにかく今はひとまず休めるな……。お前をここに送り込んだあの上司の神父に、このことをちゃんと伝えてくれよ。 お前の報告の後は異端審問官どもがきっと徹底的に調べてくれるだろう。アンデッドの相手はあいつらの仕事だからな、 俺はただの猟師にすぎねえよ。";
			link.l1 = "必ず伝えておくぜ。助けてくれてありがとう、相棒。お前みたいな奴は珍しいぜ、 死神に立ち向かうなんて普通はできねえ！幸運を祈る！";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "そこを動くな！ここは立ち入り禁止だ！";
			link.l1 = "えっ……で、中には何があるんだ？";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "そこには危険な魔術師が見つかった。\n聖職者と彼らに同行する兵士だけが入ることを許されている。";
			link.l1 = "なるほど。その魔術師は逮捕されたのか？";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "そのような質問には答える権限がありません、旦那。そろそろお引き取りください。";
			link.l1 = "わかったぜ。幸運を祈る！";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "動くな、人間！お前は神殿のど真ん中にいるんだ、もう引き返すには遅すぎるぞ。";
			link.l1 = "お前は誰だ！？";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "俺はチャビナビ族の族長、この聖なる場所の守護者だ。お前がこの神殿に入った最初の者じゃねえ。だが、 これまでに生きてここを出たのは二人の男と一人の女だけだ。それだけが、今こうしてお前と話してやる理由だ。 何のためにここへ来た、白い顔の者よ？";
			link.l1 = "俺はここに古代の遺物、翡翠の髑髏を持ってきた。五十年前、それは本土奥深くのインディアンの神殿から奪われたんだ。 俺はその聖堂を探し出して、この遺物をお前たちの神に返すつもりだった。";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "お前たちのような者からそんな言葉を聞くとは妙なものだ。信じられねえな。お前ら白い顔の連中は、 いつも何かを奪いに来るばかりで、決して何も返さねえじゃねえか。";
			link.l1 = "俺は嘘はつかねえ。ドクロを返せば、カリブ海を恐怖に陥れている幽霊船の船長にかけられた呪いを解き、 奴を再び人間に戻すことができる。そうすりゃ、この世から奴を永遠に消し去ってやるぜ。";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "どうしてお前は我々の神がその呪いを解くと知っている、白い顔のやつ？我々の神が、お前に語りかけるのか？";
			link.l1 = "いいや。俺はトゥットゥアタパクという名の偉大なシャーマンの助言でここに来たんだ。彼の言う通り、 頭蓋骨が呪いの鍵であり、カリブで唯一の神殿がここだ。そしてな、あんたも知ってるだろうが――俺は本当に彼が過去の精霊たちと語り合えると思うぜ。もしかしたら、あんたともな、ジャガー戦士たちの酋長よ。";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "お前の言葉には驚かされるな、色白の者よ。だが、まだ完全にはお前を信用できねえ。だがもし、この寺院に我々 の聖遺物を返しに来たのなら、きっと我々のシャーマンがこの場所や、その成り立ち、歴史、 住人たちについて話したはずだろう\nもしそうなら、俺の質問には簡単に答えられるはずだ。そのときは、お前が誠実だったと認めて通してやるし、 さらに褒美もやろう。";
			link.l1 = "だったら聞けよ！";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "俺はチャビナビ族とジャガー戦士たちの族長だ。千年前は人間だったが、今はこの聖なる部屋で使命を果たしている。 俺に命じる神はどの神だ？";
			link.l1 = "ミクトランテクートリ。";
			link.l1.go = "question1_l";
			link.l2 = "「ククルカン。」";
			link.l2.go = "question1_l";
			link.l3 = "ユム・キミル。";
			link.l3.go = "question1_r";
			link.l4 = "「インティ。」";
			link.l4.go = "question1_l";
			link.l5 = "カウイル。";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "お前たち白い顔の者たちが来る前は、この大地全体――北の大雪原から南の大平原まで――は、俺たち、一つの家族の兄弟たちのものだったんだ……";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "お前たち色白の者が来る前は、この大地全体――北の大いなる雪原から南の広大な平原まで――は、我ら一族の兄弟たちのものだったのだ…";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "この寺院を建てたのはどのインディアン部族だ？";
			link.l1 = "インカ。";
			link.l1.go = "question2_l";
			link.l2 = "「チャヴィン族。」";
			link.l2.go = "question2_r";
			link.l3 = "「マヤ。」";
			link.l3.go = "question2_l";
			link.l4 = "アステカ。";
			link.l4.go = "question2_l";
			link.l5 = "アラワク族。";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "我々の民は進歩し、知恵を得て、新たな森や平原、島々を征服した。\nこの神殿を建てた人々は、大いなる海の向こうの森からやって来たのだ……";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "我々の民は進歩し、知恵を得て、新たな森や平原、島々を征服した。この神殿を建てた人々は、 大いなる水の向こうの森林地帯からやって来たのだ…";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "あの栄光ある者たちの一団を率いたのは誰だ？";
			link.l1 = "偉大な酋長。";
			link.l1.go = "question3_l";
			link.l2 = "偉大なる神父。";
			link.l2.go = "question3_l";
			link.l3 = "偉大な酋長の息子。";
			link.l3.go = "question3_r";
			link.l4 = "偉大な神父の息子。";
			link.l4.go = "question3_l";
			link.l5 = "一行には指導者がいなかった。";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "インディアンたちは勇敢な戦士であり旅人で、たとえ新しい土地に移り住んでも、常に故郷を愛し敬ってきたのだ。\n故郷への愛の証として、彼らは神殿に鳥の像を造った。それは故郷の象徴なんだ。\nその像は私の後ろにある……";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "インディアンたちは勇敢な戦士であり旅人でもあり、新しい土地に移り住んだ後も、常に故郷を愛し敬ってきた。\n故郷への愛の証として、彼らは神殿に自分たちの故郷の象徴である鳥の形をした像を建てたのだ。\nそれは俺の後ろにある……";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "この鳥の名前は何だ？";
			link.l1 = "「アホウドリ。」";
			link.l1.go = "question4_l";
			link.l2 = "「イーグル。」";
			link.l2.go = "question4_l";
			link.l3 = "「ハゲタカ。」";
			link.l3.go = "question4_l";
			link.l4 = "「ロック。」";
			link.l4.go = "question4_l";
			link.l5 = "「コンドル。」";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "栄華の年月は過ぎ去り、灯火のように消え、島からは生命が失われた。ここに残っているのは、 古代インディアンの偉大な力を伝える寺院だけだ。最後のシャーマンは聖なる太陽の宝珠を台座に残し、 それは勇者に力を与え、悪しき者を罰した。その宝珠は、あんたより先にここに来た男に奪われたのだ。";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "繁栄の年月は過ぎ去り、灯火のように消え、島からは命が失われた。\n今やここに残るのは、古代インディアンの偉大な力を伝える寺院だけだ。\n最後のシャーマンは、勇者に力を与え、悪しき者を罰する聖なる太陽の宝珠を台座に残した。\nそれは、お前の前にここに来た男によって持ち去られたのだ。";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "あの聖なる宝珠の名前は何だった？";
			link.l1 = "輝く太陽のオーブ。";
			link.l1.go = "question5_l";
			link.l2 = "太陽光のオーブ。";
			link.l2.go = "question5_l";
			link.l3 = "真昼の太陽のオーブ。";
			link.l3.go = "question5_l";
			link.l4 = "昇る太陽のオーブ。";
			link.l4.go = "question5_r";
			link.l5 = "「沈みゆく太陽のオーブ。」";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "間違った答えは、お前が俺に嘘をついた証拠だ、白い顔の男よ！お前は邪悪な目的で来たのだろう！ 神殿や祭壇の守護者たちをかいくぐり、扉の仕掛けも見破ったようだが――それでも俺との死闘からは逃れられん。覚悟しろ、色白の奴め！";
				link.l1 = "ふん、そこまで言うなら――お前がどれほどの戦士か見せてもらおうじゃねえか…";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "お前の我々の民と神殿についての知識、見事だな、色白の者よ。今やお前の言葉を信じよう。さあ、 ここへ来た目的を果たせ。聖なる遺物をコンドルの前の台座、かつて昇る太陽の珠があった場所に置くのだ\nそれが済んだら、私のもとへ戻ってこい。ユム・シミルへの信仰心、 そして兄弟たちが奪ったものを自らの意思で返そうとした決断は、報いられるべきだ。";
				link.l1 = "ご信頼いただき、偉大な酋長、ありがとうございます。";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "間違った答えは、お前が俺に嘘をついた証拠だ、白い肌の男よ！悪意を持ってここへ来たな！ 神殿や祭壇の守護者たちをかいくぐり、扉の仕掛けも見破ったが――それでも俺との死闘からは逃げられん。覚悟しろ、色白の顔め！";
			link.l1 = "ふん、どうしてもって言うなら――お前がどれほどの戦士か見せてもらおうじゃねえか…";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "約束通りにやってくれたな、色白の者よ。お前が他の仲間たちのような嘘つきでなくて良かった。俺も約束を守ろう。 さあ、これを受け取れ――ジャガー戦士の力の象徴だ。ユム・キミル自身がこの毛皮にその力の一部を宿しているのだ。";
			link.l1 = "うひゃあ、なんて美しいんだ！";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "これはただの毛皮じゃねえ。この毛皮を身につければ、ジャガー戦士の力が手に入る。 火を噴き鉛を吐くお前の武器の威力も十倍になり、戦場を敵の死体で埋め尽くすことができるだろう\nだが、ユム・シミルがこの毛皮に込めた力を人間が長く耐えることはできねえ。一度その力を解き放てば、 次の真夜中までしかお前と共にいられず、やがて消えてしまう。気をつけろ、色白の奴よ。 その力をつまらねえ小競り合いなんかに無駄遣いするんじゃねえぞ。";
			link.l1 = "ありがとう！本当に敵に圧倒されたときだけ使うよ。";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "さあ、行け。\nそして、お前の仲間たちにも、この聖なる部屋の静けさを侵すなと警告するのだ。\nジャガー戦士たちは白い顔の者どもに容赦せず、決して情けをかけぬぞ。";
			link.l1 = "さらばだ、族長。";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
