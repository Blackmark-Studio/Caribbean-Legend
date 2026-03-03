// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "明らかなバグだ。開発者に伝えてくれ。";
			link.l1 = "ああ、そうするよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "carpenter":
			DelMapQuestMarkCity("Fortfrance");
			LAi_SetImmortal(npchar, false);
			npchar.lifeday = 0;
			DelLandQuestMark(npchar);
			dialog.text = TimeGreeting()+"、船長。自己紹介させていただきます—— "+GetFullName(npchar)+"。つい最近会ったばかりだが、俺のことなんて覚えてねえだろうな。";
			link.l1 = "やあ、旦那。どこかでお前を見たことがあったか？";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugger 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "sloop 'Black Dog'";
			dialog.text = "我々の造船所だ。お前は購入を済ませたな "+sTemp+"。思い出したか？俺はそこの大工だぜ。";
			link.l1 = "ああ、本当にあの船を買ったんだぜ。それで、どうしたいんだ、旦那 "+GetFullName(npchar)+"?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			AddLandQuestMark(sld, "questmarkmain");
			dialog.text = "俺たちの船大工 "+GetFullName(sld)+" あなたと話したがっているんだ。何か商談の提案があるらしい。あなたの船がうちの港に停泊しているのを見て、 俺にあんたを探しに行けと頼んできたんだ。招待を受けてくれないか？";
			link.l1 = "わかった。町での用事が済んだら、お前の親分に会いに行ってやるぜ。";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("Voice\English\soldier_arest_4.wav");
			dialog.text = "ほうほう……俺の網に新入りの密輸野郎がかかったな！";
			link.l1 = "「ええっと……」";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "くだらねえこと言うな！この造船所には樹脂の樽がいくつもあるんだ。船長、お前はその樽を共犯者に届けたんだぜ。 二人とも逮捕する、そしてこの積荷は法の名のもとに没収する！";
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "とぼけるんじゃねえぞ、旦那！どの樽だって？ お前がこの船乗りの船から最近降ろしたばかりの樽のことを言ってるんだよ！二人とも地下牢で腐ることになるぜ！動け、 この野郎ども…";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\soldier\soldier arest-02.wav");
			dialog.text = "この樹脂はな、親愛なる造船親方、我々の総督が直々に管理している戦略的価値のある物資だ！ それを全部自分のものだと主張するなら、好きにしな。お前は逮捕だ、今夜は我々の快適な地下牢で過ごしてもらい、 明日にはどうやって手に入れたのか、何のために使うのか詳しく報告してもらうぞ。心配するな、 いずれ全て吐いてもらうからな。お前は自由だ、船長。今日は運が良かったな。";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("Voice\English\soldier_arest_2.wav");
			dialog.text = "この船には何かおかしいところがあると思ってたんだ……どうやらお前を甘く見てたみたいだな、船長。";
			link.l1 = "その通りだ、少尉。俺はそこまで馬鹿じゃねえ。お前と船大工の馴れ合いはもうバレちまったぜ。";
			link.l1.go = "officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "officer_8":
			dialog.text = "なるほどな。おめでとう、俺を見つけて不意を突くとは、なかなか腕が立つじゃねえか。さて、何の用だ。";
			link.l1 = "はっきりしてるだろ？俺の樹脂を返してもらうぜ。お前と仲間が盗んだあの樹脂だ。";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "いいだろう。持っていけ、だが渡せるのはお前の分の半分だけだ。ここに隠してあるのはそれだけだ。\nそれで足りるといいが、俺が出せるのはそれだけだからな。";
			link.l1 = "まだ俺を騙そうとしてるのか？残りの半分は金か、お前の後ろに隠してる品物で補償しろ。";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "選択肢はねえ。残りの半分は共通の知り合いに聞け。";
			link.l1 = "ふざけてんのか？本気でそれを信じてるのかよ "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 俺の樽を返してくれるって？そんな馬鹿な話があるかよ。";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "船長、持ってる樹脂は全部やるから、命を守ってさっさとここから消えな。\nさらに、サン・ピエールでお前に面倒を起こさないって約束もつけてやる。\nこれが俺の最後の申し出だぜ。";
			link.l1 = "俺の命まで取引の一部になった覚えはねえぜ！はっ！";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "戦いの後でもまだ自分が無敵だと思ってるみたいだな、船長。教えてやるぜ――あいつらはただの新米で、訓練もやる気もなかった連中だ。俺の部下たちにはお前じゃ勝てねえ。 交渉抜きでここで殺すことだってできるが、俺は部下の命を大事にしてるんだ。お前を殺す過程で、 奴らが怪我したり死んだりするかもしれねえからな。だから俺の寛大な提案を受け入れるか、ここで一生過ごすか、 どっちか選べ。さあ、決めろ。";
			link.l1 = "ふざけんなよ、中尉。でも仕方なくお前の条件を呑むしかねえ。こっちは完全に分が悪いんだ。";
			link.l1.go = "officer_13";
			link.l2 = "自信過剰なんじゃねえか、副官？お前とその傭兵どもに一発教えてやるべきだな。くそったれの松脂野郎め！";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "あんたは分別のある男だな、船長。樽を持ってさっさと消えな。\n忠告しとくが、総督の前で俺を指さしたって無駄だぜ。今日中に隠し場所を変えるつもりだからな。\n時間の無駄だぜ。";
			link.l1 = "そのつもりはねえよ。役人に訴えても無駄だってことは分かってるぜ。";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "急げ、俺にはあまり時間がねえんだ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_02.wav");
			dialog.text = "おお！なんて偶然だ！こんばんは、旦那！いい夜を過ごしてるかい？";
			link.l1 = "おやすみ……あっ、あんたか！覚えてるぜ、カリブに来た初日に会ったな。グレゴワール・ヴァリニー旦那。";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "まだ覚えていてくれて嬉しいぜ。今じゃお前も船長か。船長 "+GetFullName(pchar)+"。おめでとう。";
			link.l1 = "「ありがとう……」";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "困ってるようだな、船長。ここで何があったんだ？何か問題でもあるのか？";
			link.l1 = "何かがおかしい……";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "旦那、通りの真ん中に突っ立ってるより、酒場にでも行こうぜ。ビールでも一杯やったらどうだ。そこで話せるしな。 さあ、行くぞ！";
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "注いでくれよ、船長……";
			link.l1 = "やってみろよ……";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "ううっ……で、今度は何があったんだ？お前、先週絞首台で吊るされた野郎みたいな顔してるぜ。 あいつもまさに同じ顔してたんだよな、あのとき。";
			link.l1 = "見てください、グレゴワール旦那……まあ、仕事でちょっと厄介なことがありまして。";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "船長、何でも俺に話してくれていいんだぜ。俺は総督や司令官にあんたを売ったりしねえ、そこは信じてくれよ。 俺のこと、信じてねえのか？";
			link.l1 = "俺はあんたを信じてるぜ、旦那。";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "ならば告白して、心を楽にしな。俺が助けてやれるかもしれねえぜ。";
			link.l1 = "地元の船大工に雇われて、トリニダードから出航したスペインの隊商を襲うことになった。 あいつは樹脂がどうしても必要だったらしくて、それが俺の標的だったんだ。 樽一つにつき十五ドゥブロン払うって約束してくれた。俺は隊商を追い詰めて襲い、品物をここに持ち込んだ。 船は修理に出されて、樽は造船所で降ろされた。取引もそろそろ終わるってときに、あの将校が現れやがった……どうやってバレたんだろうな？";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "あれで終わりだった、奴らに捕まっちまったんだ。造船屋には感謝しなきゃな――全部自分のせいだって言って、樹脂は自分の持ち物で俺には関係ないって言い張ってくれた。結局、彼は逮捕されて、 俺の金も消えた。スペインの隊商とのゴタゴタは時間と金の無駄だったな、 まあ牢屋送りにならなかっただけ運が良かったぜ。もう一杯注いでくれ、グレゴワール旦那。";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "「じゃあ、船大工は逮捕されたのか？」";
			link.l1 = "ああ、そうだ。その男は俺が話していたあの役人に連れて行かれて牢屋に入れられたんだ。 あいつらの様子を見ておくべきだったぜ。";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "ああ、二人とも見かけたよ。ただ、フェリシアン・グロニエ中尉が昔の友人を逮捕するなんて、夢にも思わなかったぜ。";
			link.l1 = "「な、なんだと今言ったんだ？」";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "聞いたとおりだ。フェリシアン・グロニエ中尉と船大工\n "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 昔からの友人同士だ。ヨーロッパ時代に一緒に軍隊で仕えていた。グロニエはそのまま軍に残って\n "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 自分の商売を始めることに成功した。";
			link.l1 = "なるほど、あいつらは知り合いだったのか……今やっと分かったぞ……";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "「お前さん」 "+pchar.name+"、どうやらお前は騙されたみたいだな。ここじゃまだ新参者だから、そこをうまく利用されたんだぜ。 百ドゥブロン賭けてもいいが、旦那 "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 三日以内にはまた自分の造船所を歩き回っているだろう。";
			link.l1 = "どうやらあんたの言う通りだな、旦那。奴らにまんまとやられたぜ。あの士官が樹脂のことを知ってたはずがねえし、 タイミングも完璧だった。";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "ここはカリブだ、旦那 "+pchar.name+"。慣れろよ。見た目なんて忘れちまいな、ここじゃ一番のクズがいつも立派な貴族面してるもんだぜ。";
			link.l1 = "どこかでこのセリフを聞いたことがあるな……どうするべきだ？こいつらをどうすりゃいい？総督に報告した方がいいのか？";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "この場合は恐れている "+GetFullName(characterFromId("FortFrance_shipyarder"))+" 別の話をでっち上げて、お前は牢屋行きだぜ。";
			link.l1 = "やっぱりな。まあいい！法が俺の味方じゃねえなら、俺流でやってやる、くそっ！こんなところで諦めるもんか。";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "落ち着いてくれ "+pchar.name+"。それは怒りとラムのせいであって、お前自身じゃねえ。少し寝てからもう一度考えてみろ。たぶん、 忘れちまうのが一番だぜ。フェリシアン・グロニエ中尉と "+GetFullName(characterFromId("FortFrance_shipyarder"))+" ここには権力者がいるんだ、お前の手に負える相手じゃねえ。\n馬鹿な真似はするなよ。";
			link.l1 = "どうなるか見てみよう。教えてくれて感謝する。君に会えてよかった。";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "気をつけろ。俺が言ったことを忘れるなよ。";
			link.l1 = "そうするぜ。さあ、最後の一杯をやろうじゃねえか！";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			PlaySound("Voice\English\LE\Greguar\Greguar_03.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"!";
			link.l1 = "「ああ、グレゴワール旦那！またお前か！」";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "ああ。酒場で話した後、フェリシアン・グロニエ中尉について調べてみたんだ。どうやら彼はつい最近、 十日間の休暇を申請していたらしい。その願いは認められた。今日、俺は彼を見かけたよ。 彼はロングボートでタルターヌ船に乗り込んで、すぐにグアドループへ向けて出航した。その船は「トパーズ」 という名だ。俺が知っていることは全部話した。あとはお前次第だぜ。グロニエが急に休暇を申請して、 出来たばかりのタルターヌで島を離れた――その流れ、きっとお前にも見えてるはずだ。";
			link.l1 = "くそっ、今はもうはっきり分かったぜ、間違いねえ！このタルターヌの船倉に俺の樹脂が積まれてるんだ！ グレゴワール旦那、ありがとうよ、本当に助かったぜ！お礼に何かできることはあるかい？";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "おやおや、友よ。私たちは貴族なのですから、互いに助け合うべきでしょう。これが我々の生き方です。 もし私があなたの立場なら、きっと同じことをしたはずです。\n一刻も無駄にせず、北へ航海してその士官を探し出してください。戦闘は避け、ただ彼の行動を突き止めてください。 急いでください、船長！";
			link.l1 = "またありがとう！";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "何見てやがる？ここで何の用だ？";
			link.l1 = "おい、相棒、俺は自分の荷を取りに来たんだ。あそこに見える樽、あれが俺の樹脂だぜ。あいつら、 まだ一銭も払っちゃいねえんだよ。";
			link.l1.go = "pirate_1";
			DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;
		
		case "pirate_1":
			dialog.text = "お前、バカか？生きてるうちにとっとと失せろ！";
			link.l1 = "この樹脂を手に入れるために俺は相当苦労したんだ。こんな汚ねえクズどもに邪魔されてたまるかよ。";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "ここでその立派な服を埋めてやるぜ！";
			link.l1 = "おや、埋葬を提案してくれるなんて親切だが、残念ながらお前はこの浜辺に置き去りにして、 カモメに内臓を食わせるしかねえな！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
