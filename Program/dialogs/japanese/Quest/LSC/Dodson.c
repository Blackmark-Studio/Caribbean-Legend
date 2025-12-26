// Акула: Стивен Додсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "チャールズ、なんだよこれは？";
				link.l1 = "スティーブン、問題があったんだ。俺は来ることもできなかったし、不在を知らせることもできなかった……";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "会えて嬉しいぜ、相棒！どうした、何か手伝えることがあるか？ ";
				link.l1 = "俺も会えて嬉しいぜ、スティーブ。あの見事な見世物に感謝したいんだ！";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "会えて嬉しいぜ、相棒！どうした、何か手伝えることがあるか？";
				link.l1 = "スティーブン、俺から提案があるぜ。海賊らしい話だ。";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "あいつがいたぜ！仕事は終わった。お前の男爵は厳重に守られた地下牢にぶち込まれてる。見に行きたいか？へっへっ！";
				link.l1 = "はっ、そんなもんは後でいくらでもできるぜ。あいつはちゃんと扱われてるか？";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "会えて嬉しいぜ、相棒！どうした、何か手伝えることがあるか？";
				link.l1 = "何か必要なんだ、スティーブン……";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "会えて嬉しいぜ、相棒！どうした、何か手伝えることがあるか？";
				link.l1 = "スティーブン、俺がお前に渡したいものがあるんだ。";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "会えて嬉しいぜ、相棒！どうした、何か手伝えることがあるか？";
				link.l1 = "スティーブン、ちょっと聞きたいことがあるんだ。気に入らねえかもしれねえが……お前の助けが必要なんだ。";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "「おう、そこにいたか」 "+pchar.name+"……お前を待ってたぜ。森の悪魔がトルトゥーガでの厄介事について話してくれた……";
				link.l1 = "あいつはお前がもう解決策を見つけたって言ってたぜ。本当か？";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "「調子はどうだ、 "+pchar.name+"?";
				link.l1 = "秘密だらけだな……スティーブン、あんたの助言が必要だ。";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "見せたいものがあるんだ……桟橋まで一緒に歩いてくれねえか？";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "ああ、俺の友よ "+GetFullName(pchar)+"！入れ、入れ、会えて嬉しいぜ！";
				link.l1 = "やあ、スティーブン！さて、約束通り来たぜ。お前の船は準備できてるか？";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "で、商売の調子はどうだ？まだ「黄金艦隊」を追いかけてるのか？";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "ああ、俺の友よ "+GetFullName(pchar)+"！入れ、入れ、会えて嬉しいぜ！";
			link.l1 = "よう、スティーブン。仕事でシャープタウンに来てて、ちょっとだけ寄ってみたんだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "ははっ！お前が夜の訪問者ってわけか？この件についてはついさっき知らされたばかりだぜ。お前の持ち物を調べたら、 フォレスト・デビルからの手紙が見つかった。くそっ、まるでニュー・スペインのジャングルの匂いがしそうだったぜ！\nお前の名前は "+GetFullName(pchar)+"？俺はスティーブン・ドッドソン、シャークって呼ぶ奴もいる。スヴェンソンが俺のことを話したんだろう。だが、 この正義の島じゃ、俺は提督って呼ばれてるんだぜ。\n昨夜の部下の行動については謝る。あいつらは俺の命令で、船倉に忍び込んだ奴を捕まえるようにしてたんだ。 ナーワルやリヴァドスの連中は、しょっちゅう盗人を送り込んで食糧を盗もうとしやがるからな。\nチャドが解放したんだろ？妙だな……今まさに解放するよう命じるつもりだったんだ。\nお前の船はどこだ？無事なのか？";
			link.l1 = "チャド？俺の理解じゃ、お前の甲板長は俺を生きて牢屋から出すなんて絶対にしなかっただろう。 俺は自力で脱出したんだ、あの…あのリバドスの一人と一緒にな。";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "ほう、そいつは面白えな。で、どうやってタルタロスから抜け出したんだ？チャドとその連中と一杯話さねえとな…";
			link.l1 = "一方的な会話になるぜ、残念だが。奴らはみんな死んじまった。 チャドは俺をこの檻に永遠に閉じ込めてやると脅したんだ。俺のことをリバドス野郎呼ばわりして、 黒魔術師チミセットを殺す以外に証明する方法はねえって言いやがった。";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "「なんだと？！おい、カッパー、このアホ野郎…\nチミセットは生かしておく必要があったんだぜ、チャドもそれは分かってたはずだ！それに、 なんでお前がリバドスだと思い込むんだ？あいつら全員黒人じゃねえか！」";
			link.l1 = "チミセットは死んじゃいないぜ、スティーブン。あの老いぼれ魔術師に言われたんだ、たとえ俺が奴を殺しても、 チャドが絶対にタルタロスから生きて帰してくれねえってな…";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "チミセットを殺す代わりに、武器と弾薬の入った箱をぶち壊して、チャドとその仲間たちをぶった斬ったんだ。";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "最高だぜ！まったくクソ最高だ！だが、どうしてもわからねえ……なんでチャドがこんなことをするんだ？";
			link.l1 = "今向かってるぜ！チミセットが教えてくれたんだが、チャドはナーワルズっていう別の一味と手を組んで、 お前を殺して海賊の頭の座を奪おうとしてるらしい。ナーワルズはお前に死んでほしいんだとよ、 あんたが奴らの頭領アラン…アラン・ミルトンか？ミラーか？そいつを殺したと確信してるからな…";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "ふざけんな！アラン・ミルローを殺したのは俺じゃねえ！やったのは他の誰かだ――もしかしたらナーワルズの奴らかもしれねえ！今の頭目、ドナルド・グリーンスパンの仕業だと思ったくらいだぜ。";
			link.l1 = "違う。チャドが奴を殺したんだ。チミセットはその現場を目撃した――だからチャドはチミセットも殺そうとしたのさ。自分で手を下すのは嫌だったんだろう、 チミセットに祟られるのが怖かったとか……いや、理由はよくわからねえが。とにかく、それで俺にやらせたかったってわけだ。";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "「それで…なんでチャドがアランを殺すんだ？」";
			link.l1 = "お前を陥れてナーワルズの敵に仕立て上げるためだ。やつはお前に罪を着せる噂をばらまき、 お前が人前に顔を出せなくなるようにしたんだ。そんでお前が死んだら、今度はリバドスのせいにして、 お前の仲間の海賊たちがやつらに牙をむくように仕向けるつもりだったのさ。";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "この手紙はチャドの箱の中で見つけたんだ。読んでみろ。間接的ではあるが、確かな証拠に見えるぜ。";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "…（読んでいる）…へっ！今思えば、チャドの裏切りにも驚きはねえな。あの野郎、いつももっと力を欲しがってたからな。\nだがナーワルどもめ！本気で俺がアランを殺したと思ってやがるのか！ これであいつらの補給品の値段は今の倍にしてやるぜ！\nチミセットについては…どうせ解放するつもりだったんだ。リヴァドスとそろそろ和解する時期だろうしな。お前には驚かされたぜ、相棒、 本当に…";
			link.l1 = "わかったよ、スティーブン。俺も気に入らねえさ。こんな政治の陰謀に巻き込まれるためにここへ来たんじゃねえ、 あんたとネイサン・ホークを探しに来たんだ――";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "ホーク？あいつはジャマイカにいるんじゃねえか？";
			link.l1 = "いや、今はジャックマンがマルーンタウンを仕切ってるぜ。俺と同じく、 ホークもここに来たのはククルカンの偶像のおかげだと知ったんだ。";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "…何をぬかしてやがるんだ？";
			link.l1 = "俺は船でここに来たわけじゃねえんだ、スティーヴン。信じがたいだろうが、 スペイン領本土にあるインディアンの偶像が、何かの扉みてえな役割をしてるんだ――そんな目で見るなよ、俺は狂ってもねえし、酔っ払ってもいねえ！どうしてこんなことが可能なのかは分からねえが、 事実なんだ！";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "...";
			link.l1 = "アマティケ湾の南にあるミスキート村の「スネークアイ」と呼ばれるシャーマンが、 ホークが殺されそうになっていたところを助けてくれたんだ。そいつはホークにインディアンの偶像――ククルカンの像を見せて、それがホークをこの島へと運んだんだ。スネークアイは、 自分もかつてまったく同じ方法でこの島に来たことがあると教えてくれて、俺にもそのやり方を教えてくれたぜ。";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "...";
			link.l1 = "俺はあいつに言われた通り、真夜中にその偶像のところへ行ったんだ。\nそしたら、一日中ただの石だったその偶像が、まるごと金になってやがった！\nしかも、妙な光まで放ってたぜ。";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "...";
			link.l1 = "俺があの偶像に触れたとたん、偶像のまわりに光の輪ができて、あちこちで炎が燃え上がったんだ。 それから俺は偶像の中に引き込まれて……気がついたらここ、お前の船の貨物室、下の船首近くの破損部分に投げ出されてたんだ…";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "...";
			link.l1 = "だが、ひどいもんだったぜ――渡ってきた後は気分が悪くて、ぐったりしてた。スネークアイがその効果を打ち消す特製の薬をくれたけどな。\n極めつけに、でっけえクソ蟹に襲われたんだぜ！（深呼吸） ";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "…よし、信じてやるぜ。\nつまり、カニの話の部分は信じるってことだ。あの化け物どもは正義の島の周りにたくさんいるからな。 死んだ魚でおびき寄せて、沈んだ船体の割れ目のそばに居座らせてるんだ。\n素晴らしい番犬だぜ――泥棒どもをビビらせてくれるからな。でも、その偶像の話になるとよ…\nその部分を頭ごなしに否定はしねえ。リバドスどもが船の上で妙な儀式をやってたって話は聞いたことがある…人間を…インディアンの偶像に生け贄に捧げたって噂もな…";
			link.l1 = "全部本当だと誓うぜ。";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "お前がそれを信じてるのは分かったぜ。だが、今は魔法の偶像の話は置いとこう。\nヤンの手紙によれば、俺にコースト同盟の頭領になってほしいってことか？";
			link.l1 = "その通りだ。お前とホークがいなくなってから、色々と変わっちまったんだよ。 ジャックマンはバラナスの頭になりたがってるし、もしヤンと俺が止めなきゃ、あいつがそうなるだろうな。";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "ジャックマンは本気で血生臭い勝負を仕掛けてきてるぜ。ホークの待ち伏せを仕組んだのも、あいつに違いねえ。 ブレイズ・シャープを殺したのも、きっとあいつだ。\nお前を兄弟団の頭に据えるしか、あいつを止める方法はねえんだ。";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "おい、王冠をかぶるのは喜んでやるが、まずはこの島を出なきゃな。\nもううんざりだぜ。ここはデクスターに基地を任せて、俺はすぐにでも出ていくつもりだったんだが、 部族との戦いで俺の船が燃やされちまった。\nそれに、島を出るのにインディアンの怪しい呪術なんか使おうなんて考えるなよ。俺は船以外はごめんだぜ。";
			link.l1 = "スティーブン……（ため息）まだあの偶像を見つけなきゃならねえんだ！スネークアイはここにあるって誓ってたんだぜ。さて、 お前はリバドスが偶像を使って儀式をしてるって何か知ってるって言ってたな。他に何か知ってることはあるか？";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "何もない。俺がここに来るずっと前のことだ――はるか昔にな。";
			link.l1 = "この……ククルカンのポータルを通る旅なんざ、もう怖くねえ――それが一番早くこの島を出て、船を手に入れて、お前を家に帰す方法だ。\n他のことは信じなくてもいいが、俺が本気でお前を助けたいと思ってることだけは信じてくれ。";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "わかった……だが俺は……無理だ。手伝えねえ。噂以外、この偶像については何も知らねえんだよ。\nそれに、勝手だと思うかもしれねえが、今は暗殺騒ぎのほうで頭がいっぱいだ。チャドは死んだが、 ナーワルどもが俺を殺すのを諦めるとは思えねえ。\nお前は俺が生きてる必要があるし、もうこの騒動に巻き込まれてるんだ。だから、この陰謀を調べてほしい。\n新参者のお前なら、俺の手下じゃ絶対に近づけねえ場所や人間にも接触できる。 チャドの仲間を探し出して俺のところに連れて来い――殺しても構わねえ。\nチミセットに話を聞け。あの黒い爺さんは表に出してる以上のことを知ってる。 お前の偶像についても何か知ってるかもしれねえ……\nナーワルには気をつけろ。やつらの縄張りを越えるときは、今週の合言葉がなきゃダメだ――毎週変わるからな。\nこの騒ぎが片付いたら、俺のルッターをやる。正義の島への航路や必要な情報が全部載ってるぜ。\n行け。共謀者どもを見つけて、秩序を取り戻せ。俺を生かしておけ。\nさて……デクスターには牢屋から死体を片付けさせねえとな……タルタロスには新しい看守が要るし……俺にはラムが必要だ。クソ、なんて日だ。";
			link.l1 = "...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Would you believe it? Someone has killed the Admiral's gaoler, Chad Kapper! No doubt the work of that Rivados wizard he locked up, Chimiset...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead, but there's been no official statement and his body hasn't turned up. Perhaps, the Admiral simply gave him a secret mission...?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I haven't seen our gaoler, Chad Kapper, lately. Some say he was killed, some say he's still alive. The only thing people agree on is that no one has seen him...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the Admiral doubled provision prices for the Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "さて、何を持ってきたんだ、 "+pchar.name+"「ナーワル号について何か新しい情報はあるか？」";
			link.l1 = "ああ。スティーブン、お前も喜ぶだろうが、陰謀は暴かれ、共謀者どもはくたばった。今や俺はすべてを知っている。";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "銃撃戦の音を聞いたとき、そう思ったぜ…話してみろ。";
			else dialog.text = "そうか？それは安心だぜ！話してみろ。";
			link.l1 = "全部お前の甲板長、チャド・キャッパーの仕組んだことだ。奴はタルタロスの牢でアラン・ミルローを殺して、 お前がやったってデマを流したんだ。ナーワル号の連中は激怒したぜ――特にアランの女、レッド・メアリーなんかはな…\n";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "メアリーは復讐に飢えていて、チャド・キャッパーはその怒りにつけ込んだんだ。 奴らはお前を暗殺する計画を立てたらしい。 毎晩サン・アウグスティン号の船尾ギャラリーをぶらつく癖があるって聞いてるぜ…";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "へっ！その癖は直さねえとな……続けろよ。";
			link.l1 = "彼らの計画を実行するには、長距離かつ高精度のライフルが必要だった。そこでアドルフ・バルビエがそれを用意した。 だが、彼のシュトゥッツェンはジュゼッペ・ファツィオに質入れされていたため、 メアリーとチャドが買い戻さなければならなかった――アドルフがそのシュトゥッツェンを質から取り戻したのだ…";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "彼らは元王室の狩人、マルチェロ・サイクロプスを雇って狙撃させた。\nその後、メアリーが彼を殺し、死体とライフルを証拠としてリバドスが襲撃の犯人だと見せかける計画だった。 サイクロプスはムラートだった。";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "全部チャドのずる賢い頭から出たことだ…あいつ、頭の切れる野郎だぜ！";
			link.l1 = "そして最後には、イッカクと海賊どもがリヴァドス一族を襲って滅ぼすんだ。チャドは提督になり、 メアリーはあいつの情婦になるだろうな。\nもっとも……何度か寝た後には、メアリーは知りすぎてるって理由で、あいつに喉を掻き切られてただろうがな。";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "とにかく、もう終わったぜ。アドルフはあまり口が利けねえ奴だったから、奴の船室でそのまま殺してやった。 メアリーとサイクロプスも、アドルフからシュトゥッツェンを取りに来たときに片付けてやったぜ。";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "じゃあ、みんなサンタ・フロレンティナの中で死んじまってるってわけか？しかも誰も知らねえのか？";
			link.l1 = "ああ。三人ともだ――そして俺たち以外、誰も知らねえ。";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "よし。目撃者がいると面倒だ。死体の処理は俺がやる。お前、なかなかやるじゃねえか。 "+pchar.name+"！もしお前が俺の船員だったら、一等航海士にしてやるぜ。";
			link.l1 = "大したもんだな、シャーク。ありがとな。おい、これらの手紙を見てみろ。 サイクロプスとメアリーの死体から取ったんだ…";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our scrappy madcap Red Mary has disappeared. I wouldn't be surprised if she's dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. You heard about that?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she's still inside her cabin, but I don't believe it; it's been a long time since I saw a light in her window.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she was a tough sort, but everybody loved her. Who could have done such a thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "とにかく、もう終わったぜ。アドルフはあまり口が利けねえ奴だったから、船室でそのまま殺してやった。 メアリーとサイクロプスも、アドルフからシュトゥッツェンを取りに来た時に片付けたぜ。";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "エヴァ号で喧嘩を始めちまったのは残念だな。ナーワルどもを殺したせいで、あいつらに目をつけられるぜ。 和解できるまで近づくんじゃねえぞ。\nまあ、全体的にはよくやったじゃねえか。 "+pchar.name+"！お前が俺の船員だったら、俺はお前を一等航海士にしてやるぜ。";
			link.l1 = "上出来だな、シャーク。ありがとな。おい、これらの手紙を見てみろ。 サイクロプスとメアリーの死体から取ってきたんだ…";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you've committed! The Narwhals won't forget it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits, but... the girl. Why did you have to kill poor Mary?", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "メアリーが可哀想だと？あの売女に同情してるなんて言うんじゃねえぞ。";
			link.l1 = "ああ、そうだ。チャドの野郎があの女を騙して、感情と生来の血の気の多さを利用しやがった……あいつの野心のために、彼女が死ぬ必要なんてなかったんだ。";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "まあ、そんなに気になるならジュリアン修道士のところに行って、ろうそくでも灯してこいよ。俺は正直、 あの女がくたばってくれてせいせいしてるぜ。\nよし、この話はやめだ。助けてくれて感謝してるぜ。 "+pchar.name+"。これからは俺が味方だぜ。お前の見事な働きに報いたい。ほら、五百ドゥブロンやるよ。";
			link.l1 = "ありがとう、スティーブン…";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you're the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "俺はお前のこと知らねえ。何の用だ？";
			link.l1 = "もちろん、知らねえよな。俺たちは会ったことがねえし、俺も今着いたばかりだ。やあ、スティーブン。 ずっとあんたを探してたんだ。";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "俺を探しに来た奴はたくさんいるぜ。今じゃほとんどが墓の下だ。\nお前も仲間入りしたくねえなら、何の用で俺を探してたのか話してみろよ。";
			link.l1 = "俺たちには共通の友がいるんだ。ほら、この手紙を受け取れ。ヤン・スヴェンソンが書いたものだ。 森の悪魔のじじいの方が、俺よりずっと詳しく説明できるぜ。";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "（読みながら）…ふむ。それで納得だ。てっきりお前がブレイズを殺したことで俺に黒い印を渡しに来たのかと思ったぜ――最近はそれをやりたがる海賊が多いからな。\nお前の船は外輪に置いてきたのか？それに、どうやって俺がここにいるって知ったんだ？";
			link.l1 = "俺じゃねえ。まったくの偶然だったんだ。\nそれとブレイズのことだが……俺もヤンも、あんたが奴の死に責任があるとは思っちゃいねえぜ。";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "あんたの言う通り、俺じゃねえよ。だがな、誰かが俺のせいだと兄弟連中に思わせたいらしいんだ。";
			link.l1 = "面白いな……実は俺はナサニエル・ホークを探しにここへ来たんだが、代わりにお前がいるとはな、へっ！";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "その話は島の古株どもに聞いてみるんだな。リバドスの魔術師チミセットに当たってみろ。あの黒いじじいは、 見た目以上にいろいろ知ってやがるぜ。\n";
			link.l1 = "「その魔法使いはどこで見つけられるんだ？」";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "俺の牢屋、タルタロス号の中だ。そろそろリバドスとの関係を良くする時期だし、 近いうちにあいつを解放するつもりだったんだ。\n命令は自分で伝えてこい！タルタロス号へ行って、看守のチャド・キャッパーに「チミセットを釈放しろ」 と俺の伝言を伝えろ。\nいや、まずチミセット本人に会わせてもらえ。俺が送ったと言って、もし奴が十分に口を割れば解放してやると伝えろ。 知りたいことはきっと話してくれるはずだぜ。";
			link.l1 = "ふむ……タルタロスはどこだ？";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "俺の住処を出て、橋を渡り、左に曲がって、フリゲート艦キャロラインを抜けてガレオン船グロリアを通り、 エスメラルダに着け。『店』と書かれた看板を探して、その下の扉から入れ。船の船首側の扉を通れば、 タルタロスに辿り着くぜ。\nエスメラルダでは気をつけろよ。あそこはナーワルの縄張りだ。他の奴らも訪れることはできるが、 あいつらの見張りを怒らせたり、騒ぎを起こすんじゃねえぞ。";
			link.l1 = "リバドスとナーワルってのは何者だ？";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "奴らは正義の島の最初の入植者たちの子孫でできた一族だ。ナーワル族は主にイギリス人、オランダ人、 フランス人の血を引いている。リバドス族は全員黒人だ。\nそれぞれの一族にはリーダーがいて、いくつかの船を持ち、それが外部者立ち入り禁止の縄張りになっている。\nナーワルかリバドスの縄張りに入るには正しい合言葉を知っていなきゃならねえし、合言葉は毎週変わるんだ。";
			link.l1 = "それはいいが、俺を牢屋の中に入れてくれるのか？";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "そうなるさ。これが鍵だ、チャドに俺が寄越したって分かるようにな。なくすんじゃねえぞ。";
			link.l1 = "ありがとよ。あの…あのチミセットと話して、結果を持って戻ってくるぜ。";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "タルタロスに行ったことがあるのか？";
			link.l1 = "ああ。お前の命令はチャドに伝えたし、チミセットとも話したぜ。";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "魔法使いが何か言ったか？";
			link.l1 = "ああ、そうだ。俺が探してる偶像のありかを教えてくれたんだ。サン・ヘロニモ号にあったんだが、 ナーワルの縄張り近くで、数年前に沈んじまった船さ。";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "ハハハ！お前の魔法の偶像は今や海の底か、そうだろ？まあ、相棒、これで俺たちと一緒にいるしかねえな。";
			link.l1 = " 俺がなんとかしてあの偶像までたどり着く方法を考えるぜ。さて、チミセットが言ってたが、 カッパーは信用しない方がいいらしい。チャドがアラン・ミルローって奴を殺すのを見たってよ――\n";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "「なんだと！？チャドがアランを殺しただと？チミセットの野郎、嘘ついてやがる、そんなはずねえ！」";
			link.l1 = "スティーブ、チミセットは怯えてたぜ。もし嘘をついてたんなら、見事な演技だったな…";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "ちくしょう、まったく最高じゃねえか！\nアランの殺しでナーワル団との関係は台無しだ――中には俺がやったと思ってる奴までいる――それなのに、今度は俺の部下の一人が犯人だったってのかよ！？";
			link.l1 = "お前はやってもいねえことでずいぶん責められるみたいだな。";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "気づいたぜ。";
			link.l1 = "さて、もっと面白い話があるんだぜ。チミセットが、お前の部下の何人かが殺す計画を立ててるのを聞いちまったらしい。 だが、あいつは自分を解放してやって、しかも二人きりの時じゃねえと、それ以上は話さねえってさ。\n";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "上出来だな。今日は順調すぎると思ってたんだぜ。\nチミセットが何か詳しい話をしたのか？";
			link.l1 = "いや、あいつはチャドを恐れてるんだ。まず自分の身の安全が保証されなきゃ動かねえよ。";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "よし。リバドスどもにチミセットと会いたいって伝えてくれ。あいつが何を言うか聞いてやろうじゃねえか。それと、 俺の命を狙った件については……気を付けるしかねえな。\nで、これからどうするつもりだ、 "+pchar.name+"?";
			link.l1 = "今のところ特に何もない。島を歩き回って地元の連中と知り合ってみるさ――ここから脱出する方法が思いつくかもしれねえ。それにナサニエル・ホークを探さなきゃならねえ、 奴がここに来た理由だからな。\n";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "そうだな。この島から出る方法を見つけたら、必ず俺のところに来いよ。俺の航路図と水路誌を渡してやるから、 船でここへ戻って来られるようになるぜ。必要な他の情報も用意しておくからな。";
			link.l1 = "いいだろう。必ず会いに行くぜ、スティーブ！";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = ""+pchar.name+"悪い知らせだぜ：チミセットは死んじまったし、チャド・キャッパーは姿を消した。";
			link.l1 = "ちくしょう！ついにチャドがあのジジイ魔法使いを殺しやがったか……";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "そうみたいだな。状況は時間ごとに悪くなってきてるぜ。ブラック・エディとの休戦も準備万端だったのによ……\nまあ、リバドスとの和平はもう諦めるしかねえな。ところで、 あいつらはチミセットが死ぬ前にお前が話したことを知ってるし、お前を俺の仲間だと見なしてる。だから、 あいつらには近づくなよ。";
			link.l1 = "素晴らしいな。";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "まだあるぜ。正義の島の仲介人であり外交官のジュゼッペ・ファツィオから手紙を受け取ったんだ。 やつはカロライン号の自分の船室に、真夜中に来いと招待してきた。\nしかも、俺の命が危ないから部下は信用できねえ、一人で来いとも言ってきた。\nまあ、チミセットも俺たちの乗組員に裏切り者がいるって警告してたし、理屈は通るが……それでもどうにも胡散臭え。真夜中に一人で、だとよ……\n普段ならあのデブが俺のところに来るもんだがな。お前に手を貸してもらいたいんだ。 "+pchar.name+"ヤンがあんたのことを機転が利いて勇敢な男、しかも腕の立つ戦士だって言ってたぜ。 俺を真夜中の会合まで護衛してほしいんだ。";
			link.l1 = "聞くまでもねえよ、スティーブン。俺も乗ったぜ。こんな招待状、気に入らねえしな――どうせ罠に決まってる。";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "そうかもな。俺の勘違いだといいが、用心するに越したことはねえ。お前が一緒にいてくれて心強いぜ\n真夜中にサン・アウグスティン号のメインデッキに来い。そしたらファジオに会いに行くぞ。 キャロライン号まではすぐだ。";
			link.l1 = "じゃあ、真夜中だな。俺はしっかり武装しておくぜ。";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "「ああ、いいぜ」 "+pchar.name+"さあ、時間を無駄にするな。あのデブのファツィオが何を言うか見てやろうぜ。俺のそばを離れるなよ。";
			link.l1 = "俺はお前と一緒だぜ、スティーブ。武器はいつでも使えるようにしておけよ…";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "あのデブはどこだ？どこへ行きやがった？客人への扱いがこれかよ！見えるか、 "+pchar.name+"？俺は知らねえな。\nもしかしたら、あいつの宝箱を調べてみるべきかもな。中にいるかもしれねえし……まあ、何もなけりゃ手間賃くらいはもらえるだろうぜ、ハハッ！";
			link.l1 = "へっ、あいつが自分の体を押し込める宝箱なんて、この世にあるとは思えねえな――しっ！スティーブン！何か聞こえたぞ…";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "…準備しろよ、 "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Caroline_DlgExit_3");
		break;
		
		case "caroline_5":
			dialog.text = "うおお！やったな…くそっ、あいつらにやられるかと思ったぜ。";
			link.l1 = "俺はこれよりひどい修羅場もくぐってきたが、今のはさすがに危なすぎたぜ。チミセットの言う通り、 チャドは裏切り者だった。で、あいつらを指揮してたあの女は誰だ？";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "メアリー・キャスパー、通称レッド・メアリー。故アラン・ミルローの恋人だ。\nチャドがここにいた理由はわかる――俺の地位を奪いたかったんだろう――だが、メアリーは何の用でここに来てたんだ？";
			link.l1 = "もしあいつがアランの恋人だったんなら、理由は明白だぜ。アランの死の復讐を望んでたんだろうよ。可哀想にな、 自分がアランを殺した張本人と肩を並べて戦ってるなんて気づきもしなかったんだな…";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "なるほどな。くそっ、この仕打ち、ナーワルどもにたっぷり返してやるぜ！あいつらに物資はもう売らねえ、 飢え死にさせてやる！\nで、あいつらに何ができる？攻めてきたって、サン・アウグスティンはどんな包囲にも耐えられるんだぜ！ 必ず後悔させてやる。ファジオのデブ尻は俺の椅子の後ろの壁に打ち付けてやるからな！";
			link.l1 = "スティーブ、スティーブ、待てよ！もし…もしナーワルズはこれに全く関わってなかったらどうする？チャドはお前の手下だった、ナーワルズの奴じゃねえ。 アランを殺したのもチャド、チミセットを殺したのもチャド、噂を流したのもチャドだ。もし全部、 始まりも終わりもチャド一人の仕業だったらどうするんだ？";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "…くたばれ、 "+pchar.name+"…だがよ、お前の言い分にも一理あるかもな。\nよし、借りがあるから、調べるチャンスをやるぜ。ナーワルズが無関係だって証明できたら、戦争はやめてやる。\nお前は俺の信頼を勝ち取った。これから何をするにも俺が力を貸してやるぜ。もしまだ俺の船があったら、 お前を甲板長にしてたところだ。";
			link.l1 = "ここを出たら、カリブの兄弟団の頭領を引き受けてくれりゃ、それで十分な礼になるぜ。さあ、少し休んでこい。 俺はこの船室をもう少し調べてみる。俺がいない間に死ぬんじゃねえぞ！";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "へっ、そんなこと夢にも思わねえよ。誰かにこいつらの死体を片付けさせるぜ。 今夜はカニどもがごちそうにありつけるな！（ぺっ）じゃあな、相棒。";
			link.l1 = "おやすみ。";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "「さて、」 "+pchar.name+"、新しいことでも知ったか？";
			link.l1 = "復讐はやめてもいいぜ、スティーブン。ナーワルズはお前に対する陰謀には関わってなかった。 例外はメアリーとキャロライン号で戦った連中だけだ――たぶん、あいつらはメアリーにそそのかされて俺たちを襲ったんだ。 ファツィオは無理やりお前に招待状を送らされたんだよ。あいつの船室で色々説明してある手紙を見つけた。読んでくれ。 ";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "（読み上げながら）…ふん…まったくファジオらしいな、自分の身だけ守りやがって。つまり、最初から最後まで全部チャドの仕業だったってわけか…";
			link.l1 = "全部、奴が提督になりたかったからだ。俺はドナルド・グリーンスパンに会いに行った。 奴は自分も部下もお前に対して企みなんかしてねえと誓ってたぜ。";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "あいつを信用してるのか？";
			link.l1 = "ああ、そうだ。ドナルドがアラン殺しの疑いを晴らしてくれるぜ。あいつはお前に直接会いに来て、話をつけるつもりだ。 ";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "よし。俺も喧嘩は大好きだが、今この段階で戦争したって無意味だぜ。もう十分に死んじまったし、 全部の元凶は今やカニの餌だ。\nドナルドが謝る気になったって？いいだろう、ナーワルとはできる限り関係を修復しようじゃねえか。 リバドスはチミセットのせいで、もう俺たちの手には戻らねえだろうがな。";
			link.l1 = "これがお前にとって唯一の安らぎの機会かもしれねえぞ。";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "もう説得されたぜ。ドナルドに、俺は会う準備ができてるし、和解するつもりだと伝えてくれ。";
			link.l1 = "俺は今向かってるところだ。";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "「待て、」 "+pchar.name+"。よくやったな、たっぷり報酬をやるぜ。ほら、五百ドゥブロンだ。";
			link.l1 = "ありがとう！";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "俺の監獄、タルタロスにな。そこへ行って会ってこい。鍵を渡してやる。看守のチャド・キャッパーに話しかけろ――";
			link.l1 = "待て、スティーブン。カッパーについて知っておくべきことがあるんだ…";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "…聞いてるぜ…";
			link.l1 = "どう言えばいいかわからねえが……カッパーがあんたを殺そうと企んでるんだ。";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "…俺の古くからの仲間を裏切り者呼ばわりするんなら、よっぽどの理由があるんだろうな。";
			link.l1 = "全部話してやるぜ――";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "さっさと話せ。";
			link.l1 = "浸水した貨物室で目を覚ました後、船体の穴から外に出て、難破船の間を泳いで上陸できる場所を探したんだ。 最終的に船首の扉から入れる難破船を見つけた。そこで赤い上着を着た娘と、腕っぷしの強そうな野郎二人が揉めててな――\n";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "レッド・メアリーを殺そうとした奴がいたのか？";
			link.l1 = "そうらしいな。あの野郎どもを片付けるのを手伝ってやった後、面白い話もしたぜ…なあ、スティーブ、『ナーワル』と『リヴァドス』って何者だ？彼女が何度もその名前を口にしてたんだが。";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "奴らは正義の島の最初の開拓者たちの子孫でできた一族だ。ナーワル族は主にイギリス人、オランダ人、 フランス人の血を引いている。リバドス族は全員黒人だ。\nそれぞれの一族にはリーダーがいて、いくつかの船を持ち、それが領地となっていて、よそ者は立ち入り禁止だ。\nナーワル族でもリバドス族でも、その領地に入るには正しい合言葉を知っていなきゃならねえし、 合言葉は毎週変わるんだ。";
			link.l1 = "あ、ああ、なるほどな……それでメアリーはイッカクってわけか？";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "ああ。で、あいつはお前に何を話したんだ？";
			link.l1 = "チャド・キャッパーは、お前が捕らえたアラン・ミルロー――彼女の恋人――を殺したんだ。その後、お前が殺人を犯したという噂を広めやがった。さらに、 メアリーの復讐心を自分の都合のために利用しようとしたんだぜ。";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "「チャドがアランを殺したのか！？でも、なぜだ？」";
			link.l1 = "責任をお前に押し付けて、ナーワルズをお前に敵対させるってわけだ。カッパーの最終目的はお前を排除して、 自分が提督の座に就くことだぜ。メアリーはその計画に加担するのも、カッパーの愛人になるのも拒んだから、 奴は部下に彼女を殺させたんだ。";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "「それを全部あいつが話したのか？」";
			link.l1 = "ああ。嘘はついてなかったと思うぜ。それに、チャド・キャッパーからの手紙も渡された。もう読んじまった。ほらよ。";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = " （読みながら）…ああ、これは間違いなくチャドの字だな。くそっ！信じられねえ！この野郎！裏切り者め！\nあいつの腸で吊るしてやる！レイトン！五人連れてこい、そし…\nいや、やっぱりやめだ、レイトン。下がれ！もっと賢くやるぞ。\nリヴァドスとの関係を改善する手を探してたが、これがその機会かもしれねえ。\nあいつらの魔術師チミセットがタルタロス、つまりこの島の牢獄に捕まってる。リヴァドスに自分たちで仲間を救わせて、 その時にチャドを殺させるんだ。\nレイトン！タルタロスに行って、うちの見張りを全部上甲板から引き上げろ！ "+pchar.name+"、お前に大事な仕事があるんだ。リバドスの頭目、ブラック・エディを探し出して、そいつと交渉してこい――";
			link.l1 = "俺か？でも、ここには誰も知り合いがいねえんだ！";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "これからだ、まずはエディから始めるぞ。あいつはリバドス一族全体の頭だ。\nお前が俺たちの代表として交渉するのに一番ふさわしい男だぜ。俺の手下の海賊どもじゃ、 エディに会うことすら許されねえし……正直なところ、あいつらは弁が立つわけでもねえからな。";
			link.l1 = "（ため息）わかった、あの…ブラック・エディに会いに行くぜ。";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "この鍵を持って行って、あいつに渡せ。タルタロスのすべての扉を開けられる鍵だ――チミセットを救い出すには黒人たちに必要になるだろう。\nそれから、この五十ドゥブロンも持っていけ。これから知ることになる地元のもう一人は、 カロラインの仲介者で外交官のジュゼッペ・ファジオだ。このドゥブロンで今週のリヴァドス領の合言葉を買え――ファジオは毎週選ばれる合言葉を手に入れるのが商売なんだ。\n次に、プロテクターのところへ行け。そこはブラック・エディの住処だ。チャド・キャッパーがナーワルズに加わり、 俺の命令を聞かなくなり、今日チミセットを殺すつもりだと伝えろ。\n鍵を渡して、強力な部隊を率いてタルタロスを襲撃するように言え。\nこれで一石二鳥だぜ――リヴァドスは俺たちを味方だと思うし、キャッパーは黒人たちの手で死ぬことになる。全部わかったか？";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "そうだと思うが、プロテクターとキャロラインはどこにいるんだ？";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "聞けよ、スティーブ、リバドスとナーワルって奴らが何者か教えてくれ。俺はまだそいつらについて何も知らねえんだ。";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "奴らは正義の島の最初の開拓者の子孫でできた一族だ。ナーワル族は主にイギリス人、オランダ人、フランス人の血筋だ。 リバドス族は全員黒人だ。\nそれぞれの一族にはリーダーがいて、いくつかの船を持ち、それが外部者立ち入り禁止の縄張りになっている。\nナーワルでもリバドスでも、その縄張りに入るには正しい合言葉を知っていなきゃならねえし、 その合言葉は毎週変わるんだ。";
			link.l1 = "なるほどな。だが、プロテクターとキャロラインはどこで見つけりゃいいんだ？";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "俺の住処を出て、ロープの橋を渡って左に曲がれ。そこがキャロライン号だ。\
プロテクター号に行くのは少し面倒だぜ。橋を渡ったら右に曲がって、サンタ・フロレンティナ号まで行け――板橋の向こう側だ。\nリバドスの兵士を探せ――言った通り、全員黒ずくめだ。奴らは合言葉を聞いてくる。はっきり大きな声で言え。それからフューリー号に入り、 船尾からプロテクター号に入るんだ。";
			link.l1 = "よし…分かったぜ。";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "よし、それじゃあさっさとやれ、相棒！";
			link.l1 = "すぐ戻るぜ。";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "まだここにいるのか？今すぐブラック・エディのところへ行け！";
			link.l1 = "俺は今向かってるところだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "赤毛のメアリーを殺そうとした奴がいたのか？";
			link.l1 = "あいつの名前だったか？助けようとしたが、襲ってきた奴の一人にサーベルで斬られちまったんだ。";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "あの娘には気の毒だが、驚きはしねえ。メアリーは昔から厄介者だったからな。\nそれで、チャドはどうした？あいつは俺の甲板長だぜ。";
			link.l1 = "お前の甲板長か？ああ…えっと、これだ、この手紙を読んでくれ。あの娘の遺体で見つけたんだ。カッパーがスティーブン、 お前の命を狙ってるらしい。";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "どこに行ってたんだよ！？リバドスが自分たちの魔術師を解放したって聞いたが、お前の姿は何時間も見てねえぞ！";
			link.l1 = "すまない、スティーブン。黒人たちはお前が裏切った時の保険として、俺をプロテクター号で人質に取っていたんだ。 チミセットは解放されたが、チャドは逃げちまった。";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "ちくしょう！白人の仕事を黒人に任せるんじゃなかったぜ…こんな簡単なことすらしくじりやがって…リバドスの野郎ども、くたばりやがれ！";
			link.l1 = "チャドはイッカクの連中の中に隠れてやがる……";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "もちろんだ！あいつは馬鹿じゃねえ――リバドスどもがタルタロスに入り込めたのは俺の助けがあったからだと分かってる！今ごろはどこかに隠れて、 影から企んでやがるだろうよ。\nレイトン！警備を倍にしろ！常に目を光らせておけ！チャド・キャッパーを地獄に送った奴には大金をくれてやるぞ！！";
			link.l1 = "スティーブン、俺は行くぜ。もしかしたらチャドの足取りを掴めるかもしれねえ。何か分かったら戻ってくる。";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "「何があった、」 "+pchar.name+"？まるで悪魔に追われてるみてえな顔じゃねえか！";
			link.l1 = "ウイスキーの樽は手に入れたか？";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "ウイスキーだと――？";
			link.l1 = "ウイスキーの樽を手に入れたのか！？";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "声を抑えろ、野郎！ウイスキーなんて持ってねえぞ！どうしたんだ？";
			link.l1 = "「間に合って本当に良かったぜ……チャド・キャッパーがアクセル・ヨーストからブッシュミルズの樽を買ったって――」";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "ブッシュミルズか？それは俺の大好物の酒だぜ！もう何年も飲んでねえな！";
			link.l1 = "ああ、そうだぜ、カッパーもそれを知ってる。だから奴は仲間のマルチェロ・サイクロプスに頼んで、 サンチョ・カルペンテロからヒ素を買わせたんだ。もう分かったか？";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "俺を毒殺しようとしてたのか…？";
			link.l1 = "ああ！だから俺はあんなに急いでたんだ。くそっ、心臓が……。いいか、もし誰かがウイスキーの樽を持ってきても、絶対に飲むなよ！毒が入ってるぜ。";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = ""+pchar.name+"「警告ありがとな、気をつけるぜ――おい、今度はどこへ行くつもりだ？」";
			link.l1 = "カッパーとサイクロプスを探さなきゃならねえ。あいつらがどこにいるか、だいたい見当はついてるぜ。 すぐにまた話そう！";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "ははっ！探してたのはまさにお前だぜ！どうやら命の借りができちまったようだな。";
			link.l1 = "ウイスキーは届いたか？";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "そうだ！ブッシュミルズ、その通りだぜ。親愛なるファジオが親切にも贈り物として持ってきやがった。もちろん、 俺はあいつを逮捕したさ。";
			link.l1 = "「奴は白状したか？」";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "そうだ。カッパーに無理やりやらされたってよ、俺には「ウイスキーはナーワルズからの贈り物だ」 と伝えろと命令されたらしいぜ…";
			link.l1 = "カッパーは死んだ。ナーワルの仲間どもも同じだ。残るクソ野郎は一人、マルチェロ・サイクロプスだけだ…ファジオならあいつの居場所を知ってるはずだぜ。ちょっと締め上げてやるか！";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "遠慮なくやってくれ――だが殺すなよ、俺たちのファジオは体があまり丈夫じゃねえんだ。";
			link.l1 = "優しくしてやるさ……まあ、だいたいな。";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "「うう…」 "+pchar.name+"「……友よ、俺はどうもおかしくなっちまった……」";
			link.l1 = "スティーブン！このウイスキーを飲んだのか！？";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "ああ…ブッシュミルズか…ジュゼッペ・ファツィオが今日持ってきたんだ、ナーワルの頭からの贈り物だってよ…和平のしるしだとさ…\nくそっ、痛ぇ！";
			link.l1 = "あのウイスキーにはヒ素が入ってたんだ！！やったのはチャドとサイクロプスだ！";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "うぐっ…とうとうやられちまったぜ、クソ野郎が…";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "死ぬんじゃねえぞ！聞こえるか？お前は死なねえ！さあ、これを受け取れ。このフラスコだ。世界一強力な治療薬だぜ、 何でも治すんだ。今すぐ飲め…さあ！";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "「スティーブン…！」";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "「ああ…」 "+pchar.name+"…あれはすげえな。まだちょっと気分が悪いが、痛みはほとんど消えたぜ…";
			link.l1 = "インディアンのシャーマンが俺にくれたんだ。全部一気に飲み干せ！さあ、これで……";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "奇跡だ…体がすっかり良くなったぜ！ありがとう、相棒…この恩は忘れねえからな！";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "今は休んだ方がいいぜ。死人みてえな顔してるぞ。あのクソ野郎カッパーはもうお前を脅せねえ――俺があいつとナーワルの仲間どもを片付けてやったからな。残ってるのはマルチェロ・サイクロプスだけだ。 ファジオがウイスキーを持ってきたって言ってたよな？\n";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "今は休んだほうがいいぜ。死人みてえな顔してるぞ。ファジオがウイスキーを持ってきたって言ったか？";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "ああ、そうだ。なんであいつがあんなに緊張してたのか不思議だったが……俺の偉大なる存在の前に立ってるからだと思ってたぜ、へっへっへ……";
			link.l1 = "カッパーが無理やりやらせたに違いねえな。よし、あのデブ野郎に会いに行って、いろいろ聞き出してやるぜ。 今は休んでろ、スティーブン！";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "ああ。なんであいつが緊張してたのか不思議だったが……俺様の偉大な存在感にビビってるだけかと思ってたぜ、へっへっへ…";
			link.l1 = "カッパーがあいつを無理やり巻き込んだに違いねえ。あのデブ野郎はそのうち俺が始末してやるが、 今はカッパーとサイクロプスを片付けなきゃならねえ。奴らの隠れ場所は分かってる。今は休んでくれ、スティーブン！";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "「おう、」 "+pchar.name+"！エヴァ号でのカッパーとの揉め事、聞いたぜ、ハハハ！驚いたもんだ！ チャドとその手下どもを一人でぶっ殺すなんてよ……ヤンの言った通り、お前の腕前は本物だな。";
			link.l1 = "カッパーの件は片付けただけじゃねえ、あんたの命を狙った企みも未然に防いだんだぜ。スティーブン、 お前は毒殺されるところだったんだ。だがもう大丈夫、俺が全部片付けたからな。";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "俺に毒を盛るだと？どうやってだ？";
			link.l1 = "チャドがアクセルからアイリッシュ・ブッシュミルズのウイスキー樽を買った――";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "「ブッシュミルズか？これが俺の大好物だぜ！もう何年も飲んでねえんだ！」";
			link.l1 = "カッパーはそれを知ってたんだぜ。仲間のマルチェロ・サイクロプスに頼んで、 サンチョ・カルペンテロからヒ素を買わせた。それから奴と仲間たちはファジオを捕まえて、 エヴァ号の貨物室に降りていったんだ。ウイスキーに毒を盛って、ファジオに「イッカクの連中からの贈り物」 って体でお前に持って行かせるつもりだったんだよ。\n";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "くそっ……うまくいくはずだったのによ。あのウイスキーを一気に一杯飲んでやったぜ。";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "チャドはそれを当てにしてたんだ。だが失敗しやがった――ヒ素を入れる暇もなかったってわけだ。\nだからよ……俺が樽ごと持ってきた。お前にやるよ、手つかずのままだぜ。";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "チャドはそれを当てにしてたんだ。だが失敗した――ヒ素を入れる暇さえなかったんだぜ。";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "見せてみろ… "+pchar.name+"「これは本物のブッシュミルズだぜ！最高のアイリッシュウイスキーだ！ああ、何年も夢見てたんだよ！\nお前は、俺の友だちだ……くそっ、お前は奇跡の職人だな！チャドを片付けて、俺の命を救って、 しかも俺の大好きなウイスキーの樽まで持ってきやがる、まるで朝飯前みたいにな！\nこれは相応しい褒美が必要だな。\n（ごそごそ探る）クソ、どこだ……？あっ！これだ、持ってけ。『トールの槌』って呼ばれてる代物でな、壊れねえんだ。 もう二度と大砲が暴発する心配はいらねえ！お前の砲手も大喜びだぜ！」";
			link.l1 = "なんてこった、スティーブン…ありがとう！きっと彼もそうするよ。";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "さて、と。俺はこれからこの素晴らしいウイスキーと仲良くする時間だ…… "+pchar.name+"、明日また俺のところに来い。その間にちょっと考え事があるんだ…";
			link.l1 = "よし、スティーブン、ウイスキーの邪魔はしねえよ、はは！";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "全部話してくれて助かったぜ。お前の言葉とチャドの行動について考えさせてもらう…それから呼ぶからな。";
			link.l1 = "待ってるぜ！";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "「はっ、そこにいたか、」 "+pchar.name+"。これで全員そろったな、始めるぜ。お前とレイトンを呼んだのは、この状況について話し合い、 ナーワルどもをどうするか決めるためだ。";
			link.l1 = "「『イッカクどもをどうするか』って、どういう意味だ？」";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "「『どういう意味だ？』だと？チャドがナーワルズの連中と組んで俺の命を狙いやがったんだ。\nこれは明らかに敵対行為だぜ。黙って見過ごすわけにはいかねえ。リバドスとは友好関係にあることを考えれば、 こう提案する…\nネグロスと正式に同盟を結び、仲間を集めてナーワルズを根絶やしにするんだ。\nお前、」 "+pchar.name+"、また俺たちの使者になってもらうぜ。ブラック・エディとチミセットに話して、 俺の友好の申し出を受け入れるよう説得してくれ。デクスターが戦略を立てる、 あいつはこの島を誰よりも知ってるからな。レイトン？";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "最初からイッカクどもを皆殺しにする必要はねえ。食糧はこの島で俺たちが握ってるんだ。\n奴らをサン・ガブリエル号まで追い込めば、閉じ込めて飢え死にさせられるぜ。どうだ、 "+pchar.name+"?";
			link.l1 = "俺が何を言うかって？…ナーワルズを見逃してやれ、スティーブン。";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "……ここに来る前に頭でも打ったのか？チャドと戦った連中がナーワルズだったのを忘れたのか？";
			link.l1 = "全部じゃねえよ。マルチェロ・サイクロプスは違った。実際、あいつはリバドスに忠実だった――なんせ混血だったからな。チャドに加わったイッカクどもは、金で買えた連中か、 あるいはお前がアラン・ミルローを殺したって嘘に騙された奴らだけだと思うぜ。";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "「それでどうしろってんだ、俺がこんなこと全部無視しろってのか？」";
			link.l1 = "俺が外交官の役をやってみるってのはどうだ…ただし、相手はナーワル団の頭、ドナルド・グリーンスパンだぜ。話を聞いてくれるか、スティーブン？";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "…続けろ…";
			link.l1 = "俺はここに来てから、廃墟船の街についていろいろ学んだぜ。\n島に二つの氏族しかいなかった頃は、住民たちが言うには、戦争が絶えなかったらしい。\nだが、お前たち海賊がやって来て、島に三つ目の勢力ができたことで、初めて均衡と平和が生まれたんだ。\nとはいえ、ナーワルとリバドスは今も強大で、勝利を得るには莫大な犠牲が必要になるだろうな。";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "ナーワル号の壊滅の代償は、多くの海賊とリバドスの命になるだろう。\nそれに、レイトンが言ってたが、サン・ガブリエルの包囲は長引くらしいし、 もしリバドスがこの遠征で失うものが多すぎると感じたら、手を引くだろう……下手すりゃ俺たちに牙を剥くかもしれねえ。";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "両方の一族が今もなおこの島を支配しようと狙ってるのを忘れるなよ。つい最近まで、 奴らはお前と戦うために手を組んでたんだ。この戦争が思ったほど早く、あるいは予想通りに終わるとは限らねえぜ。\nその渦中にいるのは、普通の連中だ。\n墓場の王になりたいって本気で思ってるのか？";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "…なるほど、いいこと言うじゃねえか…だが、まだ俺を納得させちゃいねえぞ。";
			link.l1 = "俺もどうにかしてこの島を出なきゃならねえんだ。海底にあるククルカンの偶像まで行かなくちゃいけねえ。 リバドスどもは助けてくれねえ……だが、ナーワルならどうだろうな。あいつらには頭が切れて腕の立つ奴らがいるって聞いたことがある。戦争中じゃ、 俺に協力なんてしてくれねえだろうがな。";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "A-ha! I knew you had selfish reasons for wanting peace! And I guess that one of them is that redhead on the Ceres, eh, my friend? Am I right? Don't worry about her, "+pchar.name+", we'll find a safe place for her before the fighting starts.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+" だが、そこまで言うなら仕方ねえ。ドナルドに会いに行け。あいつの住処はエスメラルダの奥だ。 あのろくでなしが何を言うか聞いてこい。\nもしあいつとその一味がチャドの企みに関わってねえとお前が納得したなら……和平も考えてやるぜ。";
			link.l1 = "ありがとう、スティーブン。これは正しい決断だと俺は確信してるぜ。";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "だが、あいつを簡単に許すんじゃねえぞ！チャドと一緒にいたのは、あいつの手下どもだ――ナーワルズの連中だ！しっかり土下座させて、きっちり悔い改めさせろよ！";
			link.l1 = "やるさ、やるってば。";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "それで、ドナルドと話したか？";
			link.l1 = "ああ、話したぜ、そして俺の疑念は確信に変わった。あいつも、あの一族全体も、 チャドの企みにゃ一切関わっちゃいねえ。計画に加担したナーワルどもは、全部カッパーが引き入れた連中だ。 あいつはひどく気を落としててな、アラン・ミルローの殺しやその後の出来事について、 お前には一切責任がねえと俺に保証してくれたぜ。";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "奴は俺の前に立って、これを全部俺の顔に向かって言う覚悟があるのか？";
			link.l1 = "奴は聖書にかけてそうすると誓ったぜ。";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "へっ、こりゃ驚いたぜ……やっぱり責められるべきクソ野郎は、裏切り者の俺のボースンだけってわけか……";
			link.l1 = "俺はそう確信してるぜ、スティーブン。こんな戦争なんざ俺たちに必要ねえし、誰にも必要ねえ。 商売にもならねえからな。";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "（テーブルを叩く）よし、決まりだぜ！グリーンスパンが来て俺のケツにキスしたら、全部水に流してやる…それで和平ってわけだ。";
			link.l1 = "すぐに彼に伝えるぜ。スティーヴン……この戦争を回避できて本当に良かった。";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Feel free to bring your Mary over to the San Augustine, I can set aside some quarters for the two of you.";
			else sTemp = "";
			dialog.text = "待てよ… "+pchar.name+"、こんな神に見放された正義の島によく来てくれたな、嬉しいぜ。\nヤンが手紙でお前のことをべた褒めしてたが……正直、俺の期待なんざ軽く超えてくれたぜ。\nもしお前が俺の船員だったら……いや、実際にな！カッパーの役職をお前にやる。この間、タルタロス号の守備隊を指揮してくれ。 "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "いや、スティーブン、ありがとう。でも俺はもう長くここにはいないんだ。 その仕事はもっとふさわしい信頼できる若い奴に任せてくれ。それとメアリーのことだけど……セレス号ではうまくやってるよ。";
			else link.l1 = "いや、スティーブン、ありがとう。でも俺はもう長くここにはいないんだ。 その仕事はもっとふさわしい信頼できる若い奴に任せてくれ。";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "お前ほどふさわしくて信用できる奴はいねえだろうよ。だがな、お前が何を言おうと、 この正義の島から抜け出すのはそんなに簡単じゃねえと思うぜ、期待しすぎるなよ。\nまあ、いいさ。さて、何もなしでここから出すわけにはいかねえから、黙ってこの五百ドゥブロン受け取れ。";
			link.l1 = "ありがとな！";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "俺たちの取引について話そうぜ…俺のルターを持っていけ。そこには正義の島まで無事に船を導くための航海指示が書いてあるんだ。\n絶対に失くすなよ！それがなけりゃ、お前の船は暗礁に乗り上げるか、嵐でバラバラになるぜ。それとな、 島に近づけるのは比較的小さい船だけだってことも忘れるな！ロングボート、タルタン、ラガー、スクーナー、 それ以上はダメだ。\nお前が俺を迎えに戻ってきたら、俺もスヴェンソンと一緒にその遊びに加わってやるよ。\n沈んだインディアンの偶像が本当に役立つなんてまだ信じちゃいねえが…幸運を祈るぜ、相棒。";
			link.l1 = "頼るべきは神じゃねえ、スティーブン、ククルカンだ。\nまた会う日までだぜ。";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = ""+pchar.name+"…できるだけ早く戻ってこい。俺の倉庫はもう底をつきかけてるんだ、もうすぐ食い物がまったくなくなるぞ。 武装した腹ぺこの連中が何をしでかすか、わかってるだろう？";
			link.l1 = "少し考えがあるんだ。じゃあな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "島から脱出する方法を見つけたのか、 "+pchar.name+"?";
			link.l1 = "まだだ、スティーブン、俺はまだ作業中だぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "さて、何を持ってきたんだ、 "+pchar.name+"？面白い話でもあるのか？";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "スティーブン、取り上げた俺の持ち物を返してほしいんだが。";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "スティーブン、この島についてもっと教えてくれ。";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "ホークが島にいねえって本当に確かか？あいつは偶像を通って来たんだ、ここにいるはずだろう。";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "「ホワイト・ボーイって男を知ってるか？」";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "ナーワルとリヴァドスの領土はどこだ？";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "どうやって一族の船に乗り込むための合言葉を知ればいいんだ？";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "聞けよ、この島の地図はあるのか？";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "お前のブロードソードは見事だな。こんなの、今まで見たことねえよ…";
				link.l8.go = "blade";
			}
			link.l9 = "まだ質問はねえな。まあ、そのうち出てくるかもな…";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "ああ、そうだったな！すっかり忘れてたぜ……お前の物は二階の箱に入れてある。取りに行けよ、レイトンは止めやしねえさ。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "この島は百年以上の歴史があるぜ。外輪にあるキャラベル船の中には、竜骨が1550年かそれ以前に据えられたものも見たことがある。\n俺たちの足元には浅瀬があって、ここに座礁した難破船を支えて水面上に保ってるんだ。 毎年多くの船が朽ち果てて塵になるが、嵐と強い海流が新たな船を運んでくる。\n正義の島は、まるで生き物みたいにクソして、食って、成長するんだよ。\n最初の入植者たちはデ・ベタンクールの遠征隊でここに来た。サン・アウグスティン号とタルタロス号がその一部だった。 タルタロス号には黒人奴隷が大勢積まれていて、その中にペドロ・リバドスって男がいた。 彼はスペイン人の看守に対して反乱を起こしたが失敗し、ゆっくり死ぬ刑にされた。マストに縛り付けられて、 太陽の下で焼かれるってやつだ。\nだが、彼の自由への試みがデ・ベタンクールの乗組員を弱らせたおかげで、二度目の反乱は成功し、 彼を讃えてリバドス一族ができたのさ。\nリバドス一族が島を支配することを恐れた白人のキリスト教徒たちは、野蛮なアフリカ流に対抗するため、 奇跡的に国籍の違いを乗り越えて団結し、ナーワル一族を作った。\nへっ、白人どもが自分たちより黒人が上に立つかもしれないって危機感を持てば、違いなんざすぐに脇に置くもんだ。\nナーワル一族には傭兵や兵士、士官や冒険者がたくさんいる。毎年物資を集めて、 ここに流れ着いた難破船から新しい男を選んで仲間にしてる。その成果は今も見て取れるだろう。やつらは規律正しくて、 プロの軍隊だ――それだけでリバドス一族の島支配の野望を抑え込むには十分だったってわけだ。";
			link.l1 = "この島とカリブの他の場所に何か繋がりはあるのか？";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "この十年は誰も来てねえな。ここらの連中の話じゃ、島の周りの天気が変わったらしいぜ。嵐は増え、 潮の流れも強くなった。\nまるである日突然、島がカリブの他の場所から切り離されたみてえだ。\n昔は島の連中もキューバのバッカニアどもと交易してた。難破船から拾った金や宝で食い物を買ってたが、 正義の島にはもう十年もバッカニアが来ちゃいねえ。\nま、帰ってきたやつは一人もいねえがな。";
			link.l1 = "ふむ。つまり、フォレストデビルもブラックパスターも両方正しかったってわけか……。\nそれで、なぜチャンスがあったのに人々は正義の島を離れなかったんだ？";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "何人かは出て行ったが、大半はここに残りたがったんだ。多くの連中はここを自分の家にしちまったし、 他の奴らはここで生まれて他を知らねえんだよ。\n出て行きたいやつもいるが、嵐の海域をオンボロの寄せ集めの船で渡るのが怖くて踏み出せねえんだ。\nリバドスの連中については……まあ、あいつらは黒人だしな。俺が知る限り、外の世界は白人のもんだ。ここに残りたがるのも無理はねえだろ？";
			link.l1 = "「で、なんでここに来たんだ、ドドソン？お前はフリゲート艦を持ってたし、名の知れた海賊だったじゃねえか――」";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "（ドンッと机を叩く）俺は狩られてたんだ！！\nブレイズ・シャープ殺しの濡れ衣を着せられた！誰に、何のためにかなんて、全く分からねえ。\n誰かの企みに俺は駒にされて、敵に囲まれ、仲間にも見捨てられた。 だからイスラ・テソロを離れて身を隠すしかなかったのさ。\nこの島の存在は前から知ってたが、俺のフリゲートじゃここには来れなかった。でかすぎて礁を越えられなかったからな。 だからブリッグと交換したんだ。\nここに着くなり、ナーワルズとリバドスに襲われたぜ――黒人も白人も、お互い以上に海賊を憎んでやがるらしい、へっへっへ。 夜中に奴らがロングボートで俺の船に乗り込んできて、火を放ちやがった。\nこっちは大砲で奴らのボロ船を木っ端みじんにしてやったが、火の勢いは止められなかった――俺の可哀想なブリッグは骨組みだけ残して焼けちまった。\n俺たちはブチ切れて反撃した――サン・アウグスティン号に突撃して、コルセアの戦い方を見せてやったぜ！奴らは持ちこたえられず、 腰抜けどもは尻尾巻いて逃げやがった。\nサン・アウグスティン号を奪って分かったのは、島中の連中があの船を倉庫代わりに使ってたってことだ！一夜にして、 俺たちはこの島で一番の一族になったのさ。\n今じゃ、正義の島のクソども全員が、自分の食い物を俺たちの言い値で買い戻さなきゃならねえ、ハハハ！\nそれに、ナーワルズのアラン・ミルロウと、リバドスのブードゥー使いチミセットって二人の族長も捕まえた。 相棒のレイトンが数日かけて島を偵察して、それから奴隷船タルタロスを襲ったんだ。\n今じゃ二隻の船を押さえて、他の一族どもは俺たちと取引するしかねえ……さもなきゃ飢え死にだ。今はまあ、ここにも平和みたいなもんがあるぜ。\n市民どもについては……食い物は安く売ってやってる――奴らは俺たちに武器を向けなかったからな。ま、他の二つの一族のバランスを俺たちが取ってるのが、 奴らには気に入ってるみたいだぜ。";
			link.l1 = "信じられねえ……そりゃあすげえ話だな！";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "あいつは見てねえ。ホークがマルーンタウン以外にいるなんて、今初めて聞いたぜ。\n島のどこかや外輪に隠れてる可能性もあるが――隠れる場所ならいくらでもあるしな――でも、もうとっくに俺に顔を見せに来ててもおかしくねえだろうに…";
			link.l1 = "なるほど……";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "白い坊主？ふん……いや、その名前は聞いたことねえな。だが、ここにいねえってわけじゃねえ――この島のクズども全員を俺が知ってると思うなよ？";
			link.l1 = "いや、いや。わかった、他の奴に聞くぜ。";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "この島はナーワルズ、リヴァドス、そして俺たちの海賊で分け合ってる。その間には中立地帯があるんだ。\n俺が支配してるのはサン・アウグスティン号とタルタロス号だ。\nリヴァドスはプロテクター号（あいつらのリーダーの住居）、フューリー号（兵舎）、ヴェラスコ号（倉庫） を押さえてる。よそ者は立ち入り禁止で、そこに行くには特別な合言葉が必要だぜ。\nナーワルズはたくさんの船を持ってる。エスメラルダ号は店であり、リーダーの住居でもある。 サン・ガブリエル号とフェニックス号は、なんか科学者みたいな奴が仕切ってる。それからセレス号は鍛冶屋だ。\nエスメラルダ号以外の船は全部立ち入り制限区域だ。中に入るには合言葉がいる。リヴァドスも同じだぜ。 しかも合言葉は毎週変わるんだ。\n残りの船は中立地帯とされてて、住民たちはそこで暮らしてる。\n誰か忘れてねえか……ああ、フルロン号はサンチョ・カルペンテロって男がやってる酒場だ。それからグロリア号は地元の教会で、 ジュリアン修道士が牧師をしてるぜ。";
			link.l1 = "覚えることが多いな……まあ、自分の足で街を歩いて覚えるしかねえな。";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "族と寝返るってわけだ。だが、お前はナーワルズにはタフさが足りねえし、リヴァドスには肌の色が合わねえからな、 古いフリゲート艦キャロライン号に行って「ジュゼッペ・ファツィオ」っていうデブ野郎を探せ。 あいつはここじゃ外交官みてえなもんだ。\n島に来る前に何してたかは知らねえが、あの男は筋金入りの悪党だぜ。誰とでも商売するしな。 族連中はあいつを仲介役に使ってるから、毎週の合言葉も必ず渡されてる。\nファツィオは強欲で、ドゥブロン銀貨一枚のためなら自分の肉でも食いそうな奴だ。 リヴァドスかナーワルの領地の今週の合言葉を聞けるが、金を払う覚悟はしとけよ。";
			link.l1 = "キャロライン…ファツィオ…ああ、大丈夫だ、ありがとう。";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "デクスターが一つ持ってるぜ。あいつは俺の一等航海士だ。ここに着いた直後に詳しい地図を作ったんだ。 上の階に行ってデクスターに話してみな、売ってくれるかもしれねえぞ。";
			link.l1 = "了解だ。ありがとな！";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "はっ！ナーワル一族の頭領アラン・ミルローからの戦利品だぜ。\nナーワルの鍛冶屋ユルゲンが、海の底で見つけた珍しい鉄で作ったんだ。錆びねえし、切れ味も鈍らねえ。 一振りで二人を真っ二つにできる代物さ。\nこの剣は、この遠征で手に入れた数少ねえ良いものの一つだ。だからこそ、どんな値でも手放す気はねえよ。";
			link.l1 = "「ユルゲンはこんなブロードソードをもう一本作れるか？」";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "ふん！ありえねえな。ユルゲンはイッカク野郎だ、自分の一族にしか忠誠を誓わねえし、 よそ者のために武器なんざ絶対作らねえよ。\nそれに、もう一本剣を作るにはあの特別な鉄が必要だ。その鉄は海の底にしかねえし、エラでも生えてねえ限り、 どうやって手に入れるつもりだ？だから、諦めな。";
			link.l1 = "なるほど…残念だな…";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = ""+pchar.name+"！おい、イカれ野郎め、はははは、よく来たな！！地平線にお前の帆を見たぜ！調子はどうだ、相棒？航海はどうだった？ ";
			link.l1 = "へっ、俺も会えて嬉しいぜ、スティーブン。生き延びたぞ。";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "よし！畜生、俺はもうこの正義の島から出て、フォレストデビルと一杯やりたい気分だぜ。\nレイトンは提督として残ることになる――もう俺の椅子を奪っちまったからな、はは！あいつ、本気でこの場所が気に入ってるみたいだ。";
			link.l1 = "お前は以前、ここに上陸した多くの奴らが外の世界よりもここでの暮らしを好むようになるって言ってたな。 デクスターも同じだってことに驚いてるのか？";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "ええ、"驚いた"ってわけじゃねえ……ただ、あいつを失って悲しいだけだ。あんなに優秀な副長はいねえよ。\nさて……いつ出航するつもりだ？";
			link.l1 = "すぐだ。俺の船に乗れ、スティーブン。ここでの用事が済み次第、すぐに出航するぞ。";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "お前が船長か！ああ、また甲板の揺れを足元で感じられるのは最高だぜ！";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "ブルーウェルド……妙なもんだな……もう二度と緑の木や野原なんざ見られねえと思ってたぜ……\n…\n…ゴホン、まあ……俺はスヴェンソンに会いに行く。お前も奴に会って、これからのことを話してこい。これから熱い日々が待ってるぜ、な？ ";
			link.l1 = "間違いないな、スティーブン。順風を祈るぜ！";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "ああ、できることはやってやるぜ！さあ、話せ。";
			link.l1 = "スティーブ、見てみろ…サメの歯だぜ。まさか見覚えがねえなんて言わねえよな！";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "ははっ！そうだ、その歯は俺のもんだ――いや、正確には、女を惚れさせるために仕留めたサメの歯さ。だから俺は「シャーク」・ドドソンって呼ばれてるんだぜ。 \n素手のサーベル一本で水中でそんな芸当できる奴は滅多にいねえが、当時の俺は若くてバカだったし、 ベアトリス・シャープはカリブで一番の美人だったんだよ……\nで、それをどうやって手に入れたんだ？";
			link.l1 = "セントジョンズの元死刑執行人がこれを俺にくれたんだ。これで一人の男がぶった斬られた。 奴の名はジョシュア・リードビーターだ。";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "ふん、お前の「ブッチャー」ならここにいるぜ。この牙で奴の喉を掻っ切ったんだ。\nベアトリスが死んだ時は心が張り裂けそうだったし、リードベーターだけが俺の手の届く唯一の罪人だと信じてた。\n奴が最後に泡吹いて死んだ後、いくつか書類を見つけてな……色々と事情が分かった。復讐を望む権利は奴にもあったんだ。\nブレイズの妹はただ運が悪かっただけで、マスクが彼女の死を責められる筋合いはなかった。 奴の狙いはブッチャーだけだったからな。正直に言うと……あいつを殺したことは後悔してる。\n全部仕組んだのは、あのクソ女ジェシカだ。";
			link.l1 = "まだその書類を持ってるのか？";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "もちろん違うぜ。俺にはあいつらなんて必要なかったからな。だが、もし興味があるなら、 なぜマスクがブッチャーを追い回してたのか教えてやってもいいぜ。";
			link.l1 = "ああ、そうだとも。よし、インクと羽ペンを寄越せ、全部書き記してやるぜ。";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "ああ、いいぜ。じゃあ聞けよ。ジョシュア・リードビーターは英国の艦長で、 伝説となったフリゲート艦ネプチューンの指揮を執っていたんだ…";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "…だが、リードビータは生き延びて、通りかかった船に救われた――ただし、傷で顔が変わり果ててな。\nそれ以来ずっと仮面をつけて、自分を不幸にした張本人を見つけて罰することが奴の生きる目的になったんだ。";
			link.l1 = "なるほど…よし、全部書き留めたぜ。あとで読み返すさ。悲しい話だな。ジェシカのこと、知ってたのか？";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "ああ、もちろんだ！あいつはブッチャーの全ての航海に付き添ってたんだが、 ブッチャーがベアトリスに乗り換えてからは捨てられちまった。ジェスはそれを絶対に許さなかったぜ。\nみんな彼女のことを「ブッチャーのお守り」って呼んでた。彼女が一緒にいる限り、 ブッチャーには運がついて回ったからな。\nだがバルバドスに彼女を置き去りにした途端、商売は傾き始め、戦利品も枯れちまって、 ネプチューン号はイサ・テソロルの造船所の常連になった。まあ、 ブッチャーが船尾楼じゃなくてベアトリスと船室にこもりっきりだったせいもあるだろうがな。\nベアトリスはジェシカとは違った。冒険や戦いを求める女じゃなかった――ニコラスが剣術や航海術を教えたが、あいつはロマンチストで、海賊になるには芯が足りなかったんだ。\nこの暮らしはベアトリスには向いてなかった。結局、それが彼女を殺したんだ。";
			link.l1 = "「それでジェシカはどうしたんだ？」";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "ああ、あいつはすごかったぜ！ネプチューン号の船乗りはみんな、彼女の命令に一切逆らわなかった。 船長の女だったからってだけじゃねえ。\nジェスは剣術も航海術も達人でな、全部ブッチャーから学んだんだが、やがて師匠すら超えちまった。 気が強くて怖いもん知らず、それでいて天使が赤面するほどの美貌まで持ってやがった。\n多くの男がジェスを狙ったが、彼女が欲しかったのはブッチャーだけ。下手に言い寄れば、 剣の稽古をタダでつけてくれるが、それが人生最後の稽古になる奴も多かったぜ。\nジェスは特別な剣を持っていた。カリブで唯一の代物だ。どこで手に入れたかは知らねえ。炎のような波打つ刃の剣だ。 その刃が少しでも触れれば、ひどい傷を負うことになる。\nジェスは生まれつきじゃなく、志で冒険者になった女だ。もっと知りたきゃ、お前の知り合いの中に、 ジェスについて俺より詳しい奴がいるぜ。";
			link.l1 = "本当か？それで、その男は誰だ？";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "ヤン・スヴェンソン。\nあの老いぼれ森の悪魔は絶対に認めねえが、ジェシカに目をつけてたんだ。 スペイン領西インドを自分のものにした直後で、カリブ中に名が知れ渡ってたから、 あの女豹も自分のもんだと踏んでたんだろうよ。\nブッチャーがジェスを始末した後、ヤンは定期的にバルバドスに顔を出すようになった。 それでイングランド野郎どもはピリピリし始めた。知ってるだろ、 ジェシカはブリッジタウンのプランターの娘だったからな。\n俺たちはみんなヤンの狙いが分かってたし、ろくな結末にならねえとも思ってたが、誰も何も言わなかった。 今じゃブルーウェルドでケツを温めてるヤンだが、 当時はちょっとでも悪口言おうもんなら毒の刃と荒くれバッカニアどもを引き連れて家まで来やがったもんだ、へへ……\nだがヤンの企みは全部水の泡さ。ブッチャーの仕打ちに耐えかねたジェスは、 一年後にマスクの手を借りて復讐を果たした。\n結局、その復讐がジェス自身も、マスクも、ベアトリスも、ブッチャーも、みんなまとめて滅ぼしちまったんだ。";
			link.l1 = "ブッチャーはまだ生きてるぜ。";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "…くだらねえ…";
			link.l1 = "スティーブン、ブッチャー船長はまだ生きてるぜ。 ジェイコブ・ジャックマンとヘンリー・ザ・ハングマンが処刑人に会いに行ったんだ。\n絞首刑はでっち上げだった。証拠もあるぜ。";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "偽物か…で、今ブッチャーはどこにいるんだ！？";
			link.l1 = "今は自分のことをローレンス・ベルトロープと名乗ってやがる。ポートロイヤルに住んでるぜ。だが、 あいつは今でも危険な野郎だ。ブレザレンに散々迷惑をかけたジャックマンも、実はブッチャーの命令で動いてたんだ。\n";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "畜生め！ついに四分士が船長の元に戻ったってわけか！\nベルトロープだと…待てよ！そうか、ブレイズの書類に妙な尋問記録があった理由が今わかったぜ…どうやらブレイズもブッチャー＝ベルトロープのことを掴んでたらしいな…";
			link.l1 = "何の話だ？";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "俺がこの住処を手に入れた後、ブレイズの古い書類を漁ったんだ。 サミュエル・ブルックスとかいう奴の尋問記録を見つけたぜ。\nそこには「トーマス・ベルトロープの冒険」って話が出てきて、そいつが海賊で、 ニコラス・シャープの親友として知られてたってな！\nどうやらトーマスってのはブッチャーの親父らしいぜ。";
			link.l1 = "面白いな……シャープとベルトロープのガキどもは親の稼業をそのまま継いだってわけか……";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "そうみてえだな……だがよ、相棒、お前はなんで死人どもの所業にそんなに興味があるんだ？";
			link.l1 = "俺が欲しいのは書類だ――ヘレン・マッカーサーがビアトリス・シャープの娘であり、 彼女の財産に対するすべての権利を持っていることを証明する書類だぜ。ヘレンがベルトロープの娘でもあるなんて、 俺にはどうでもいい。";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "リードビータの書類にもブレイズの記録にも、ヘレン・マッカーサーについては何も書かれてねえな。\nベアトリスが自分の姪の誕生をブレイズに知らせなかったなんて、あいつらしくねえな……";
			link.l1 = "聞けよ、もしかしてシャープの書類に他にも何かあるんじゃねえか？細かいことまで全部必要なんだ！";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "ふむ、そうだな……ブレイズの手記によれば、奴は妹が死んだ島を探そうとしていたらしい。\nリードベーターの懲罰遠征に関する書類もあるが……緯度の数字以外は面白いことは書いてねえな。\nこの緯線はカリブ海の北側を横切ってる。だが経度がねえ。\n明らかにブレイズの探索は失敗したんだろうな。その緯度に沿ってどれだけ小さな島があるか、想像もつかねえぜ。";
			link.l1 = "数字を教えろ。";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "そうだな……ここだ：北緯21度32分。\nだが、経度がなけりゃ役に立たねえじゃねえか。";
			link.l1 = "それは俺に任せてくれ。話を聞かせてくれてありがとう、スティーブン。また今度な！";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "そう言えるかもな。さて、トルトゥーガの話だ。\nあの島の名は、亀に似ているから付けられたんだ。まあ、 ルヴァスールは十二年もかけてその亀の甲羅を分厚くしてきたぜ。\n奴の最高傑作がラ・ロシュ要塞だ。正面から攻め込むなんざ自殺行為だぜ。あの要塞の重砲なら戦列艦だって粉々だ。\nこの美味いスープを作るのは簡単じゃねえ。スペイン野郎どもも長いこと挑戦してるが、まだ成功しちゃいねえんだ。";
			link.l1 = "スヴェンソンがルヴァスールを倒すのに協力してくれるって約束したんだ。お前が作戦を考えてるって聞いたが、 どうなってるんだ？";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "ここ数週間、俺の手下どもがトルトゥーガの街を歩き回って、面白い情報をたっぷり集めてきたぜ。\nいい知らせだ、相棒：どうやらラ・ロシュの大砲とやり合う必要はなさそうだ。俺たちだけじゃなく、 ルヴァスールにうんざりしてる奴は他にもいるらしい。あいつの友達が、あいつの死を望んでるってよ。";
			link.l1 = "続けろ…";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "ルヴァスールが若い娘に目がないってのは、けっこう有名な話だ。あいつが楽しんだ後は、 娘たちは跡形もなく消えちまう。\nトルトゥーガで奴隷を一番さばいてるのは、ガレオン船ヴォルティジュールのロバート・マーテンだ。そいつの相棒で、 ルヴァスールの甥っ子アンリ・ティボーが、港で一番の美人を patron のために選んでるってわけだ。\nちょっと前、マーテンがイギリスのブリッグ船モリー・ジョーンズからとびきりの美人を手に入れた。 夜にトルトゥーガのどこかの秘密の洞窟で、その娘をルヴァスールの甥ティボーに引き渡したらしい。\n船員たちには「その娘は心臓発作で死んだから、遺体は海に捨てた」って話してたが、 実際は港の哀れな売春婦でも買って殺して、そいつの死体を使ったんだろうよ。\n結局のところ、マーテンとティボーはモリーをルヴァスールに渡さず、自分たちのものにしちまったってことだ。 ルヴァスールがそれを知ったら、ただじゃ済まねえぞ。";
			link.l1 = "これを利用できるって本当に思ってるのか？マーテンとティボーも自分たちがどんな危険を冒してるか分かってるはずだ。 やつらも用心してるに決まってるぜ。";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "そうだな。でもどんな鎖にも弱い輪があるもんだぜ。\n三日前、元ヴォルティジューの船員フェルナン・リュカって野郎がバステールの酒場で飲みすぎて、 面白いことをいろいろ喋っちまったんだ…\nどうやらモリー・ジョーンズが、セントジョンズにいる兄貴に助けを頼むようリュカに頼んだらしい。 だがリュカは兄貴のところにたどり着けなかった。\nあいつは船長から逃げて、今はグアドループで自分の臆病さを忘れようと酒をあおってる。\nアンティグアはフランスの海賊には安全な場所じゃねえ――覚えておけよ！フォックス大佐は、フランスの私掠船に妻を殺されてから、 島中のヤシの木に一人ずつ吊るしてやると誓ったんだ。あいつの海兵どもは、 その願いを叶えるために全力を尽くすだろうぜ。";
			link.l1 = "気を抜くな、スティーブン……マーテンとティボーについて教えてくれ。なぜあいつらはそんな危険を冒したんだ？ モリーの色香がそんなに強かったのか、それともあの奴隷商人どもが珍しく情けを見せたのか？";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "あのクズ野郎マーテンのことはよく知ってるぜ。あいつがこんな危険を冒すってことは、金か自分の身を守るためか、 どっちかだろうな。\nもしかしたら、マーテンはあの娘で大金の身代金を取れると思ってるのかもな――だが、それはありえねえ。あの娘は召使いの格好でトルトゥーガに来たんだからな。\nそれとも……ははっ！マーテンがルヴァスールよりも恐れる奴がいるとしたら、誰だろうな……？";
			link.l1 = "ふむ……ティボーについてもっと話してみろ。";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "あの男についてはあまり知らねえが、ルヴァスールが自分の後継者にするほど信頼してるってことだけは知ってるぜ。\n女がどこに監禁されてるのか、なぜティボーがマルテンをそんなに自由にさせてるのかは分からねえが、 この小さな謎の答えが分かれば、トルトゥーガに突撃しなくてもこの勝負に勝てるかもしれねえ。 お前はフランス人だろうから、こういうやり方の方が好みだと思ってな。\nだが急いだ方がいいぜ、ルーカスの酔っ払いの戯言がいつトルトゥーガ行きの船に乗るか分からねえし、 もしルヴァスールが俺たちより先にこの話を嗅ぎつけたら……終わりだぞ！";
			link.l1 = "すぐに出発するぜ。";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "こうするんだ。まずアンティグアに行け。モリーがルーカスを兄貴探しにそこへ送ったんだ。もしかしたら、 その兄貴が役に立つ情報を持ってるかもしれねえ。\nその後はグアドループに尻を運べ。ルーカスを見つけて、マルタン、ティボー、ヴォルティジュー、 それからモリーについて知れることは全部聞き出せ。";
			link.l1 = "ありがとう、スティーブン。アンティグア、それからグアドループだな。";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "行けよ！";
			link.l1 = "セントジョンズでモリーの兄貴を見つけたぜ。フォックス大佐の書記だ。\nだが、何かおかしいんだ……あいつは妹のモリーを「お前と同じくらいの背丈で、でもお前ほど可愛くない有名な婆」と言ってた。\nモリーはフォックスの娘キャサリンのお付きで、つい最近までイングランドで一緒にいたらしい……";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "キャサリンについてだが、確かに美貌で有名な女だし、父親の誕生日に会いに行く予定だったんだが、 彼女を乗せた艦隊が遅れてしまってな…";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "フォックス大佐が護衛艦隊なしでイングランドを出るのを禁じたから、 モリー・ジョーンズがティボーの捕虜ってわけじゃねえ。じゃあ、あいつは一体誰なんだ……？";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "ふむ……俺にも分からねえな。たぶん、あんたが探してるモリー・ジョーンズとは別人かもしれねえ。\nだがよ……偶然が多すぎる。全部が偶然だなんて信じられねえ！\nなあ……ちょっとした疑いがあるんだが……";
			link.l1 = "どういう意味だ？言ってみろ！";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "…もしキャサリンが父親の命令に背いて護衛なしで出航したとしたらどうだ？先月はかなり嵐が多かったし、 アルバトロス号も損傷して、マーテンの格好の獲物になったかもしれねえ。\nキャサリンは本当の名前をマーテンに隠して――理由はわかるだろ――代わりにモリーの名前を教えたんじゃねえかと俺は疑ってるぜ！";
			link.l1 = "ちくしょう！そうなると、すべて辻褄が合う……だが、とんでもねえ仮定だぜ！";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "そういうことだぜ、相棒。俺が間違ってるかもしれねえが…";
			link.l1 = "…だが、もしそれが本当なら、すべてが変わるぜ！イングランドに支援を頼んで、 シーフォックスどもの銃剣で道を切り開かせることもできるじゃねえか！";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "「落ち着け」 "+pchar.name+"！証拠が必要だ。俺が言った通り、俺が間違ってるかもしれねえし、キャサリンはまだロンドンにいて、 護衛が出航するのを待ってるかもしれねえ。\nイングランド人にも自分たちの問題があるから、ラ・ロシュを攻撃するリスクは冒さねえだろう。でも、 もし俺たちが正しくて、フォックス大佐が娘に何が起きたか知ったら……\nやつはトルトゥーガの周りに封鎖線を張って、援軍を待つはずだ。それから街を攻撃する。 シー・フォックスどもは接近戦じゃ恐ろしい連中だから、軍も民間人も死傷者が山ほど出るぜ。\n そして最後には、きっと三日後にはトルトゥーガの廃墟にイングランドの旗が掲げられるだろう。 それでも本当にいいのか？";
			link.l1 = "いや……いや、知らねえよ。今やっと、マーテンが言ってた身代金のことがわかったぜ。";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "用心しねえとな。マーテンがキャサリンの本当の正体を知ってるかどうかも分からねえ。 フォックス大佐を脅すなんて自殺行為だぜ、特にクロムウェルの艦隊がカリブに来るって時にな。\nもしキャサリンが俺たちのせいで死んじまったら、最悪の事態になる。フォックス大佐が自分の娘を殺されたと思えば、 コーストの兄弟団なんざ一発で潰されちまうぞ。\nだが、どうしてもキャサリンを消さなきゃならねえ時は、絶対に俺たちの仕業に見えねえようにして、 なおかつ奴に俺たちの目的を手伝わせるんだ。\n一番いいのは、あの娘を親父の元に送り届けることだな。助けた奴にはたっぷり褒美がもらえるぜ、へっへっへ…";
			link.l1 = "スティーブン、あんたは天才だぜ！俺はトルトゥーガに行く。モリーがキャサリン・フォックスかどうか確かめてくる。";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "時間を無駄にするな、 "+pchar.name+"。もし俺の言った通りだったら、あの娘を必ず生かしておけよ。";
			link.l1 = "できることは全部やるぜ。";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "ホッホー！言ってみろ、相棒！どんな問題でも俺たちが必ず解決してやるぜ！";
			link.l1 = "じゃあ、単刀直入に言うぜ。ミゲル・ディチョソを知ってるか？";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "あいつのことは知ってるぜ。あのスペインのドンが俺に素晴らしい船――フリゲート艦を売ってくれたんだ。ええ、あれはすげえ船だったぜ、想像してみろよ…";
			link.l1 = "当ててやろうか、特別な船体、最高速度十六ノットってとこか？『サンタ・キテリア』か？";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "船体と速さについてはお前の言う通りだが、名前が違った――『サン・マルティン』だった。俺はあいつに大金を払ったんだ、持ってた金を全部な。貯めてた金は全部、 あの悪党の懐に消えちまったぜ。";
			link.l1 = "本当にその船の名前はサン・マルティンで、サンタ・キテリアじゃなかったのか？それに、いつ手に入れたんだ？それと、 なんであいつを悪党呼ばわりしてるんだ？";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "質問が多いな！全部順番に答えてやるぜ。間違いなくサン・マルティンだったと俺は確信してる。 アレクサスの手下どもが船尾からあのカトリック野郎の名が書かれた板を外すのを、俺自身が手伝ったんだ。 俺がこの船を「フォーチュン」と名付けた――こんな姫様にはずっとふさわしい名だろう。\nブレイズ・シャープが1654年の冬に殺される少し前に、この船を買ったんだ。なぜミゲルをそう呼んだかって？ あのクソ野郎がプロビデンスのスペイン軍基地からこの船を盗み出すことに成功しやがったからさ。 俺たちはサン・フアンの砦の目の前で、やつらに見事な芝居を打ってやった。もっともらしく見せるために、 半死にのラガー船を二隻犠牲にした。俺たちは船を燃やし、沈めて、フリゲートとの戦闘を演出したんだ。 そして闇が降りた頃――サン・マルティンをテソロ島へと運んだ……俺が船を手に入れ、ディチョソは金を手に入れた。やつは上官に「フリゲートは海賊との戦闘で沈んだ」と報告し、 サン・フアンの司令官もそれを確認したのさ。";
			link.l1 = "それがスペインのドンどもが懐を肥やすやり方か！なんて悪党だ！教えてくれ、ほんとに1654年の冬のことだったのか？それとも春か？それに、フリゲートは嵐で損傷したのか？";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "冬だったか……くそっ、はっきり覚えてねえな――春だったかもしれねえ。本当に思い出せねえんだ。フリゲートは無傷だった、まっさらでな。 造られたばかりって感じだったぜ。あの船のことを思い出すと、悔しくて泣きたくなるんだよ……";
			link.l1 = "「なぜだ？ああ、それで今はお前の美しいフリゲート艦はどこにあるんだ？」";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "あいつはもう俺の元にはいねえからだ。奴らは俺をハメやがった、俺のお守りをブレイズの死体に置いて、 俺が殺し屋だって噂を流しやがった。それから聞いたんだ、マーカス・タイレックス――俺たちの掟番――が俺にブラックマークを渡すつもりだってな。だからしばらくそのゴタゴタから逃げようと思って、 正義の島に身を隠したんだ、そこでお前が俺を見つけたってわけだ\nフリゲートじゃそこまで行けなかったから、ブラック・パスターにあの船を担保にして、 食料満載のブリッグと引き換えたんだ。あのずる賢いディチョーソとの取引の後じゃ、 手元に金もほとんど残ってなかったしな。食料を売って、ひと月かふた月でイスラ・テソロに戻るつもりだった……まあ、その後のことはお前も知ってるだろう。";
			link.l1 = "それでブラック・パスターはお前を待たずに、あいつを売っちまったんだ";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "その通りだ。あの娘はイングランド人、いや、正確にはスコットランド人のウィリアム・パターソンに買われたんだ。 俺があの娘を取り戻そうとすることもできるがな、だがこのハイランダーは手強い野郎でな、 王立海軍の艦長でフォックス大佐の親友だ。それに、あいつはジャックマンと商売してた、 お前がスヴェンソンとやってたのと同じようにな。\nあのスコットは艦隊を持ってる……くそ、もう俺の船には二度と会えねえな。";
			link.l1 = "なるほどな。で、今そのディチョソがどこにいるか知らねえのか？";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "知らねえな。俺が自分のフォーチュン号を手に入れてから、あいつの姿は一度も見てねえ。";
			link.l1 = "「それで、なんでミゲルは他の奴にそれを買わせようとしなかったんだ？タイレックスとか、バルバゾン、 シャープはどうだ？それともパターソンか？」";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "俺には全然わからねえ。その時パターソンはいなかったはずだ。ザカライアとジャック、 それにマーカスも絶対に同意しなかっただろうし、俺は……俺はあのフリゲート艦が本当に気に入ってたんだよ！";
			link.l1 = "分かったつもりだが…全然分からねえ。どこもかしこも謎だらけだ…";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "また昔話か？今度はどの島を手に入れたいんだ？ははは！";
			link.l1 = "一つ島がある……だが、まだそこへの道が見つからねえ。まあいい、スティーブン、情報ありがとよ！じゃあな！";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "幸運を祈るぜ。 "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "「そして、俺はいつも通りお前を助けてやれて嬉しいぜ。で、今回は何の用だ、」 "+pchar.name+"?";
			link.l1 = "またお前の古い友達ミゲル・ディチョソのことだ。奴がまたイスラ・テソロで目撃されたって話は知ってるぜ。お前、 奴を見つけるのを手伝えねえか？";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "おう、相棒、それは知らなかったぜ。ここであいつは見てねえな。『フォーチュン』をあいつから買って以来、 会ってねえ。で、なんでそのスペインのドンが必要なんだ？";
			link.l1 = "俺にはあいつが必要だ。ミゲルは古いインディオの都市への道を知ってるんだ。俺はどうしてもそこに行きたいんだぜ。";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "いつも通りだな、相棒。お前はまた厄介ごとに首を突っ込むつもりか。残念だが、俺にはどうにもできねえ。\n集落を歩き回って人に聞いてみろ、もしかしたら誰かが見かけたかもしれねえぞ。ここじゃ有名な男だからな。";
			link.l1 = "おい、スティーブン、せめてそいつがどんな顔してるか教えてくれねえか？";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "そうだな、あいつは二十五か二十八歳くらいで、お前と同じくらいの背丈だ。目は黒くて、カツラはかぶってねえ。 右の頬にサーベルの傷があるぜ。";
			link.l1 = "ふん。その説明に当てはまる奴はたくさんいるぜ。";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "彼について他に特筆すべき点はねえ。自信満々で、傲慢で、すげえ危険な野郎だ。やつについての噂もあったがな…";
			link.l1 = "なるほど。わかった、そいつのことを聞いて回ってみるぜ。幸運を祈る、スティーブン！";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "ほうほう！ここは正しい場所だぜ！言いたいことをぶちまけな！";
			link.l1 = "海賊を恐れねえ奴がいるんだ。俺たちのことをなめてやがる。礼儀ってもんを叩き込んでやる必要があるな。だが、 殺すんじゃねえぞ。\n";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "ほう！こりゃあ、あのじじいのチャールズじゃねえか！また何かやらかしたんだろう？\nさあ、詳しく聞かせろよ。今度の標的は誰で、そいつに何を教えてやるつもりだ？";
			link.l1 = "ヨーロッパからの客人、フランス財務省の監察官であるノエル・フォルジェ男爵だ。 ここにフランスの交易会社を設立したいらしいが、俺と親しい仲間はそれに反対してるんだ。 レヴァスールが倒された後は、オランダ人やイギリス人、そして特に海賊どもがいるせいで、 ここでの交易は非常に危険だと男爵を説得しようとしたが、あいつは耳を貸さなかった。やつに恐怖を味わわせて、 自分の身で思い知ってもらう必要があるな。";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "ああ、そうだそうだ……本物の男爵だぜ！……で、あいつの船を襲うのか？";
			link.l1 = "こういう計画だ：あいつの船はもうすぐポルトープランスからキャップスタービルへ出航する。 出発した後でバロンを捕まえて人質にしろ。船を沈めたり、乗組員を殺したりしない方がいいぜ。 フランス人は俺たちの友人だからな。お前にそれができるか？";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "まあ、何も約束はできねえが、やってみるさ。どの船だ？";
			link.l1 = "「ファヴォリー」という名のブリッグだ。";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "ブリッグなんざ俺のフリゲートの敵じゃねえ。楽勝で片付けてやるさ。もし降伏するなら、全員生かしてやるぜ。";
			link.l1 = "完璧だ。奴らに恐怖を与えて降伏を勧めろ。その後、バロンをネズミだらけの船倉にぶち込め。 一番汚い場所を探して入れてやれ。ただし、一日以上は置くなよ、病気になって死なれたら困るからな。 そしたら船室に移してやって、正義の島へ向かうんだ。人目のつかない場所に閉じ込めろ。 部下の何人かを捕らえられたフランス商人に扮装させて、それらしく振る舞わせろ。三日間ぶっ通しで、 容赦ない海賊どもに追われ、奪われ、身代金を要求され、拷問された話を細かく全部聞かせてやれ……必要なだけな。";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "ハハハ！こんなに面白え仕事は久しぶりだぜ！よし、最高の役者を見つけてやるよ、相棒。心配すんな、 あいつらの話を聞いたらお前のバロンもチビっちまうぜ！ カットラスや焼けたラマー棒でできた傷跡まで見せてやるからな… ";
			link.l1 = "上出来だぜ。そしたら、あいつにポワンシー宛ての身代金要求の手紙を書かせるんだ。 大物の割に三百五十万なんて安いもんだろ。";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "よし。次はどうするんだ？";
			link.l1 = "それからお前がバロンをタークスまで連れて行くんだ。そこで身代金を受け取って、バロンを俺に渡すんだぜ。\nそれともう一つ、トルトゥーガとルヴァスールの件はフランス野郎ども全員に責任を取らせるって伝えておけよ。";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "ハハハ！とんでもねえ手だな！俺たちが、まあ、あのルヴァスールに何をしたかは知ってるだろうが、今度は……ハハハ！……いいぜ、相棒。やってやる！船がもうすぐ到着するって言うのか？";
			link.l1 = "すぐだ。警戒を怠るな。";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "気にするな、俺がしくじるわけねえ。これは俺が自分で片付ける。あのバロンが捕まったって噂を聞いたら、 俺のところに来い。";
			link.l1 = "いいだろう。礼を言う、スティーブン。";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "もちろんだぜ、相棒。約束通りにな。悪党の海賊が無垢なフランス商人を虐殺する怖い話、鞭の音、うめき声と悲鳴。 炭火の入った火鉢に焼け焦げた手錠。まさにそうあるべきだな。";
			link.l1 = "おいおい！ちょっと待て。そいつは生かしておく必要があるんだ。";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "心配すんな、あいつは生きてるぜ。手が震えながらも手紙を書いたんだ。ほら、これだ。";
			link.l1 = "そこには何て書いてあるんだ？ポワンシーに助け出してくれって泣きついてるのか？";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "その通りだぜ、相棒！あいつ、泣きついてやがる！";
			link.l1 = "この手紙は捨てろ、いや、燃やした方がいいな。\n一週間後にタークスで会おう。\n身代金を集めるために時間が必要だと思わせるんだ。";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "了解だ。一週間後、北の湾だぜ。金を持ってくるのを忘れるなよ、見栄えが大事だからな。終わったら俺のところに来い、 きっちりケリをつけようじゃねえか。";
			link.l1 = "もちろんだ、ウニでさえ気づくことだろうぜ。じゃあな！ ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "おい、カエル食い！止まりやがれ！";
			link.l1 = "俺は動かねえ。";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "ほらよ、お前のバロンだ。少しボロくなっちまったが、ちゃんと一つの塊で戻ってきたぜ。こいつで間違いねえか？";
			link.l1 = "ああ。";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "完璧だ。さあ、金を渡せ、さもねえとあいつは終わりだ！ごまかそうなんて思うなよ、こっちはお前を狙ってるんだぜ！";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "ほら。";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "くそっ！船に忘れてきちまった……";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "ハハハ！お前、なかなか頭が切れるな、フランス野郎。ほら、聖職者を連れて行け。それとポワンシーに伝えろ、 金を用意しとけってな。フランスのクソ野郎どもは、ルヴァスールとトルトゥーガにやったことのツケを払わせてやる。 お前らの商人どもも、商品と船で俺たちに払うことになるぜ。ハハハ！それから、 もっとバロンどもをこの諸島に連れてこいよ、あいつらはたっぷり儲けさせてくれるからな！ハハハ！";
			link.l1 = "俺の船に行ってくれ、バロン。";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "追ってくるなんて考えるんじゃねえぞ、船長。俺が誰だかわかってるだろう。 俺はカエル食いどもをまだ何人も捕まえてるんだ。もし俺が時間通りに帰らなかったら、部下が全員ぶっ殺すぜ。 わかったか？";
			link.l1 = "時が来たら、お前ら呪われた冒涜者どもをぶっ潰してやるからな！";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "「ハハハハハ！」";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "俺をからかってんのか？";
			link.l1 = "ちょっと待ってろ、今持ってくる…";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "ああくそ、スティーブン、てめえの間抜けが何しやがったんだ！";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "チャールズ、何してやがった？金はどこだ？俺の手下どもには、これが偽物だなんて言ってねえんだ……だからこのバカが、お前が奴らを騙そうとしたと思い込んじまったんだよ……";
			link.l1 = "なんてこった！バロンが死んじまったか……これからポワンシーはどうするんだ？";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "さて、相棒、これはお前のせいだぜ、わかってるよな。まあ、 もしかしたらその方がお前にとっちゃ良いことかもしれねえな。";
			link.l1 = "俺はなんて間抜けなんだ！全部台無しにしちまった。まあいい、ポワンシーに行くさ…バカな俺を許してくれよ、スティーブン。またな。";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "休めよ、腕が鈍ってきてるぜ。たまには俺のところに来い、ラム酒といい女を用意してやるからな。";
			link.l1 = "ありがとう、時間ができたらお前のところに顔を出すぜ。";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "どういたしまして、相棒。今年一番楽しかったぜ！俺と仲間たち、腹がよじれるほど笑ったからな！\nだから礼を言わせてくれ。ほら、約束の金だ。";
			link.l1 = "自分の取り分はちゃんと取っとけよ。";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "気にすんな。これは俺たちの友情のためにやったんだぜ。沿岸の兄弟団はお前にもっと借りがあるってのに、 お前はドゥブロン銀貨一枚も要求しなかったじゃねえか。";
			link.l1 = "それでも、せめて五万は受け取ってくれよ、手間賃と償いだ。\nありがとう、スティーブン！あの沈没船だらけの奇妙な島、正義の島でお前に会えたこと、本当に嬉しく思ってるぜ。";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "俺もだぜ。チャールズ、時間ができたらいつでも俺のところに来いよ！";
			link.l1 = "喜んでだぜ！";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "一週間も遅いじゃねえか！俺は仲間たちにこれが本当じゃねえって言わなかったんだ…！あいつらはもう待てねえってさ、お前のバロン人生を終わらせるって決めやがったんだ！";
			link.l1 = "なんて間抜けなんだ、俺は！全部台無しにしちまった！ポワンシーに何て言やあいいんだ？";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "まあ、相棒、これはお前のせいだぜ、わかってるだろうな。たぶん、その方がお前にとっても良いかもしれねえな。";
			link.l1 = "わかった、ポワンシーに行くよ……バカだった俺を許してくれ、スティーブン、またな……";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "休めよ、お前、腕が鈍ってきてるぜ。たまには俺のところに来い、ラム酒といい女を用意してやるからな\n";
			link.l1 = "ありがとうな、時間ができたらお前んとこに顔を出すぜ。";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "面白いな、興味が湧いてきたぜ。さて、散歩でもしようじゃねえか。";
			link.l1 = "...";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "脾臓が飛び出しそうだぜ！信じられねえ！本当にあいつなのか？教えてくれ、あれは本当にあいつか？これが『 フォーチュン』なのか！？";
			link.l1 = "ああ、相棒、目の錯覚じゃねえぞ。あれがそうだ。恋しかったか？";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "ははは、信じられねえ！くそったれが千匹もいるってのか！だが、どこで手に入れたんだ？";
			link.l1 = "あるスコットランド野郎、ウィリアム・パターソンってやつからだ。\nああ、そうだ、あのブラック・パスターからそれを買ったやつさ。";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "ぶったまげたぜ…で、あいつが「フォーチュン」をお前に売ったってのか？あんな美しい船を？しかもお前が買った後にか？";
			link.l1 = "へへ、まあ、ほとんどそんなもんだ。こう言っておこうぜ：俺たちはまったくウマが合わなかったんだよ、 それで俺は揉め事で被った損失の埋め合わせとして船をいただいたってわけさ。あいつにはどうせ船なんて必要ねえしな。 ";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "さらに驚かせてくれるじゃねえか……あいつはイングランドに仕える軍人の船長だぜ。あの植民地の艦隊なら、やろうと思えば略奪もできる。俺ですら、 あいつには手を出す勇気がなかったんだ。で、どうやって確かめたんだ？「フォーチュン」 を艦隊から引き離すことに成功したのか？";
			link.l1 = "いや、艦隊は沈んじまったんだ。実は簡単じゃなかったぜ。戦いは本気だったが、人の住んでねえ場所から遠く離れてて、 目撃者は俺の水夫と士官だけだった。だからまあ、イギリス当局に追われる心配はねえよ。ウィリアム・パターソンは、 ただのいつもの冒険の最中に消えちまったってわけさ…";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "なんてこった…俺はもう自分のスワロー号に二度と会えねえと諦めてたんだ。まあ、 この船があんたの忠実な相棒になってくれることを願ってるぜ。本当に良かったな、友よ！";
			link.l1 = "なんだと？あいつはいらねえのか？俺は正当な持ち主に返してやりたかったんだが…";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "ハハハ、相棒よ、「フォーチュン」はお前のものにしておけ。まず第一に、お前が正当な持ち主だ。戦いで正々堂々 と手に入れたんだからな。これで船を捨てるのは良くねえ。それに、俺にはもう新しい船があるんだ。「フォーチュン」 を買った時は、まさか他の船に乗り換えるなんて思ってもみなかったが……まあ、もう二度とあの船に会えねえと思ってたから、アレクサスに新しいフリゲート艦を注文したんだよ。でな……あいつ、すげえ腕前だぜ。聞いた話だと、しかも今回はお前も一枚噛んでたらしいな、ハハ！";
			}
			else
			{
				dialog.text = "ハハハ、相棒よ、「フォーチュン」はお前のものだぜ。まず第一に、お前が正当な持ち主だ。戦いで堂々 と手に入れたんだからな。ここで船を手放すなんてよくねえ。そして第二に、俺のために新しい船がもう建造中だ。 もちろん「フォーチュン」を買ったときは、他の船に乗り換えるなんて思ってもみなかったさ。だが、 もう二度とあいつに会えねえと思ってたから、アレクサスに新しいフリゲート艦を注文したんだ。 そいつの甲板に足を踏み入れる日が待ち遠しいぜ。";
			}
			link.l1 = "じゃあ、この美しい船は俺がもらうしかねえな、スティーブン！";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "その通りだ。俺が頼むのは「フォーチュン」を大事にしてくれってことだけだぜ。信じてくれ、 あんな船は他にどこにもねえ。唯一無二だ。俺にとっちゃ思い出の品でもあるしな。だから、 友達であるお前がこの船の持ち主になるって思えば、安心できるし嬉しいんだ。どこかのクズ野郎じゃなくてな。";
			link.l1 = "わかった、スティーブン。俺が「フォーチュン」を必ず守ると約束するぜ。";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "ああ、それともう一つ……";
			link.l1 = "聞いてるぜ。";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "今や「フォーチュン」を手に入れたんだ、ひとつ商売を持ちかけたいんだが。";
			link.l1 = "俺はお前の話をすっげえ注意深く聞いてるぜ。";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "言った通り、アレクサスは今俺のために新しいフリゲートを建造中だ。もちろん、やつが作る船が「フォーチュン」 ほど速くはならねえだろうが、そう大きく劣ることもねえ。\nそれに、俺には強力で速い船が二隻ほど必要なんだ。一人でもやれなくはねえが、二隻あればずっといいからな。";
				link.l1 = "いいだろう。それで、どんな商売なんだ？";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "言った通り、アレクサスが最近俺のために新しいフリゲートを造ってくれたんだ。もちろん、あいつが「フォーチュン」 ほど速い船を作れるとは思っちゃいねえが、そう大きく劣ることもねえだろう。それに、 俺にはどうしても強力で速い船が二隻ほど必要なんだ。一人でもやれなくはねえが、二隻あった方がずっといいからな。";
				link.l1 = "いいだろう。それで、どんな商売なんだ？";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "その話をするにはまだ早いな。新しい船がいつ造船所から出るのか、俺にもまだ分からねえんだ。 アレクサスが資材の調達でちょっと苦労してるらしい。\nそうだ、お前に機会があれば、手伝ってやるといいぜ。きっとちゃんと報酬もくれるさ。 俺がかなり前金を渡してあるからな。\n全部の資材が揃ったら、たぶん一ヶ月で船が仕上がるだろう。その時はお前を待ってるぜ。だが、必ず『フォーチュン号』 で来て、事前に装備も整えておけよ。時間があまりねえからな！\nそれと、スペイン野郎どもに首を銀の皿に乗せて差し出されねえように気をつけろよ。詳しいことはまた後で教えてやる。 ";
			link.l1 = "よし、うちの船大工に何か手伝いが必要か聞いてみるぜ。\nそれから、俺がアレクサスを手伝って一ヶ月後、お前がまた航海に出る時に話の続きをしようじゃねえか。";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "それについて話すのはまだ早いぜ、俺の船はまだ造船所からも出てねえんだ。装備もこれからだしな。だから、 早くても一ヶ月後にしか待ってねえぞ。だが必ず『フォーチュン号』で来いよ、事前に装備も済ませておけ、 そうすりゃ時間もかからねえ！それと、スペイン野郎どもがお前の首を銀の皿に乗せたがってねえか、 ちゃんと気をつけろよ。詳しいことは後で全部教えてやる。";
			link.l1 = "よし、じゃあお前がまた航海に出る時にでも、話の続きをしようじゃねえか。";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "まあ、いいだろう。今から屋敷に行くぜ、文句はねえな。物事ってやつは、待っちゃくれねえからな。";
			link.l1 = "すぐに会おうぜ、シャーク！別れの挨拶なんてしねえぞ。";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "俺のは準備できてるぜ、お前のはどうだ？「フォーチュン号」で来いって言っただろ。どこに置いてきたか知らねえが、 他の船でこんな賭けに出るのは危険すぎる。だから、約束したあの船で待ってるぜ。あと、締めすぎるなよ。";
				link.l1 = "くそっ、すっかり忘れてたぜ、このクズ野郎！待ってろ、ちゃんとした船に戻ってくるからな。";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "チャールズ、俺は艦隊を連れてくるなと言っただろう。お前とやりたいことに余計な船なんざ絶対にいらねえんだ。 自分の艦隊をどっかにやってから戻ってこい。";
				link.l1 = "ああ、すっかり忘れてたぜ。待ってろ、すぐ戻るが、艦隊は連れてこねえからな。";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "おお、やっと来たな、相棒！やっとだぜ！お前が来ねえから心配しちまったじゃねえか。 俺の船はもうすぐ仕上がるところだ。今はティラックスのところに送ってる――先月、戦利品の大型ガレオンから手に入れた三十二ポンド砲を装備させるためにな。 あの船でトルコ野郎のとこまで往復してきたが、アレクサスはいい仕事してくれたぜ。ところで、 まだあの船にふさわしい名前を決めてねえんだ。いくつか候補はあるが……お前、選ぶの手伝ってくれねえか？";
			link.l1 = "もちろん手伝うぜ！船の名前次第で運命も決まるってもんだろ？どんな候補があるんだ？";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "今のところ、三つの選択肢に絞ったぜ。";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "最初の選択肢は「ファントム」だ。あのフリゲートは速くて強力だし、 その名を聞いただけでハバナからクマナまでの守銭奴どもが震え上がるぜ！";
			link.l1 = "ああ、しかも霧の中に現れたり消えたりして、水夫どもが本気で洗礼を受けたくなるくらいにしねえとな、ははは！ いい名前だ、気に入ったぜ。";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "俺も気に入ったぜ。二つ目の選択肢は「サメ」だ。で、どうした？俺の船にもあだ名をつけてやろうじゃねえか。 あいつと同じ名前にしてやる、ははっ！";
			link.l1 = "「シャーク」にサメがいるとは……皮肉だな。だが、これで誰の船か一目瞭然だぜ。";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "ここでも俺は同じようなもんだぜ。そして三つ目の選択肢は「フラーリー」だ。 俺の船に近づくことすら誰もがビビるようにな、ははは！";
			link.l1 = "横っ腹から弾丸の嵐を食らうこともあるからか？それがどうした、悪くねえじゃねえか。";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "その通りだ！だが今、この三つの名前の中から決められねえんだ。だからよ、手を貸してくれ。好きにしてくれていいぜ。 ";
			link.l1 = "「『ファントム』と名付けるのはどうだ。そうすりゃ、商人どもはお前が地平線に現れた瞬間、白旗を投げ出すぜ！」";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "「シャーク」って名前、気に入ったぜ。みんなに知らしめてやる、この船はただの新参者じゃなくて、 海賊同盟の頭そのものだってな！";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "「フラーリー」はいい名前だと思うぜ。どんな戦士でも私掠船でも商人でも、 この船と戦おうとすりゃどうなるか思い知ることになるだろうよ。";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "お前の様子を見てみろよ――軍隊まで真似し始めるぜ、はは！じゃあ、決まりだな。ジョッキを持て、相棒。俺の新しい船に乾杯しよう。『 ファントム』に！";
			link.l1 = " 「ファントムのために！」";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "俺の前に立ちはだかる前に、三度は考えさせてやるぜ！\nよし、決まりだ。ジョッキを持て、相棒。俺の新しい船に乾杯だ。\n『シャーク』に！";
			link.l1 = "「シャーク」のために！";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "それでもまだ決めるってんなら、あいつを襲う嵐は熱帯の嵐なんざそよ風に思えるほどだぜ！\nよし、決まりだ。ジョッキを持て、相棒。俺の新しい船に乾杯しよう。\n“フラーリー”に！";
			link.l1 = "「フラーリーのために！」";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "この船が忠実に仕え、敗北の苦しみを知らずに済むよう祈るぜ！\nさて、本題に入るか。";
			link.l1 = "俺はお前の話をちゃんと聞いてるぜ。";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "教えてくれ、チャールズ、「黄金艦隊」って何か知ってるか？";
			link.l1 = "カッカッ！…もうラムでむせちまったぜ。スティーブン、 お前まさか二隻のフリゲートだけでカリブ一番の重武装護送船団を襲うつもりじゃねえだろうな。\n";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "いや、もちろんだが、俺は自殺志願者じゃねえ。護送船団全部を襲うなんて絶対にしねえさ。だが、 ここなら何か一つくらいはかすめ取れるだろうぜ。";
			link.l1 = "スティーブン、すまねえが、俺にはまだ無理だ。スペイン野郎どもに艦隊へ突っ込んだら、生きたまま焼かれちまうぞ！ 俺は遠慮しとく、先に行ってくれ。";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "よし、俺たちが消えなかった場所だな……参加する準備はできてるぜ！";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "アーッ！残念だぜ。お前がいねえと俺は危なっかしすぎるんだ。まあいい、もう無理に説得はしねえが、 考えてみてくれよ、いいな？もしその気になったら、必ず知らせてくれよ。";
			link.l1 = "もしそうなら、もちろんだ。悪かったな、スティーブン。";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "そんな冒険は簡単に諦めねえぜ！\nで、どうだお前は？気が変わったんじゃねえか？";
			link.l1 = "いや、友よ、悪いが、俺はまだ遠慮しておくぜ。";
			link.l1.go = "exit";
			link.l2 = "よし、俺たちは消えちまわなかった……参加する準備はできてるぜ！";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "お前は準備できてるかもしれねえが、お前の船はまだだ。俺は「フォーチュン号」で来いと言ったはずだ。 どこに置いてきたか知らねえが、他の船でこんな賭けに出るのは危険すぎる。だから、 俺は約束したあの船でお前を待ってるぜ。\nそれと、あまり気を張りすぎるなよ。";
				link.l1 = "くそっ、すっかり忘れてたぜ、このドジ野郎！待ってろよ、ちゃんとした船に戻ってくるからな。";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "だが違う、チャールズ。お前はまだ準備ができてねえ。俺は艦隊を連れてくるなと言ったはずだ。 お前とやりたい事には余計な船なんざ絶対にいらねえ。艦隊をどこかに移動させて、また戻って来い。";
				link.l1 = "ああ、すっかり忘れてたぜ。待ってろ、すぐ戻るが、艦隊は連れてこねえからな。";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "悪魔どもめ、まさにそれが聞きたかったんだぜ！だからよ、俺とお前で護送船団から一つかっぱらおうじゃねえか。 たんまりと獲物があるぞ…";
			link.l1 = "かっぱらうってことか？見張りの軍艦に見つからずにな？";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "その通りだ。見ろよ、お前も知ってるだろうが、「黄金艦隊」ってのはポルトベロに集まって、 そこからハバナへ向かうんだ。ハバナを出た後じゃ、もう奴を襲うのは無駄だぜ。大西洋を渡ってスペインに行く時には、 アホでも近づかねえほど厳重な護衛がついてるからな。ポルトベロからハバナへの移動中も、状況は大して変わらねえ。 もちろん、やってみてもいいが、そのためには要塞を木の実みてえにぶっ壊せる艦隊を揃えなきゃならねえ。でもな、 ポルトベロにはメイン中から船が集まってくるし、そこじゃもう特に守られてるわけじゃねえんだ。";
			link.l1 = "だがな、今じゃその移送の時期も、そういう船の名前も厳重に秘匿されてるんだぜ。 俺たちが半年もポルトベロあたりでうろついて、 港に向かうスペイン船全部を待ち伏せするなんてやってられねえだろうが。\n";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "もちろんそんなことはしねえよ。例えばカルタヘナからは、船は勝手に出ていくし、あんたが言った通り、 どんな船がいつ行くのかなんて神様しか知らねえ。\nだが、スペインの鉱山が近くにあるカラカスからは、しかもポルトベロからもかなり離れてる場所だが、 そこの船はまるっきり単独ってわけじゃねえんだ。";
			link.l1 = "どうしてまったくの孤島じゃねえんだ？";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "カラカスから積荷を満載した船が単独、もしくは少数の護衛と共に出航することを突き止めたんだが、 マラカイボ湾の経度あたりでスペインの軍艦がその船と合流して、さらに安全を確保してやがる。\nどうやって、いつ、誰をそこで迎えればいいか、あいつらはどうして分かると思う？";
			link.l1 = "何か聞かされてたに違いねえ…";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "そうだ。母船が出航する前に、カラカスからポルトベロへ伝令船が向かい、会合の場所と日時、 それにスペイン船の名前を報告するんだ。\nその後、伝令船は戻ってきて、船が正しい時と場所で迎えられるという確認を運ぶ。\nそれが済んで初めて、俺たちの標的がカラカスから出発するってわけだ。";
			link.l1 = "だが、もし俺たちが使者を捕まえたら、カラカスの船は確認を受け取れず、港を出られねえってことだ。 これについて何か考えはあるか？それに、使者本人をどうやって捕まえるんだ？いつ出発するかも分かっちゃいねえぞ。";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "ここでちょっとした問題があるんだ。スペイン野郎どもは、もちろんこういう用事にクーリエ・ラガーを使うが、 これは危険だぜ。最初に出くわした海賊に捕まる可能性が高すぎる。だから、 船を送り出すまでにずいぶん待たされることもあるんだ。だからな、もしチャンスがあれば、 やつらは命令書を速くて力のある船――例えば商船や、ちょうどいい航路を通る私掠船なんかに託して送るんだ。\nまるで封印された郵便みたいにな。しかも、別にクーリエ船――ラガーでさえも――を仕立てるよりずっと安上がりだ。ケチなスペイン役人どもは、懐に何かを入れながら節約するのが大好きだからな、 へへ。";
			link.l1 = "わかった気がする！俺もそんな商人にならなきゃいけねえのか？";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "その通りだ！しかも運が良かったぜ。信頼できる筋から聞いたんだが、今カラカスじゃ、まさにそんな使者を探してて、 三週間以内に手紙を持たせて送り出すつもりらしい。お前には強力で速い船があるし、 それもスペイン人が造った船だろう！もっともらしくするためにGVIKの許可証を半年分まとめて取って、カラカスで転売用の商品を十分に買い込んでポルトベロで儲けてこい。 それから現地の港湾局の責任者のところに行って、道中で何か運ぶものがあるか聞いてみろ。\nもし港湾局に聞かれたら、スペイン人だと名乗れ。あと、絶対に艦隊を引き連れて行くなよ。目立つ必要はねえし、 下手すりゃこの計画自体が全部パーになっちまうからな。";
			link.l1 = "そして、奴らが俺に渡す書類から、船と護送船団が会う日時と場所が分かるってわけか？";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "そう簡単にはいかねえぜ。言っただろう、書類は封印されてるんだ。お前が勝手に開けることはできねえ。 ポルトベロの港役所で開封されて、そこで返事を書いてくれる。それから、 もしお前がカラカスに戻るって言ってくれるなら、その返事を持って行くよう頼まれるだろうな。もちろん、 その返事も封印されるぜ。";
			link.l1 = "「それじゃあ、どうやって集会の場所と日時を知ればいいんだ？」";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "頭を使って、どうにかして覗き見するしかねえな……例えば、ポルトベロで書類が開かれて返事を書いてる時とかによ。\nあるいは、確認書を渡された時に盗んじまうって手もあるが、その確認書はカラカスまで持っていかなきゃならねえ。\nだが、これはあまりいい手じゃねえな。そうしたら、全部うまくいかなくなるかもしれねえからな。";
			link.l1 = "もちろん難しいさ…だが、俺なら何とかできると思うぜ。";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "俺はマーカスから自分の船を受け取って、キュラソーのサンタ・マリア岬沖で錨を下ろして待ってるぜ。\nお前の準備ができたら、俺のところに来い。指定された座標でその船を捕まえて、すぐにとっととずらかるぞ。\nだからこそ、強力で速い船が必要だってわかっただろ？\nスペインの軍艦隊なんざと戦いたくねえんだ。\nお前はあいつらから逃げ切らなきゃならねえぞ。";
			link.l1 = "了解だ。じゃあ、俺は出発するぜ。サンタ・マリア岬で会おう！";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "そうだ、その場所で会おうぜ。\nじゃあ、幸運を祈るぜ、相棒！俺たちの取引がうまくいくといいな。";
			link.l1 = "俺もそう願ってるぜ。まあ、とにかく、俺は行くぜ。";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Exploration mode: timer is disabled.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "くそっ、チャールズ！もう二度と会えねえと思ってたぜ！どこに行ってたんだ？約束の場所でずっと待ってたのによ、 結局お前は来なかった。しかもお前から何の知らせもなかったじゃねえか。";
			link.l1 = "悪いな、スティーブン。俺は任務を果たせなかったんだ。";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "へっ、あんな大物を逃しやがって……まあ、落ち込むな。次はうまくいくさ。";
			link.l1 = "そうだといいが。";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+"、なんだと？俺はお前に艦隊を連れてくるなって言っただろうが！分かれよ、余計な荷物はいらねえんだ、 そうじゃねえと作戦が全部台無しになるかもしれねえ！お前に何があったか知らねえが、そんなやり方は通用しねえ。 とっととキャラバンをどこかにやって、一隻で戻ってこい。ここで待ってるぜ。";
				link.l1 = "ああ、俺もそう思ったんだ……まあ、わかったぜ。ここで待ってろ、すぐ戻るからな！";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+"、なんだと？俺は「フォーチュン」に乗ってろって言っただろうが！いいか、速くて強い船が二隻必要なんだ、 そうじゃなきゃ作戦全体が台無しになるぜ！お前に何があったか知らねえが、そんなやり方じゃダメだ。 今すぐそのボロ船から「フォーチュン」に乗り換えて戻ってこい。ここで待ってるからな。";
				link.l1 = "ああ、ただこの船の方がいいと思っただけだ…わかった、わかったよ。ここで待ってろ、すぐ戻るからな！";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "おう、来たな、相棒！どうだい、俺の自慢のやつは気に入ったか？";
			link.l1 = "見事なフリゲートだな、スティーブン！これを断る理由なんてねえよ…";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "いや、今は「フォーチュン号」があるじゃねえか、はは！さて、どうだったか話してみろよ。";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "すべてが完璧に運んだぜ。俺は誠実で信頼できる商人になりすますことに成功したんだ。書類をポルトベロに持っていき、 そこの港長を五分間うまく引きつけている間に、船団と軍艦隊が積み荷と会う日時と座標を自分用に書き換えたんだ。\n";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "ちょっとした問題があったんだ。手紙は使者によってポルトベロに送られていた。俺がそれを途中で奪って、 宛先に届けて返事まで受け取ったが、港の責任者に書類を持ってくるはずの奴じゃねえってバレちまった。だから、 戦いながら脱出する羽目になったぜ。だが、積荷を積んだ船と軍艦隊が会う日時と座標は突き止めたし、 返事もカラカスに届けたから、あとは生産物が俺たちを待ってるってわけだ！";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "ちょっと待て。今「船」って言ったか？";
			link.l1 = "ああ、シャーク！二人来るぜ！";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "ハハハ、そうだ、でっかい儲けになるぜ！さて、俺の野郎も火の洗礼を受ける準備はできてる。ただ、 まだ戦闘には参加したことがねえから、戦いはお前が率いてくれ。今のところは、俺もお前の艦隊に加わるぜ。";
			link.l1 = "俺がブレザレン・オブ・ザ・コーストの頭目、スティーブン・ドッドソン本人を指揮するってのか？しかも仕事で！";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "いいか、あんまり調子に乗るなよ。俺が自分の船で戦うのはこれが初めてだからだ。それとな、 拿捕した船のために自由な士官をちゃんと用意しとけよ。あいつらの船倉はパンパンになるし、 俺の仲間だけじゃ船を動かせねえからな……まあ、くだらねえ話はここまでだ。獲物が俺たちを待ってるぜ！";
			link.l1 = "その通りだ！俺は自分の船に行くぜ。";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "ああ、継いだんだな……じゃあ、艦隊が約束の日より早くそこに到着することを覚悟しねえとな。そしたら、全員まとめて戦う羽目になるぜ。";
			link.l1 = "なんでそう言うんだ？";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "お前も頭を使えよ。ポルトベロじゃ、積荷を積んだ船が必ずカラカスを出るって知ってるはずだぜ、 なぜならお前が返書を持って行ったからな。だが、お前が正体を明かしちまったからには、 向こうも俺たちがその船を拿捕するのを全力で阻止しようとするだろう。多分、あいつらの艦隊が先に着くはずだ。 俺ならそうする。だから、きつい戦いに備えるぞ。遅れて撤退なんてごめんだぜ。";
			link.l1 = "心配すんな。お前と俺は海の狼だぜ、こんなことでくたばるわけねえだろ！";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "お前の言う通りだ。さて、俺の化け物も火の洗礼を受ける準備はできてるぜ。だが、まだ戦闘には参加してねえから、 今回はお前が戦いを指揮しろ。その間、俺はお前の戦隊に加わるとしよう。\n";
			link.l1 = "俺が正義の島の海賊頭、スティーブン・ドドソン本人を指揮するってのか？こりゃ一大事だぜ！";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "話してる暇はねえ、 "+pchar.name+"！さあ、戦利品を取りに行くぜ！";
			link.l1 = "運が俺たちに味方するように！";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "悪魔が千匹もいるぜ！よくやったな、チャールズ！戦利品は最初に思ってたよりずっと豪華じゃねえか！この航海、 間違いなくやる価値があったな。";
				link.l1 = "俺もまったく同感だぜ、スティーブン！今日は間違いなく俺たちの日だな！";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "よくやったな、相棒。だが、正直言って獲物はだいぶ逃しちまったぜ。";
					link.l1 = "俺も同感だぜ、スティーブン。もっとやれるかもしれねえが、今あるものも悪くねえ！";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "くそっ！せっかくいい考えだったのによ…結局、この遠征の出費は利益より多くなっちまった。チャールズ、実際にお前に指揮を任せたのに、全部失いやがったな！ ";
					link.l1 = "何も言うな……俺だってくそ怒ってるんだぜ。どれだけの獲物を取り逃がしたことかよ……";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "そうだな、俺たち二人ともよくやったぜ。俺が策を考えて使者の情報を手に入れた、 そしてお前がその策を見事に実行した。獲物のために互角に戦ったのも事実だ。\nだからこそ、カリブの兄弟たちの掟どおりに分けようじゃねえか――等分にな！";
			link.l1 = "やってやるぜ！";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "さて、これからイスラ・テソロへ向かうぜ。船の修理もしなきゃならねえし、 新しい船での最初の成功をしっかり祝わねえとな。\n幸運を祈るぜ、友よ！俺の屋敷にはいつでも歓迎だぜ！";
			link.l1 = "俺たちの取引がこんなに儲かるとは嬉しいぜ。必ずそのうち会いに行くからな。幸運を祈るぜ！";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "勝手に全部独り占めしな。どうせ何も残っちゃいねえだろうがな。俺はこんな小物どもには興味ねえ。結局のところ、 この騒ぎにお前を巻き込んだのは俺だからな。";
			link.l1 = "ああ、俺も悪かったな……すまねえ、スティーブン。";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "謝るなよ、俺はまだお前に命を借りてるんだ、その恩は忘れねえぜ。さて、これからイスラ・テソロへ向かう。 船を修理して洗わなきゃな……まあ、洗うほどのもんでもねえがな……幸運を祈るぜ、相棒！俺の屋敷にはいつでも歓迎だぞ！";
			link.l1 = "まあ、何が起きてもおかしくねえし、負けることもあるさ。大事なのは俺たちが生きてるってことだ。 いつか必ず会いに行くぜ、友よ！幸運を祈る！";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}
