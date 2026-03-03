// диалоги персонажей по квесту Дороже золота
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
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
			link.l1 = "俺は行くべきだな……";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "シャルル・ド・モール船長！やっと見つけた！ ジャック・ディル・ド・パルケ公閣下があなたにお会いしたいとおっしゃっています！これは急ぎです！";
			link.l1 = "なぜ驚かないんだろうな？まあいい、閣下に私がすぐ参るとお伝えください。";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "俺の目が信じられねえ、まさかシャルル・ド・モールご本人とはな！こんな歓迎会はそうそう開かねえし、 あんたがこのつましい修道院に時間を割いてくれたこと、本当に嬉しいぜ。俺は運がいいな！これは乾杯に値するぜ！";
			link.l1 = "ごきげんよう、奥様。もし私の態度がご期待に添えなかったらお許しください――このような催しに出席するのは、実に久しぶりでございます。\n船上での礼儀作法といえば、命令への服従、清潔なスカーフ、そして毎朝の一杯の香り高いコーヒーくらいのものですわ。 ";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "なんて魅力的なの、船長。あなたにはまだパリの洗練が残っているわね。この荒波に揉まれた仮面の下に、 控えめな輝きが見えるもの。\n心配しないで、やっとお会いできて本当に嬉しいから、今のところは色々と許してあげるわ。\nこれから先、私たちの関係がどうなるか見ていきましょう。ワインはいかが？赤、それとも白？";
			link.l1 = "ラムの冗談を言うには絶好のタイミングだが、あいにく今はそんな気分じゃねえんだ。すまねえな。だが、 お前の可愛い手で注いでくれる酒なら、喜んで飲むぜ。";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "いいね。しかし、俺は譲らないぜ。ワインの好みで人となりが分かるもんだ。今夜はお前のことを全部知りたいんだよ。 だからもう一度聞く。赤か白、どっちだ？";
			link.l1 = "好きにしな。赤ワインを飲んでるんだな。俺も同じのをもらうぜ――お前のことも少し知りたいからな。";
			link.l1.go = "Julianna_3";
			link.l2 = "それなら、俺は白にするが、お前が選べ。どっちでもうまくいくだろう、そう思わねえか？";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "素晴らしい、じゃあ今度は俺の番か？これはブルゴーニュのピノ・ノワールだ。醸造家たちはこれを「いたずら娘」 と呼ぶんだぜ。扱いが難しくて、後味もなかなか手強いんだ。満足したか？";
			link.l1 = "ピノ・ノワールか、ふん。悪くねえな。頼りなくて謎めいてて、最初は渋い味だが、しばらく空気に触れさせれば驚くぜ。 色と香りが軽やかに踊る、通好みの一本だ。最初の印象に騙されるな、そうだろ？あなたの美しい瞳に乾杯です、旦那！";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "素晴らしい、じゃあ今度は俺の番か？ロワール渓谷直送の素晴らしいソーヴィニヨン・ブランがあるんだ。 かなり野性的で、舌の上で泡立つのが感じられるぜ。極めつけは……火薬の香りがほんのりとするんだ。俺たち、どこか共通点があるんじゃねえか。";
			link.l1 = "もっといいものを期待してたんだがな、たとえばリースリングとかさ。まあいい、 この夏と火薬の匂いがする安っぽい酒で乾杯しようじゃねえか。\n「ピピ・ド・シャ」と間違える奴もいるって聞いたことあるか？\nお前の笑顔に乾杯だ、このサファイアみたいに輝いてるぜ！";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "見事だわ、チャールズ！そう呼んでもいいかしら？あなたのこと、見誤っていなかったわ。別の日なら、 今夜の主役はあなたになっていたでしょうね。でも、残念ながら、船長様、今日は手強いライバルがいるのよ。 あちらでスキャンダルが起きそうなの、見えるかしら？\n";
			link.l1 = "怒鳴り声が聞こえるな。あの不愉快な旦那は誰だ、そして我らが最愛の総督を怒らせるようなことを何をしでかしたんだ？ ";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "この「不愉快な」旦那はアンジェラン・ド・シェヴース、 カウント・ド・レヴィ・ヴァンタデュールの認知されていない私生児だ。あなたは彼らの議論の話題を楽しんでいるわ。 ド・シェヴースは何年も私のご機嫌を取ろうとしてきて、ここまでついてきたの。 自分の父親の代わりになれると思ってね。正当な息子じゃないけれど、金も権力もあるのよ。頑固さも彼の特徴の一つで、 ある人々にとってはそれが知恵の代わりになるの。あなたが来る直前、彼とジャックが例の明白な話題で口論を始めたの。 閣下はいつも感動的なほど私を守ってくれるのよ、ぜひ見てほしいわ！さあ、観察して、 今回はどうなるか見届けましょう。";
			link.l1 = "空気がきな臭いな……どうしてこんな素晴らしい夜にも、必ず裏があるんだよ……";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "「なんだって、チャールズ？」";
			link.l1 = "忘れてくれ。しつこい友人を紹介してくれよ、それからどうするか決めようじゃねえか…";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "旦那、私の大切なお客様をご紹介させていただきます――このお方こそ、かの有名なシャルル・ド・モール船長ご本人でございます！ このような著名な方が当館にお越しくださることは滅多にございません。";
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "「チャールズ、俺はこの流れが気に入らねえ！ジャックは俺の言い分なんか耳に入っちゃいねえし、 アンジェランはきっと何か企んでる。こいつらの争いには目的があったんだ、だからお前の助けが必要なんだ！」";
			link.l1 = "申し訳ないが、話がよく分からない……俺に一体何ができるっていうんだ？あいつはもう俺との決闘を断ったじゃねえか……";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "船長、俺をがっかりさせないでくれよ。さっきまで会話の名人だったのに、 今じゃ剣で突けるものと突けないものしか見えてねえじゃねえか。もっと頭を柔らかくしろよ！ アンジェランの企みをぶち壊そうぜ。あいつは哀れなジャックに一騎打ちを挑みたいらしいが、それじゃつまらねえ！ ここには本気の賭けに乗れる旦那たちが何人もいるし、あんたの幸運はすでに伝説だぜ！ 今夜はカードの女神があんたに微笑むかもな？\n";
			link.l1 = "それがどうやってデ・シェヴィウスが我らの可愛い総督と戦うのを防ぐのか、俺にはよく分からねえが、乗ったぜ、 お嬢さん。あいつの憎たらしい笑顔を消せるなら、何だってやるさ。";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "素晴らしいわ、さあテーブルに行って何か食べてきて。今夜は長くなるから。準備ができたらホールで私に会いに来てね、 これにはもっと広い場所が必要だもの。その間、私はちょっとした見世物をやって、 他の人たちから眼鏡や大勝負のゲームを引き出してみせるわ。退屈で溺れそうなレディがここにいるって、 あの雄鶏どもに気づかせるために大声を上げるかもしれないわね。お願いだから邪魔しないで、 今夜私たちが同じチームだって誰にも知られてはいけないの。あとで会いましょう、私の船長！";
			link.l1 = "「お好きなように、奥様、お好きなように……」";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "さて、祝ってくれ、うまくいったぜ！ちょっとした誇りと偏見、そしてほら完成だ！退屈そうな顔をしろ、見られてるぞ。 あたしに興味があるんじゃなくて、酒に興味があると思わせておけ\nトーナメントがもうすぐ始まる、賭け金は高いし、やり直しも再戦もない。どういうわけか、 あんたはこういうのに慣れてる気がする。きっと乗り越えられるさ。覚えておけ、アンジェランは絶対何か企んでる、 ジャックの友人に手を出すつもりだが、あんたの登場は計算外だ。あたしの切り札になってくれ、あいつの自信満々 で嫌味な面を見るのは縁起が悪いからな。参加者は八人、でもあんたが決勝まであいつと当たらないようにしておいた\nおっと！最初の対戦相手だ！大佐であり、砦の司令官。海と陸の対決――軍人経験者にはふさわしい勝負だな！拍手！";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "素晴らしいぞ、シャルル、本当に見事だった。アンジェランとジャックがもうすぐ対決するところだ。残念ながら、 連中は話を聞かずにトーナメントを一週間延期しなかった。もし延期してくれれば、本当に豪華な顔ぶれを集めて、 パリまで噂が届くほどの宴を開けたのに！まあ、次の機会に期待しよう。 どうやら次の対戦相手は君の幸運にふさわしい強敵、まさに海の狼、モレノ船長だ！\n船長たち、どうぞ！";
				link.l1 = "";
			}
			else
			{
				dialog.text = "残念だが、運は尽きたな、船長。申し訳ないが、あんたの勝負はここまでだ。 アンジェランはもうジャックと勝負しているから、俺は行くぜ。さらばだ。";
				link.l1 = "……光栄でした……奥様。";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "おめでとうございます、船長！まさに当然の勝利ですな。さて、決勝であなたと戦う相手はまだ分かりませんが……少し脇に寄りましょう。声を落として、あのテーブルを見てください。ほら、あいつだ！ アンジェランの企みが見えてきたぞ！もう可愛いジャックから金を巻き上げたのに、まだテーブルから離れさせない。 俺が通りかかった時、あの哀れな奴は船と積荷丸ごとを賭けて書類までギャンブルしていた。残念ながら、 今夜は運が味方していないようだ。いや、誰かが運に味方するなと命じたのかもしれんがな。";
				link.l1 = "「ド・シヴィアスがイカサマしてると思うか？」";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "残念だが、運が尽きたな、船長。申し訳ないが、これでお前の勝負は終わりだ。 アンジェランはすでにジャックと勝負しているから、俺は行くぜ。さらばだ。";
				link.l1 = "……光栄でした……奥様。";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "奴さんがその気になりゃ絶対できただろうが、証拠はねえ。うちの旦那総督はカードが得意だが、相手も負けちゃいねえ。 アンジェランは自分のフリゲート艦を賭けても眉一つ動かさなかったんだぜ、想像してみろよ。 これがパリやリヨンでの決闘だったら、伝説になってたさ、シャルル！\nとはいえ、今夜はただ運がいいだけかもしれねえ。奴らに近づいて、自分の目で確かめようぜ。";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "「シャルル、抱きとめてくれ、じゃないと倒れそう……いや、倒れなくてもいいか――こいつら、俺が気絶しても気づきもしねえだろう。\n見たか？ジャック、この馬鹿野郎め！まるで子供じゃねえか、ジーザス！間抜けなガキだ！」";
			link.l1 = "マルキーズ、私には話がよく分かりませんわ。\nあのテーブルで今何が起きているのです？\n彼らは何を賭けているのですか？";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "俺に賭けたんだ、シャルル。俺たちの可愛い、お人好しのジャックは俺に賭けたんだ。 アンジェランは唯一の弱点を見抜いて、まさにその瞬間を突いたんだ。";
			link.l1 = "ちくしょう！だが俺は次の試合に出るんだ、あいつのクソ船を取り返せるかもしれねえのに！なんでだよ？";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "アンジェランはよく考え、すべてを計画していたんだ。俺の話を聞け、時間があまりない。同じことをあいつにやるんだ。 奴からすべてを奪え、金も船も全部取れ、挑発しろ！評判でも名誉でも情熱でも、何でもいい、奴の頭を熱くさせろ！ 今夜のやり方を見ただろう。奴を追い詰めて、賭けに出させるんだ\n頼む、シャルル！俺は何だってやる覚悟だ、だが、あんな形で奴のもとへは行けない！絶対に！ ヴァンタデュール伯爵でさえ、正々堂々とカードで勝った相手には逆らえない、 俺を助けるために指一本動かしやしないさ。分かるだろ、貴族にとってカードは血のように神聖なんだ、くそったれめ！ お前だけが最後の、唯一の希望なんだ、シャルル！";
			link.l1 = "まだ総督を埋めるのは早いですわ、旦那様。もしかしたら、彼は自分の船を取り戻せるかもしれませんわよ？ 運命の女神は気まぐれな……女性ですもの。";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "まだ分かってねえのか？あのテーブルに運なんて関係ねえんだよ！アンジェラン・ド・シェヴーが全部仕切ってるんだ。 奴は俺を手に入れつつ、親父を巻き込まない方法を見つけやがった。どれだけ前から計画してたか分からねえが、 今やほとんど勝ちかけてる。奴がゲームを操ってるんだ、俺たちが打ち破るチャンスは一度きりだ。ほら、 これを持ってけ！俺が陽動する、その間に一、二分稼げるはずだ。うまく使えよ。";
			link.l1 = "マルキーズ……誰か、助けてください！マダムの具合が悪いんです！早く！";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("You have received amulet 'Turtle'");
			Log_Info("You have received amulet 'Joker'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "いや、いや、大丈夫です……ここはちょっと息苦しいですね……申し訳ありません、皆さん。少し外の空気を吸いに出ますので、しばらくお席を外します。 どうぞ私抜きで続けてください。";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "今はこの場でもサン・ピエールでもないが、心当たりはある。約束するぜ、アンジェラン、これはきっと立派な絵になる……";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "アンジェラン、お前は本当に手に負えないやつだな！負け方も覚えろよ！これはただの遊びだし、 何もかも予想できるわけじゃねえんだ。ワインを飲み干して、服を着ろ――ルールは変わらねえ、負けたやつはこの居心地のいい宴から出ていくんだぜ。";
			link.l1 = "マルキーズ、お待ちください……";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "いい加減にしなさい、諸君！すぐにやめなさい！\n皆さん、長い夜でとても疲れているのですから、残念ですがお客様方にはお引き取り願わねばなりません。\n議論は明日、名誉ある紳士らしく続けていただいて結構です――もし気が変わらなければ、ですが。\nただし、ここで武器を抜くことは絶対に許しません、よろしいですね？";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "チャールズ、申し訳ないが、君にも席を外してもらわねばならない。\n二階に上がって、自分の部屋を取ってくれ。\nあとは私がすべて手配する。\n君がしてくれたことには感謝してもしきれないが、少し一人の時間が必要なんだ。 それに君もきっとひどく疲れているだろう。";
			link.l1 = "そんなに悪くはありませんわ、奥様。でも、ベッドを断る理由もありません。 この気軽な宴のほうが大艦隊との戦より堪えましたわ。これがあなたにも楽なことではなかったのは分かっています、 マルキーズ。どうぞお休みになって、心配なさらないでくださいませ。あなたに借りはありませんわ。 今の私に必要なのは、ただ眠ることだけですの。";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "昼までには必ず起こさせるぜ。もう夜明けだから、これ以上「おやすみ」とは言えねえな。ゆっくり休んでくれ。";
			link.l1 = "あなたもですわ、マルキーズ。";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "やっと来たな、チャールズ。正直に言うと、俺は全然眠れなかったが、お前はよく休めたみたいだな。よく眠れたか？ 朝飯はもうすぐ来るぞ。";
			link.l1 = "あなたのご親切は伝説的ですわ、奥様。でも、あいにく楽しむ時間がございませんの。閣下やド・シェヴィウスの立会人、 それに私が手に入れた船――すべてが私を待っておりますの。";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "お前は船だけじゃなく、他のものも手に入れたんだ。もう一つ聞きたいことがあるんだ、チャールズ……";
			link.l1 = "私はジャックでもアンジェランでもありません、侯爵夫人。女性のご機嫌を取るために賭け事などしません。 あなたは私に何の借りもありません。";
			link.l1.go = "Julianna_41";
			link.l2 = "あなたは私の庇護下にあります、マルキーズ。ジャックもアンジェランも二度とあなたを悩ませはしません、 私が約束します。";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "お前はとんでもなく高潔か、あるいは恋をしているんだな、チャールズ。しかも相手は私じゃない。でも、 改めて心から感謝しているわ。もし私にできることがあれば、何でも言ってちょうだい。";
			link.l1 = "ジュリアンヌ、時間がなくなってきていて、これから俺は最も厄介な仕事に直面するんだ。 ド・シェヴィウスはクズ野郎で、正々堂々とした決闘ですら、昨夜俺たちが見たような結末になることもある。 すべてが片付いたら、また改めて話そう。静かな夜を過ごせる機会をくれて感謝しているし、 また君に会えるのを楽しみにしているよ。";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "心から感謝しています、チャールズ……あなたの戦利品になることも、私にとっては一種の勝利なのですわ。\nこの話の続きを、もっと……二人きりの場所でしませんこと？";
			link.l1 = "ジュリアンヌ、時間がなくなってきていて、これから俺は一番厄介な仕事に立ち向かわなきゃならない。 ド・シェヴィウスはクズ野郎だし、正々堂々の決闘だって、昨夜見たみたいにすぐに卑怯な結末になるかもしれねえ。 すべてが終わったらまた話そう。安らかに眠る機会をくれてありがとう。また君に会えるのを楽しみにしてるぜ。";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "それでは、これ以上お引き止めしません、船長。ですが、アンジェランは危険な男だということを忘れないでください。 戦闘の腕前は分かりませんが、いくつもの戦争に参加し、ロクルワの戦いでも戦ったそうです。それに、 彼がピストルで何度か決闘に勝ったという話も聞きました。何よりも、あなた自身が気づいた通り、 彼はとても狡猾な人物です。どうかご注意ください。そして、あとで必ず私のところにいらしてください！";
			link.l1 = "ご心配いただき恐縮ですわ、マルキーズ。ですが、信じてくださいませ、ド・シェヴィウスごとき、 私の前に立ちはだかった最初のろくでなしではありませんの。私なら何とかなりますわ。\nさて、そろそろ閣下のもとへ行って、決闘の件についてお話ししなくてはなりませんわね。";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "ご武運を、俺の船長！それとジャックに、俺の家の扉には絶対近寄るなって伝えてくれよ。";
			link.l1 = "約束するぜ。またな、マルキーズ！";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "船長、来てくれたんだな、助かったぜ！どうだった？血は出てねえか！？";
			link.l1 = "これは俺の血じゃねえ……少なくとも全部じゃねえよ。マルキーズ、ド・シェヴィウスはどこだ？";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "俺もまさに同じことを聞こうと思ってたんだが――お前、あいつを倒さなかったのか？何があった？なんで町の衛兵の半分が外にいるんだ？";
			link.l1 = "総督にはお前が危険かもしれないと伝えた。ド・シェヴィウスは負傷して逃げやがって、 手下どもを俺たちにけしかけてきたんだ。まるで虐殺だったぜ。\nもっとも、こんな話はお前の美しい耳にはふさわしくねえな。もう終わった。お前はあいつからも、俺たちの“可愛い”ジャックからも解放されたんだ。";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "これは非常にまずいな、チャールズ。アンジェラン・ド・シェヴューみたいな敵は、 チャンスがあればきっちり始末しておくべきだったんだ。あいつのことは長年知っているが、 絶対に許すような男じゃねえ。遅かれ早かれ、必ず復讐の手を伸ばしてくるだろう。\nだが、お前のそのだらしない姿勢は気に入らねえな、傷の手当てはちゃんとしたのか？";
			link.l1 = "ただのかすり傷さ、もっとひどいこともあったぜ。ちょっと痛むだけだ。それより、心配してくれてありがとうよ、奥様。 でも、俺はもう行かなくちゃ…";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "船長、あなたは私のために賭けに出て、自分の船や財産を危険にさらしたわ。取引でも私のために戦い、 命や立場まで賭けてくれたのよ。せめて私にできることは、あなたの傷の手当てをして、 安心して休める場所を用意することだけ。\nもうこれ以上は聞きたくないわ。さあ、私の手を取って上へ来て。あなたのお部屋はもう用意してあるの。";
			link.l1 = "お申し出をお受けします、奥様、ありがとうございます。しかし、ご迷惑はおかけしたくありません。 自分で二階へ上がります。";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "マルキーズ、あなたは私の守護天使ですわ。今や借りがあるのは私の方ですわね。";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "チャールズ、お前は騎士道の鑑だぜ！神に誓って、そんな調子でいられたら俺の頭がおかしくなっちまう！\nよしよし、我が騎士よ、デニーズをお前のもとに行かせるぜ。あいつがちゃんと医者らしく傷の手当てをしてくれるさ。";
			link.l1 = "ありがとうございます、マルキーズ様。もし私の心がすでに他の人に奪われていなければ、喜んでお相手したでしょうに。 ですが、ああ残念！おやすみなさい！";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "この場合は、すぐに私の言うことを聞いてもらうわ。手を握って、私の指示に従いなさい。デニーズ！綿と熱いワイン、 それから何か食べ物を上に持ってきて！\nさあ、行きましょう、私の船長。今回は絶対に逆らわないでくださいね！";
			link.l1 = "おっしゃる通りです、マルキーズ、私はすべてお任せいたしますわ。";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "おはよう、チャールズ。お前のその「かすり傷」はどうだ？";
				link.l1 = "あなたのおかげで生まれ変わった気分です。心から感謝します、Julianna。";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "おはよう、私の英雄。あなたのその「かすり傷」はどうかしら？";
				link.l1 = "ご心配いただきありがとうございます、奥様、私はまったく問題ありません。 もしあなたのデニスが私の船医として働いてくれるなら、財産を払ってもいいくらいです。彼女はまさに奇跡です！";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "それを手配するのは簡単じゃなさそうだ。しかし、俺はよほどの理由がなければあんたを起こすなんてしねえよ。 信じてくれ、あんたの眠りはしっかり守ってたぜ、だが下にいるこの男がしつこくてな。自分はあんたの船員の一人で、 急用だと言ってるんだ。";
			link.l1 = "俺の船員たちか？起こしてくれて正解だぜ、侯爵夫人！すぐに出発する。";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "状況が違えばそうしたいところですが、船長、今回は延期しなければなりません。 下の階であまり教養のない旦那があなたを待っています。彼は自分があなたの船員の一人だと言っており、 急ぎの用事だそうです。";
			link.l1 = "戻ったらまた取り掛かります、マダム。これはまたスペイン人が包囲しているという話ではないといいのですが。";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "「チャールズ、戻ったのか！お前の部下はどんな知らせを持ってきたんだ？別れの挨拶もなかったじゃねえか！」";
			link.l1 = "申し訳ありません、侯爵夫人。ド・シェヴィウスがまた汚い手を使いました。奴は私の船を盗み、今夜出航しました。 私の信頼する士官の一人がその船に乗っていて、あの野郎の手に彼女を渡すわけにはいきません。";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "彼女だと？お前の船に女の士官がいるのか？それは俺の知ってる船乗りの常識に反してるぜ。 何でまだ生きてると思うんだ？";
			link.l1 = "願うしかないんだ。ジュリアナ、今の俺には希望しか残っていない。 アンジェラン・ド・シヴーについてもっと知る必要がある。絶対に奴がどこへ行ったのか突き止めなきゃならない！ 彼女を必ず取り戻すんだ！";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "なるほど！本当に恋しているのね、私の騎士！そんな忠誠と愛情があれば、 私も迷わず命の半分を差し出してもいいくらいですわ！";
			link.l1 = "俺はまだ誓いを立てちゃいねえが、この女は俺にとってとても大切なんだ、侯爵夫人。";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "これは嫉妬しちゃうわね。聞いて、シャルル、私、あなたに嫉妬しちゃいそうよ！でも、 本当の愛の声に耳を塞げる女なんていないでしょ？それに、あなたは私を救ってくれたのよ、私の騎士様。もちろん、 あなたを助けるわ。何でも聞いてちょうだい。";
			link.l1 = "ありがとうございます。あなたはデ・シェヴィウスをかなり前から知っているんだな。あれだけの騒ぎの後、 彼は父親の怒りが収まるまでどこへ身を隠すと思う？";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "ブランチで誘ったらどうだ？この…娘のことは二日も考えていないんだろう、もう一日ぐらい待たせてもいいじゃねえか？";
			link.l1 = "マルキーズ、私があなたの目にどう映るかは分かっておりますが、過ぎたことはもう戻せません。 誓いを立ててはいませんが、私の心は彼女のものです。どうかご理解いただき、お力添えをお願い申し上げます。";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "さあ、チャールズ！高級娼婦の前で恋の話で自分を弁護するなんてか？こんなに笑ったのは久しぶりだよ！ お前は本当にすごい奴だな！安心しろ、この屋敷で起きたことはこの屋敷だけの秘密だ。借りがあることは覚えている。 何でも聞いてくれ。";
			link.l1 = "ありがとうございます。あなたはデ・シェヴィウスのことをかなり前から知っているんだな。あれだけの騒ぎの後、 彼は父親の怒りが収まるまでどこに身を隠すと思う？";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "正直に言えば、アンジェラン・ド・シェヴューを招くのはあまり気が進まないことだが、政治的には非常に有益なんだ。 彼はどこでも歓迎される客人で、フランスと同盟している国々でも同じだ。だが、近くで彼に必ず手を貸し、 匿ってくれる男を一人だけ知っている。フランソワ・ド・リヨン、我々のグアドループ植民地の総督だ。 彼はルヴィ・ヴァンタデュール伯爵の古い知り合いで、このろくでなしには昔から甘いところがあるんだ。";
			link.l1 = "グアドループか！これ以上の手がかりは望めねえぜ！今晩出航すりゃ、奴らの一日後を追うだけだ。";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "待ってくれ、チャールズ、まだ他にもあるんだ。つい最近、お前宛ての手紙を受け取ったんだ。 決闘に関係していると思っていたが、今はもうそうとも言えない気がする。これだ。";
			link.l1 = "印章はないが、紙は高級だな。俺はこういうの、気に入らねえ……";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "さあ、チャールズ！じらさないでくれ、それはあいつからなのか？";
			link.l1 = "ああ、彼からのものだ。彼女は生きている！俺の船を奪う時に彼が彼女を捕まえたんだ。今、 彼は落ち着いた場所で会って話し合おうと提案してきている。お前の言った通り、グアドループ、バステールだ。";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "リヨン旦那は間違いなくルヴェ・ヴァンタデュールの息子をお前より選ぶだろう。 シェヴュー旦那はまたお前に罠を仕掛けてくるかもしれない！俺を守ったことで、とても強力な敵を作ってしまったな、 シャルル。力になりたいが、せめて気をつけてくれと願うことしかできないんだ。";
			link.l1 = "ジュリアンヌ、俺が新世界でやってこれたのは、いつも正面突破ばかり選んでいたからじゃねえ。 裏の仕事は得意じゃねえが、うまく立ち回るコツは知ってるんだ。";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "何か新しい知らせはあるか、船長？";
			link.l1 = "ああ、何もない……";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "おかえり、チャールズ！元気そうで何よりだ。何か新しい知らせはあるか？";
			link.l1 = "我々が知っていたド・シェヴィウスの腕前は、まったくもって甘かったようだ。あの野郎、俺の……士官を人質に取ってやがるんだ。身代金を集める猶予はたった二週間しかねえ。お前の助けなしじゃ、 とても無理だと思うんだ。";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "チャールズ、お前の恋はまるで風の花のようだな。だが、俺はお前に大きな借りがあるし、できる限り力になるぜ。 どうすればお役に立てる？";
			}
			else
			{
				dialog.text = "シャルル、私はすでにあなたがしてくれたことを決して忘れないと伝えましたわ。 できる限りお返ししたいと思っていますの。準備はできていますけれど、正直申しまして、 私がこの件でどのようにお役に立てるのか、まだよく分かりませんの。";
			}
			link.l1 = "どうぞ、おかけになって、ジュリアナ。ご覧のとおり、アンジェランの身代金は……君なんだ。しかも、正式な庇護じゃなくて、貨物室に縛られた捕虜として、という意味だよ。";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "言葉も出ない……しかし、お前の顔を見ると冗談じゃなさそうだな。あいつ、正気を失ったのか？";
			link.l1 = "むしろ、俺がやったとあいつは思い込んでるんだ。あいつは必死で、どんな一線でも平気で越えるほどだぜ。";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "それで、私に何を頼むつもりなの？誘拐されている間、叫ぶなって？\n船長、それはさすがに無茶なお願いじゃない？私はあなたに大きな借りがあるけど、 他人の恋人を救うために自分の命を名もなきろくでなしに差し出すなんて……\n騎士道精神に溢れているのはあなたの方よ。私は現実主義で、しかもとても打算的な女なの。";
			link.l1 = "申し訳ありませんが、奥様、まさにそれをお願いしているのです。荷物をまとめてください、出発します。 心からお詫びしますが、時間がありません。";
			link.l1.go = "Julianna_76";
			link.l2 = "マルキーズ、俺は俺を信じてくれた女を誘拐したりしねえ。\nそれに、これが俺たちのチャンスかもしれねえぜ。";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "お前は本当に驚かせてくれるわね、チャールズ。\n聞いた？今のがあなたへの最後の情けだったのよ、それも今砕け散ったわ。\n愛があろうとなかろうと、私を誘拐させたりしないわよ。\n衛兵！助けて！！！誰か！！！！";
			link.l1 = "俺はてっきり、俺たちは友達だと思ってたんだぜ。";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "これはひどすぎる！私の応接間を何に変えてしまったのだ！？これは一体どんな悪魔の所業だ？チャールズ、 しっかりしなさい！あなたは貴族ですわ、忌まわしい海賊なんかじゃありません！！";
			link.l1 = "もうすでにお前には謝っただろう。これ以上ややこしくするなって頼んだのに、聞かなかったじゃねえか。信じてくれ、 俺だってこんなことしたくねえんだ。でも他に道はねえ。あの女のためなら、俺はどんなことでもやるさ。";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "どんな女があんたみたいな騎士を選ぶんだ？あたしが自分で行くよ、手を出さないで！牛を盗むわけじゃないんだから、 もう少し品位を見せなよ！";
			link.l1 = "よし。ついてきな、奥方。俺の後ろにいろ、頭を下げてろ――もしかしたら撃ち始めるかもしれねえぞ。";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "一瞬、俺はお前のことを全く知らない男だと思っちまったぜ、チャールズ。その目つき……だが、これから何をするつもりなんだ？さっき言ってた「チャンス」ってのは何だ？";
			link.l1 = "なんであの野郎は俺を使ってお前に近づこうとするんだ？\nなんで欲しいものをただ奪わずに、わざわざあのカード勝負を仕組んだんだ？\nあいつは何を恐れてやがる？";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "何もないわ。残念だけど、その理由はつまらなくて単純なの。アンリ伯爵は今でも私に未練があるのよ。アンジェランは、 私の意志に反して何かすれば大きな危険を冒すことになるわ。ごめんなさい、シャルル、でもこれは行き止まりよ。 彼はすべてを否定して逃げ切るでしょう。誘拐犯であるあなたの言葉なんて誰も信じないし、 彼の父親はあなたを滅ぼすわ。";
			link.l1 = "くそっ！こんなことにならなきゃよかったのに……準備しろ、侯爵夫人、行かねばならん。あと、静かにしてくれよ。";
			link.l1.go = "Julianna_76";
			link.l2 = "だが、あの野郎には親父以外にも弱点があるはずだろ？完璧なんかじゃねえ、むしろ真逆だぜ！";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "これが……俺たちに役立つかどうかは分からねえ。アンジェランは地元の海賊男爵と何か取引があったんだ。ジャック・バラバンか？ ";
			link.l1 = "バルバゾンですよ、奥様。二人ともいい夫婦ですわ！でも、親切者ジャックは私のことを好いておりませんし、 確かな確証がない限りル・フランソワへの攻撃は仕掛けられませんの。";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "また率直すぎるぞ、私の騎士よ。モレノ船長を覚えているか？二人目の賭博の相手だろう？ きっとあいつはアンジェランのことでここに来たんだ。俺たちにとって価値ある何かを知っているに違いない。";
				link.l1 = "モレノ船長か、ははっ！ああ、もちろん知ってるさ。まだこの町にいるのか？どこで会えるんだ？";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "また率直すぎるわね、私の騎士さま。誰かは必ず何かを知っているものよ、 そして状況によっては口をつぐめない人もいるわ。この館では……私の教え子たちが色々と耳にしているの。\n一日時間をちょうだい。もっと調べてみせるわ、それか、あなたに協力できる人を見つけてあげる。";
				link.l1 = "マルキーズ、心配しているあなたも素敵だと思っていましたが、怒っているあなたはもっと魅力的です。 ありがとうございます、あなたのおかげで希望が湧いてきました！";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "ああ、彼はまだここにいるし、わざわざ探し回る手間はかけさせねえよ。明日の夕方にここへ来な、 モレノ船長がこの部屋で待ってるぜ。もっと力になれたらいいんだが、これ以上は無理なんだ、チャールズ。";
			link.l1 = "もう十分すぎますわ、マルキーズ。彼が味方についてくれれば、物事はずっと楽になりますわ。ありがとうございます。 では、また明日の晩に。";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "できれば別の状況でその言葉を君から聞きたかったよ、チャールズ。\n明日の晩に私のところへ来てくれ。\n君が必要としているものを用意できているといいんだが。";
			link.l1 = "改めてありがとう、ジュリアナ！では、明日の晩に。";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "おう、来たな、相棒！モレノ船長はもうお前を待ってるぜ。";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "チャールズ、何か見つけたと思うんだ。モレノ船長を覚えてるか？あの不運な夜にお前と勝負した奴だよな？";
				link.l1 = "ああ、まったく、なんて放浪者だ。で、あいつはどうなんだ？";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "俺は最初から知っていたんだぜ、バルトロメオ・デ・ラ・クエバ。だからこそ最初にお前を俺の宴に招いたのさ。 まるで夕食にハラペーニョを加えるようなものだった。 お前とその手下どもがこの島を数週間も嗅ぎ回っていることも知っている。 これはル・フランソワの海賊男爵やアンジェラン・ド・シエヴスと何か関係があるに違いない。俺の友人にすべて話せ、 そうすればお前の伝説的な名は内緒にしてやる。さもなくば、すでに扉の後ろで待機している衛兵を呼ぶぞ。 お前が来た時点で呼んでおいたからな。";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "あいつらだけじゃないぜ！アンジェランが俺に首飾りをくれたんだ、すげえ綺麗なやつさ！ でっかくて傷一つない真珠が並んでて、真ん中には南の夜みたいに黒いこの珠もあるんだ。だけど、 それは地元の宝石職人に注文したものだったんだよ！";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "奴があんな豪華な贈り物をくれたのは、俺を喜ばせるためだけじゃねえだろうな。とはいえ、 あの贈り物は礼儀の範囲で俺の機嫌を取るための最後の手段だったんだろう。アンジェランには爵位も土地もなく、 フリゲート艦ですら親父の気分次第でどうなるかわからねえ。権力や影響力は使ってるが、 自分の収入源は持ってねえんだ。もしかして、親父の施しを待つのにうんざりして、 自分の懐事情を立て直そうとしたのか？";
			link.l1 = "待ってください、奥様！カードゲームですよ！もし俺たちの推理が正しくて、 ド・シェヴィウスが最初から全部仕組んでいたのなら、 知事を本気で追い詰めるためには相当な賭け金が必要だったはずだ。親にそんな大金を頼めば、 余計な疑いを招くかもしれません。すでに私掠船から盗まれた財宝をさらに盗むのは、 静かで安全に金を手に入れる方法だ。誰にも気付かれない！";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "俺たちのために、シャルル！今回はアンジェランを逃がしちゃいけねえ。あいつが俺の上に立つのはもう我慢ならねえし、 あんたがそれを正すのを手伝いたいんだ。";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "負け犬の海賊と、ほとんど恋に落ちかけてる高級娼婦か。チャールズ、お前は最高のチームを手に入れたな！";
			link.l1 = "それでも、二人ともありがとう。本当に感謝している！さて、少し考えて作戦を練らないとな。";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "この屋敷には客人が望むものは何でも揃っている。準備は俺がしておく。準備ができたら合流してくれ、チャールズ。";
			link.l1 = "「かしこまりました、お嬢様。」";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "何もないが、町の誰かがあいつを探している。あの夜のあんたや他の客についても積極的に聞き回っているんだ。 今のところ何が起きているのかは分からないが、 あんたは自分が思っているよりも大きな何かに巻き込まれているのは間違いないぜ。 ";
			link.l1 = "もっと大きなこと？どういう意味だ、ジュリアンヌ？";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "アンジェラン……いや、ド・シェヴー旦那が素晴らしい真珠のネックレスを贈ってくれたの。真珠のひとつは夜のように黒かったわ。 私はただの作り物で、いい話がついているだけだと思っていたの。身につけたことは一度もないわ、 変な期待を持たせたくなかったから。でも、その美しさには本当に心を奪われるのよ。";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "どうするつもりだ、チャールズ？何が起きてるか分かってるのか？";
			link.l1 = "まだだが、これからやるつもりだ。デ・シェヴィウスは何か重大なことにどっぷり首を突っ込んでる。 これは俺のチャンスだ。奴の祖国は手出しできねえが、イギリス当局ならやるかもしれねえ。ジュリアンヌ、 お前を誘拐するなんてまっぴらごめんだ。";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "とても優しいわね、チャールズ。でも、あまり面白くないわ。";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "チャールズ、何か分かったのか？落ち着かない顔してるな……どうしたんだ？";
			link.l1 = "くそっ！状況が違っていればよかったのにな……荷物をまとめてくれ、マルキーズ。頼むから、騒ぎは起こさないでくれよ。";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "チャールズ、入ってくれ。バロネットはすでに来ていて、楽しく話していたところだ。 ちょうど君が最近の出来事に興味を持っていることを彼に話していたんだ。";
			link.l1 = "ジュリアンヌ、俺はそれが賢明だったかどうか自信がないんだ……";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "バロネット、どうやらあなたの部下がドアの後ろに何かを落としたようです！ もっと行儀よくするように注意していただけませんか？";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "ひどい！これからどうするんだ！？";
			link.l1 = "くそっ！状況が違えばよかったのに……荷物をまとめてくれ、マルキーズ。頼むから、騒ぎは起こさないでくれよ。";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "なんてこった！旦那方、俺の居間に何をしたんだ！？まるで中世の悪夢じゃねえか！こいつらは誰だ？ それに衛兵はどこに行ったんだ？";
			link.l1 = "大丈夫か、ジュリアンヌ？よし。衛兵どもはせっかく手に入れた賄賂を酒場で使ってるだろうな。バロネット、 祝辞を述べさせてもらうぜ――お前はグッドマン・ジャックをかなり怒らせることに成功した。こんな雑で準備不足な暗殺未遂は、 あいつのやり方じゃねえよ。";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "おもしろい話の途中で悪いが、誰も怪我していないなら、書斎へ移動しようじゃないか。 こんな光景はご婦人にはとても見せられない……血がついていないのは天井だけだぞ！\n";
			link.l1 = "それでは、マルキーズ、上の階へどうぞ。少し横になって、この血の惨状から離れた方がよろしいですわ。 コートニー準男爵と私はこの件について話し合います。\n続けてもよろしいですか？";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "チャールズ、俺たちに作戦を話す準備はできてるか？";
			link.l1 = "ほとんど合ってる。教えてくれ、ド・シヴィアスは几帳面な奴か？帳簿や航海日誌をきちんと整理してるのか？";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "アンジェランは財政のことになると、まさに先延ばしの権化だぜ！ 俺の知ってるどんな銀行家よりも書類にサインしてるからな。まあ、あいつは子供の頃からそうだったんだろうよ、 父親が誰かも分からず、路上で貧乏暮らしをしてたんだからな。";
			link.l1 = "素晴らしい！さて、今度は奴の日誌と帳簿が必要だ！それがイギリス人への確かな証拠になる。 どうやって手に入れるか考えねばならねえ！あの船を手に入れた時にこれを知っていればよかったのにな……はあ。";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "待てよ、チャールズ、これまでのことがあったのに、俺がデ・シェヴィアスに家畜みたいに売られるなんて、 本気で思ってるのか？";
			link.l1 = "心配するな、ジュリアンヌ、ほんの数日で済むさ。約束する、中国の高価な花瓶みたいに大事に扱ってくれるぜ。 もし違ってたら教えてくれよ、でもデ・シェヴィウスは交換の場には絶対に姿を見せないんだろう？";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "俺は確信してるぜ。アンジェランはフランソワ・ド・リヨンの庇護の下で待ち構えていて、 決してお前に公海で会おうとはしねえだろう。だが、この俺の拿捕については……";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "チャールズ、邪魔して悪いが、この件について俺の意見を聞くのを忘れてないか？何週間もあのきしむ棺桶の中に……お前は俺に何を求めてるのか分かってるのか！？確かにお前はあの……娘に執着してるみたいだが、俺はお前の船員じゃねえぞ！悪いが、どうもこれは本気の恋物語には聞こえねえな。";
				link.l1 = "申し訳ありませんが、マルキーズ、どうしても譲れません。彼女を失うわけにはいかないのです。";
				link.l1.go = "Julianna_127";
				link.l2 = "誰だって間違いは犯すさ、ジュリアナ。お前こそ一番よく分かってるはずだろう。俺に力を貸してくれ。";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "チャールズ、邪魔して悪いけど、この件について私の意見を聞き忘れていない？何週間もあのきしむ棺桶の中に……あなた、私に何を頼んでいるのか分かってるの！？あなたの気持ちは騎士道物語にふさわしいけれど、 私はただの普通の娼婦よ。あなたのことは尊敬しているし、力になりたい。でも、何事にも限度があるわ！";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "分かるわ、Charles。私、本当の純愛を信じたいけれど、この世にそんなものは存在しないのでしょうね。";
				link.l1 = "ありがとうございます、侯爵夫人。今度こそ必ずすべてを正します。この出来事から多くを学びましたし、 自分のしたことに対してあまりにも大きな代償を払わずに済むよう祈っています。";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "覚悟を決めたのね、私はずっとあなたを支えてきたけど、もう限界よ。すべてを犠牲にしてまで、 私の寝室で既に捨てたはずの愛のために生きるなんて。\nとても感動的だわ、シャルル。でも私はもうそんなに若くも、世間知らずでもないのよ。";
				link.l1 = "申し訳ありませんが、マルキーズ、どうしても譲れません。彼女を失うわけにはいかないのです。";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "さて、船長、好きにしなさい。俺は抵抗しねえが、これは本意じゃねえってことは覚えておけよ。";
			link.l1 = "俺のことは好きに思えばいい、ジュリアナ。それだけのことはしてきたさ。だが、どんな犠牲を払っても、 あいつを取り戻すつもりだ\nジュリアナ、聞いてくれ。俺が何を頼んでいるか分かってる。すべてを捨てて、 他人に怪しい賭けに巻き込まれることになる。でも今、この瞬間、お前だけが俺の唯一の希望なんだ！ お前の助けが必要だ、そして死ぬまでその借りは忘れない！";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "承知した、船長。結局のところ、アンジェランは完全に始末しなければならん。俺も手を貸すが、教えてくれ、 どうやって奴の船から俺を救い出すつもりなんだ？";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "待って。俺の真珠のネックレスを持っていけよ、イギリス人は黒真珠を探してるんだろ？これがあれば、 あいつらもお前の話を聞くだろうさ。次はどうする？";
			link.l1 = "次に、俺は調査官を乗せてグアドループへ向かうぜ。お前が乗って戻ってきたとき、 デ・シェヴィウスのフリゲートを正式に捜索する。マーキュリー号の件は我々 の同盟者を巻き込んだ重大な事件だったから、デ・リヨンも認めざるを得ねえだろう！";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "奴は自分の部下が俺を捕虜から救い出したと皆に吹聴するだろう。\nそれと覚えておけ、船長、俺が何を話すかはまだ決めていないからな。";
				link.l1 = "何も言わなくても構いませんよ、マルキーズ。信じてください、俺があんたを引きずり出して、 アンジェランにすべてのツケを払わせてやる。";
			}
			else
			{
				dialog.text = "私は見知らぬ者たちに自宅からさらわれて、アンジェランの船に乗せられたと伝えるつもりだ。\nまるで彼が傭兵に金を払って私を誘拐させたように見えるだろう。";
				link.l1 = "アンジェランの棺にもう一本釘を打ちましたな、侯爵夫人。";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "朝まで待ってちょうだい、袋に詰めて運ぶ気がないならね。それと、何人か手伝いの者を寄越してくれる？ このあたしみたいな身分の女が、何の快適さもなく旅なんてできないわ。\nシャルル、あなたはあたしを救ってくれた、だから今度はあたしが力になるわ。それから、 このかけがえのない黒真珠を受け取って。あなたへの贈り物よ。うまくいったら、これでおあいこね。";
				link.l1 = "おっしゃる通りです、マルキーズ。お二人ともご武運を！終わったらまたここで会いましょう。";
			}
			else
			{
				dialog.text = "夜明けまでには出発できるぜ。俺は貨物室でガタガタするつもりはねえからな、ちゃんとした部屋か何かを用意しとけよ。 チャールズ、これを持っていけ。これは貴重な黒真珠だ。この場所よりも価値があるのは分かってるが、 金じゃ測れねえものもあるんだ。お前の役に立てばいいがな。神のご加護を！";
				link.l1 = "お二人とも、ご武運を！終わったらまたここで会おう。";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "おめでとうございます、船長。あなたの計画は成功しましたね。なんて大きな騒動を引き起こしたんだ！ イギリス人はアンジェランとその船、そして中身すべてを奪いましたが、私だけは除かれました。";
				link.l1 = "ウィリアム旦那は別れの挨拶にも来なかった。謝ると約束していたのに。";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "チャールズ、やったぞ！もうすぐお前は釈放される！\nだが、できるだけ早く島を出なきゃならねえ。総督はアンジェランの最近の逮捕にひどく怒ってるんだ。";
				link.l1 = "会えて嬉しいよ、Julianne。元気だったか？取引はどうだった？彼女は無事か？";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "あいつはそんな暇じゃなかったんだろうな。今の我々の総督みたいにな。あんたのことを思い出す前に、 この町を出たほうがいいぜ。総督はアンリの息子を可愛がってたが、イギリスの新聞に完全に追い詰められちまった。 総督がその鬱憤を全部あんたにぶつけると決めるまで待つ気はねえな。";
			link.l1 = "まあ、いいだろう。それに、彼女はマルティニークで俺を待ってるんだ。\n交換はどうだった？彼女は無事か？";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "申し訳ないが、そのことについて話したくないんだ。代わりに彼女に聞いてくれ。では、船長。俺は自分で戻るよ。 しばらく海から離れて休みたいんだ――フランソワは、退屈なイギリスの役人に邪魔されていなければ、なかなか良い主人だからな。";
			link.l1 = "このたびは本当に申し訳ございません、マダム。いずれにせよ、ご協力いただきありがとうございます。新しい……お友達ができたと聞いて、嬉しく思いますわ。";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "チャールズ、お前も約束を守ってくれて礼を言う。\nバルトロメオはサン・ピエールの俺の家にいるから探してくれ。\nさらばだ。また会おう。";
			link.l1 = "さらばだ、ジュリアンヌ。ご武運を。";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "俺はあの女を見てねえが、バルトロメオは無事に生け捕りにしたんだ。あのイギリス野郎はデ・シェヴィウスを逮捕して、 地元の総督の目の前で奴の財産まで押収した――総督は一言も言わなかったぜ！奇跡みてえな話だ！";
			link.l1 = "思ったよりも、この逮捕の裏事情を考えれば驚くほど順調に進んだな。まあ、後でしっぺ返しが来るかもしれねえが、 どうでもいい！とにかくすぐにマルティニークへ行かねえと、できるだけ早く彼女に会わなきゃならねえ！\n";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "きっと二人は話したいことが山ほどあるんだろうね。\nああ、シャルル、あんたみたいに目に情熱を宿した男がそばにいてくれたらなあ。\nさあ、急ごう。熱い風呂と清潔なシーツが恋しくてたまらないんだ。\nバルトロメオがサン・ピエールの私の家で待ってるはずさ。";
			link.l1 = "ああ、海の旅のロマンなんて大げさなものさ。マルキーズ、私の船室をお使いください、せめてもの礼です。さあ、 どうぞ。";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "あなたはもう私のためにできる限りのことをしてくれたわ、チャールズ。皮肉屋だった私に、 もう一度信じる心を与えてくれたの。";
			link.l1 = "「あたしもだよ、ジュリアンヌ。あたしもさ。」";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "「チャールズ、来てくれて本当に嬉しいわ！あなたのあのご婦人はどうしてるの？お元気かしら？」";
				link.l1 = "すべてうまくいっているのは、君のおかげだ、ジュリアンヌ。もう一度君に伝えたかったんだ。 君は本当に素晴らしい女性だし、その勇気と機転には一生頭が上がらないよ。";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "チャールズ、来てくれて本当に嬉しいわ！あなたのあのご婦人はどうしているの？お元気かしら？";
				link.l1 = "すべてうまくいったのは、君のおかげだ、ジュリアンヌ。もう一度伝えたかったんだ。君は本当に素晴らしい女性だよ。 君の勇気と機転には一生感謝してもしきれない。";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "もしかすると、借りがあるのは俺の方かもしれないな。何しろ、あんたはあのしつこい客二人から俺を救ってくれたんだ。 まだ恩返しが済んでない気がする。何でも言ってくれ、チャールズ。";
			link.l1 = "その場合、少しお願いがございます、お嬢様。お互い様にするために、あなたにしていただきたいことがございます。";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "俺はちゃんと聞いてるぜ、船長。何の用だ？";
			link.l1 = "人は間違いを犯すものだが、それで世界が悪くなるわけじゃない。\nそのことを忘れずに、幸せになってくれ、ジュリアンヌ。\n君は幸せになる価値があるんだ。";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "私……頑張ってみるわ、チャールズ。ありがとう。時々、友達として私に会いに来てくれる？ あなたはいつでも私の家に歓迎するわ！";
			link.l1 = "感謝いたしますわ、侯爵夫人。ごきげんよう、そして私に約束したことをお忘れなく。";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "それでも、どうやらそこまで驚くべきことではなかったようだな……だが、君にとって良い結末になって本当に嬉しいよ。君は何も借りていないさ。君がしてくれたことに、 どれだけ感謝しても足りない！陸に上がったときはいつでも会いに来てくれ。友人として、いつでも俺の家に歓迎するぜ！ ";
			link.l1 = "ありがとうございます、マルキーズ様。ご多幸をお祈りいたします。ごきげんよう！";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "チャールズ、友よ、お前は本当に無礼だな――滅多に会いに来ないじゃねえか！寂しかったんだぜ、わかってるか？ワインでもどうだ？ お前の冒険話を直に聞きたくてたまらねえんだ！それに、お前の有名な幸運も試してみたいしな！";
			link.l1 = "マルキーズ、ただご挨拶をして、あなたがご無事かどうか確かめたかったのです。";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "おう、いたな、相棒！また会えて嬉しいぜ！";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "さて、あんたが俺の友人にした仕打ちを見れば、もう選択肢はねえな、旦那。挑戦、受けてやるぜ。時間と場所は？";
			link.l1 = "今すぐだ。召使いたちを呼んで、ろうそくを持ってこさせろ、こんな薄暗い雰囲気じゃ駄目だ。 この場所は昼間のように明るくしなければならん！";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "旦那、頼むから、あまり気にしないでくれ。アンジェランは確かに嫌な奴だが、お前が皮肉を言うことはない。 ここは俺に任せてくれ。";
			link.l1 = "本当にいいんですか、閣下？あいつはうちの四等航海士が一週間陸に上がった後みたいに酔っ払ってますが、 剣の扱いは間違いなく一流ですぜ。そういうのは俺にはすぐ分かるんだ。";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "とんでもない、シャルル！俺はあいつと決闘なんてしないぜ。俺たちは賭けをするんだ、カードこそ文明人の武器さ。 あいつの懐を空っぽにして、お前のところへ送り返してやるよ、安全にケベックへ帰るための借金を頼みに来るだろうな。 ";
			link.l1 = "そいつはなかなかいい策だな。ただ、俺に言わせりゃ、あの野郎は貧乏になるより死んだほうがマシだぜ。ご武運を、 閣下！";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "くそっ、アンジェラン、そこに10が出るわけねえだろ！絶対にありえねえ！";
			link.l1 = "それは非難か？取引を持ちかけたのはあんただろ、旦那。";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "違うんだ。俺はただ…ちょっと興奮しすぎただけで、謝るよ。あれは事故だったんだ、だから再戦の機会を要求する！この船は、俺が…どうしても取り戻さなきゃならないんだ！\nいや、もう勝負なんてどうでもいい、いくらならこの船を売ってくれる？値段を言ってくれ、明日の正午までに必ず払う！ ";
			link.l1 = "残念だが、俺は心の底から思うんだ、賭博で失った戦利品は買い戻せねえ。勝ち取るしかねえんだよ。 笛は今や俺のもんだし、売る気はさらさらねえ。お前の情熱がこんな状況に追い込んじまったのは気の毒だが、 自分の力をもっと現実的に見たほうがいい時もあるぜ…他に船の書類でも持ってるのか？";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "お前はクズだな、アンゲラン。しかも俺を追い詰めやがって……だがな、きっとお前が受け入れる賭けを提示できると思うぜ。";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "チャールズ、君だけが頼りなんだ、どうか助けてくれ！ あのフルート船と積み荷はすでにオランダ商会に売られてしまった。明日、 全ての書類を彼らに引き渡さなければならないんだ。今夜はここに泊まるつもりだったから、書類も持ってきた。 もし取引が失敗したら、俺は破滅してしまう！";
			link.l1 = "「だが、“可愛いジャック”よ、お前が贔屓にしたあの女は、今やもっと悲惨な状況に陥っていると思わねえか？俺も賭け事には慣れてるし、 たとえ自分の船じゃなくても船を賭けるってのは分かる。だが、女を賭けるだと！？本当に驚いたぜ！そして今や、 お前が気にしてるのは自分の取引の行方だけか？」";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "俺を裁くなよ、チャールズ。権力者の伯爵の元愛人をひいきして、ちょっと恋に落ちたくらいで騒ぐなっての。 ピーテル・スタイフェサントに百万ペソの借金があることに比べりゃ大したことじゃねえ。 これをあいつの代理人にどう説明しろってんだ？俺の評判がどれだけ傷つくか、想像してみろよ！";
			link.l1 = "俺も前に似たような借金を抱えてたが、まったく何も持ってなかったのに、なんとかなったぜ。お前もきっと大丈夫さ。 じゃあな、ジャック。また会おう。約束はしねえし、どんな積み荷が百万の価値で、 しかもフルート船に積んでるのかなんて聞きもしねえよ。";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "やっと来たな、チャールズ。今にも呼びに行こうとしていたところだ。ド・シェヴィウスが決闘を強く要求していて、 和解の余地はもうないそうだ。カードではうまくやったが、本当にこれを続けたいのか？";
			link.l1 = "どうもかゆいような疑念があるんですよ、閣下、あなたは最初からこの結末を望んでいたんじゃないかってな。\nだから俺は「はい」と答えるぜ。これで決着をつけるしかねえ。\n決闘の条件はどうするんだ？";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "お前は考えすぎだぜ、友よ。世の中のすべてがお前中心に回ってるわけじゃねえんだ。信じてくれ、 昨夜の成り行きには俺も心底がっかりしてる。本当に、深くな。\nだがまずは、お前の……勝ち取ったものの行方について話そうじゃねえか。";
			link.l1 = "いいだろう。笛を取り戻す方法を知りたいのか、それともジュリアンヌ夫人がどうしているか知りたいのか？";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "皮肉をやめて今度は悪意か？チャールズ、俺たちは同じ側なんだぜ、それを忘れるなよ。";
			link.l1 = "議論の余地がありますな、閣下。控えめに言っても。さて、どちらから始めましょうか――船ですか、それともご婦人ですか？";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "もちろんスタイフェサントの取引だ――彼の代理人が朝からずっと俺を待っていて、言い訳ももう尽きそうだ。フルート号の書類が必要なんだ、チャールズ。";
			link.l1 = "いいだろう。彼女はお前のものだ。俺はド・シェヴィウスが正々堂々と勝負したとは思えねえ。だから、 お前の財産は半額、十五万で返してやる。";
			link.l1.go = "governor_18";
			link.l2 = "喜んで引き受けよう。船の値段はいくらだったって？50万か？それでいいぜ。";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "さて、税金込みで四十六万ペソになるぜ。\n取引成立だ。十三万五千だ。";
			link.l1 = "聞けよ……もう言い争うのはうんざりだ。だからさっさと金を払って書類を受け取って終わりにしろ。";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "お前は昔の友だちに情けをかけたりしねえよな、チャールズ？さて、税金も全部込みで……";
			link.l1 = "カードの借金と友情は全く別物でございます、閣下。買い手であるあなたが自分で税金を払っていただきます、 さもなくば私はル・フランソワでこの船を売りますぞ。念のため申し上げますが、 私はまだあなたの立場を利用してはおりません……今のところは。";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "よろしい、そうしよう。さて、決闘だ。俺はルヴィ・ヴァンタデュール伯爵と揉め事を起こしたくないから、 すべてできる限り合法的に進めるぞ。聞こえたか、シャルル？法律に従ってだ！私の守備隊から士官を二人同行させる――どちらも高貴で評判の良い男たちだ。彼らが君の普段の…仲間の代わりに立会人を務める。決着がつくまで、すべてを明白にしておきたいのだ！";
			link.l1 = "気が利くじゃねえか。だが、もしあの旦那が汚い手を使う気になったらどうする？俺は、友と呼べる奴や、 こういう時にどう動くべきか分かってる連中に背中を預けたいんだ。生まれがいいだけの奴らよりな。";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "シャルル、まるでこの決闘が俺とお前だけのものみたいな態度はやめろ。これは本気の話だ。ド・シェヴィウスは、 殺してもただで済むような男じゃねえ。どんな結末になろうと、調査が入り、場合によっちゃ裁判にもなる。 信頼できる証人が必要になるぞ。分かるか、俺はお前のためを思って言ってるんだ！だが一番大事なのは、 絶対にあいつを殺すなってことだ。アンジェランが覚悟を決めてて、腕も立つのは分かるが、シャルル、 お前は絶対に殺しちゃいけない！傷を負わせるのも、辱めるのもいい、だがそこで止めろ。もし殺したら、 必ず報いが来るし、俺たちどっちも逃げ切れねえし、生き残れねえ。 たとえルヴィ・ヴァンタデュール伯爵が正式に自分の私生児を認めていなくても、他に息子はいないんだ。 あいつの怒りは、果てしないぞ。";
			link.l1 = "素晴らしいな、つまり俺は激怒した伯爵に殺されるままにして、お前が総督の座を追い出されるのを止めろってことか？";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "お前が言うことを聞かなければ、俺たちはアンジェラン・ド・シェヴーよりも長く生きられねえかもしれねえぞ。 忘れるな、そして気をつけろ。決闘は今夜十時、町の門の外で行われる。俺の部下たちがそこで待っている。\nさて、最後の件だが……ジュリアンヌ・ボトー夫人はどうしている？";
			link.l1 = "俺がもう戦利品を手に入れて楽しんだか知りたいのか？いや、閣下、まだだし、これからもないかもしれねえ――そんなことはどうでもいい。大事なのは、あんたがもうマルキーズの屋敷から完全に追い出されたってことだ。 彼女はその点についてはっきりしてたぜ。俺は彼女を責めるつもりはねえ。ジュリアンヌは次の後援者を自分で選ぶさ。";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "本当に驚かせてくれるな、チャールズ。\nさて、これから会社の代理人との退屈な会議に出席しなければならない。\nお前も行くんだ、準備をしておけ、そして俺が警告したことを忘れるなよ。";
			link.l1 = "必ずやってみます、閣下。しかし戦いですから、約束はできません。助けてくれてありがとうございます。";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "生きてたのか、チャールズ！助かったぜ、どうだった？この血は何だ！？ド・シェヴィウスは無事か！？";
			link.l1 = "残念ながら、その通りだ。奴は怪我をしているが、重傷じゃねえ。逃げる羽目になったが、 手下どもを俺たちにけしかけやがった。\n要するに、この血の一部は俺のもんじゃねえ。";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "この野郎！それで俺の部下たちはどうした？あいつらは生きていて、何が起きたか証言できるのか？";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "皆無事でございます、閣下。少し傷を負っておりますが、命に別状はございません。";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "全員ではありません、閣下。一人の紳士は助かりませんでした――ド・シェヴィウスがわざわざ銃士たちを連れてきたのです。俺にはどうすることもできませんでした。";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "あそこはまさに地獄でした、閣下。勇敢な紳士お二人は戦闘で倒れました。もし彼らがいなければ、 俺はひどい目に遭っていたでしょう。ド・シェヴィウスが見事な血まみれの待ち伏せを仕掛けてきたんです。";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "素晴らしい！信頼できる証人の前で彼らの書面による証言を手に入れるぞ。 ド・シェヴィウスには必ず報いを受けさせてやる！";
			link.l1 = "俺たちじゃ、あいつの名にほんの少しの傷もつけられねえと思うぜ。お前の忠告なんざ無視してでも、 俺が自分で見つけてケリをつけてやりてえ。あんな腰抜け、生きてる価値なんざねえんだ。";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "ひどいな。しかし、少なくとも一人の証人から書面の証言を手に入れるぜ。 ド・シェヴィウスには必ず報いを受けさせてやる！";
			link.l1 = "奴の名に少しでも傷をつけることなんてできねえと思うぜ。お前らがどれだけ警告しようが、 俺は自分で奴を見つけてケリをつけてやるさ。あんな腰抜け、生きてる価値なんざねえんだ。";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "くそっ！あいつらはいい奴らだったんだ、チャールズ！絶対にあの野郎に報いを受けさせてやる！";
			link.l1 = "俺たちじゃ、あいつの名にほんの少しの傷もつけられねえと思うぜ。お前の忠告なんざ無視してでも、 俺が自分で見つけてケリをつけてやりてえ。あんな腰抜け、生きてる価値もねえんだ。";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "気にするな、チャールズ。あの野郎は自分で必要なだけの被害を出しやがった。 今ごろはどこか貧乏な植民地の土の中に隠れて逃げてるだろうぜ。もうお前にとって脅威になることはなさそうだ。 あれは逃げる蛇の最後の一噛みってやつさ。\nお前も怪我してるようだが、医者が必要か？";
			link.l1 = "ご心配いただきありがとうございます、閣下。しかし私は大丈夫です。";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "知っておいてよかったな。もう安心していい、この話はこれで終わりだ。ゆっくりして、仕事に戻れよ。\nところで、そのことだが……さっきのお前の最近の勝利についての話、まだ終わってなかったな。あれをどうするか、もう決めたのか？";
			link.l1 = "「よくわからんぞ、ジャック。何のことだ？マルキーズのことか？くそっ！ボトー夫人！ド・シェヴーは逃亡中で、 もう俺の脅威じゃねえが、あいつは追い詰められてて何をしでかすかわからん！俺は行かねばならん！ 衛兵をマルキーズの屋敷に送れ！今すぐだ！」";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "有名な船長だって？この小さな町を焼き払おうとしたスペイン軍の襲撃を撃退したあの人物か。なるほどな。で、 何を飲むんだ？";
			}
			else
			{
				dialog.text = "有名な船長だって？聞いたことねえな……何を飲むんだ？";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "ピノ・ノワールかい、美しい女主人と同じものを？この海の塩気の後で、本当に味が分かる自信があるのか？\n普通、お前みたいな上等な連中は、古靴でも溶かせそうな酒を好んで飲むもんだぜ。";
			link.l1 = "もし一緒に門を通り抜けようという提案なら、乗ったぜ。俺もお前のことは好きじゃねえし、 その気持ちが互いに同じで嬉しいぜ。無駄話はやめようや――どうせお前は口が立たねえしな。条件と武器の選択はお前に任せるぜ。";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "土と猫の小便のブーケだと？こりゃあ風情があるな！こんな酸っぱいクズ酒、樽で寝かせることもねえんだろうな、 どうせワインになりゃしねえし。なあ、海の塩気ってのはここまで味をぶっ壊すもんなのか？\n";
			link.l1 = "もし一緒に門を通り抜けようという提案なら、乗ったぜ。俺もお前のことは好きじゃねえし、 その気持ちが互いに同じで嬉しいぜ。話はもうやめようや――どうせお前は口が立たねえしな。条件と武器の選択はお前に任せるぜ。";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "はっ、なんて勇ましい坊やでしょう！さあ、落ち着いて距離を取りなさい。ここは酒場ではありませんし、 私はあなたの飲み仲間でもありません。あなたなど私の身分には到底及びませんわ。 本来ならお話しする必要もないのですけれど、あのお嬢様のご要望ですから。さて、 ジャックと私にはまだ片付けるべき用事がございますの…\n";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "「ジュリアンヌ、大丈夫か？水だ、バカ野郎ども！水を持ってこい！」";
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "まったくその通りだ、ここは蒸し暑いな。今までなかなか面白い勝負だったが、決戦の前に少し休憩しようじゃねえか。 じゃあな、ジャック――我々の勝負の条件、覚えてるだろ？\nさて、こちらはシャルル・ド・モールで間違いないな？ワインの趣味が悪い船長、覚えてるぜ。心配すんな、 ここが終わったらお前は水しか飲めなくなるさ。だからゆっくりしろ、この瞬間を楽しんで、酒でも飲んでな。 準備ができたら、この小部屋に来いよ。夜の締めくくりは、もっと快適な場所で過ごそうじゃないか……";
			link.l1 = "楽しみにしてるぜ、旦那。";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "やっと来たな。金を払う覚悟はできてるか？";
			link.l1 = "できればお前のもそこに加えたいんだ。頼む！";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "よく言ったな、だが残念ながら、我らの親愛なる総督殿が恥ずべき敗北の直前に規則を変えると強く主張したのだ。\n今や賭けには金だけでなく、何か他のものも加えねばならん。\n両者が等しいと認める賭けでなければならんのだ。\n俺の賭けは銀細工のフルートだぜ。";
			link.l1 = "さあ、こんなの退屈だぜ――略奪を数週間やりゃ、あんなもん五つも金で手に入る。もっとデカい獲物をよこせ。";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "ああ、君の船は見たぜ、正直言って本当に見事なもんだ。じゃあ、賭けを上げようじゃねえか――二隻対一隻だ。俺のフリゲートとフルート、それに銀を君の船と勝負するってのはどうだ？";
				link.l1 = "見事な勝負だ！ボトー夫人は間違っていたな――この決闘は伝説として語り継がれるぜ。取引成立だ！";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "見ろよ、うちの船長はずいぶんとやんちゃだな！だがな、私掠は神聖なもんだぜ。戦列艦はどうだ？フリゲート、 四十八門だ。多くのコルベットより速い――王立造船所の産物で、さらに世界一の船大工が改良したんだ。搭載してるカルバリン砲は射程も精度も抜群だぜ。どうだ、 乗ってみるか？\n";
					link.l1 = "ずっといいぜ、俺も乗った！行こう！";
				}
				else
				{
					dialog.text = "ここに投錨したと聞いたぞ、船長。お前のオンボロ船を賭けに受け入れてやったこと、感謝しな。さあ来い、 まさか逃げるつもりじゃねえだろうな？";
					link.l1 = "なるほど、一理あるな。行こうぜ。";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "ゲームオーバーだ、船長。お前の望み通りになったな。好きにほくそ笑むがいいさ。 俺のフリゲートの買収条件については、明日の正午に話し合おうじゃねえか。";
					link.l1 = "それだけか？俺もあんたと同じく、賭けで失ったものは買い戻せず、勝ち取るしかねえと心から思ってるぜ。あるいは、 あの船を地元の漁師に材木として売り飛ばして、あんたの気前のいい寄付話でも聞かせてやろうか。";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "運命の女神が決着をつけたようだな。これは実に奇妙な展開になった。おめでとう、ド・モール船長。 私のフリゲート艦の買収条件については、明日の正午に話し合うことを提案しよう。";
						link.l1 = "もうそんなに早く？他のお客様をがっかりさせてしまいますよ、旦那。私の記憶が正しければ、 あなたにはまだもう一隻船が残っています。私もあなたと同じく、賭けで失ったものは買い戻せず、 勝ち取るしかないと心から信じております。";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "運命が語ったようだな。これは実に奇妙な結果になった。おめでとう、ド・モール船長。 お前さんは立派な酒を飲む資格がある、サンジョヴェーゼを試してみな。 ジャックがこのボロ船にたっぷり金を払ってくれるだろうと俺は思うぜ； どうやらあいつはこの船に特別な思い入れがあるらしい、他の何かよりもずっと強い感情をな。 これで上等なワインが買えるはずだ。";
						link.l1 = "もう降参かい？他の客人たちががっかりしてるぜ、旦那。俺の記憶が正しければ、 あんたにはまだもう一隻船が残ってるはずだ。あんたが俺の船を質素すぎると見なしたから、 今度はあんたのフリゲート艦を俺の銀装飾のフルート船と賭けようじゃねえか。";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "運が悪かったな、船長。それでも、お前の勇気は評価するぜ。今日は機嫌がいいからな。金はもらうが、船は返してやる。 さっさと俺の前から消えろ。そして今後は賭博を控えるんだな。いつか命取りになるぜ。";
				link.l1 = "とても高潔だな、そんなことは予想していなかったよ。さらばだ、de Chievous旦那。";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "敗者を嘲笑うのと侮辱するのとでは大きな違いがありますぞ、ド・モール旦那。";
			link.l1 = "もう自分が負けたと思ってるのか？せっかくいい始まりだったのによ……ああ！ボトー夫人、あなたのサロンにまたひとつ、「言葉と行動の違い」に関する素晴らしい逸話が加わりましたな！";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "他に何が欲しいんだ？もう隠し船なんて持ってねえし、一隻分の金すら残っちゃいねえよ。 ダブロンを賭けてギャンブルなんて、今夜の出来事の後じゃ冗談にもならねえさ。";
			link.l1 = "お前は、あの愛すべきジャック・ディル・デュ・パルケよりも才覚がないのか？私は、 お前に素晴らしい機会を与えてやろう。すべての愛が金で買えるわけじゃないと証明するチャンスだ。運命もまた、 その寵愛を売ることはない。銀の船とお前のフリゲート、そしてお前が金よりも大切にしているものを賭けるのだ。";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "船長、こんなの笑い事じゃねえよ。さっさと終わらせようぜ――もうすぐ夜明けだ。俺のフリゲート艦の買い戻しについては明日話そう。";
			link.l1 = "よし、わかった―三隻だ！本物の軍艦も含めてな、しかも新世界で一番…まあ、高価な女船長が相手だぜ。こんな賭け、断れるか？";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "狂気の沙汰だ。しかし、実際狂気だよ、ド・モール旦那。どうか頼む。ただし、 これはあなたの発案だったことを忘れないでくれよ。";
			link.l1 = "これは一年間も密かに語り継がれる伝説になるぜ！\nおい、そこのお前、もっとワインとロウソクを持ってこい！\n宴はまだ終わらねえぞ！";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "ついこの前まで、このフルートなんぞ俺たちの船に賭ける価値もねえと思ってたじゃねえか。何が変わったんだ？";
			link.l1 = "退屈してきたぜ。決闘にちょっと刺激を加えようじゃねえか――お前のフリゲートと俺の船で勝負しよう…";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "お前があんなに軽く見てたフルートか？もしかして熱でもあるのか？あんまり元気そうじゃねえな。";
			link.l1 = "私はまったく問題ありません、ありがとう。君は聞いていなかったな。二対一の賭けはそれほど見事でもない、 そうだろう？ならば条件を公平にしようじゃないか！すべての貴重品が金で測れるわけじゃない、そう思わないか？ それとも、何かが君の計画通りにいかないとすぐに風と戦うのをやめて進路を変えるのが好きなのか？それなら残念だ、 君のことを見誤っていたようだ。ボトー夫人、あなたのサロンにはまた一つ、「言うこと」と「やること」 の違いについての面白い話が加わったようですね…";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "俺の神経を逆なでするつもりか、ド・モール旦那。お前にはまだ早すぎるぜ。";
			link.l1 = "確かにな。意志の弱さは罪じゃねえ……軍人でもなけりゃな。あるいは貴族――家の名誉ってやつは、時に重荷になるもんだぜ。ま、お前さんがそんな悩みを知ってるとは思えねえがな。";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "決闘を始めたいのか、それとも勝負を続けたいのか？";
			link.l1 = "どちらでもいいぜ。お前が落ち着くまで、俺は侯爵夫人のワインコレクションに感謝しておくとするか。";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "そうか。今夜はきっちり締めくくろうじゃねえか。二隻の大型船が、 銀とニュー・フランス一の美女を乗せたオンボロ船に挑むってわけだ！もっと深く息を吸え、ド・モール旦那、 この賭けは上流社会の噂話で語り継がれる伝説になるぜ。";
			link.l1 = "お前の敗北は伝説になるぜ、確かにな、ド・シェヴース旦那。もっとワインとろうそくを持ってこい！やるぞ！";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "運に夢中になりすぎてるぜ、ド・モール旦那。ここで危険を冒してるが、幸運なんてすぐに逃げちまうもんだ。";
			link.l1 = "ささやかな親切は真実の愛への道だ。\n買われた忠誠も同じことが言えるが、それが導くのは軽蔑か退屈だけだ。";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "お前が俺を苛立たせようとするのは面白いな。そういう好意や愛、そして金で買えるものも買えないものも、 マダム・ジュリアナに聞いた方がいいぜ。だが急げよ――明日には彼女は町を発つからな。";
			link.l1 = "少なくとも、お前の知識は一方的だな。ここで勝っても払っても、運命の女神のご加護は得られねえ、 だから彼女の愛も知ることはできねえんだ。リスクを取るには勇気と揺るがぬ意志が要るんだぜ、旦那。それに、もっと…現実的な女たちもそういうものを重んじるもんさ。俺の船二隻をお前の一隻に賭ける、乗るか？\n";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "そんなに続けたいのか？まあ、好きにしろよ。だがせめて、ちょっとは盛り上げようじゃねえか、ド・モール旦那。 さっきは愛だの値段だの言ってたよな？だったら、賭けを対等にしようぜ――お前のオンボロ船と銀の笛、こっちは俺のフリゲート艦とヌーベルフランス一の美女だ。どうだ、乗るか？";
			link.l1 = "お見事だな、旦那！粋な賭け方を知ってるじゃねえか！もっとワインと蝋燭を持ってこい！さあ、行くぜ！";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "信じられません、ド・モール旦那、これは本当に信じられません！";
				link.l1 = "そうですとも、実に、ロクロワの戦い以来ヨーロッパはこれほどの敗北を知らなかったのですよ、ドゥ・シェヴー旦那。 私の中の芸術家が、こんな歴史的瞬間を描き留めたいという衝動で震えております。 若い頃のようにはもう絵を描けないのが残念です。しかし、 ジュリアンヌ夫人のそばにはきっと腕の立つ画家がいるのでしょう、違いますか？";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "運が悪かったな、船長。それでも、お前の勇気は認めるぜ。今日は機嫌がいいからな。金はもらうが、船は返してやる。 さっさと俺の前から消えな。今後は賭博はやめとけよ。いつか命取りになるぜ。";
				link.l1 = "たいしたご立派な心がけだ、まさかそんなことをするとは思わなかったよ。さらばだ、de Chievous旦那。";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "いいや、お前にはわかっちゃいねえ。こんなこと、信じられねえほどありえねえんだ！";
			link.l1 = "俺たちはみんなカードを見たんだ、ド・シェヴー旦那――運命は決して嘘をつかねえ。";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "運命は違うが、あんたは違う、ド・モール旦那、あんただ！\nどうやら、あんたの厚かましさの裏には情熱だけじゃなく、計画があったように思えるぜ。\nあんたは嘘つきで詐欺師だ――俺はこのことを全ての客の前で証明する用意があるぜ。";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "ド・シェヴー旦那、今の発言、聞き間違いじゃないですよね？その疑い、口先だけじゃなく証明する覚悟はありますか？ どうやらあなたの侮辱は度を越えたようだ。俺はあんたと違って、家族の名誉を大切にしているんだ。";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "次男よ、詐欺師やペテン師ごときに家名の誇りを説教される筋合いはない！黙っていろ、ジュリアンヌ、 お前には後で話す！シャルル・ド・モール、今すぐ決着をつけろ！剣か？それともピストルか？";
			link.l1 = "両方さ。正直言って、お前が考えを変えてくれて嬉しいぜ。覚えてるか、俺が門の外を散歩しようって言ったのを？ 俺の身分が卑しいとか何とか言ってただろ？どうやらカード遊びで少しは度胸がついたんじゃねえか？";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "過分な光栄だが、侯爵夫人に同意しよう。貴様にはその価値はないが、貴族らしく決着をつけてやるぞ、ド・モール。 明日正午、総督閣下を通じて決闘を申し込む。自ら総督に会いに来るか、代理人を送って条件を話し合うがいい。 それまでだ。\n奥方、敬意を表します。";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "おお、ここにいたか、運に恵まれた奴め。\n持ち物の用意はちゃんと済ませたか？\n告解を忘れてねえだろうな？\nあの世じゃ、告解なしだと地獄はずいぶん居心地が悪いらしいぜ。";
			link.l1 = "口だけは達者だな、旦那。カードもまともにできねえんだから、今度は剣の腕前を見せてもらおうじゃねえか……さあ、踊ろうぜ！";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "やるじゃねえか、この野郎……だが、俺はまだ生きてるぜ！";
			link.l1 = "傷の具合は良くないが、それでも医者に診てもらうべきだ。明らかにこのままじゃ無理だぜ；このままだと死ぬぞ。\nここはもう終わりみたいだな。俺の勝ちだ、イカサマはしてねえ。お前の船は返してやる、 そしてサン・ピエールを出ていけ。\nもう二度と会うことはないだろう。";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "なんて大した騎士道精神だ！見ろよ、ド・モール旦那、お前は生まれつきの剣士かもしれねえが、 カードでは間違いなくイカサマしたな。俺は三度も山札をいじったんだぜ。三度だ、くそっ！ この世のどんな奇跡でもお前を救えねえはずなのに、それでも勝ちやがった！どうやったのか知りてえもんだ……まあいい、すぐに地獄で全部しゃべることになるさ。やれ、野郎ども！\n";
			link.l1 = "この野郎！俺が情けをかけてやったのに、こんなお返しか！？\n旦那たち、武器を取れ！";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "認めますよ、ド・モール旦那、ここであなたに会うとは少し驚きました。それは、 私のあなたへの見立てが間違っていなかったということですね――あの荒っぽい娘のこと、本当に気にかけているのでしょう？";
			link.l1 = "お前の親友デ・リヨンは、我が海軍の名高い船長から士官を誘拐することについてどう考えているんだろうな？\nいっそ奴も呼んで、全部話してやるか？";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "それじゃあ全く助からねえぜ、信じな。あと、お前の女は捕虜の将軍よりも丁重に扱ってやった。今のところはな。だが、 すべては変わるかもしれねえし、それはお前次第だ、チャールズ。";
			link.l1 = "俺たちがあんたと恋人の一杯を分け合った覚えはねえぜ。チャールズなんて呼ぶんじゃねえ、ド・シェヴー旦那。 用件があるならはっきり言いやがれ、俺に何を望んでるんだ？";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "お前から？とんでもねえ、そんなことあるか！俺たちはただ、あのいまいましいカード遊びの後で不運な喧嘩を片付けて、 酒を何杯か飲んで、この部屋を昔からの友人同士として出ていっただけだぜ。\n";
			link.l1 = "アンジェラン、最近の傷があるくせに元気そうじゃねえか。このくだらねえおしゃべりを続けるたびに、 またお前を痛めつけたくなってくるぜ。フランソワ・ド・リヨンの立派な絨毯を血で汚すのも、 だんだん悪くねえ気がしてきたぜ。";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "だがな、フランソワのじいさんはこの絨毯が大好きなんだよ、シャルル。誰だって何かを愛してるもんさ。 お前がここにいるってことは、きっとその小さな恋人を大事に思ってるんだろう。俺は自分の財産と引き換えに、 あの娘を返してやる用意があるぜ。お前はこの勝負を台無しにしたが、普段なら許さねえところを、 今回は特別に大目に見てやる。俺が欲しい賞品を渡せば、お前にも同じものを返してやる。 そうすればきれいに別れられるってわけだ。愛なんてそんなもんさ。\n";
			link.l1 = "俺が侯爵夫人を財布の中の宝石みたいに持ち歩いてるとでも思ってるのか？馬鹿言うな！ どうやってお前に彼女を引き渡せるってんだよ！？";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "俺は全く気にしないよ、チャールズ。これを片付けるのに二週間やる。\nそれと、そうだな、この賞品は目立たずに受け取ってほしい。\n例えば、とんでもなく高い娼婦を手に入れたのに、結局その気を引けなかった船長が、 馬鹿なことをしでかすかもしれないだろ？\nお前ももう、十分に追い詰められてるんじゃないか、チャールズ？";
			link.l1 = "まず自分の士官に会って、彼女がまだ生きているか確かめたい。";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "論外だ。俺の言葉を信じるしかねえ。あの女は安全な場所にいるし、俺が報酬を手に入れるまでそこに留めておく。だが、 どうしても先に会いたいとしつこく言うなら、喜んであの女の一部を送ってやるぜ。どれが好みだ？耳か、鼻か、 指を二本か？\n";
			link.l1 = "あの娘に手を出してみろ、このクズ野郎、俺がこの手で絞め殺してやる、神に誓ってな！ 俺を本気で怒らせるんじゃねえぞ！";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "落ち着け。これから起こることはすべてお前自身のせいだ。俺は暴力は好きじゃねえ、必要な時しか使わねえんだ。 俺にやらせるな。俺の獲物をドミニカのケープ・スコット岬で二週間以内に渡せば、お前の物は返してやる。 やり方なんてどうでもいい。盗みたきゃ盗めばいいさ、どうせお前は海賊だろう、見た目が少しマシなだけでな。";
			link.l1 = "お前は血迷ってるぜ、海賊とくそったれな奴隷商人じゃ大違いだ…";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "もっと深く息を吸って、これからフランソワの前で華やかに登場するんだぞ。今は俺たち友達だろ、覚えてるか？笑えよ、 シャルル、ほら！じゃあここでお別れだ。ケープ・スコット岬、ドミニカ、二週間後だ。遅れるなよ。";
			link.l1 = "そこで会おう。";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "こんばんは、Botot夫人、de Maure船長。どうかご冷静に。";
			link.l1 = "マルキーズ、俺の後ろに！旦那、これは一体どういうことだ！？";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "この扉の向こうには俺の部下が十数人いるし、貴国から非常権限も与えられている。衛兵たちはお前を助けてくれねえ。 だから、剣を収めてくれ、旦那。今はただ話がしたいだけだ。今のところはな。";
			link.l1 = "旦那、あんたは何者で、どうやってここに来たんだ！？ちゃんと説明してもらおうか！";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "自己紹介させていただこう――ウィリアム・コートニー卿、コートニー準男爵だ。さて、みんな落ち着いて話そうじゃないか。";
			link.l1 = "「よろしいですわ、コートニー様、皆で耳を傾けておりますわ。」";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "盗み聞きしてしまったことをお許しください、だが今の状況では他に方法がなかったのです。\nここサン・ピエールでは私は匿名のままですが、イングランド王室の代理として極めて重要な調査を行っています。\n海で消息を絶った伝令船についてです。ブリガンティン船「レジーナ」について聞いたことはありますか？ ";
			link.l1 = "俺は知らねえし、あんたの怪しい示唆にも乗らねえよ、旦那。俺は正直な船長だぜ……";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "お前のいかがわしい取引なんざ、俺はこれっぽっちも気にしちゃいねえ、旦那。お前について少し調べさせてもらったが、 正直言って、レジーナ号が消えた直後にマルティニークを訪れたと聞いた時点で、まず最初にお前を疑ったんだ。だが、 お前は馬鹿じゃねえし、お前の部下もここで真珠をいじった形跡はなかった。だから、 今のところはお前を疑いの対象から外しておくぜ。";
			link.l1 = "真珠だと？どの真珠のことをぬかしてやがるんだ？";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "スペイン領西インドの作業場から厳選された大粒の真珠だ。しかも黒真珠だから、極めて珍しいぜ。こんな話、 聞いたことあるか？";
			link.l1 = "そうかもしれねえが、俺はずっとただの船乗りの与太話だと思ってたぜ。フライング・ダッチマンの話と同じさ。\nジュリアンヌ、どうしたんだ？";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "ここでご提示いただきたいのです、奥様。これは非常に重要な件でございます。その間に、旦那、 あなたにはモレノ船長についてすべて話していただきましょう。 あなたにその手がかりを与えたのは彼だと私は疑っております。この件における彼の役割について、ぜひ知りたいのです。 ";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "モレノというのは本名ではありません、コートニー旦那。本当の名前はエルナンド・バスケス、通称「血塗れのドン」。 かつて悪名高いポルトガル人バルトロメウの船「アルバトロス号」の四分士を務めていたスペインの海賊です。";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "ほんの少し言葉を交わしただけだ。話せることはあまりない。奴は本物の海の狼って感じだったぜ。";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "おやおや。それをどうしてご存知なのか、お聞きしてもよろしいですか？";
			link.l1 = "俺はあいつの船長を知ってたんだ。実は、俺が捕まえてオランダ人に引き渡したのさ。長い話だぜ。 あの時にバスケス本人を捕まえられなかったのが悔やまれるな……";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "あんたも海の狼だろう、旦那。もっと気づかなかったなんて信じられねえな。";
			link.l1 = "ちょっとした訛りと、あの仕草や態度。きっとスペイン人だぜ、コートニー旦那。";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "それは大きな変化だな、旦那。しかも悪い方向だ。奥さん、首飾りは見つかったか？見せてくれ\nうむ、間違いない、これはスペインの黒真珠の一つだ。見てみろ、この海の噂話はほとんど本当だったわけだ。あとは、 どうやってあのド・シェヴィウスがこれを手に入れたのか調べるだけだな。ところで、 あいつはド・ルヴィ・ヴァンタデュール公爵の私生児じゃなかったか？";
			link.l1 = "間違いなくあいつだ。俺たちの知る限り、ル・フランソワの地元の海賊男爵と取引があったらしい。もしかすると、 この真珠もそいつから買ったのかもしれねえな？";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "そうかもしれねえが、この件にスペインの影があるのは気に入らねえな。ともかく、協力に感謝するぜ。悪いが、 また明日の同じ時間に訪ねさせてもらう。ド・モール船長にも同席してもらいたい。もしかしたら、 さらに質問があるかもしれねえ。今はル・フランソワへ行くとするか。\n";
			link.l1 = "コートニー旦那、待ってくれ。俺も一緒に行っていいか？ ジャック・バルバゾンは優しくて愛情深い人間だからあのあだ名を得たわけじゃねえし、この件には俺も興味があるんだ。 ";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "船長、ご心配いただき感激ですが、お答えはノーです。これは国家の問題です。あの悪党も自分の立場はわかっており、 王冠の使者に手を出すなどとは決してしないでしょう。さもなくば、あの哀れな村は跡形もなく消え去ります！ 再びお邪魔して申し訳ありません、奥様。良い夜を。";
			link.l1 = "また明日の晩に会おう、バロネット。";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "怒らないでやってくれよ、船長。俺は口が達者なんだぜ。あんたの話は実に見事だ。本当に感心したよ。どうやら、 あんたを使う道があるかもしれねえな。";
			link.l1 = "満足そうだな。ル・フランソワではどうだったんだ？";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "思った通り、お前のあの男爵は子羊のようにおとなしかったぜ。俺が知りたかったことは全部話してくれた。 言っただろう、俺はとびきり説得力があるんだ。";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "今日は俺一人でここに来たんだ、あの扉の向こうに俺の手下はいねえ。何だと！？";
			link.l1 = "嫌な予感がするぜ。ジュリアンヌ、今すぐ俺の後ろに下がれ！バロネット、 王冠の使者ってのは口だけじゃなくて腕も立つのか？";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "剣の扱いはさすがだな、船長！えっと、正直言って楽な相手じゃなかったぜ。あいつら一体何者だったんだ！？";
			link.l1 = "奴らの仲間に聞いてみるべきだな――足音が増えてきたぜ。衛兵だったらよかったんだが……";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "信じられねえ！あの野郎がこんなことをやったと思うのか！？必ず報いを受けさせてやる、誓うぜ！";
			link.l1 = "落ち着け。バルバゾンの野郎はどんな疑いも巧みに逃げおおせるさ。 あいつはただの小物泥棒どもが金持ちの屋敷を襲っただけだとでも言うだろう。\nそれに、あいつはくそったれの海賊だ、役人なんぞ気にするわけがねえ！\nだがな、今はお前が本当に貴重な情報を手に入れたと確信してるぜ。その知識を俺にも分けてくれないか。";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "断れねえよな？じゃねえと、次は本当にやられちまうかもしれねえしな？まあいい、 あんたの声に脅しが混じってたのは気づかなかったことにしてやるよ。恩返しってことにしとこう。 親切者ジャックはあんたの貴族のろくでなしに真珠を売ったんじゃねえ。買ってたんだ。それだけだ。";
			link.l1 = "つまり、レジーナ号を拿捕したのはド・シヴィアスだったのか？あいつは悪党だが、 普通の海賊行為にまで身を落とすとは信じがたいな。";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "レジーナ号を典型的な海賊の戦利品とはとても呼べませんな、船長。少なくとも黒真珠を六つは積んでいたと我々 は見ています。黒真珠一粒でも値がつけられぬほど貴重です。 どうしてもあのド・シェヴィウス旦那に会わねばなりません。";
			link.l1 = "ここで少しは力になれるぜ、旦那。でもまずはっきりさせておきたい。俺はボトー夫人の首飾りには興味がなかった、 つまり真珠があんたの目的じゃねえってことだ。他にレジーナ号には何が積まれてたんだ？";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "仕方ないな、この状況だ、もう少し話さなきゃならんようだ。いいか、実は貨物そのものよりも船自体が重要なんだ。 運び屋のブリガンティン「レジーナ」はサンホセ、トリニダードの港に配属されていた。 その船長は俺たちのために情報を集めたり、いろいろと…雑用をこなしてくれていたんだ。\n最後の仕事は、うちの連中がスペインの真珠採掘場からかっぱらった戦利品を運ぶことだった。 その手がかりを掴むのに三年もかかったんだぜ。黒真珠は確かに大きな価値があるが、レジーナを失ったのは致命的だ。 事故なんかじゃねえ、真珠のことを知っていた奴は、他のことも知っていたはずだ。";
			link.l1 = "素晴らしい、つまり結局は諜報活動の話か！お前が築き上げたスパイ網全体が危機に瀕しているとでも恐れているのか？ 今やっと、お前の抱えている問題の全貌が見えてきたぜ。";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "ジョン・サーローのことを聞いたことがあるか？奴は王室諜報部のトップだ。いつか俺はロンドンに行き、 レジーナ号の運命について直接奴に報告するつもりだ。どこから情報が漏れているのか突き止めて……元を断たなきゃならねえ。それに、お前のあの謎めいたモレノ船長もいるしな。 もしスペインが俺たちの植民地スパイ網を突き止めたら、何年もかけた苦労が水の泡だぜ！";
			link.l1 = "おい、全体像を見れば、すべてがだんだん筋が通ってきた気がするぜ。 スペイン訛りの誰かがデ・シェヴィウスにレジーナ号と黒真珠のことを話したんじゃねえかって、俺は思い始めてるんだ。 ";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "考えが同じだな。露見したスパイ網を利用するにはこれ以上ない方法だ。そんな高位の人物が絡む外交事件……それはイギリスとフランスの関係に深刻な打撃を与えかねない。あとは適切な情報を流して、 国際的なスキャンダルが起こるのを待つだけだ。もしかすると、 あの黒真珠の情報もわざと俺たちに流されたのかもしれねえな。";
			link.l1 = "あの忌々しいカスティーリャ野郎どもだろ？で、デ・シェヴィウスをどうするんだ？";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "正直に言うと、俺には全く分からない。もしこれがスペインの挑発なら、無視するのが賢明だろう。ただ、 あいつがどうやってレジーナのことを知ったのか、そしてスペイン植民地で我々 のネットワークにどれほど悪影響があるのかを調べなければならない。それに、俺はお前に命を救われた恩があるから、 必ずその借りは返すつもりだ。";
			link.l1 = "正直に言うぜ、バロネット。どんな助けでも欲しいくらいだ。もう必死すぎて、 マルキーズを誘拐することまで考えちまってるんだ。";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "お前も分かってるだろうが、これがド・シェヴィウスの尻尾切りのやり口だぜ？あの野郎、 レジーナ号の失踪も含めて全部お前に押し付けるのは簡単なことだ。だから、俺はこう提案する。 ボトー侯爵が言ってたが、ド・シェヴィウスは交換には出席せず、バステールに安全に留まるつもりらしい。 自分がどれだけ厄介な事態に巻き込まれたか気づいたか、何かを疑い始めてるのかもしれねえ。 まるで台所のネズミみたいに用心深くなるだろう。だからこそ、俺はお前と一緒にドミニカへ行くんだ。";
			link.l1 = "だが、奴の捕虜は俺の最優先事項だ。彼女の命を危険にさらすわけにはいかねえ！彼女は交換を待つ人質なんだ！";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "心配するな――俺がジャック・ディル・ド・パルケを問い詰めて、デ・シェヴァスの船の逮捕状を手に入れるさ。 あいつの部下どもは自分たちの置かれた状況を完全には把握していないだろう。そうでなければ、 あの真珠をもっと慎重に扱っていたはずだ。俺たちはロングボートで奴らのところへ行き、直接逮捕状を突きつけてやる。 ";
			link.l1 = "ああ、お前の強引なやり口は覚えてるぜ、旦那。でもそれは危険だ。しかも大きなリスクだぞ。";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "おっしゃる通りですが、俺の助けが欲しいなら受け入れてもらうしかないぜ。ドミニカでの用が済んだら、 バステールへ行ってリヨン総督にお前の敵を引き渡すよう要求する。俺の権限でそれができるんだ。 シェヴィウスに逃げられるわけにはいかねえ。";
			link.l1 = "本当にやる気かい、旦那？戦争が始まるかもしれねえんだぜ？";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "奴らがそんなことを許すはずがねえよ。俺たちはもう真実を知ってるんだ、絶対に無理だぜ。 政治なんて娼婦みてえなもんさ、船長。あんたのために、必ずde Chievousをイギリスの牢獄にぶち込んでやるよ。\nそれなら、あいつの親父ですら納得する静かな解決ってやつだろうな。";
			link.l1 = "お前の計画が気に入るとは言えねえが、他に手はなさそうだな。";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "必ずやり遂げると保証しよう。これから総督に会いに行き、部下たちに指示を出さねばならん。\nもし侯爵夫人を見かけたら、捜査に協力してくれた礼として真珠はそのままお持ちいただいて構わないと伝えてくれ。";
			link.l1 = "ありがとうございます、バロネット。私の船でまた会いましょう、すぐに出航します。";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "ウィリアム・コートニー、コートニー準男爵、あなたのために仕える者だ。\nイギリス帝国から与えられた権限と、信頼できる同盟国フランスの全面的な支持をもって、 あなたの船はこれより拿捕される。\nこれが書類だ。必ず目を通し、部下たちには武器に手を出さぬよう伝えてくれ。\n君は拘束されるが、まだ逮捕されたわけではない。\n愚かな真似をしなければ、最初の港で解放されるだろう。";
			link.l1 = "バロネット、俺は……俺の士官を取り戻さなきゃならねえ！";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "ご心配なく、船長、彼女は俺があなたの船まで送り届ける。今はロングボートに戻ってくれ。俺がこの船の指揮を執り、 バステールまで航海するつもりだ。宿敵を自分で嘲笑うつもりがないなら、遠慮なくここを離れてくれて構わない。ただ、 グアドループまで行くために何人か部下を俺に預けてほしい、それだけ頼む。";
			link.l1 = "承知しました、旦那。遠慮しておきます。あいつには最低の挨拶を伝えてくれ。では、改めてありがとう！";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "チャールズ、会えて嬉しいよ。お前が戻ってくることを願ってはいたが、本当に実現するとは思っていなかったぜ。";
			link.l1 = "同じく、バロネット殿。侯爵夫人にご挨拶に来られたのですか？ところで、彼女はどこにいらっしゃいますか？";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "まだ分かってねえのか？あの女は逃げたんだ。それと、アンジェラン・ド・シェヴューが心から謝罪してるぜ。 お前が最初からこの企みに関わってなかった、ただの被害者だって俺が説得したんだ。あいつ自身と同じようにな。 あの善人は手紙を書く気もなかったが、事の成り行きについては本当に申し訳なく思ってるらしいぜ。";
			link.l1 = "「深く反省している、だと！？何を言ってるんだ、旦那？」";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "お前と俺、肝心なことを見落としていたな。どうやってあいつは真珠のことを知ったんだ？ 誰があのスペイン人船長をこの家に招いた？誰があの野郎にそんなお宝を狙わせたんだ？";
			link.l1 = "本気か？そんなはずねえ…";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "間違いなくそうだ。マルキーズは見事に役を演じきり、あと一歩で全てをやり遂げるところだった。だが、 俺たちの調査のおかげで、俺は盗賊や海賊としてではなく、 まさに騙された被害者としてド・シェヴィウスに接触したんだ。彼は自分が何に巻き込まれたかすぐに気付いたが、 証拠がなくて独断で動くことにした。その後どうなったかは、お前も知っているだろう。";
			link.l1 = "「つまり、あれは全部マルキーズの仕組んだことだったのか？ デ・シェヴィウスはうかつな子供みたいにまんまと引っかかったんだな！」";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "その通りだ。情熱ってのはとても危険なものなんだぜ、チャールズ！あの夜、 この屋敷でお前が賭けをしたことを覚えているか？アンジェランは、マルキーズに後援を与えることで、 必要な証拠を引き出そうとしていた。確かに奴はイカサマをしたが、絶望的な情熱に何年も苦しみ、 最後には最悪の裏切りに遭って、追い詰められていたんだ！だが、お前が割って入り、自分を彼女の擁護者と名乗り、 その役目を果たした。ド・シェヴィウスは、お前と彼女が同じ考えだと思い込んだ。奴は、 お前が手に入れようとしていた航海日誌を渡さないために、お前に負けた船を盗みやがった。さらに、 お前の部下を利用して、彼女とお前――奴が信じるところの死敵同士――を争わせようとしたんだ。";
			link.l1 = "言葉も出ねえぜ！";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "これで分かっただろう、シャルル！マルキーズは頭が切れて、息を呑むほど美しく、しかも危険な女だ。どれだけ長い間、 ヌーヴェルフランスの一流の連中を手玉に取っていたのか、俺には分からねえ。何年もだろうな。まあ、 もうお前には関係ない話だ。再会できて嬉しかったぜ。でも、まだひっくり返す部屋が残ってるんだ、 この屋敷は広いからな。たぶん何も見つからねえだろうが、やれるだけやらなきゃな。\n別れる前にもう一つ。ほら、これを持っていけ。思い出の品だ。準備ができたら、お前のご婦人に渡してやるといい。 お前は本当に運がいいぜ、分かってるか？特にあの哀れなシェヴィウスと比べりゃな！";
			link.l1 = "おっしゃる通り、そうです。では、ごきげんよう、ご武運をお祈りします、バロネット！";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "今日はなんていい天気だな、船長？あんたの武勇伝は聞いてるが、まさか普通の海賊だとは思わなかったぜ。 あんなことをしでかしておいて、よくもまあセント・ジョーンズに来やがったな、ふてえ野郎だ！";
			link.l1 = "俺が海賊なのは確かだ、旦那、だが俺が馬鹿に見えるか？ なぜわざわざマーキュリー号を襲ってスペインの真珠を奪った後にここへ来るってんだ？";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "認めよう、今こうしてお前と話しているのは、その理由だけだ。さもなければ、 もうとっくに首吊り縄にぶら下がっていたはずだぜ。\nいいか、この件には俺たちが隠していた小さな事実がある。\nお前から見つけた真珠のことじゃねえ。問題は、あのブリガンティンの名前だ。";
			link.l1 = "「どういう意味だ？」";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "伝令用のブリガンティン船レジーナ号は、過去二年間サンホセ港に配属されていた。\nその船長は我々のために情報を集め、さらにあらゆる雑用もこなしていた。\n公式には、彼女が運んでいた外交郵便が失われたという名目で捜索している。\n正直、あまり巧妙な口実ではない。\nだが、船長の船室をきちんと調べなければ、その船の本当の名前を知ることはできなかっただろう。";
			link.l1 = "俺は今まで何も見えてなかったが、今ははっきり分かるんだ。どうか聞いてくれ、旦那、説明する！";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "もっと頑張れ、船長。お前の命がかかってるんだぜ。";
			link.l1 = "俺はこのスパイ話には全く関係ねえ！スペイン人も同じだ。お前のネットワークは安全だ、心配すんな。だがな、 どこかから情報が漏れて、誰かがそれを利用したんだ。それで、俺はそいつと揉め事になっちまった。 そいつがマーキュリーの取引に関わってる証拠を見つけて、それを使って奴を出し抜こうとしたんだ。";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "神よ、証人になってくれ、俺はこの件をただの海賊行為だと思っていたんだ、 まさか王冠の諜報部が関わっているなんて想像もできなかった！俺の手元にあるのはこの真珠だけだが、 もっと手に入る場所と時はよく知っているんだ。";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "ジョン・サーローの名を聞いたことがあるか？王室諜報部の長だ。いつか俺はロンドンに行き、 マーキュリー号の運命について直接彼に報告するつもりだ。\nだから、お前のその哀れな敵の名を教えろ。";
			link.l1 = "アンジェラン・ド・シェヴー、ルヴィ・ヴァンタデュール伯の私生児だ。\nあいつはマーキュリー号をただの略奪品運搬船くらいにしか思ってなかったんだろう。\n真珠のことは知ってたかもしれねえが、イギリスの諜報との繋がりまでは知らなかったはずだ。";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "期待を裏切らねえな、船長！さすがだぜ！こんな面白い娯楽と敵を選ぶとはな！\nよし。他に真珠以外の証拠はあるのか？";
			link.l1 = "ド・シェヴィウスはフリゲート艦を持っている。俺もかつてその船の持ち主だった……たった一晩だけだがな、それでも少しは学ぶことができた。あいつはとんでもなく几帳面な男だぜ。 マーキュリー号への襲撃については、やつの航海日誌を見ればすべて分かるはずだ。 賞金の一部もまだ持っていると俺は確信している。もし複数あったなら、もっと黒真珠を持っているかもしれねえな。";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "一つや二つじゃねえぜ、それは間違いねえ。 俺たちはただのありふれた真珠のためにレジーナ号を危険にさらすようなことは絶対しねえよ。 あんたも分かってると思うが、どうしてもド・シェヴュー旦那と話さなきゃならねえんだ。真珠なんざどうでもいいが、 漏洩のことをもっと知る必要がある。上司たちは、俺が全貌を報告できなきゃ俺を地中に埋めちまうだろうからな。";
			link.l1 = "お会いできるよう手配してもいいが、急がねばならん！ 今まさにド・シェヴィウスのフリゲート艦がグアドループへ向かっているところで、 そこの現地総督の庇護下に船主が滞在しているんだ。やつは自分のやったことに気づいているはずだし、 できるだけ早く新世界から逃げ出すつもりだろう。";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "「これは非常に重大な人物に対する、極めて深刻な告発ですよ、船長。あなたは…どれほどの大騒動が後に巻き起こるか、分かっていますか？同盟国の旗を掲げた船への賊の襲撃――これは二つの大国の関係を著しく複雑にしかねません。彼があなたの神経をどれほど逆撫でしたのか、 そこまでの危険を冒すほどとは、私には到底想像できません。」";
			link.l1 = "あいつは俺から何かを奪ったんだ、旦那。俺が命よりも大事にしているものをな。絶対に取り戻さなきゃならねえ。 たとえそれが戦争に繋がろうと、俺は国のためにその旗の下で戦うだけだ。それでも、 デ・シェヴィウスには報いを受けさせる。すべての責任はあいつ一人にあるんだ！";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "誰かあなたに言ったことがあるかい、船長、あなたはとんでもなく危険な男だと？ 目的のためなら世界の半分を戦争に巻き込む覚悟があるのか？いいだろう、あなたのやり方に従おう。 バステールへ一緒に行くよ。こんな手がかりを見逃すわけにはいかない。証拠を記録するために書記を送ろう、 私は自分の船の準備をする。";
			link.l1 = "ありがとうございます、旦那。しかしここでぐずぐずしている時間はありません、警告しておきますよ！";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "ド・モール船長、俺たちは間に合うさ、あんたを信じてるぜ。だがな、この冒険がうまくいかなかったら……わかるだろ？ちゃんとした墓すら約束できねえんだ。";
			link.l1 = "はい、旦那様。完全に理解しております。";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "賽は投げられたぞ、船長。俺はアンジェラン・ド・シエヴスに会見を要求した。 奴のフリゲートは到着次第すぐに捜索される。フランソワ・ド・リヨンは疑っているが、 俺の書類の封印が今のところ奴を抑えている。事態が収まるまで町に留まっていてくれ。";
			link.l1 = "かしこまりました、旦那様、承知いたしました。";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "それなら、これも理解してくれるといいんだが。あそこの旦那方に剣を渡して、約束を守ると俺が確かめられるように、 彼らについていってくれ。";
			link.l1 = "信じられない……コートニー卿、本気なのか！？";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "本気だ。お前はいまだに俺の主要な容疑者の一人だし、この状況でお前を逃がすなんて俺の大馬鹿ってもんだ。 もしお前の言葉が本当だと証明されたら、その時は俺がふさわしいと思うやり方で謝罪してやるさ。";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "ごきげんよう、de Maure様。参りましょうか？";
			link.l1 = "喜んで、で、ルールは何だ？正直言うと、食い物に夢中で条件を聞き間違えたかもしれねえ。";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "ルールは簡単だ。1枚につき1万ペソ、どちらかが降参するまで勝負だぜ。領収書や掛け売りは受け付けねえぞ。";
			link.l1 = "俺は構わねえ。やろうぜ、大佐。";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "くそっ！もう二度とやらねえ！まあいい、ド・モール旦那、次の勝負で幸運を祈るぜ。";
				link.l1 = "喜んでお受けしました、大佐。では、ごきげんよう。";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "よく戦ったが、運命の女神は別の思惑があったようだ。さらばだ、ド・モール旦那。対局、感謝する。";
					link.l1 = "ああ、今回は自分を過信してたみたいだな。さよなら、カーネル。";
				}
				else
				{
					dialog.text = "あなたは勝負を放棄し、敗北を認めたのだな！勇敢に戦ったが、運命は味方しなかった。さようなら、ド・モール旦那、 そして対局に感謝する。";
					link.l1 = "ああ、今回は自分を過信していたようだ。さようなら、Colonel。";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "「シャルル・ド・モール船長、なんてこった、まさかお前に会うとは！」";
					link.l1 = "船長。モレノだと？ふざけやがって！何の用だ、ここに来たのは！？";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "「シャルル・ド・モール船長、どうもよろしく。」";
						link.l1 = "以前会ったことがあるか、モレノ旦那……？";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "「チャールズ・ド・モール船長、光栄です。」";
						link.l1 = "以前に会ったことがあるか、旦那…Moreno？";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "シャルル・ド・モール船長、光栄です。";
				link.l1 = "俺たち、以前に会ったことがあるか、旦那…Moreno？";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "長い話になるぜ。いつも通りだよ、船長。お前の目を見りゃ、疑問があるのは分かる。静かにして、 ただの水夫をからかってるふりをしとけ。";
			link.l1 = "ああ、この洒落た服、よく似合ってるぜ、俺の素朴な友よ。着こなし方をわかってるじゃねえか。";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "運が良ければ、たまにだけだ。今日はその日だぜ。賭けてみようじゃねえか、船長。皆が見てる、 待たせるのは礼儀じゃねえぞ。\n";
			link.l1 = "そうだな、話は後にしよう。取引だ……モレノ船長、頼むぜ。";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "お前のことは少し知ってるが、そんなの関係ねえ。カードを配れ、ド・モール船長。みんな見世物を期待してるぜ。";
			link.l1 = "興味深いな。特にお前のスペイン訛りと、ボトー夫人の推薦が気になる。よかろう。海の男同士、 勝負といこうじゃねえか！";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "ちゃんと覚えてるぜ。お前と俺の元船長がル・フランソワで俺の仲間を串刺しにした時のことをな。あの野郎は結局、 自業自得だったがな――お前の助けもあったと記憶してるぜ。だが感謝なんざ期待するなよ。お前はフランツ・ガルケを殺した、 俺はそれを絶対に許さねえ。";
			link.l1 = "ポルトガル人の四分士か？血塗れのドンだろ？今夜はどんどん面白くなってきたぜ。やってやろう！";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "これ以上の勝負を断ったということは、負けを認めたってことだな！運命の女神様が口を挟んだってわけか。じゃあな、 船長。";
				link.l1 = "同様に、モレノ旦那。ゲームをありがとう。";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "運命の女神が口を挟んだようだな。さらばだ、船長。またどこかで会うかもしれねえな。";
					link.l1 = "同様に、Moreno旦那。ゲームをありがとう。";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "運命の女神がもう決めたようだな。さようなら、船長。また違う状況で会うこともあるかもしれねえな、へっへっ。";
						link.l1 = "楽しみにしているぜ、Moreno旦那。";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "それで決まりだ。運命が決めたんだ、船長。さらばだ。";
						link.l1 = "さようなら、Moreno旦那。";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "それで決まりだ。運命が決したぞ、船長。さらばだ。";
				link.l1 = "さようなら、Moreno旦那。";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "お会いできて嬉しいですわ、de Maure船長旦那！正直申しまして、何が来てもおかしくないと覚悟しておりましたの。衛兵の一団でも驚きませんでしたけれど、 まさかあなたご本人がいらっしゃるとは思いませんでしたわ。";
			link.l1 = "モレノ旦那、地元の役人たちと何か揉め事でもあるのかい？それと、俺も会えて嬉しいぜ、ははっ！";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "おいおい、あの女主人の招待を断るなんてできねえよ。少なくとも、ああいう誘いはな。\nさあ、チャールズ、茶番はやめろ。マルキーズは俺の正体を知ってるって、ちゃんと俺に伝えてきたんだ。";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "奥様、あなたは本当に魅力的ですわ！このあなたの新しいご友人は、以前私を一度裏切ろうとしたことがございますの。 でも、実のところあまりうまくいかず、むしろ彼には何度も命を救われて、その回数ももう数え切れませんわ。とにかく、 今は私が彼に借りがあるので、脅しなんて必要ありませんのよ、ご心配なく。";
			link.l1 = "感謝するぜ、バルトロメウ。アンジェラン・ド・シヴーに追い詰められて、俺はとんでもなく苦しい立場にいるんだ。 どうしてもあいつを倒さなきゃならねえ。俺にとって…とても大切な人の命がかかってるんだ。信じてくれ、今回は何があっても俺は止まらねえ。";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "もういいだろう、船長、俺たちは仲間じゃねえか？群島の半分を横断したあの競争を覚えてるか？ あれは俺にとって大きな意味があったんだ。できる限り力になるぜ。マーキュリー号のことは聞いたことあるか？";
			link.l1 = "さて、あれは何だ？船か？";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "正確に言えば、イギリスのブリガンティンだ。任務は、 ドイル大佐の私掠船団が西インドのスペイン真珠採掘場を襲撃して奪った戦利品を運ぶことだった。伝説の黒真珠を時々 狙う連中だ、聞いたことあるか？俺の情報源が確かなら、その黒真珠がいくつかマーキュリー号に積まれていたらしい。 一か月前、マルティニークとグアドループの間で待ち伏せして、あの紳士たちを待ったんだ。だが無駄だった！ 一週間も海で粘ったが、結局失敗を認めざるを得なかった。";
			link.l1 = "そうか、つまりお前の情報源は結局あてにならなかったってわけだな、自分の取り分もなしってことか。で、 ド・シェヴィウスがこの件にどう関わってるんだ？";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "俺も同じことを考えてたんだが、マーキュリー号がアンティグアに現れなかったと知って驚いたぜ。さらに驚いたのは、 あの船がキュラソー近くで目撃されたってことだ。マルティニークの近くを俺の目をかいくぐって通れるはずがねえのに。 イギリス野郎どもは激怒してるぜ！あんなお宝を取り逃がしたんだからな！ともかく、俺は興味が湧いて調べ始めたんだ、 みんなの楽しみを台無しにした特別な奴についてな。あんな戦利品はすぐに売りさばけるもんじゃねえ。 だからル・フランソワに行って、あの野郎を見つけて俺の取り分を取り返してやろうと思ったのさ。\n";
			link.l1 = "お前の話、どこかで聞いたことがあるぜ。「カルマ」って言葉を知ってるか？ お前は自分から厄介ごとを呼び寄せる才能があるみたいだな。だが、それが俺にどう役立つのかは、まだ分からねえな？";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "焦るなよ、船長、これから話の一番面白いところを教えてやるぜ。 あんたのその小綺麗な格好してるくせに風呂に入ってなさそうな友達――あいつの手下どもが、地元の店に上等な真珠を派手にばら撒いていったんだ。スペイン産の真珠の山を、 惜しげもなく大量に使い果たしてな。";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "「聞いたかい、船長？」";
			link.l1 = "お前はド・シェヴィウスが“親切者ジャック”とその仲間から盗まれた真珠を買ったと思うのか？俺はな…これじゃ足りねえと思うぜ。";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "そうだぜ、船長。あいつは買ってたんじゃなくて、売ってたんだ！この件についてバルバゾンと話したら、 あいつは自分の仲間から大量の完璧な真珠を買ったって認めた。その後、それをヨーロッパに送ったらしい。それに、 あのネックレスの黒真珠もあるし、ド・シェヴィウスの船が修理されたって事実もある。作業員たちが言うには、 あのフリゲートには十二ポンド砲の穴が空いてたそうだ。正気の奴なら、 そんな小さな砲でフリゲートに攻撃なんてするか？";
			link.l1 = "俺たちのブリガンティンのことみたいだな！それに、 ド・シェヴィウスが自分のフリゲートがどれだけ速いか自慢してたのも覚えてるぜ。\nだが、なんでこんな無茶を？今はイギリスと和平中だろ、そこまで危険を冒して何のためだ？ 黒真珠は確かに極めて珍しいが、手に入らないわけじゃねえ。";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "「そこが奴の失敗だったんだよ！イギリス人どもはすでにマーキュリー号の失踪について公式な調査を始めてる。 あいつらは重要書類を積んだ使者船が行方不明になったって言ってるがな。 手がかりを持ってる奴にはたっぷり褒美を出すし、関係者は厳しく罰するってさ。一番面白いのは、 特別な貴族役人をアンティグアに送り込んで、そいつが今も必死に事件を掘り下げてるってことさ。名前は思い出せねえ――あの偉そうなツラと同じくらい気取った名前だったが――まあ、俺を追ってないだけマシだな！」\n";
			link.l1 = "そりゃ面白いな！あいつらは黒真珠を相当欲しがってるみたいだぜ。マーキュリー号には一体いくつ積んでたんだろうな、 それにこの情報が俺にどう役立つか……？";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "なに、あのクズ野郎がマルキーズ様まで怒らせたのか？忌々しい奴め！この件でも俺はあんたの味方だぜ、 ド・モール船長！バルトロメウ・ポルトガル人から戦利品を盗むなんて、誰にもできやしねえ！";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "こんなに話した後は、ちゃんとした酒が欲しいぜ。マルキーズ、今や俺たちは友達だしな……";
			link.l1 = "この家にはラム酒なんて置いてねえと思うぜ、バルトロメオ。";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "ああ、そうだな、あのイギリスの調査官の注意をあいつのフリゲート艦に引きつけろってか！これが俺たちの作戦なら、 俺はもう昔馴染みのド・モール船長だなんて認めねえぞ！";
			link.l1 = "笑うかもしれねえが、それが計画だ。お前たち二人の協力が必要なんだ。\n奥方、あんたは俺が雇った海賊の囚われの身になる――バルトロメオ、それがお前の役目だ。";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "俺のこの悪事についてもだ！バルトロメウ・ポルトガル人は女をさらったことなんて一度もねえぞ！";
			link.l1 = "奴はそうしないが、デ・シェヴィウスの連中にはそう見えるだろう。それに、お前の名前を奴らに教える必要もない。 あのご婦人を船に乗せて、スコット岬近くでアンジェランのフリゲートと会え。 ジュリアンナを俺の士官と交換してマルティニークに戻るんだ。\nそれから侯爵夫人と俺を待て。";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "これは本当に面白かったし、お前は生まれついての騎士だな、チャールズ。\nだが、取引の後でどうやって彼女を返せばいいんだよ？";
			link.l1 = "俺がやる。時間がないから手分けしよう。お前と侯爵夫人はドミニカへ行け、俺は急いでセント・ジョンズへ向かう。 ドイリー大佐かあのイギリスの調査官を見つけて、マーキュリー号失踪の責任者を伝えるつもりだ。";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "こんな事件の後に必ず巻き起こる大騒動について、考えたことはあるのか、船長？今のアンティグアはまるで蜂の巣だぜ、 そこに石を投げろって言うのかよ。これより小さなことで戦争が始まったのを俺は覚えてるぞ！";
			link.l1 = "一度に一つの問題だ……どんな犠牲を払っても彼女を取り戻す！デ・ルヴィ・ヴァンタデュールが噂通りの大物なら、 自分の尻拭いくらい自分でやらせればいいさ！それに、 デ・シェヴィウスもマダム・ボトがどうして自分の船に乗っていたのか、説明に苦労するだろうな。\n";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "準備はいいか？祈りを捧げて！マルキーズ、誘拐される覚悟はできているか？";
			}
			else
			{
				dialog.text = "準備はいいか？祈りでも捧げるか！マルキーズ、荷造りにどれくらいかかるんだ？";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+"、ド・モール旦那。私の名は "+GetFullName(npchar)+"、そしてこれが "+GetFullName(characterFromId("GG_SecundantGG_2"))+"。閣下が我々に、ムッシュ・ド・シェヴーとの決闘を見届けるようお頼みになりました。";
			link.l1 = "こんばんは、諸君。今夜は何事もなく、誰も死なないことを願っている。しかし、 念のため何が起きてもいいように備えておけ。この「紳士」とやらが期待外れかもしれんからな。";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "お前の不安は根拠がない。この決闘の事前の取り決めによれば、どんな状況でも立会人が介入することは許されていない。 \nだが、警告してくれて感謝する。相手が到着した。幸運を祈る、船長。閣下から伝言だ――あなたの…慎重さのために祈るそうだ。";
			link.l1 = "きっと大いに役立つだろう。\nまあ、とにかく始めよう。";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "船長、問題だ。俺たちの船が……その、消えちまったんだ。";
			link.l1 = "待て、なんだと！？どうやって、誰が？あの船には見張りが丸ごと配置されてたはずだろ、いったい何を言ってるんだ！？ ";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "いや、船長、船のことじゃねえ。あいつはピカピカだ。昨日お前さんが手に入れたフリゲートさ、 今じゃ俺たちのもんだろ？あそこには賞金船の乗組員をたった12人送り込んだだけだ。あの女がそれで十分だって言ってたぜ。";
			link.l1 = "とにかく黙って最初から何があったのか全部はっきり話せ！";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "分かりませんぜ、船長。フリゲート艦は朝霧の中で出航しました。見張りが艦の不在に気づいたのは、数時間後、 霧が晴れた時でした。";
			link.l1 = "そんなはずがない！あいつが俺にこんなことをするわけがねえ！でも…くそっ、つい最近ケンカしたばかりだ。まさか、あいつが…";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "もっとひどいことになってるかもしれねえ、船長。今朝早く、 漁師たちが戦利品の乗組員だった俺たちの仲間二人を見つけたんだ。どっちも喉を切られて死んでたぜ。";
			link.l1 = "くそったれの悪夢だ！ド・シェヴィウスの野郎！俺が侯爵夫人とやってる間に、あいつが船を盗みやがった！ あの女が無事でいてくれりゃいいが……もし髪の毛一本でも傷つけられたら、俺は……";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "「準備するように野郎どもに命令してくれるかい、船長？二時間後には出航できるぜ。今朝からみんなピリピリしてる、 特にあんたの副官がな。あいつ、あとを追って出航しそうになるのを、なんとか止めたんだ。」";
			link.l1 = "それはまだ早すぎる。俺は……ちゃんと考え直して、誰かと話さなきゃならねえ。そうだ！船を準備しろ！全員に準備させておけ、 俺が戻ったらすぐに出航するぞ。";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "ド・モール船長、何が起きているんだ？誰かが奥様を襲ったのか？";
			link.l1 = "ここに来るべきじゃなかったんだ。\nまあ、神に誓って、俺はこんなこと望んじゃいなかった。";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "旦那、あなたがここに来てくれるとは、ほとんど諦めかけていましたよ。\nあなたのロングボートにボトー侯爵夫人がいるのが見えます。どうしてそうなったのかは、あえて聞きません。\nあなたの仲間が待っています。彼女は無事です、連れてさっさとここから立ち去ってください。";
			link.l1 = "もしあの娘に手を出したら、てめえのオンボロ船をバラバラにしてやるぞ！";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "なんとまあ、思いがけないご配慮だな。心配はいらねえ、あの女はまるで囚われの女王みてえに扱われてたぜ。 お前の脅しなんざ俺には通じねえ。ちなみに、シュヴァリエ・ド・シェヴィウスがよろしくと言ってたぞ。";
			link.l1 = "あいつの伝言なんざクソくらえだ。俺の……士官はどこだ？取引を始めようぜ。";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "旦那、あなたがここに来てくれるとは、もうほとんど諦めかけていました。\nあなたの仲間が待っています。彼女は無事ですよ……待て、こいつは一体誰だ？侯爵夫人はどこにいるんだ？";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "旦那、剣を渡してもらおう。\nふざけた真似はやめとけよ、うちの連中は最近ピリピリしてるんだ。\n鉛玉を食らいたくはねえだろ？";
			link.l1 = "本気か？まあ、持っていけよ、でも丁寧に扱え、あんたの兵舎より高いんだぜ。コートニー男爵閣下との面会を要求する！ ";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "心配するな、きっとあいつも時間を作ってお前に会いに来るさ。";
			link.l1 = "誰かを助けようとするとき……";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "俺も気に入らねえよ、旦那。しかし、残念ながらこの生意気なイギリス野郎は権力があって、 リヨン旦那ですらどうにもできねえんだ。申し訳ねえが、船長、剣を渡してくれ。";
			link.l1 = "ムッシュ・ド・シェヴーと同じ牢に入れられないことを願うよ。\nさあ、旦那方、俺はもうくたくただ。\nやっと眠れるな。";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "失礼するつもりはないが、旦那、今は話している暇はねえんだ、見ての通りだろう。何も見逃したくねえんだよ！";
			link.l1 = "かしこまりました、旦那。";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "今夜は歴史に残る夜になる、そんな気がする！ここからヴェルサイユまで、この話題で持ちきりになるだろう！ 私のマリアンヌもきっと大喜びで、すべての詳細を知りたがるはずだ。どうか、旦那、どいてください、 私の視界を遮っています。";
			link.l1 = "もう行くぜ、旦那、ショーを楽しんでくれよ。それと、忘れられないマリアンヌによろしく伝えてくれ……誰だか知らねえがな。";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "ははっ！さて、ここにムッシュ・ド・モールがいるじゃねえか！失礼……シャルル・ド・モール船長！どうぞおかけください、ここには素晴らしい旧世界のワインが揃っております。\n今宵の始まりはどうなさいますか？新しいものなら、我らが愛するジロンドの岸辺から届いたカベルネ・ソーヴィニヨン、 あるいは時を超えた定番、イタリアのサンジョヴェーゼはいかがでしょう？";
			link.l1 = "ありがとうございます、旦那、あなたと飲みますが、少し後にしましょう。";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "おお、ド・モール船長！もう一杯ワインはいかがですか…ひっく？見てくださいよ、今出されたばかりのワイン――ローヌ渓谷北部の丘から届いた、1643年のシラーですぜ。こいつは、くそっ、本物の逸品だ！しかも、その年は何もかも最高だったんだ…ガット岬でスペイン野郎どもを打ち破っただけでも価値があるってもんだ！ところで…なんでみんなあんなに騒いでるんだ、知ってます？誰か具合でも悪いのか？まあ――どうでもいいか、乾杯…";
			link.l1 = "まあ、少なくとも誰かはこのご馳走に感謝してくれるんだな。さようなら、旦那。";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "ああ、シャルル・ド・モール船長、あなたの噂はこの街の誰もが知っていますよ！自己紹介させてください―― "+GetFullName(npchar)+"、お会いできて大変光栄です、本当ですよ！本当に我々の総督と親しいのですか？紹介していただけますか？ ぜひ彼に最大限の敬意を表したくて…";
			link.l1 = "また今度な。良い夜を、旦那。";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "モール旦那、これを見ましたか！？我らが名高い総督とシェヴー旦那ご本人が――ここで殺し合うかと思いましたよ！壮観でした！ボトー侯爵夫人は今日は本当にやってくれましたね――全てがたまらなく刺激的です！続きが待ちきれません。\nところで、今こそ絶好のタイミングでは？紹介してくれると約束してくれましたよね… ";
			link.l1 = "何も約束した覚えはねえな。悪いが、もう行かなくちゃならねえ。";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "モール旦那、ついに才女ボトー夫人のサロンにお越しになりましたね！ 彼女はすでに何度かあなたに会いたいとおっしゃっていましたよ。彼女の「弟子」たちを評価することはできましたか？ ええ、侯爵夫人のような星々は、あなたや私のような凡人には手の届かない存在です。しかし信じてください、 このご婦人方はまさに芸術品です。驚嘆すべきほどではないかもしれませんが、それでも――ミケランジェロや、そうですね、ティツィアーノのようなものです。";
			link.l1 = "興味深い比較ですね、旦那。では、あなたに夜を楽しんでもらいましょう……";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "いや、ここはいつも賑やかだが、今は大きなスキャンダルの匂いが空気に充満しているのを感じないか？ ジャクリーヌ嬢が上の階で私を待っているのに、どうしても賭博台から離れられないんだ！ 旦那様とシェヴュー旦那は手強い相手で、闘志も並々ならぬものがある。今夜の賭けは星空どころか、 天蓋を突き破って悪魔の元まで飛んでいきそうだぞ！\n";
			link.l1 = "悪魔どもは下におります、旦那。天の大空の向こうにはきっと天使たちがいるのでしょう。";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "まあ、少なくとも一つは楽しい出会いだな！俺たちはすでに会っているんだぜ、ド・モール船長。もっとも、 あんたは覚えていないかもしれねえが。 "+GetFullName(npchar)+" －俺は駐屯地第六歩兵中隊の隊長だった。お前と一緒にこの街の通りでスペイン野郎どもと戦ったんだ。正直に言えば、 膝に弾を食らって、戦いのほとんどをこの娼館が燃えるのを溝の中から眺めて過ごした。\nそして今またここにいる――またもや内戦だ。そしてまた俺はそれを眺めている、だが今度は中からだ。";
			link.l1 = "お会いできて嬉しいです、旦那。あの日は本当に暑かったですが、正直に言うと、 それ以来この場所はずっと美しくなりました！";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "ここはどうだい、船長？この俗物どもは血まみれの騒ぎを起こすつもりらしいぜ！知りたいもんだな、 総督の椅子もカード賭博みたいに賭けられるのか？俺の言葉を覚えとけ――最後は剣で決着だ。残念だが、この膝じゃもうそういう遊びは無理だな。そういえば、 どこかでジャクリーヌを見かけたぜ――あの旦那は今の騒ぎにどっぷり巻き込まれてるみたいだ……まあ、ここがまだ静かなうちに、俺も運試しに行ってみるとするか。";
			link.l1 = "良い決断だな、成功を祈るぜ、旦那。さて、俺は……ワリーズに戻らなきゃならねえ。";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
