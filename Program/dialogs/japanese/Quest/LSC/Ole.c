// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何もない。」";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "おっと……こんにちは、おじさん。白いビーズ持ってる？白いビーズをちょうだい……";
			link.l1 = "ふむ。こんにちは。お前……白い坊やか？";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "ビーズだ！白いビーズは白い坊やのもの！おじさん、白いビーズ持ってる？";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "ふむ、ビーズは持ってないが、この真珠ならあげられるぜ。白くてビーズみたいだろ。それでいいか？";
				link.l1.go = "store_2";
			}
			link.l2 = "いや、ビーズなんて持ってねえよ。白いのも赤いのもな。俺は女でもインディアンでもねえから、 ビーズなんか身につけねえんだ。さあ、教えてくれよ…";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "ビーズ！白いビーズ！ビーズがなきゃ話さない。悪いおじさん……ビーズちょうだい！";
			link.l1 = "くそっ！なんて狂人だ！スネークアイとチミセットの言った通り、あいつは頭がおかしい…どんなビーズが欲しいんだ？";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "ビーズをちょうだい、おじさん。いいおじさん……白いビーズを！";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "ほら、ビーズをやるよ。これが欲しかったんだろう？";
				link.l1.go = "store_2";
			}
			link.l2 = "「ああ、くそっ……」";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "はい、はい！そうだよ！おじさんがビーズをくれた！ありがとう、いい人！これでオレにはビーズがもう一つ増えた。 もうすぐママに会えるんだ……";
			link.l1 = "あなたのことを嬉しく思うよ。さて、今話せるかい？";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "ああ、いい人だな。おじさん、あんたは本当にいい人かい？俺たちは友達になれるさ。オーレも話せて嬉しいぜ。 名前は何ていうんだ？";
			link.l1 = "私の名前は "+pchar.name+"「…オーレ、昔ある男があんたのことを話してくれたが、今はもうここにはいねえ。その男は、 あんたに助けてもらったって言ってたし、俺のことも助けてくれるかもしれねえってさ。」";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "おじさんがオーレにビーズをくれた――いいおじさんだ。オーレはいい人を助けるのが好き。いい人はあまりいない――悪いおじさんばかりだ。君を助けるよ、きっと。助けるのが好きなんだ。";
			link.l1 = "いいね！これで俺たちはもう仲間だな。さて、オーレ、ちょっと聞くが、 赤い肌に立派な羽根帽子をかぶった男を覚えてるか？あんたが昔そいつを助けたって話してたぜ。";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "あのおじさんのことは覚えてるよ。いい人だった。俺が助けたんだ。像のところまで連れて行った。それから最近、 食料のある貨物室からまた別のいい人を助けたんだ。悪い提督のおじさんたちから救い出したんだよ。あいつら、 彼を殺すつもりだった。俺もその人を像のところに連れて行きたかったけど、完全に拒否されたんだ。";
			link.l1 = "「船倉からか？へっ、誰のことか察しがつくぜ……あの叔父さんのことも知ってる。なあ、オーレ、お前が助けたその男は誰なんだ？」";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "彼の名前はナサンおじさんだ。彼は病気で、とても、とても重い病気なんだ。オーレが見つけたとき、 ほとんど歩くこともできなかったんだよ。";
			link.l1 = "ああ……まさか本当にそんなことができるとは、不思議だな。";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "いや、変じゃないよ。俺はあいつを見つけて、火のラムをやったんだ。あの船には食い物があるから、 穴の中を泳いで入ったんだよ。悪い奴らが扉を閉めるけど、俺はいつも開けるのさ。へへへ……おバカな悪い奴らだ。カニをおびき寄せてるのは知ってるんだ。悪い奴らのところに行って、ナサンを見つけた。あいつ、 調子が悪そうだった。俺は火のラムを持ってたから、飲ませてやったんだ、そしたら元気になった。 それからチンキもやったよ、俺はいつもそれを持ち歩いてるんだ、怖いカニがオレを噛んだ時のためにな。 優しいチミセットおじさんがそうしろって言ったんだ……\n";
			link.l1 = "奴に解毒剤とラムを渡したのか？へっ、みんなが思ってるほどお前は馬鹿じゃねえな。やるじゃねえか、オーレ。";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "悪い叔父たちはオーレを馬鹿にしてからかうんだ――「オーレの馬鹿」ってな……。でも、オーレは馬鹿じゃない。ただ全部の白いビーズを集めなきゃいけないだけさ、 そうしないと母さんに追い出されるから。\nあとでビーズをもう一つくれるかい？";
			link.l1 = "ふむ……もちろんだ、オレ、俺たちは仲間だぜ。で、教えてくれよ、どうやってホーク……ナサンおじさんを像のところに送るつもりだったんだ？チミセットおじさんが言ってたけど、 あの像は船と一緒に沈んじまったって……\n";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "像は底にあるんだ。オーレが知ってるよ。でも深くないし、 優しいヘンリクおじさんがナサンおじさんをそこに送れるんだ。ヘンリクおじさんは水中を歩く方法を知ってるからね。 でも怖いカニがたくさんいるんだ。オーレはそれが怖いんだよ。あいつら、痛く噛むんだ。";
			link.l1 = "「ヘンリックおじさん？誰だ？」";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "ヘンリックおじさんは悪いナーワルおじさんたちの中で暮らしているんだ。みんな彼のことを知っているよ。 水の中を歩けるし、ナーワルおじさんたちに潜り方を教えているんだ。ヘンリックおじさんは優しいよ。 オーレに白いビーズをくれたんだ。";
			link.l1 = "「それで、ナーワルたちはどうやってお前を中に入れてくれるんだ？それとも、 あいつらの縄張りはお前にとって自由に出入りできる場所なのか？」";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "うふふ……悪いおじさんたちはオーレを中に入れてくれないけど、オーレは夜になるとあいつらの船のどの部屋にも入れるんだよ。 あいつらは大きくてうるさいけど、オーレは静かで用心深いんだ。\nそれに、オーレは泳いでいるときにヘンリックおじさんに会ったんだ。 ヘンリックおじさんが飛び込むために使ってる船のまわりさ。ヘンリックおじさんはオーレに白いビーズをくれて、 今では友だちなんだよ。";
			link.l1 = "面白いな……俺もヘンリックおじさんと友達になりたいぜ。";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "像のところまで潜りたいのか？あそこだよ、古い船の残骸の中にあるんだ。\nでっかくて怖いカニがたくさんいるぜ。\nあんた、あいつらが怖くねえのか？噛みついてくるんだぞ。";
			link.l1 = "いや、俺はあいつらなんか怖くねえ。もう一人仕留めたからな、今度はあいつらが俺を恐れる番だぜ。";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "「ああ、」 "+pchar.name+" とても勇敢だね！それならヘンリックおじさんのところへ行くといい、彼が海底の歩き方を教えてくれるし、 そこで全部のカニを倒せるはずだ。さらに、オーレのためにもう一つ大きなビーズも見つかるよ。そうだろう？";
			link.l1 = "もちろん、そうするよ。でもまずヘンリックおじさんを探さなきゃいけないんだ。";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "なぜ彼を探したいんだ？彼は「サン・ガブリエル」という船の工房に住んでいるよ。だが、 意地の悪いナーワルのおじさんたちは歓迎してくれないかもしれないぜ。\n";
			link.l1 = "悪い叔父たちは俺が自分で片をつける。\nそれと、最後にもう一つだけ聞きたいんだが、ナサン叔父さんは今どこにいる？\nずっと探していたんだ。俺がここに来たのも、全部あの人のためなんだよ。";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "俺はナサンおじさんを「フェルナンダ」の自分の隠れ家にかくまったんだ。あそこは遠くて誰も住んでねえ。 みんなもうすぐ沈むと思ってるが、オレだけは違うって知ってる。俺がナサンおじさんを助けて、 そこに連れていったんだ\nおじさんはまだひどく具合が悪くて、ずっと火のラムを飲んでる。ほとんど歩けないし、五ポンドより重い物は持てない。 おじさんがかわいそうで、俺は宝箱から火のラムを、提督の悪党どもの船倉から食い物を持ってきてやってる。それに、 捕まえたネズミも料理してやるんだ。すごくうまいネズミだぜ！";
			link.l1 = "美味いネズミだと？なるほどな。で、ナサンはその……なんだっけ、「フェルナンダ」って船にいるのか？俺はその船は知らねえな……";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Uncle "+pchar.name+"「ここから遠くないって、今言ったばかりだよ。彼女のところへ行くには泳がなきゃならないんだ。後ろに扉があるけど、 ナサンおじさんは開けてくれないよ。オーレが開けるなって言ったから。でも、もし君がナサンおじさんの友達なら、 開け方を教えてあげる。こうやって扉を叩くんだ：トントン…トントン。そうしたら開けてくれるよ。」";
			link.l1 = "それは覚えておくよ。ありがとう、オーレ！本当に助かったぜ！どう感謝したらいいかわからねえよ。";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "もう一つ白いビーズを持ってきてくれ。もちろん、見つけたらな。";
			link.l1 = "ああ、そうだ！白いビーズだな！よし。またな、オレ！";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "「ああ、おじさん」 "+pchar.name+"！会えて嬉しいぜ！元気にしてたか？";
			link.l1 = "ありがとう、オーレ、俺は元気だ。お前に会えて嬉しいぜ。";
			link.l1.go = "exit";
			link.l2 = "なあ、オーレ、お前が言ってたよな、提督の海賊どもが貨物室の扉を閉めるけど、お前はいつも開けてるって……でも、あそこにある箱は全部鍵がかかってるし、 お前はナサンおじさんのためにラム酒を取ってくるって言ってたじゃねえか。どうやってやってんだ？";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "オーレは立派な鍵の一式を持ってるぜ。それでどんな扉や箱も開けられるんだ。まあ、全部ってわけじゃねえがな。 開かないやつもあるけど、ほとんどは開くんだよ。オーレはそれを悪いおじのユルゲンの船室で見つけたんだ。 あいつは毎日、かまどのそばで槌を振るってる。錠前や鍵を作ってるんだよ。それに、 悪いナーワルの連中のためにでっかくて恐ろしいマスケット銃も作ってるんだ。";
			link.l1 = "なるほど。オーレ、その鍵を俺に売ってくれないか？金は払うぜ…";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "わかったよ、おじさん "+pchar.name+"、鍵を売ってやるよ。俺の分だけは取っておくがな。それは提督の部屋を開ける鍵だ。 ナサンおじさんには食い物とラム酒がたっぷりあるぜ。どうせ宝箱にはもうビーズもラムも残っちゃいねえからな。";
			link.l1 = "「それらにいくら欲しいんだ？」";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "まず教えてくれ、おじさん "+pchar.name+"、大きな船を持っているのか？";
			link.l1 = "ああ、あるよ。でも彼女はここにはいない、外輪にいるんだ。だけど俺はもうすぐ島を離れるし、 叔父さんナサンのために自分の大きな船でここに戻ってくるつもりだ。";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "ナサンおじさんのために？ああ、それは素晴らしい！聞いてくれ、約束してほしいんだ。 あんたの大きな船でここから連れてって、必要なだけ一緒に航海させてくれよ。俺、役に立てるぜ。 ネズミを捕まえて料理もできる……それから、白いビーズを五つくれ。そしたら鍵を渡すよ。";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "もちろん！これがあんたのビーズだ。持っていきな。";
				link.l1.go = "lock_4";
			}
			link.l2 = "ネズミを捕まえて料理する？へっ！面白い腕前だな。よし、オーレ、取引成立だ。俺がビーズを五つと、 俺の約束を持ってくるぜ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "「ああ、おじさん」 "+pchar.name+"！会えて嬉しいぜ！元気にしてるか？";
			link.l1 = "ありがとう、オーレ、俺は元気だ。お前に会えて俺も嬉しいぜ。";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "お前の鍵のために白いビーズを五つ持ってきたぜ。";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "ビーズだ！白いビーズだ！おじさん "+pchar.name+"  オレにビーズをくれたぞ！すぐに会えるよ、お母ちゃん！…おじさん "+pchar.name+"、戻ってきたときには私をここから連れて行ってくれると約束してくれるか？";
			link.l1 = "ああ、オーレ。まだネズミは食ってねえよ。お前も一緒に連れてくぜ。";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "「ありがとう、ありがとう、おじさん」 "+pchar.name+"！鍵を持っていけ。使い方は簡単だ、一本ずつ差し込んで試してみな。いずれかが必要な錠を開けるはずだ。 もし開かなければ、その錠は手強すぎるから、特別な鍵が絶対に必要になるぞ。";
			link.l1 = "なるほど。私が対処しよう。";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "待って、おじさん "+pchar.name+"！俺、また鍵を手に入れたんだ。これがなかなか綺麗で、しかも凝ってるんだぜ。 悪いユルゲンおじさんはこんな鍵は作らねえよ。何を開けるのかは分からないけど、 もしかしたらあんたが見つけるかもな。見てくれよ、すごく綺麗な鍵だろ、こんなの今まで見たことないだろう？";
			link.l1 = "見せてくれ……うん、その鍵はとても興味深いな。\nだが、それが何を開けるのか分からなければ、何の役に立つんだ？";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Uncle "+pchar.name+"「……お前、ほんとに変わってるな。何の意味があるんだ？鍵があるなら、どこかに錠前もあるはずだ。錠前があるなら、 どこかにコインもある。俺はこの島で鍵を見つけた。つまり、錠前もここにあるってことだ。間違いねえ。 これは賢い鍵だし、こんな鍵で閉じられてるのはすごく価値のある物だけだ。オレが知ってる。」";
			link.l1 = "正直言って、お前は面白い奴だな、オーレ。よし、買ってやるよ。それでビーズが欲しいのか？";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "ああ、オーレはビーズを五つ欲しがってるんだ。くれるかい、おじさん\n "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "ほら、数珠を持っていけ。";
				link.l1.go = "key";
			}
			link.l2 = "今は持ってねえが、必ずビーズを持ってきてやるぜ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "ビーズだよ！白いビーズ、白い坊やのために！お母さんのために！ほら、おじさん\n "+pchar.name+"鍵を持っていけ。そして錠前も見つかるさ、オレにはわかる。お前は勇敢だな、凶暴なカニさえ怖がらねえんだから。";
			link.l1 = "おい、おれを笑わせるなよ、オーレ！鍵をありがとう。また会おうぜ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "「ああ、おじさん」 "+pchar.name+"！会えて嬉しいぜ！元気にしてたか？";
			link.l1 = "ありがとう、オーレ、俺は大丈夫だ。お前に会えて嬉しいぜ。";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "お前の鍵のために白いビーズを五つ持ってきたぜ。";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "「ああ、おじさん」 "+pchar.name+"！会えて嬉しいぜ！元気にしてるか？";
			link.l1 = "ありがとう、オーレ、俺は元気だ。お前に会えて俺も嬉しいぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "「ああ、おじさん」 "+pchar.name+"、戻ってきたんだな！また大きな船に乗ってるんだ！俺をここから連れて行ってくれるのか？おじさん "+pchar.name+"、約束しただろ、覚えてるか？";
			link.l1 = "ああ、もちろんだ、オーレ。乗船歓迎だぜ！ネズミどもは困ったことになりそうだな、ははっ！";
			link.l1.go = "return_1";
			link.l2 = "本当か？それで、俺がいつ約束したってんだ？そんな約束をした覚えはねえぞ…";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "ありがとう、おじさん！オレは役に立つぜ、きっと見ててくれよ！あ、もしかして母さんにも会えるかな？今すぐ行くよ！ ";
			link.l1 = "そんなに急ぐなよ、オーレ。荷物をまとめていいんだ。俺はすぐに出航するつもりはないからな。";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "約束したじゃないか、しただろう！オーレをここから連れ出すって約束したのに！悪いおじさん！オーレをだましたな！ ひどいおじさんだ！";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "おじさん、おじさん……もう一つ白いビーズが必要なんだ。お願い、オーレに白いビーズをちょうだい！";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "聞かれると思ってたぜ。ほら、ビーズを持っていけ。これで満足か？";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "ああ、まったく面倒くさいな……もうビーズはないんだよ、オーレ、ないんだってば！";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "ありがとう！いいぞ、いいぞ、おじさん "+pchar.name+"！オーレはもう一つビーズを持ってるし、残りのビーズも少ないんだ！それに、俺はおっかさんのところへ行くぞ…";
			link.l1 = "ああ、なんでお前はそんなに変なんだよ……";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "ビーズをありがとう、おじさん "+pchar.name+"!";
			link.l1 = "どういたしまして…";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "「ビーズがない？でも、そんなはずないよ、おじさん」 "+pchar.name+"？！あと少しでビーズが集まる……集めなきゃ。\nそうなると、上陸するしかないな。\nビーズを探そう……";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "それで、どこへ行くつもりだ？一人で何をするんだ？いや、お前の運命に責任を持ちたくねえ。待て、 ポケットを調べてみる……ほら！ビーズを持っていけ、俺と一緒にいろ。これで満足か？";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "それはお前の権利だぜ、オーレ。俺と一緒に航海するのが退屈になったんなら、引き止めはしねえよ。約束はしたからな。 だが、お前はちゃんとあのレートを稼いでくれてたじゃねえか…";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "さようなら、おじさん "+pchar.name+"…オーレは白いビーズが必要なんだ、そうじゃなきゃ母親のもとに戻れないんだよ…";
			link.l1 = "ああ、お気の毒に。でも、私にできることはないわ。行きなさい、オーレ。幸運を祈るわ。";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Uncle "+pchar.name+"！あと一つ白いビーズが必要なんだ。最後の一つだ。お願いだ、オレにそれをくれよ！";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "聞かれると思ってたぜ。ほら、ビーズを持っていけ。これで満足か？";
				link.l1.go = "mother_1";
			}
			link.l2 = "ああ、まったく面倒くさいな……もうビーズはないんだよ、オレ、もうないんだってば！";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "「ありがとう、ありがとう、おじさん」 "+pchar.name+"！これでオーレが全部のビーズを手に入れたぞ。そう、ひとつ残らず全部だ！これでオーレはお母さんに持っていけるし、 もう追い出されることもないんだ…";
			link.l1 = "聞けよ、お前がいつも話してるその「ママ」って誰なんだ？それと、結局のところ、なんでそんなに真珠……白いビーズが必要なんだ？それに、「全部持ってる」ってどういう意味だ？";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "「良いおじさん」 "+pchar.name+" オーレが母ちゃんのためにビーズを集めるのを手伝ってやったんだ……オーレは小さい頃、母ちゃんの白いビーズの首飾りを引きちぎっちまったんだよ。全部水の中に落ちてさ。 母ちゃんはオーレにすごく怒って、全部のビーズを集めるまで家に帰るなって言われたんだ\nいくつあったか、俺は覚えてるぜ。五掛ける十、つまり五十個のビーズだ。今やオーレは全部集めた。おじさんより "+pchar.name+"「お願い、家に連れて帰って！ママを喜ばせたい、ビーズを返したいんだ。家に連れて帰って！」";
			link.l1 = "なんてこった、すごい話だな……子供の頃に正義の島まで来たのか。お前、母ちゃんの真珠のネックレスを壊して家を追い出されたのか？気味悪いな……";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "「おじさん、母さんのところへ連れて行って」 "+pchar.name+"。あの子に会いたい。きっとこのビーズを見て喜ぶだろう。";
			link.l1 = "そうしたいけど、自分の家がどこか分かるのかい？\nお前の母親はどこに住んでいるんだ？";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "彼女は島に住んでいる、赤い屋根の家だ。";
			link.l1 = "本当に！ここにいくつ島があるか、赤い屋根の家がいくつあるか知ってるのか？\nその島の名前は何だ？詳しく教えてくれ…";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "名前は知らないよ。島だったのは覚えてる、ママがパパに「私たちは島にいるのよ！」って言ってたんだ！それで、 赤い屋根の家に住んでたんだ。きれいな家で、大きかったよ。ママのところに連れてって、おじさん\n "+pchar.name+"……お願い……";
			link.l1 = "ああ、わかった。どの島でもそんな家を探して、お前の母親について聞いてみるさ。母親の名前は何だ？";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "「名前？おじさん、あんた変わってるね」 "+pchar.name+"。母の名前は「母」だ。君の母の名前は違うのか？";
			link.l1 = "ああ、神よ、どうか私に少しの忍耐をお与えください……わかった、オーレ。お前の家を探してみよう。さあ、船に行け。";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "ありがとう、おじさん "+pchar.name+"。あなたは本当に、本当に親切でいい人だ！もうすぐオーレはお母さんに会えるんだ！";
			link.l1 = "「ああ……」";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "母さん…母さん、ママ！帰ってきたよ！";
			link.l1 = "息子よ…";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "お母さん、白いビーズを持ってきたよ！全部集めたんだ！またネックレスができるよ。まだ僕のこと怒ってる？";
			link.l1 = "神よ……（泣きながら）オーレ！息子よ、なぜだ？なぜ行ってしまったんだ？あんな真珠なんてどうでもいいのに！";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "ママ、ここに……これを受け取って。ずっと集めてきたんだ。親切なおじさんたちが手伝ってくれたよ、特におじさん\n "+sld.name+"……あの人は大きな船に乗せてくれて、ビーズを集めるのを手伝ってくれて、家まで送ってくれたんだ……";
			link.l1 = "おお…本当に大きくなったな、でもまだ子供だ…息子よ、抱きしめさせてくれ！すまなかった、あの忌々しい首飾りのことを許してくれ！ もう二度とお前を一人にはしない、絶対に！これからは一緒に暮らして、俺が面倒を見る…必ず償う、約束する…";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "お母さん、会いたかったよ……一緒にいたいんだ。まだ僕のこと怒ってる？どうして泣いてるの？";
			link.l1 = "（泣きながら）いやだ、いやだ……本当にごめんよ、息子よ！許してくれ……";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Uncle "+pchar.name+"！来てくれて本当に嬉しいよ！お母さんのところまで連れてきてくれてありがとう。 こうして一緒にいられるなんて素晴らしい……ねえ、おじさん、家に帰ってこられて本当に素敵だよね？ "+pchar.name+"?";
			link.l1 = "ああ。オレ。そうだ。お前が喜んでくれて嬉しいぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("聞いてくれ、武器はしまってくれよ。そうされると落ち着かねえんだ。","ここではな、刃物を振り回すのは許されねえんだ。しまいな。","聞けよ、剣を振り回して中世の騎士みたいな真似はやめろ。\nしまえよ、それはお前には似合わねえ…");
			link.l1 = LinkRandPhrase("「いいだろう。」","「いいだろう。」","おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、俺はこの街の住民だ。剣を下ろしてもらえないか。","聞いてくれ、俺はこの街の住人だ。だから剣を下ろしてくれ。");
				link.l1 = LinkRandPhrase("「いいだろう。」","いいだろう。","おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"気をつけろよ、相棒、武器を持ってうろついてると俺がビビっちまうじゃねえか…","男たちが武器を抜いたまま俺の前を歩くのは好きじゃねえ……怖いんだよ……");
				link.l1 = RandPhraseSimple("了解だ。","俺がそれを持っていくぜ。");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
