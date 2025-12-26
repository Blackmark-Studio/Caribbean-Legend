// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何だい？";
			link.l1 = "いいえ、何でもないよ。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "助けてくれてありがとう、船長！";
			link.l1 = "なんてこと……想像していたより、あなたはずっと美しい！";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "美しさなんて、くそくらえだよ！この顔のせいで、どれだけ苦労したと思ってるの？名誉さえ傷つかないなら、 自分の鼻だって切り落としてやるさ。あの野郎、私をコルベットから生きて出させる気なんてなかった、「知りすぎてる」 って何度も言われたよ。昨日なんて、もう待ちくたびれたから無理やり自分のものにするとまで言い出して……\nあなたが来てくれて、本当に助かったよ！でも、自己紹介が遅れたね。私はヘレン・マッカーサー。パパは私のことを 「ルンバ」って呼んでたんだ。せっかく手に入れた高価な食器を、私がよく割っちゃってたからね。それで今じゃ、 乗組員もみんなそう呼ぶんだ。";
			link.l1 = "私の名前は "+GetFullName(pchar)+" それで、あんたを助けに来たんだよ。数日間カリブ中を探し回って、グラディスさんのためにあんたを探してたんだ。";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "グラディスさん！？彼女はどうしたの？";
			link.l1 = "あんたのことが心配でたまらなかったよ。\nでもすぐに彼女に会えるさ、これからブルーヴェルドへ向かうんだから。\n道中で、あんたに何があったのか全部聞かせてくれよ。";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "「正直に言うと、」 "+pchar.name+"今は何か食べて、少し眠りたいわ。あの化け物みたいな船で何日も過ごして、もうくたくたなのよ……";
			link.l1 = "もちろんです、マッカーサーさん。執事に食事を用意させ、あなた専用の個室に寝床も整えさせます。";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "ド・モール船長、改めて心から感謝します。あなたの迅速な救出に救われました。ぜひ、 あたしと母の家にいらしてください。家はここからそう遠くありません、桟橋から来て左手にあります。それと、 もう一つ知っておいてください\n "+pchar.name+"、何も言わずに出航したら絶対に許さないからね！";
			link.l1 = "光栄でしたよ、マッカーサー嬢。また必ずお伺いします！";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "ああ、やっと見つけた、ド・モール船長！来てくれて本当に嬉しいわ、あなたに聞きたいことがたくさんあるの。";
			link.l1 = "申し訳ありません、マッカーサーさん、ですが少しだけお話を延期させてください。納得のいく答えをお伝えするには、 もう少し情報を集める必要があります。\n今は、どうか通りに姿を見せないようにお願いします。お待たせする時間が長くならないことを願っています。\nどうか私を信じて、お待ちください。";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "「寄らなかったら許さないって、自分で言ったじゃない。」";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "ああ、やっと見つけた、私のキャプテン！その目つき、何か知らせがあるんだね！";
			link.l1 = "スヴェンソン船長から、あなたが私と一緒に航海したいと聞きました。あなたの関心に感謝しますし、 グラディスさんもあなたが海を恋しがっていたと話していました。ようこそ、マッカーサー嬢！";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "スヴェンソン船長から、あなたが私と一緒に航海したいと聞きました。あなたの関心に感謝しますし、 グラディスさんもあなたが海を恋しがっていたと話していました。私の乗組員へようこそ、ヘレン・シャープさん！";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "アイアイサー、船長！言いたくはないんだけど、旦那、あたしは自分の身は自分で守れるし、 男たちの無礼は絶対に許さないよ。手首が飛ぼうが、目玉がえぐれようが、あたしのせいじゃないからね。";
			link.l1 = "心配しないで、私の船では揺るぎない規律があるの。\nでも、ひとつ聞きたいことがあるんだけど……";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "……はい？";
			link.l1 = "ヤン・スヴェンソンと私は、あなたがイスラ・テソロの正当な後継者だと突き止めたんだ。\nそう、本当だよ、首を横に振らないで！\n私はその証拠となる地図の半分を持っている。\n簡単な道のりじゃないけど、ヤンと私はあなたが正当な所有者になれるよう全力で助けるつもりだよ。";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+"、本気なの？そんな、可哀想な女の子をからかうなんてひどいよ！あたしが島一つを所有する権利なんて、 どうして持てるっていうの！？";
			link.l1 = "私は本気ですよ、マッカーサーさん。あなたが本来の権利を取り戻すのを、私が手伝います。さあ、 今すぐ出航しましょう！";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "な、なんですって？ヘレン・シャープ？なぜシャープなんだ？";
			link.l1 = "エレン、君はベアトリス・シャープの娘であり、シャープ家の唯一の後継者だ。 これはグラディスさんが長年守ってきた地図の半分だよ。君がイスラ・テソロを継ぐ正当な証拠だ。簡単な道じゃないが、 ヤン・スヴェンソンと俺で、君が祖父の島を継げるよう全力で助けるよ。";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			Notification_Approve(true, "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "ああ……かわいそうなお母さん！いつかお墓を見つけて、そこで魂のために祈りたいわ。でも……待って！そんなはずない！";
			link.l1 = "どうしたの、シャープ嬢？";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "ジプシー女の予言が今まさに現実になった……やっと今、その意味がわかったよ。";
			link.l1 = "え？どんな予言？";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+"、あたしのことを世間知らずだと思うかもしれないけど、それでも話すわ。あたしがまだ少女だった頃、 ジプシーの女がこう言ったの――『お前の運命は、未亡人のコインを受け取らず、死者の金を返し、母の名を口にする男の手に委ねられる』って。\n当時は全部馬鹿げた話だと思ってたけど、どういうわけか、あなたはその予言を全部叶えてしまったのよ。そんなこと、 あなたが知ってるはずがないのに！";
			link.l1 = "「運命、ですって……まあ、あなたの言う通りかもしれないわね。期待は裏切らないわ。一緒にあなたのお母様のお墓を探しましょう。さて、 今は……ヘレン・シャープ嬢！出発の準備をして、遅れないで！」\n";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "了解だよ、船長！";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Captain "+pchar.name+"！いい考えがあるんだ…";
			link.l1 = ""+npchar.name+"？ここは危険だよ、だから船にいるように言ったでしょ…";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "シャルル、この古い船には火薬がぎっしり詰まってるんだよ。もし爆発したら、島ごと聖ペテロの玄関まで吹っ飛ぶよ！ あんたが隠れろって言おうが言うまいが関係ないんだから、あたしの話を聞きな！";
			link.l1 = "いいわ、早く話して！";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "コルベットとフリゲートだ。あいつらはナイフの船を敵だと認識していない。その油断を逆手に取れるよ。 火薬樽をいくつか持ち出して、導火線を仕掛けて船に近づこう\nあいつらは近づかせてくれるから、導火線に火をつけて、樽をどちらかの船に落としたら、できるだけ速く離れるんだ。 そして壮絶な爆発を見物しよう……どう思う？";
			link.l1 = "即席の火船か……なんて狡猾なの！あなたの計画は無茶だけど、うまくいくかもしれない……もし私たちが気付かれずに十分近づければね。";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "失うものなんてないよ "+pchar.name+"？二隻同時に戦うのは簡単じゃないけど、形勢を立て直すチャンスはきっとあるよ……";
			link.l1 = "よし。さっさと始めようぜ！野郎ども！火薬樽を三つ持ってこい！ここからぶっ飛んでやるぞ！あんたの想像力、 大好きだよ。 "+npchar.name+"…こんな考え、あたしには絶対に思いつかなかったよ。";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "ああ、船長、どうしたんだい？";
			link.l1 = "ジャックマンの船はサボ＝マティラ入り江に停泊している。重フリゲート艦『センチュリオン』だ。 この船はかつてホークス家のものだったから、ジャックマンの船室にはきっと重要な品や書類があるはず……乗り込まなきゃ。";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "言うは易く行うは難し、だよ。あたしたちのポラッカ船でどうやってやるつもり？向こうは人数も火力も上なんだよ。";
			link.l1 = "その通りだよ。ジャックマンの手下は少なくとも私たちの倍はいるし、しかも全員が剣の達人だ。 事前の砲撃なしで攻め込むなんて無謀だよ。でも、長引く戦いも得策じゃない。だから、 どうするべきかずっと考えていたんだ。";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+"…まだ敵だと気づかれていないよ、トルクスの馬鹿どもと同じでさ…もう一度あの手を使ってみよう…";
			link.l1 = "エレン、さっき言っただろう、俺たちはあのフリゲートに乗り込んで捜索しなきゃならないんだ。 ぶっ壊すなんて選択肢はないぞ。";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "「ちょっと待って、」 "+pchar.name+"、沈めはしないさ。ちょっと趣向を変えよう。\nいいか、空のラム樽をいくつか用意して、それに火薬とブドウ弾、それから短い導火線を詰めるんだ。 それからあいつらのフリゲートにもっと近づいて、その即席爆弾を甲板に投げ込むぞ。";
			link.l1 = "ははっ！お前の女の機転には毎度驚かされるよ！火船の代わりにフガスを使うって？本当にうまくいくと思うのか？";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "なぜ駄目なんだい？あいつらの舷側はうちより高いけど、滑車を使って二、 三人いれば満載の樽を簡単に持ち上げて投げ込めるよ。\n「ナイフからの無料のラムだぞ！」って叫んでやればいい。やつらが反応する前に樽が爆発するさ。";
			link.l1 = "炸裂ブドウ弾を使えば、あいつの甲板の精鋭どもがミンチになる……くそ、そそられるじゃないか。";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "「船尾甲板からポープデッキまで、一度に樽を五つ投げよう。」 "+pchar.name+"、奇襲の利があるわ。あいつらはまだ何も気づいていない！それからすぐに出航して、乗り込まれる前に逃げるのよ。";
			link.l1 = "さて、やってみよう。あいつらに爆薬樽を甲板に運び込む前に正体がバレちゃいけない……近づくのは簡単じゃないよ。ジャックマンはグールほどの間抜けじゃないからね。";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "「賭けてみよう」 "+pchar.name+"！前にも言ったけど、あたしたちに失うものなんてないでしょ？";
			link.l1 = "いい指摘だ……構えろ、野郎ども！フガスを用意して戦う準備をしろ！";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "さて、私の大切なキャプテン……そろそろお別れの時だね。あたしの役目は終わったし、 これからはイスラ・テソロの海賊女王としてやっていく覚悟を決めなきゃ。叔父の後継者として、 ふさわしい存在になれるといいんだけど。手を貸してくれて、本当にありがとう。";
				link.l1 = "ああ、あなたと別れるのは残念だけど、これも運命の気まぐれさ。今のあなたには、 私の船で働くよりずっと大事な責任があるんだよ。";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "あなたの船にずっといられたらいいのに。あなたのそばに……でも、それは無理なの。幸せになって、シャルル。\nそして、あなたのそばにいる彼女が、あなたにふさわしい人でありますように！";
					link.l1 = "ごめん、エレン。";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "「とても不思議だわ、」 "+pchar.name+"！あたし、島ひとつの持ち主になったばかりなのに、イスラ・テソロの女王って気分じゃないんだよね……。新しいバラナスの頭領の方が、きっとあたしより植民地をうまく治められるんだろうな。あたし、 まだまだ学ぶことがたくさんあるよ。";
					link.l1 = "心配するな、エレン。お前は自分の身を守れる女だろう――最初に乗船したとき、そう言ってたじゃないか。";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "まあ、それでも私たちは友達のままでいられるよね？";
			link.l1 = "もちろん……エレン、またイスラ・テソロで会おう。君を島まで送り届けようか？";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "あんたの言う通りだよ……ほら、あたしもあんたの船で航海してる間に分け前をちゃんと取っておいたんだ。これを受け取って。 断るなんて考えないでよ――あたし、あんたに借りを作りたくないんだから。";
			link.l1 = "おいおい、ちょっと待ってくれよ……";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "あなたが何を言おうとしているか分かっているよ。確かに、あなたの助けはこのささやかな宝箱よりずっと価値があった。 でも、今あたしが持っているのはこれだけなんだ。どうしてもお礼をしたいの。受け取って。もし自分で取らないなら、 あなたの船室に置いていくからね。";
			link.l1 = "これから一人で航海するつもり？\nよかったら、あたしがイスラ・テソロまで連れて行こうか？";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "そんなことしなくていいよ。 "+pchar.name+"…あたしが自分で島に行くよ。剣もピストルも持ってるし、しばらくはそれで十分さ……あたしが着けば、イスラ・テソロの女王は収入の心配なんてしなくていいはずだよ。";
			link.l1 = "アイアイサー、陛下。新しい人生に幸運を祈るよ。";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "冗談でも、もうその話はやめてよ。あたしはまだあなたにとってエレンなんだから。でも、それだけじゃなくて、 他にも伝えたいことがあるの。父と再会できたのよ、ちょっと奇妙な形だったけど。 彼はイングランド貴族としての名誉を犠牲にして、あたしの相続権を守ってくれたの。それが心に引っかかってる。 イングランド共和国が父を追っていて、あなたには…\n "+pchar.name+"、それに参加するために。";
			link.l1 = "目を覚ませ、エレン！あいつは盗賊で海賊なんだぞ！";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "海賊？そんなことを言うあんたは一体何者なの？あの人は私の父よ、それが私には一番大事なの！ あたしは盗賊で海賊の娘、イギリスの正義が父をどう思おうと全然気にしないわ。 もし父に少しでも危害を加えようとしたら、あんたが私にしてくれた良いことなんて全部忘れるから、 そのつもりでいなさい。これは警告よ。";
			link.l1 = "そうかい？実はな、お嬢ちゃん、もう少し礼儀をわきまえた方がいいぜ。 俺があんたの可愛い身をあの強姦野郎ドノヴァンから救い出した時や、一緒に戦利品の分け前を山分けした時には、 俺の海賊らしい態度に文句なんて言わなかったじゃねえか！";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "あ…ごめんなさい。今のは取り消すわ、許して。取り乱しちゃって……でも、それでも、あなたの友達でいたいの。もしあなたが私の父を追い始めたら、それは絶対に無理になるから。";
			link.l1 = "了解だ。しかし、女、お前が俺を脅すなんて絶対に許さねえぞ。俺の船で一緒に航海してきて、 俺が誰にも何にも恐れねえってことはもう分かってるはずだろ。特に女からの無礼なんざ、 たとえ海賊女王だろうが絶対に我慢しねえ。俺は紳士かもしれねえが、我慢にも限度があるんだ。これで話は終わりだ、 さらばだ。幸運を祈るぜ。";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "ありがとう……また会えるかもしれないわね。 "+pchar.name+"...";
			link.l1 = "なぜいけないんだ？これからも何度もイスラ・テソロに行くつもりだ。\nそこで会おう……さようなら、エレン。";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "間違いないよ。 "+pchar.name+"、もし許してくれるなら、あなたの船に残りたいの。あなたと一緒にいたい……";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "（メアリーを選ぶ）ヘレン、君には分からないよ。君の未来はこれからで、心配することなんて何もないんだ。 俺の前にあるのは戦争と政治の陰謀、そして完全な不確実さだけさ。君は自分自身の人生を築くべきだ。 俺みたいな放浪者の居場所なんて、君の人生にはないんだよ。";
				link.l1.go = "result_10";
				link.l2 = "（ヘレンを選ぶ）こんなこと、夢にも思わなかったよ、ヘレン。もちろん君を失いたくはない。 でも君がイスラ・テソロへ行く方がきっといいんだ。僕の運命がどこへ向かうか、まだ誰にも分からない。 今の僕の前には、戦争と政治の陰謀、そして不確かな未来しかないんだ。";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "ヘレン、こんなこと、夢にも思わなかったよ。もちろん君を失いたくはない。 でも君にとってはイスラ・テソロへ行く方がきっといいんだ。僕の運命がどこへ向かうかなんて、誰にも分からない。 今の僕の前には、戦争と政治の陰謀、そして先の見えない未来が待っているんだ。";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"！嘘つかないでよ。あんた、本当はしたくないだけでしょ…教えて、誰なの？捨てられた船の街のあの赤毛の女狐でしょ、違う？";
			link.l1 = "エレン！君のために一番いいと思うことを言おうとしてるんだ！どうしてそれが分からないんだ！？";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "「ああ、もちろん、そうなんだろうね……で、どうやって彼女があんたを虜にしたのさ？あたしにない何かがあるってわけ！？そんなにいい女なの？ええ？」 "+pchar.name+"…まあ、あなたの決断だから、あたしにはもう自分の島に帰るしかないわ。 あなたたち二人の間に割って入ることはできない\n今まで本当にありがとう、シャルル。あなたはあたしが出会った中で一番素敵な男よ。 これからも友達でいられるといいんだけど？";
			link.l1 = "もちろん……エレン、またイスラ・テソロで会おう。君をそこまで送ろうか？";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "必要ないよ。新しい船を買うつもり。あなたの指揮下で働いている間に、 スクーナーを買って装備するだけのお金は十分に貯めたから。また新しい『レインボー』で航海するわ。";
			link.l1 = "嬉しいよ、エレン、君がそんなに…倹約家だったとはね。\nでも、スクーナーで航海するなんて、イスラ・テソロの海賊女王には似合わないよ。\nそのうち、自分だけのフリゲート艦を手に入れるべきだよ。";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "「たぶん」 "+pchar.name+"……わかったよ。船渠に行くけど、その前に……別れのキスをして……お願い……？";
			link.l1 = "エレン……";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "あたしの運命は、あんたと出会ったときからずっと一緒に縛られてるんだよ。わかってないの？ "+pchar.name+"？あたしはあなたについて世界の果てまで行くよ！";
			link.l1 = "それで、あなたの父親はどうするの？ローレンス・ベルトロープ？あの人はあたしの敵だよ…";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "私の父はショーン・マッカーサーよ。私は彼を愛していたし、彼の死を深く悲しんだ。父親は彼だけだったの。\nそれに、あの海賊のことは……話したくもないわ。";
			link.l1 = "エレン……愛しいエレン！";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+"、ずっと言いたかったの。あなたは私が今まで出会った中で一番素晴らしい人よ！あなたがしてくれたことは、 私には一生かかっても返せないわ。あなたと一緒にいたいの。ずっと。もし望むなら、あなたと結婚したい……愛してる。";
			link.l1 = "私たちは一緒になるよ。約束する！"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "今すぐ私のために何かしてくれるって約束してくれる？それと、お願いだから笑わないで！";
			link.l1 = "約束するよ、あなた！";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "本当の名前で呼んで。お願い！";
			link.l1 = "あたしは君を愛してる、ヘレン・シャープ。";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+"……ねえ……抱きしめて！この瞬間をずっと待っていたのよ！";
			link.l1 = "エレン、愛しい人よ…";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"！すごかった…！どこにも行きたくないよ…朝までここにいよう。世界なんて待たせておけばいいんだ！";
			link.l1 = "待たせておこう、エレン！";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			npchar.SpecialRole = "fgirl";
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Выполнено требование для Дороже золота
			pchar.questTemp.GoldenGirl_Ready = true;
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "船長！ジャックマンは死んだ……これで私の家族はやっと安全になったの？";
			link.l1 = "ああ、エレン、君たちはみんな無事だよ。だが『センチュリオン』は沈んでしまったし、君のお母さんの墓を探し出し、 イスラ・テソロの継承権を証明できる書類も全部失われた……はあ……これじゃ俺一人でトルトゥーガに乗り込まなきゃならないな……";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+"そんなに心配しないで。どうしようもないことだよ。あたしのことも気にしないで、あの島がなくても大丈夫だから。 今まで本当にありがとう！";
			link.l1 = "あたしのことを…置いていくつもりなんだね、そうでしょ？";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "はい、私のキャプテン。なんとかお金を集めてスクーナーを買い、装備も整えたわ。もう一度『レインボー』 で航海するの。ブルーヴェルドでまた会いましょう……あたしは故郷に帰るわ。";
			link.l1 = "「じゃあ……幸運を祈るよ、エレン！」";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "そうね、私のキャプテン……どうやら失敗しちゃったみたい。さようなら。あたしは故郷に帰るわ。あなたの指揮のもとで十分なお金を稼いだから、 新しいスクーナーを買えるの。\nまた海で会いましょう！";
			link.l1 = "幸運を祈るよ、エレン。すべてのこと、本当にすまない。じゃあな。";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "船長！ジャックマンは死んだ……これで私の家族は無事ということですね？";
			link.l1 = "ああ、エレン、安全だよ。しかし、満足はしていない。時間をかけすぎたし、 イスラ・テソロは今やイギリスの植民地になってしまった。君は相続を失ったから、 俺が自分でトルトゥーガに攻め込むしかないな……";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+"、弁護士はあなたに何と言ったの？";
			link.l1 = "私はあまりにも多くの時間を失い、今やイスラ・テソロはイギリスの植民地になってしまった。\nあなたは遺産を失い、私が自分でトルトゥーガを攻め落とさなければならない……\n残念だが、我々は負けてしまった。";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "だめよ、あなた、それじゃうまくいかないわ。";
				link.l1 = "まあ、いいじゃないか！？";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+"、今日はちょっと体調が悪いの。気にしないで、あなたのせいじゃないわ。今日はやめておきましょう…",""+pchar.name+"ねえ、最近本当に疲れてるの。正直なところ、ただ眠りたいだけ。ごめんね。また今度にしましょう。");
				link.l1 = RandPhraseSimple("……いいわ……","大丈夫。ご自由に……");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+"、今がちょうどいい雰囲気だ、行こう！",""+pchar.name+"「もちろん、何も聞かないよ！行こう！」");
				link.l1 = RandPhraseSimple("あたしの自慢の娘だよ……","ヘレン、君は本当に美しいよ……");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("素晴らしかったわ "+pchar.name+"!..","いつも通り素晴らしかったわ、あなた…"),RandPhraseSimple("素晴らしかったわ、シャルル！","素敵な時間を過ごせたわ、あなた！"),RandPhraseSimple("あんたと一緒だと退屈する暇もないよ、私のキャプテン！","素晴らしかったよ、あなた！"));
			link.l1 = RandPhraseSimple("愛してる……","君と一緒にいるのは、いつだって嬉しいよ、エレン…");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+"……あたし、いつだって嬉しいんだよ……でも今は違うよ――あの悪党ティボーが逃げる前に捕まえなきゃいけないんだから。";
				link.l1 = "いつも通り君の言う通りだよ、エレン……";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "だめよ、あなた、それじゃうまくいかないわ。";
				link.l1 = "まあ、いいじゃないか！？";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+"、今日は体調が良くないの。お願い、怒らないで。今日はやめておきましょう…",""+pchar.name+"「ねえ、最近は本当に疲れてるの。正直、ただ眠りたいだけ。ごめんね。また今度にしましょう。」");
				link.l1 = RandPhraseSimple("……わかったよ……","かまわないよ。ご自由に……");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+"、愛してる！行こう！",""+pchar.name+"「了解、船長！行こうぜ！」");
				link.l1 = RandPhraseSimple("あたしのいい子だよ……","ヘレン、君は本当に美しい……");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "LoveSex_Room_Go");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("「はい」 "+pchar.name+"?","はい、私のキャプテン？","聞いているよ。 "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "見てて、私のキャプテン！";
				link.l1 = "おったまげたぜ、すごい握力だな！ヘレン、時間を無駄にしてないみたいだな。";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "ねえ、あなた、娼婦のところへ通っていることについてだけど。";
				npchar.quest.refusesex = true;
				link.l1 = "「え？エレン、誤解だよ！あたしはただ…」";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "エレン、私は失われたインディアンの都市タイアサルへ行くつもりだ。嘘はつかないよ。この旅はとても危険だし、 しかも――偶像を通じてのテレポートも関わっているんだ。君は……ついてきてくれるか？";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "エレン、船の状況を詳しく報告してくれ。";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "毎回寄港するたびに、特定の商品を仕入れてほしいんだ。";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "ご命令どおりに参りました、船長。";
				Link.l2 = "エレン、君にいくつか指示を出す必要があるんだ。";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "「面白いと思ってるの？」";
					link.l1 = "いい船だろ？ヘレン、お前のために手に入れたんだ！考えてみろよ、カリブで自分の女に本物の船を贈る男なんて、 どんな奴だと思う？";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "エレン、君の助言が必要なんだ。";
				Link.l3.go = "fugas";
			}
			Link.l1 = "エレン、君に頼みごとがあるんだ……";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("エレン、キャビンで二人きりで一緒に過ごさないか……数時間だけでも。どう思う？","ねえ、あなた、これから数時間ふたりきりで過ごさない？どう思う？");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("エレン、部屋を借りて、二人きりで少しの間過ごさないか……数時間だけでも。どう思う？","ねえ、あなた、これから数時間、二人きりで過ごさない？\n部屋を借りて……どう思う？");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "エレン、親愛なる人よ、酒場で一緒に過ごさないか？";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "エレン、君の崇拝者フランシスの遺言状を見つけたみたいだ。彼は君に遺産を残しているよ。";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "このカトラスはもうあんたのものだと思うよ。ブレーズは、いわゆるあんたの叔父さんなんだろう……";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "今は何もないよ、エレン。";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "シャルル、あなた、具合でも悪いの？それとも何？あたしに船底に降りて、船倉を掃除して、 ネズミの数でも数えろって言いたいの？";
			Link.l1 = "ああ、ごめんね、ダーリン、あたしのせいだよ……";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "あたしだって百門の大砲を積んで、二十ノットで走る自分だけの戦列艦が欲しいよ。 あんたみたいにずっと船長やってきたんだ。そんなことは船の会計士にでも言って、そっちで悩ませてきなよ。";
			link.l1 = "ああ、ヘレン、その通りだ。悪かったな。";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "何でも聞くよ。";
			Link.l1 = "「私たちの乗船規則について…」";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "「あなたが指揮している船について…」";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "今のところ何もないよ。";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "ご用件は何ですか、私のキャプテン？";
			Link.l1 = "あんたにはどの船にも乗り込んでほしくないよ。自分も部下たちも無事でいてね。";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "最初の機会に敵船に乗り込んでほしい。";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "はい、私のキャプテン？";
			Link.l1 = "乗船した後に船を乗り換えるのは控えてもらえると助かるよ。あの子はあたしにとって大切すぎるんだ。";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "もし誰かの船に乗り込むことがあったら、賞品の船をよく見てごらん。もし使えそうなら、遠慮せず自分のものにしなよ。 ";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "わかった、考えておくよ。";
			Link.l1 = "彼女が考えてくれるだろう…まあ、どうせ俺が命令できる立場じゃないけどな。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "わかった、考えてみるよ。";
			Link.l1 = "彼女が考えるだろう…まあ、どうせ俺が命令できるわけじゃないしな。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "わかった、考えてみるよ。";
			Link.l1 = "考えてくれるだろう…いや、どうせあたしが命令できる相手じゃないけどね。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "わかった、考えておくよ。";
			Link.l1 = "考えてくれるだろうさ……まあ、どうせ俺が命令できる立場じゃないけどな。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "ご命令は？";
            Link.l1 = "「ここに立って！」";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "ついてきて、遅れるなよ！";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "火器の弾薬の種類を変更する。";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "弾薬の種類を選んでください：";
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
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "ただちに、船長！";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "ただちに、船長！";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "やっと見つけた！ここにいたんだね……すごかったよ、私のキャプテン！あんな屋根の上を駆け抜けて、あんな高いところから飛び降りるなんて、初めて見たよ！ 心臓が破裂しそうだった！いつかあなたのそんな芸当で、あたし死んじゃうかもよ、ねえ……あら、一人じゃないのね……この娘は誰？";
			link.l1 = "こちらはキャサリン・フォックス、名高いイギリス海兵連隊「シー・フォックス」の指揮官フォックス大佐の娘だ。\n彼女をアンティグアへ連れて行くところさ。";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "そうか……ようこそ乗船を、フォックス嬢！いやいや、ド・モール船長の腕につかまらなくても、自分の足でちゃんと歩けるだろう！ さて、早くロングボートへ行こう――ここから脱出しなきゃならないんだ。"; 
			link.l1 = "ははっ！ありがとう、エレン！君がいなければ俺はどうなっていたことか！キャサリン、ついて来い！";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "やっと目を覚ましたのね、あなた！気分はどう？本当に心配したんだから……";
			link.l1 = "エレン、どうしたんだ？頭が割れそうに痛い……";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "船長の船室に入ったとき、あなたは床に倒れて動かなかった。あたし、心臓が止まりそうだったよ！ みんながあなたを抱き上げて、急いでうちの船まで引きずっていったんだ――ちょうどその時、甲板に倒れていた死人たちがまた立ち上がり始めてさ。\nなんて恐ろしいこと！神様を信じたくなるくらいだよ！奴らには刃も弾もまったく効かなかった！ 急いで綱を切って逃げ出そうとしたけど、あちらの船からの一斉射撃でうちの船は大きく損傷して、 操縦不能になっちゃった。その後、奴らは帆を上げて、一瞬で姿を消したんだ。\nうちの船は座礁してしまったから、嵐で壊される前にこの岸まで逃げるしかなかった。今日は多くの仲間が死んだけど、 船はなんとか生き残った……あたしが退船命令なんて出さなければ……";
			link.l1 = "ヘレン、君のせいじゃないよ。正しい判断だった。君がいなかったら、俺はどうなってたんだろう？";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "あんたをボートに引きずり込んで、それから岸まで運んだんだよ。死んだみたいだった、かすかに心臓だけが動いてた。 見て！あたしの手、まだ震えてるんだ\n";
			link.l1 = "ありがとう、あなた。あなたには借りができたわ。私、ここにどれくらい横たわっていたの？";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "丸一日、あんたの傷を洗って手当てして、薬を飲ませて、ラム酒も少し飲ませたんだよ。さあ、元気にならなきゃね！";
			link.l1 = "今回は死なないよ、ダーリン。だけど、あんまり気分が良くない……うっ……。";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "教えて……本物の『フライング・ダッチマン』だったの、シャルル？どうしてあいつらは私たちを襲ったの？それに、 接近したときは砲撃しなかったのに、乗り込んできた途端すぐに沈めようとしたのはなぜ？";
			link.l1 = "彼らの船長はあのアミュレットを必要としていたんだ。 それについてはトゥトゥアタパクというインディアンのシャーマンと話したことがある。 なぜ彼らがそれを欲しがったのかは分からない……だが、彼らの頭がアミュレットを手に入れた途端、俺たちは始末された……全能の神よ、なんて惨めな悪夢だ！生ける屍が乗る船なんて、信じられやしない……";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "ああ、今度は俺たちが“フライング・ダッチマン”に遭遇する番だったんだな。うっ！鳥肌が立つぜ！次の港に着いたら、教会に行って、ろうそくを灯して、 主イエス・キリストに奇跡の救いを祈るつもりだ。くそ、あまりにも感謝してるから、 カトリックの聖人たちにも祈ってやるよ……";
			link.l1 = "すぐに君と一緒に行くよ、エレン。ちゃんとした告解なんて、しばらくしていないけどな……。\nでもまずは、あの村に戻らなきゃ。トゥトゥアタパクに全部話す必要があるんだ。あの呪われた船が俺たちを襲ったのは、 あのアミュレットのせいだ！\nあの赤い肌の悪魔が、なぜ生ける死者どもがそれを欲しがったのか、何か心当たりがあるといいんだが。";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "わかったわ。でも気をつけないといけないよ――あなたの傷はまだほとんど治っていないんだから。";
			link.l1 = "でも君がいれば、もっと早く癒えるだろう？愛してるよ、エレン……";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "あたしも愛してるわ、あなた…";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+"一度言ったはずだよ、今やあたしたちの運命は一つ。あなたの運命はあたしの運命。いつ出発するの？";
			link.l1 = "それは本当に嬉しいわ。あとで、あそこに行くときに話すね。今は準備をしないと。";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "準備はできてるよ、私のキャプテン！地の果てまでもあなたについていくわ！";
			link.l1 = "ありがとう、私の愛しい人…";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "「あっ、」 "+pchar.name+"！会えて嬉しいよ！どうしてイスラ・テソロに来たの？";
			link.l1 = "いつも通り――仕事さ。ついでに君の顔も見たくて寄ったんだ。調子はどうだい、エレン？";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "「うちのご自慢の総督様、どうしたの、キャプテン？今度は誰の尻を蹴飛ばすの？スペイン野郎か、海賊か、 それとももっとタチの悪い奴？」";
			link.l1 = "もっとひどいんだ、エレン、はるかに悪い。総督は高級娼婦のもとを訪れるつもりで、 俺は珍しい見世物として付き添わされることになったんだ。愛人に「本物の私掠船長で冒険者、海の荒くれ者」 を連れてくると約束したらしい。つまり、退屈な会話と法外に高いワイン、つまらない貴族どもが待っているってわけさ。 ";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "まったく逆よ。淑女が主催する楽しい社交の催しへの招待状なの。総督閣下が私に同行を頼んできたのは驚いたけど、 正直なところ、たまには仕事のことを忘れて気分転換できる機会があって嬉しいわ。";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "ああ……あの恐ろしいシャルル・ド・モール船長が、奴らのために猿のように着飾って踊るってわけ？可愛いもんだね！でも、 もっといい案があるよ。帆を上げて、さっさとここからおさらばしよう。もし長い間待ち望んでた休暇気分なら、 イスラ・テソロへ行こうよ。あそこならいつでも歓迎されるから。日光浴、白い砂浜、昔の仲間たち、ラムパンチ、 嫌なこと全部忘れて――なんでもありだよ。";
			link.l1 = "見てよ、全部すごく魅力的に聞こえるし、あたしも本当は…でも今は無理。総督に約束しちゃったし、この件はあの爺さんにとって大事なんだよ…";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "それで？自分の高貴な血筋があいつらにとって何の価値があると思ってるの？あたしはフランスの血を引いてないけど、 あいつらの“上流社会”のことはよく知ってる。あいつらにとってシャルル・ド・モールは、命を預けてついていくような船長じゃないし、 自分たちのような紳士でもない。本物の紳士は海になんか出ないし、火薬の煙の中で戦ったりしない。 シャルル・ド・モールなんて、あいつらの食卓に添えられた珍しい飾り物みたいなもんさ。ペットのヒョウとか、 着飾った黒人の召使いみたいな、ただの派手なおもちゃ！いつからあんたはそんな扱いを受け入れるようになったの？！";
			link.l1 = "エレン、落ち着いてくれ。総督のご機嫌取りや俺たちの将来のために、多少の冷たい視線くらいどうにかできるさ。 力のある友人がいるのは悪くない。何しろ、白兵戦を仕切るよりは楽なはずだろう！それに、こいつら“役立たず”ばかりじゃない。上流社会にも立派な人間はいる……少なくとも、そういうことになってるんだ。";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "どうでもいいわ。（髪を払う）でも、よく覚えておいて――絶対にドレスなんか着ないからね。もし行かなきゃいけないなら、あたしはズボンで行くよ。 カリブ中の貴婦人たちがどれだけ気絶しようと、そんなの知ったこっちゃない。";
			link.l1 = "無理に付き合わせるつもりはなかったよ。二人とも苦しむ必要はないからね。この宴が終わったら、 私たちはイスラ・テソロへ出航しよう。ご褒美に、貨物室に極上のスペイン産マデイラ酒を一本取っておいたんだ…";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "おほほ、シャルル！あたしがそんな高貴な連中にはふさわしくないって言うの？ ズボンをはいた女があんたの夜を台無しにするって？面白いわね。いいわ、 でも自分のこともちゃんと着飾るのを忘れないでよ。きらびやかな服を着た猿だって、 時には高級娼婦の心を動かせるんだから。\n楽しんできな！";
			link.l1 = "エレン、待てよ！くそっ……女ってやつは！";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "ああ、確かに少しは休む権利があるよ。でもな、ドレスなんか着るくらいなら海に放り込まれた方がマシさ。 あんたの女が男や水夫みたいな格好してるって噂、どこまで広まると思う？";
			link.l1 = "ああ…それはあまりいい考えじゃないと思うよ。どう言えばいいかな…これは男たちが妻やちゃんとしたご婦人を連れてくるような催しじゃないんだよ…";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "ははっ！売女と堕落か！素晴らしいじゃないか――つまり乱交パーティーに行くってわけね！だったら最初からそう言えばよかったのに。あたしが嫉妬深い女じゃなくて、 今ここで撃ち殺さないだけありがたく思いなさい。少なくとも今は撃たないけどね。";
			link.l1 = "エレン、頼むよ、俺はただ総督のお供をしてるだけなんだ、彼に頼まれて、しかもしつこく頼まれたんだよ。 娼婦なんて絶対にいないってば\nいや、違う、今のは言い方が悪かった……つまり娼婦とヤるとか、そういう意味じゃ……くそっ！俺はただ挨拶しに行くだけなんだ！";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "「敬意を表す」ために、流行の服を着ることをおすすめするわ、ド・モール船長。何しろ上流社会なんだから。 襟やカフスもなしに現れるなんて、まったくのスキャンダルよ。たとえ乱痴気騒ぎでもね。楽しんできて。";
			link.l1 = "エレン、待て！くそっ……女ってやつは！";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "カフスと襟、それにレースもね、船長。最近また流行ってるって聞いたわ。でも、あたしに何が分かるっていうの！";
			link.l1 = "「おい、エレン、頼むよ！」";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "見てよ！あたしの大切なキャプテンが乱痴気騒ぎから帰ってきたじゃない！";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "地元の貴族たちは、まだ新しい猿を気に入っているのかい？昨夜の芸は伝説的だったって噂だよ！ 船や娼婦を賭けて博打を打ったり、身分の高い坊ちゃんたちに決闘を挑んだり？一体全体、 あんたに何が起きてるのか説明してくれる？";
			link.l1 = "エレン、説明させてくれ！そんな単純な話じゃないんだ。くそっ、ごめん、 本当にマダム・ボトの家で夜を過ごすことになるなんて思ってもみなかったんだ。ただ寝ただけだ、そう、一人でだ、 誓うよ！それに、カードゲームでフリゲート艦を勝ち取ったんだ。信じられるか？";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "さて！あんたは大嘘つきか、聖人か、それともただの馬鹿かのどれかだね。娼婦や勝ち取った船の話は後にしよう――今は決闘のこと、そしてなぜ皆があんたが王太子に決闘を申し込んだと噂してるのか、全部話してもらうよ。";
			link.l1 = "王太子じゃなくて、ただの伯爵の私生児さ。あいつはすごい権力を持つ貴族、 ルヴィ・ヴァンタドゥール伯爵の息子なんだ。\nほら、俺が始めたわけじゃない！最初に挑んできたのはあいつだし、今は伯爵の怒りを買わないように、 あまり傷つけずに決闘に勝たなきゃならないんだ。";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "あら、「ただの伯爵の息子」だって？本気なの、シャルル！？それでどうやってやるつもりなの？ もしあいつがイカサマしたら？あんた、殺されちゃうよ！";
			link.l1 = "だからこそ閣下は私に高貴な立会人を付けてくださったのです。\n同行するのは彼らだけです――もし事がうまくいかなくても、決闘規範と法に則っていたと証明できますから。\n私が不在の間、フリゲートの見張りをお願いしたいのです。";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "ちょっと確認させて…あんたは丸一日いなくなって、カード勝負で娼婦とフリゲート艦を手に入れたってわけね。それで今度は、 殺しちゃいけない貴族のクソ野郎と戦うつもりで、*あたし*はここでただ待ってろって？こんなの、どう思えばいいのよ！？";
			link.l1 = "エレン、聞いてくれ、君が俺に怒るのは当然だし、本当にすまないと思ってる。でも、それはただ……";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "もういいわ、こんなのうんざりよ。さっさと自分のやることやってきなさい！私はあんたの船室でも掃除して、 汚れた洗濯物でも片付けておくから！でも、これで終わりだなんて思わないでよ。全部終わったら、 ちゃんと話をするからね。新しいフリゲート艦の世話は任せて、偉大なるド・モール船長、心配しないで。ああ、 それとド・モール船長、死なないように気をつけて…だって、その後であたしが自分で殺すつもりなんだから。じゃ、失礼するわ。自分の部屋にこもって、 あんたの船室で見つけたあの美味しいマデイラ酒を一本飲むことにするから。\n";
			link.l1 = "エレン、ちょっと説明させてくれ！くそっ…また始まったな！";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "最近のパリの流行じゃ、紳士たちは船や高級娼婦を買うんじゃなくて、カードゲームで勝ち取るもんだって聞いたよ！ しかも、いい印象を残したいなら、前の持ち主に決闘を挑まなきゃいけないんだとか。\nいったい今度はどんな面倒ごとに首を突っ込んだのさ、あんた！？";
			link.l1 = "エレン、そんなに簡単な話じゃないんだ。くそっ、ごめん、 でもまさかボト夫人の家で夜を明かすことになるなんて思ってもみなかったよ！昨夜は、 頭脳戦の果てにもうクタクタになったんだ。それに、そう、カードで血まみれのフリゲート艦まで勝ち取ったんだぜ。 信じられるか？";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "素敵ね。それじゃあ、あなたは高級娼婦まで手に入れたってこと？それと、 あのフリゲート艦を手に入れた時は何を賭けたの？まさか私たちの船じゃないでしょうね……";
			link.l1 = "仕方なかったの。見て、もう今さらどうでもいいことよ。結局はあたしが勝ったんだから。\n相手はあたしに決闘を挑んできて、イカサマだって非難したの。\n彼はとても影響力のある貴族、ルヴィ・ヴァンタデュール伯爵の私生児なのよ。\nつまり、あたしは彼を殺したり、ひどく傷つけたりしないように全力を尽くさなきゃいけないってこと。";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "彼も同じことをすると思うの？シャルル、正気を失ったの？自分の船を、命を、他の女のために危険にさらすなんて！？ 彼女はそこまでの価値があるの？私のことはどうでもいいの！？";
			link.l1 = "エレン、嫉妬する理由なんてないんだ、誓うよ。たまたまそうなっただけなんだ。やらなきゃならなかったし、 総督が決闘の立会人として貴族の士官たちを用意してくれたんだ、すべてが規則通りに行われるようにね。 君や俺たちの仲間を連れていくことはできないんだ。俺がいない間、どうかフリゲートのことを頼むよ。";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "まったくもう！最初は、見知らぬ女たちと乱痴気騒ぎに行って、翌朝平然と帰ってきたけど、 あたしは何も言わなかったよ。今度は、カード勝負でうちの船を危うく失いかけたけど、 代わりに高級娼婦を手に入れたって！？そして今度は、その女の『名誉』のために、 殺すことも許されてない貴族のろくでなしと決闘しようっていうの？こんなの、あたしはどう思えばいいのさ？教えてよ。 ";
			link.l1 = "エレン、聞いてくれ、俺に怒るのは当然だ。でも、ちょっと説明させてくれ……";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "もういいわ、こんなのうんざりよ。勝手に決闘でも何でもしてきなさいな。あんたの新しいフリゲート艦のことは、 偉大なるド・モール船長様、私がちゃんと面倒見てあげるから心配しないで。じゃあ失礼するわ、 これから自分の部屋にこもって、あんたの船室で見つけたあの上等なマデイラ酒を一本飲むつもりよ。だけど、 もしあんたに何かあったら、神に誓ってこの町に地獄の業火を降らせて、この売春宿も、 あんたの大好きな閣下の宮殿も全部埋めてやるから！\n";
			link.l1 = "エレン、大丈夫だ、俺を信じてくれ……待て、どこへ行くんだ！？くそっ！またかよ……";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "シャルル、説明してもらわないと困るわ。いったい何があったのか、ちゃんと話してくれる？ 私が見張りをちゃんと立てなかったし、みんなは酒を飲んでた……その隙に悪党どもが船を襲って、私たちが寝ている間に縛り上げられたの。そいつら、 あんたが私を助けるためにどこまでやるか聞いてきたわ。最後には私を船倉に閉じ込めて……どれだけ待ったか、もう日数もわからないくらいよ！";
			link.l1 = "あの野郎、私が恥をかかせた仕返しをしたかったんだよ。あなたに何かするんじゃないかと心配だった！ 無事で本当に良かった！";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "あたしを助けるために、何かしなきゃならなかったんでしょ？悪いこと……したんじゃない？";
			link.l1 = "大事なのは、君がまたあたしのそばに戻ってきてくれたことだけだよ。あたしは君を守れなかった、ヘレン。 本当にすまない！どうか、君の心であたしを許してくれるといいんだけど！";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "もう言ったよ。自分の言ったことについて、ずっと考える時間があったんだ……あたしもごめんね、シャルル。あたしがあんたとあの侯爵の取引をあんなに個人的に受け止めなければよかったのに。 あの夜、ちゃんと見張りを立てていれば、もっと警戒していれば……ああ！あたしなんて、役立たずの女だよ！";
			link.l1 = "そんなこと言わないで、過去は過去よ。あたしはあなたを愛してるし、もう二度とあなたのそばを離れない。約束するわ！ ";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "あたしはあなたが何をしたのか、詳しく知らない方がいいんだろうね？\nまあいいわ、また一緒になれたことが大事なんだから。";
			link.l1 = "あなたには隠し事はないよ。話してあげる……";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "なんてこと……仕方なかったのは分かるけど、これをディ・ル・パークスやその仲間たちにどう説明するつもり？つまり、 今やあなたは犯罪者なのよ！";
				link.l1 = "あたしはその代償を払うことを選んだけど、本当は選択肢なんてなかったんだよ。\n心配しないで、必ず何とかして名誉を取り戻してみせるから。\nもし無理でも、イスラ・テソロならいつでも歓迎されるさ！\nあなたが一緒にいてくれれば、あたしは大丈夫だよ。";
			}
			else
			{
				dialog.text = "すごい話ね、シャルル……あなたには選択の余地がなかったんだと思うけど、これからどうなるの？あのイギリス人が事態を収めるのか、 それとも戦争になるの？あのろくでなしが鎖につながれるのを見届けにバステールへ来たくないの？";
				link.l1 = "ヘレン、二週間前の俺なら絶対に見逃さなかったさ。でも今は、あいつなんてどうでもいい！ 正当な罰なんてもう気にしちゃいない。俺たちはまた一緒だ――それだけで十分だよ！";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "あたしはいつだってあなたのそばにいるって知ってるでしょ。\nははっ！あんたとあたしがビルジの中で首まで浸かったの、これが初めてじゃないしね。\nまたきっと乗り越えられるよ。";
				link.l1 = "そうだね。出航しよう、あなた！地平線が私たちを待っているわ！";
			}
			else
			{
				dialog.text = "あんたの考え、好きだよ、シャルル！もう貴族なんてごめんだ――フランスだろうが、イギリスだろうが、スペインだろうが、関係ないよ。あたしたち、 ちょっと休暇をもらってもいいくらい頑張ったでしょ！";
				link.l1 = "同感だよ。あたしとあんた、二人きり！もう総督も貴族のクソ野郎もいない！";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "了解だよ、キャプテン！";
				link.l1 = "";
			}
			else
			{
				dialog.text = "素敵だね！みんなに錨を上げる時間だって伝えてくるよ！それと、シャルル…";
				link.l1 = "分かっているよ、エレン、分かっている。すぐに君のところへ行くよ。";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "シャルル、来てくれたのね！ポルトガル人から全部聞いたわ！なんて話なの！";
			link.l1 = "「神に感謝します、エレンが生きていてくれて！また会えて本当に嬉しいよ！」";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "そういえば。何か話してくれるって約束したよね？大きくて複雑なことを。今がそのチャンスだよ、キャプテン。 一体何があったの！？";
			link.l1 = "エレン、君を愛している。他のことなんてどうでもいい。";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "ああ、それは助かったけど……くそ、あたしもだよ、シャルル。あたしもあなたを愛してる。神様、どれだけあなたに会いたかったか！";
			link.l1 = "あたしもよ。一緒に来て、今夜はこのみじめな町に空が落ちてきても、あなたを置いていかない。もう二度と、 絶対にあなたを離さないわ。";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "あなたが何をしたのか、詳しくは知らない方がいいんだろうね？\nうん、また一緒になれた、それが一番大事だよ。";
			link.l1 = "あなたには隠し事なんてないよ。全部話すね…";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "信じられない！今、あたしのせいでフランスとイングランドが戦争寸前だって言ったの？";
			link.l1 = "いいや、エレン。俺の判断がとても悪かったせいだ。でも、君を連れ戻して、すべてを正さなきゃならなかったんだ。";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "それはとても感動的でロマンチックね、最初にどう始まったかさえ忘れそうよ。ほとんど、だけど。\nでも本気で言うけど、あんたが捕まったのは、ポルトガル人が例の忌々 しいブリガンティンの名前を間違えて伝えたからなの？";
			link.l1 = "まったく逆よ、彼は正しいものをくれたの！どうやってこんなことをやり遂げたのか、そしてなぜなのか、 知りたいくらいだわ。\nところで、本人はどこにいるの！？";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "彼はもういないわ。私をここに連れてきた直後にね。あなたが勝ち取ったあの高級娼婦の“もてなし”は受けたくなかったから、バルトロメオに部屋を借りてもらったの。彼は代金を払って、何も言わずに姿を消したわ。あ、 でも待って、違う――あなた宛てに手紙を残していったのよ！";
			link.l1 = "手紙？ポルトガル人のバルトロメウから？これは初耳だね。なんだか嫌な予感がするよ……";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "そうね、ここで読んでて。あたしはちょっとみんなに顔を出してくるよ。きっと心配してるだろうし。 あんな陰気で情けない顔ぶれが恋しくなるなんて思わなかったよ！その間に、また何かやらかさないように気をつけてね！ ";
			link.l1 = "くそっ……まさか本当にあんたを連れ戻してしまうなんて、今でも信じられないよ！";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "白い砂、透き通る緑の海、あなたと私、そして美味しいワイン――シャルル、なんてロマンチックなの！こんなふうに一緒に散歩するの、もっと増やしましょう、いい？";
			link.l1 = "気に入ってくれて嬉しいよ。これからはもっとこういう時間を作ったほうがいいと思うんだ。";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "シャルル、何をしているの？どうして膝をついているの？こんなに突然…";
			link.l1 = "エレン、君を愛している。天が与えてくれたこの命のすべての日々を、君と共に生きていきたい。だからこそ、今ここで、 この海と空のもとで、君にお願いする――エレン・ベアトリス・シャープ、どうか私に、人と神の前で永遠の誓いを立てる栄誉を与えてほしい。 死がふたりを分かつその時まで。\n 私、シャルル・ド・モール、モンペール騎士は君に問う――私と結婚してくれますか？";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "あたしね、こういう形式ばったのは昔から好きじゃないんだ。でも、あんたとなら世界の果てまで一緒にいるよ。で、 質問の答えは……あっ、ごめん、こぼしちゃった！";
				link.l1 = "気にしないで、ただのワインだし、このシャツも元々好きじゃなかったから…";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "シャルル、もちろんよ！ええ、ええ、そしてもう一度、ええ！！！でも、お願いだから、 私たちをどこか埃っぽい家族の城に引退させて、一生カブを育てるつもりじゃないでしょうね？";
				link.l1 = "まあ、うちには家の城があるけど、埃っぽくなんかないし、そこに留まるつもりもないよ。あたしたちの人生は自由と、 手の届く水平線なんだから！";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "「それじゃ、私のキャプテン、私の旦那様、そして私たちの結婚に乾杯！」";
			link.l1 = "君に、私の愛しい人！そして、これからの二人の未来に乾杯よ。まだまだ素晴らしいことが待っているわ！";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "それでは、私のキャプテン、私の旦那様、そして私たちの結婚に乾杯しましょう！";
			link.l1 = "君に、私の愛しい人！そしてこれからの二人の未来に、まだまだ素晴らしいことが待っているよ！";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "それで、ブノワ院長が戻ってきて、私たちの結婚式を執り行う準備ができたんだね。でも、念のため言っておくけど、 こんな特別な時でも私はドレスなんて着ないよ！あたしがズボンを履いたら、みんな驚くと思う？";
			link.l1 = "エレン、どんな服でも君を愛しているよ。みんなそのうち慣れるさ。まずは、 招待客と式について君に相談したかったんだ。";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "ああ、ひとつ問題があるんだ――本当に祝いたい大事な仲間たちのほとんどは、この町どころか教会にも入れてもらえないんだよ。\nだからさ、まずはここで皆が納得する形で大事な人たちと結婚式を挙げて、それからイスラ・テソロへ船を出して、 本当の仲間たちと盛大に祝おうじゃないか。どう思う？";
			link.l1 = "いいね！ベノワ院長に話してみるよ。でも招待状を送ったり、他にもやることがあるんだ……";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "落ち着いて、船長。あなたの可愛い未来の奥さんが、ちゃんと負担を分かち合うから！イスラ・テソロで全部手配して、 仲間たちにも手紙を書くわ。ねえ、どれくらい盛大な結婚式にしたいの？";
			link.l1 = "あたしたち二人と、親しい仲間だけよ。マルティニークでの公式なきざな儀式の後は、本当の親密さが欲しくなるでしょ。 ";
			link.l1.go = "LongHappy_10";
			link.l2 = "みんな、この日を絶対に忘れるな！\n全員を呼べ！\n誰一人として漏らすなよ！";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "居心地がよくて親しみやすい――まさに私の考えていた通りだよ！シャープタウンに行って、全部準備しなくちゃね。ラム酒は五十樽、 ワインは二ダースもあれば十分だと思う。それから、食事と娯楽のために三十万ピース・オブ・エイトが必要になるよ。";
			link.l1 = "もう一度教えてくれない？どうして君は船の財務を管理しないんだっけ？全部任せてくれよ。 ちょっと修道院長に会いに行くだけで、それが終わったらシャープタウンへ出航しよう。";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "つまり、本物の海の狼みたいに宴を開きたいんだね？よし！シャープタウンに行って、あたしが全部準備するよ。 しっかり仕入れないとね――ラム酒は百樽、ワインは五十樽くらいで足りると思う。他の出費も最低でも五十万エイトはかかるよ。";
			link.l1 = "「海賊同盟の連中全員を招待するつもり？ああ、くそ、やってやろうじゃない！物資はあたしが用意するよ。 修道院長にちょっと顔を出したら、すぐにシャープタウンへ出航だね。」";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "シャルル、積み込みはあたしがやるから、その後でバロンに招待状を配って、酒場の親父と話をつけてくるよ。 そんなに時間はかからないはずだよ。";
			link.l1 = "心配しないで、お嬢さん。ちゃんと稼げる仕事でも探すさ……それとも、砂の上で昼寝でもしようかな。まさか自分の結婚式の準備よりトルトゥーガを攻める方が楽だなんて、 思いもしなかったよ、まったく。";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "休めたかい、シャルル？いい知らせと悪い知らせがあるんだ。悪い知らせは、先週地元の連中があまりにも楽しみすぎて、 うっかりあの忌々しい「オールド・ウッドペッカー」酒場を全焼させちまったことさ！\nでもいい知らせもあるよ。男爵が、俺たちが戻る頃には、前よりも大きくて立派に建て直すと約束してくれたんだ。 手配は済んでるから、すぐに出航できるよ。";
			link.l1 = "私たちの結婚式が、町にこんな焼け跡を残して終わらないといいんだけどな。\n本当に残念だよ、「オールド・ウッドペッカー」はけっこう気に入ってたんだ――居心地が良くて、こぢんまりしてて、ほんのりと吐しゃ物とオークムの匂いがしてさ！\nまあいいさ、ダーリン、君の言う通りだ――そろそろ行こうか。";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "ヤンはグラディスと一緒にもう町にいるのよ、信じられる？まさか二人が本当に私の結婚式に来るなんて思わなかったわ！ ああ、なんてこと……！あの恐ろしいインディアンの神殿都市にいた時でさえ、今ほど怖くはなかったのに！";
			link.l1 = "大丈夫よ、あなた、大丈夫。私も不安だけど……緊張するのは普通よ。もうお客さんたちが来てるから、ベノワ神父のところへ行って、式がいつ始まるか聞いてくるわね。 ";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "とんでもなく長くて厳しい一日になりそうだ……ヤンとグラディスに会いに行くよ。";
			link.l1 = "来てくれて本当によかったよ。スヴェンソン親父はあんたを自分の娘みたいに大事にしてるし、 マッカーサー夫人はそれ以上だ。今日ここにいてくれて本当によかった。さあ、行っておいで――心配しなくていい、きっとすべてうまくいくさ。";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "ええ。";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "「はい。」";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "はい。";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "私、シャルル・アンリ・ド・モール、モンペールのシュヴァリエは、あなた、 ヘレン・ベアトリス・シャープを妻として迎えます。今日この日より、良き時も悪しき時も、富める時も貧しき時も、 病める時も健やかなる時も、死が二人を分かつまで、あなたを愛し、守り続けます。神の聖なる掟に従い、神の御前で、 この誓いを立てます。";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "私、ヘレン・ベアトリス・シャープは、あなた、シャルル・アンリ・ド・モールを夫とし、今日よりこの先、 良き時も悪しき時も、富める時も貧しき時も、病める時も健やかなる時も、死が二人を分かつまで、 共に歩むことを誓います。\n神の聖なる掟に従い、神の御前で、この誓いを立てます。";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "アーメン。";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "エレン・ベアトリス・ド・モール、モンペール夫人――ああ、この響き、気に入ったわよ、最愛の旦那様！";
			link.l1 = "それ以上に素晴らしい話は聞いたことがないよ、俺の嫁！";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "ねえ、これで何も変わらないと思ってたの、もしかしたら本当にそうかもしれないけど――私は前からあなたを愛していたし、これからもずっと一緒にいたいと思ってた。でも今日、この神聖な式を経て……本当に幸せよ、シャルル！今までで一番幸せ。見て、グラディスもヤンも輝いてる！周りはみんな笑顔でいっぱい！ それより――そろそろお客さまと交流して、お祝いの言葉を受け取ってきて。終わったら戻ってきてね、忘れないで――私たち、シャープタウンに行くことになってるんだから。";
			link.l1 = "すぐにやるよ、可愛い子ちゃん。行く前にキスを一つくれ！";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "こんにちは、旦那。もうお客様たちとお話しになりましたか？";
			link.l1 = "まだだ、我慢してくれ、妻よ、すぐ戻るからな。";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "ええ、一度にあんなにたくさんの祝福の言葉を聞いたのは初めてよ。\nそれにね――ほとんどが本心だったと思うの！";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "ええ、この貴族たちは驚くほど誠実だわ――正直に言うと、もっと偽善や嘘があると思ってたの。でも、 もしかしたら私が幸せすぎて何も気づいていないだけかもしれない。\nでも、とにかく、私たちの仲間がシャープタウンで待っているんだもの！いつ出航する？";
			link.l1 = "今すぐだよ。鷲の翼に乗って、そのまま楽しい宴へ飛んでいこう。妻よ、 今夜は私たちの船室で過ごしてもかまわないかな？\n";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "ああ、旦那さま、とてもロマンチックですわ！それに、そんなにそわそわしないでくださいませ、 今やあたくしには人前であなたにキスする権利があるのですもの……はい、もう行きましょう！";
			link.l1 = "航海士、シャープタウンへ針路を取って、どんな理由があってもあたしたちを邪魔しないで！\n幽霊船団が迫ってきても、あたしは気にしないよ！";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "ああ、私の愛しい旦那様、あたしはとっても幸せだよ！今日は素晴らしい日だね…";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "行くよ、シャルル。この嘘つきは地面に着く前に死んじまうよ！";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "大丈夫よ、シャルル、心配いらないわ。ネイサンはどう？";
			link.l1 = "こんなにも血が……ダニー、彼は息をしてる？あ、息してるのが見える！";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "急いで、あなた、時間を無駄にしないで！";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "シャルル、大丈夫？なんてひどい殺戮なの！ごめん、私たちは上の階に閉じ込められてたの。あいつらが十人もいて、 まずそっちを片付けなきゃならなかったんだ！";
			link.l1 = "大丈夫、あたしが片付けたよ。ジャックとのあの話にやっと決着をつけられて、ほっとしてる……。彼は自業自得だったわ。";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "いいわよ、あなた。ここを片付けて戻りましょう。ナサンのことが頭から離れないの。 彼は私をあの弾から守ってくれたんだもの！\n";
			link.l1 = "そうだね、あなた、私も心配してるよ。行って、すぐ後ろにいるから。";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "マーカスを見つけたよ！貨物室に縛られて、気を失っていたんだ。";
			link.l1 = "生きてるの？";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "心配しないで、愛しい人。タイレックス男爵は私たちより長生きするわよ。さっき目を覚ましたばかりなのに、 もう元気いっぱいで、ラム酒とサーベルとブリッジを順番に呼んでるんだから。";
			link.l1 = "それが俺たちの昔馴染みのマーカスさ！ここが片付くまで少し休ませてやって、それから岸に戻ろう。";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "ごめんなさい、あなた…まずは忠実な友ティチンギトゥ、そして今度はジーノ…バルバゾンなんて、あれだけのことをしておいて何度も殺されるべきだったのに！";
				link.l1 = "ああ、たった一度だけやったんだよ。あたしも胸が痛い……でも、私たちが勝ったし、あいつはもう誰も傷つけられないわ。";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "ジーノのこと、本当に辛いよ、シャルル！知ったとき、信じられなかったんだ！\nあなたは大丈夫？愛しい人。";
					link.l1 = "あたしも信じられないよ……こんな終わり方なんて……今日がこんな日になるなんて、思いもしなかった。";
				}
				else
				{
					dialog.text = "将来の歴史家たちはプライベティア湾の大激戦について書くのかしら？\nコーストの兄弟団のバロンたちが堂々と戦場でぶつかった日――スペインのコスタ・ガルダは感謝の涙をぬぐっているに違いないわ！\nでも、また私たちの勝ちよ！仲間は生きて、敵は死んだ――なんて素晴らしい結婚祝いなの！";
					link.l1 = "ああ、まさに祝宴だね。でも、やり遂げたよ、あたしの天使。やり遂げたんだよ。";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "さあ、ダニーが町外れに家を見つけてくれたんだ。今は船に戻りたくない、掃除が終わるまではな。 ここで腰を落ち着けて、帰らぬ仲間たちに酒を捧げよう。";
			link.l1 = "「ああ、エレン、一緒に行こう。」";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "ジーノのこと、本当に辛いよ、シャルル！知ったときは信じられなかった！\nあなたは大丈夫？";
				link.l1 = "あたしも信じられないよ……こんな終わり方なんて……今日がこんな日になるなんて、思いもしなかった。";
			}
			else
			{
				dialog.text = "ホークを見かけた？ジーノが「危険は去った」と言った時、ダニーがあたしを外に出してくれたの。 すべてが無事で本当に嬉しいよ。仲間は生きてて、敵は死んだ――最高の結婚祝いだね！";
				link.l1 = "あたしもよ、ダーリン。それに、あたしたちの勝ちだわ。バルバゾンは死んだし、バロンたちは残った手下を集めてる。 戦いは終わったのよ。";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "シャルル、立っているのがやっとみたいだけど、あたし酒場に行ってきたの。そしたらね、 バーテンダーから信じられない話を聞いたんだよ。";
			link.l1 = "ああ、ヤンから聞いたよ、あいつもそこに行ったことがあるんだ。 どうやら俺たちの親愛なるインディアンが戦の道に進んだらしいな。サボ＝マティラ入り江まで歩いてみよう、 何人かがあっちの方向へ出ていくのを見たってさ。\n";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "なんてこった！それでこそだ、ティチンギトゥ！ふう、あたし、笑いすぎて頭が飛びそうだよ！ どうしてヨーロッパ人もこんな風習を取り入れないんだろうね？！ああ、シャルル、もう立ったまま寝そうじゃない！ さあ、ダニーがこのはずれに家を見つけてくれたんだ――ちょっと休まなきゃ。";
			link.l1 = "案内して…あの浜辺で前にも寝落ちしたことがある気がするよ。";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "…大丈夫だよ。";
			link.l1 = "それは良かった。";
			link.l1.go = "exit";
			link.l2 = "本当に？";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "はい。";
			link.l1 = "「それは良かった。」";
			link.l1.go = "exit";
			link.l2 = "さあ、何か悩んでるのが見えるよ！";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "あたしは全然平気だから、もう放っておいてよ！\nシャルル、地獄に落ちなさい！牢屋なんて大嫌い、あんたも大嫌い、この忌々しい島も大嫌い！今すぐここから出して！\nごめん…本当に牢屋は苦手なの、触らないで！";
			link.l1 = "ごめん。誰だって何かを恐れているんだよ。";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "「うわああ！ここから出してくれ！シャルル、何とかして！」";
			link.l1 = "しっかりしなよ！";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "私のキャプテン、敵が第二甲板の船体を破って乗り込んできたわ。船内のあちこちで戦闘が激しくて、 砲手のほとんどがやられてしまった！\n乗組員とエルキュールを救い出さなきゃ！あなたが行く？それとも私が行くべき？";
			link.l1 = "今回はあたしが行くよ、エレン！船の指揮を取って、ここから脱出して！";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "了解だよ、私のキャプテン。あたしは絶対にあなたを失望させないし、どうか気をつけて！";
			link.l1 = "わかってるよ、エレン。君も気をつけてくれよ！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "勝利です、私のキャプテン！上陸部隊は全滅し、敵は撤退を選び南へ向かいました。船の状態は許容範囲です。 乗組員の生存者数：\n "+GetCrewQuantity(pchar)+" 人々。報告は完了した！";
			link.l1 = "ありがとう、ヘレン、そして何を……";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "脱がせて、勝者さん。あなたの好きなように、あたしを好きにしていいんだよ！";
			link.l1 = "えっと…";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "行こう！";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "あら、やあ、エルキュール。ごめんね、ちょっと都合の悪い時に来ちゃったみたい！でも、くそ、あんたが生きてて、 しかもまた他人の血まみれで現れるなんて――まさにあんたらしい姿だね！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "へえ、エレン、あんたはすごい女だな！";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "まだ始まってもいないよ、私のキャプテン。お祝いしようか？";
			link.l1 = "説得なんて必要ないよ！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "見ないで、見ないで、見ないで……これは別の世界だよ、私のキャプテン！こんなの、ありえないよ！";
			link.l1 = "今やここは私たちの世界だと思うわ、ダーリン。あなたの言う通り、ぐずぐずしていられないわね…";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "この疫病であなたの娘たちも参っているようね、ロドリゴ。編み物でもさせて気を紛らわせてあげなさい！";
			link.l1 = "この会話は明らかに進展しそうにないわね。\n明日、一緒に教会へ行くって約束したでしょ。\n祈るために……もちろん。";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "あたしはあなたを誇りに思うわ、愛しい人！";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "「さて、シャルル…」";
			link.l1 = "また何を考えているの、エレン？";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "カリブで一番スキャンダラスなカップルが、島を二つも持っているなんてね！あたしの海賊の楽園イスラ・テソロと、 あなたの約束の地――文明がついに西インド諸島にやって来たら、どれだけ持ちこたえられると思う？\n";
			link.l1 = "私たちの一生分には十分よ、ダーリン。\nその後のこと？それは私たちにはどうにもできないわ。\n他の誰かが私たちの物語を語るでしょう。\n一番大切なのは、あなたと私が今ここにいて、一緒に幸せだということよ。";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "幸せと言えば……今から上の階に行くところなの。ろうそくに火を灯して、ベッドを整えて、それから日記でも書こうかしら……";
			link.l1 = "もう少しここにいるけど、そのあとであなたの「ベッド作り」を手伝いに行くわ。";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "あまり時間をかけないで……";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "そんなに忙しいの？残念だけど、わかるよ。あたしは他のことで時間をつぶすから。";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "覚えていてくれて嬉しいよ。伝えたかったんだけど、本当に感謝してるんだ。毎日誰かに……その、命を救われるわけじゃないからね。\nさあ、一杯やろう。今日はあたしのおごりだよ。";
			link.l1 = "エレン……グラディスは何て言うかな？";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "とても面白いわね、シャルル。さあ、行くよ、私を苛立たせないで。";
			link.l1 = "これってデートなの？";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "今行くよ、そんなにイライラしないで。";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "ははっ！そんなの無理だよ！あたしがベロベロに酔っぱらってなきゃね！";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "それでいいわ。";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "…彼女にはたくさんの美徳があったけど、酒には弱かったんだ。それが、あたしたちの出会いさ。";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "…父がどうしても軍務に就けと言い張ってね。私は折れて、推薦状を持ってパリへ行ったんだ。でも、 指定された住所には結局たどり着かず、画家になったのさ。";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "ああ、今やっと君が言っていた「美徳」が何のことかわかったよ。彼女の名前は何だったっけ？";
			link.l1 = "ルル。";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "ルル……君の話を聞いたら、パリのイメージがすっかり壊れちゃったよ。華やかな暮らしの都だと思ってたのに、 まるで豪華な売春宿みたいじゃないか。";
			link.l1 = "売春宿を非難するの？";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "はい、キャプテン、そしてああいう場所に通う男たちの気持ちはわからないよ。";
			link.l1 = "（マグをじっと見つめる）";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "（ひどく咳き込む）";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "うーん……人それぞれ……かな？";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "（笑）ハッ！あんたの顔、見ものだったよ！怖かった？もう一杯いこう！パリに乾杯！";
			link.l1 = "パリへ！";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "（笑）あ、あんたが！？芸術家だって？じゃあ、イギリス艦隊の美と誇りであり、強姦魔でただのクソ野郎、 ドノヴァンが、パリの芸術家の手で死んだってわけ？ああ、乗り込みの時に真っ白なジャボを着て、 そのクズをステッキでぶちのめしてくれたら最高だったのに！";
			link.l1 = "ああ、本当に運が悪かったよ。その日はちょうどジャボが洗濯中だったんだ。";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "（笑）まあ、ありがとう、シャルル。今夜がこの先どうなるかは分からないけど、もうすでに素敵な夜になってるわ。 もしかしたら、あたしの肖像画を描かせてあげてもいいかもね。でも、気をつけてよ、 パリの女の子たちを描いたみたいなスタイルじゃ絶対ダメだからね！";
			link.l1 = "ははっ！それは、あたしがあんたを描くのに同意したらの話だよ。";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "失礼します、私のキャプテン。あなたの冒険や高貴な…男女両方の娼婦たちの暮らしを聞いていると、サメに噛まれても信じられませんよ、 あなたがもっと有意義なことをせずに過ごしてきたなんて！まさか、 ただ絵の具を塗りたくって父上のお金を無駄遣いしていただけだなんて言わないでくださいね。それが本当なら、 私たちと一日たりとも生き残れなかったはずです。";
			link.l1 = "あたしには……他にやることがあったの。";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "宮廷生活と軍務を両立してたんだ、でも…へへ、もちろん父さんが望んだやり方じゃなかったよ。窓から何度か逃げ出したり、一度喧嘩したりして――それで衛兵たちと友達になったのさ。自然といろいろ覚えたし、体も鍛えられた。年上の仲間たちが、 打たれ強くなる方法や鎧の着方、剣の扱い方、それにちゃんと羽を伸ばすコツまで教えてくれた。特に最後のやつは、 あたしにぴったりだったね。信じられないかもしれないけど、朝から昼まで剣を振って、 昼から次の朝まで飲み続けられる奴なんて、そうそういないんだよ。";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "評判が悪く、財布も空っぽの貴族が、首都で楽にやっていけると思うかい？しかも初日に親父の推薦状までなくしてさ。 自分の立場を示して、誰にもバカにされないようにしなきゃならなかったんだ。家で習った剣術は忘れてなかったし、 横目で見られたらすぐ決闘で応じてやった。だんだん夢中になっていったよ。だけど、人を殺したことは一度もないし、 腕の立つ剣士に命を取られる前にパリを出ることができたんだ。";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "墓地で過ごす時間が多かったんだ。悪く思わないでくれ――それが俺たちの社交界では流行りの遊びだったんだよ。勇気試しに、夜の墓地へ行って、柵の上に空き瓶を並べて、 時間を計りながら撃ちまくるんだ。朝には弾丸を百発も無駄にして、シャンパンの箱も空っぽさ。 今ではそんな振る舞いを恥ずかしく思うけど、当時は勝者が大金を手にして、宮廷のご婦人方から…ご褒美ももらえたんだ。何もかも活用してたよ――火薬の調合にも少し手を出した。でも、どうして誰も紙薬莢の作り方を覚えようとしなかったのか…今でも分からないよ。";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "勉強もしたし、しかもかなり熱心にね――ソルボンヌに入る寸前までいったんだ。事務仕事もしてたけど、退屈になってやめたし、まあ、 いろんなことを少しずつやってきたよ。先生は父の古い友人で、理論より実践派だったから、 パリのいろんな面を見せてもらえたし、盗賊から貴族まで、あらゆる人と話す機会があった。\nその全部が、ここで役に立ったってわけさ。";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "「それで……終わり？やっぱり、あんたの中にはまだ何かが残ってるんだね、私のキャプテン。 あんた自身がまだ気づいていない何かが。乾杯！」";
			link.l1 = "「いい乾杯だね！」";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "君の話を聞かせてくれ、エレン。\n首都での俺の冒険なんて、三十にも満たない女の子が百人の男を乗せたスクーナーを指揮することに比べたら、 色あせてしまうよ。";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "三十歳手前か、シャルル？そんな大胆なこと言ったからには、次の酒はあんたの奢りだよ！ あたしの部下はみんな死んじまったし、もはやスクーナーの船長でもないんだ。正直、 もう一度船を指揮できるかどうかも分からないよ。";
			link.l1 = "ごめん、エレン。気に障るつもりはなかったんだ。でも、どうして自分の船長としての人生が終わったと思うんだい？";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "あたしの乗組員はもう全員死んじまったし、他の連中があたしを受け入れることなんて絶対にないんだよ。ええい！ まあいいさ、私のキャプテン、あんたは自分の人生をたくさん語ってくれたね。今度はあたしの番だ！ 真実はこのマグの底にはないんだから、もう謎めかすのはやめよう。";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "私の事情は特別なの、シャルル。父はこの海域で屈指の船乗りだったわ。フォレスト・デビルにも一目置かれていたし、 乗組員たちからは崇拝されていた。そして父は、命よりも私を愛してくれたのよ。";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "このうち一つでも失えば、父は私をロンドンの「文明社会」とやらに送るか、母のようにここで朽ち果てさせたでしょう。 最初はすべてうまくいっていたの。私は自由、本当の自由が欲しかったのよ、シャルル。そして、 忠実な乗組員とともに軍艦を巧みに指揮できれば、それがまさに手に入るの。 父はできる限りのものを私に与えてくれたわ。十二歳で父と一緒に海に出て、 最初の半年は船倉でネズミを追いかけて過ごし、それからやっと水夫たちと一緒に働くことを許されたの。";
			link.l1 = "ショーン・マッカーサーがあんたを船のネズミにしたのかい？悪いけど、エレン、それじゃもう元には戻れないよ！ 乗組員たちはあんたをどう迎えたんだい？";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "まあ、いい話にするためにちょっと大げさに言ったかもしれないね？父の船員たちはあたしを受け入れてくれたよ。 父は素晴らしい人たちを集めていたから。でも、それ以来、あたしはずっと怖いんだ……船倉とか、狭くて暗い場所全般がね。ははっ！スヴェンソンはそのことを知ったとき、父を殺しかけたんだよ！";
			link.l1 = "あなたにとって彼は大切な人なんだね。あなたの運命に関わったのは、ショーンに劣らず明らかだよ。";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "ええ。全てのバロンたちは父に面と向かって「愚か者だ」と言ったけど、クルーの登檣記録を破った後、 私に賛同して握手してくれたのは森の悪魔だけだったの。あの瞬間は一生忘れないわ。乗組員たちの歓声、 どこを見ても果てしない海の地平線。そして父の誇らしげな眼差し――見えなかったけど、心の奥で確かに感じていたのよ。";
			link.l1 = "私の勝利は、グアドループへ向かう初日に帆桁から落ちて終わったんだ。";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1+" 私の操舵手デリュクも、とても意味深な表情をしていたよ。"}
			link.l1.go ="drinking_my_background_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "あははは！想像できるよ！心配しないで、それはもう昔のことさ。今のあんたは立派な海の狼だよ！";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "我らの勝利に乾杯！";
			link.l1 = "「よし、よし！」";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "…それから少しずつ階級を上げていって、父や士官たちと一緒に船長の卓で評議に出るようになったの。たくさん学んだわ。 十五歳の時から軍事遠征にも連れて行かれるようになって、最初の戦いで人を殺したのよ。あれはひどい遠征だった…月曜日に出航するべきじゃなかったのに…本当に、するべきじゃなかった！";
			link.l1 = "十五歳で？エレン、君には驚かされるよ。";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "何が起きたのか、あたしには全然わからなかったよ。オランダの商人は先陣に会社の傭兵を連れてきてた。 奴らは大胆にも攻めに出て、うちのポープデッキに逆襲してきたんだ。で、あたしは馬鹿みたいに、 自分の命なんか気にもせず、金髪の頭をひょいっと出しちまった。そしたらすぐにピストルの柄で殴られたよ。でも、 その直前に、会社の間抜けな奴の腹にレイピアを突き刺すことだけはできたんだ。";
			link.l1 = "なんてこと……ショーンはどうしたの？それなのに、どうしてあんたを陸に蹴り出さなかったの？";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "父もあの戦いで無傷では済まなかったし、私の割れた愚かな頭を見て余計に気を落としたはずだよ。 父はゆっくりと衰えていって、たぶん気づいたのは私だけだった。そして、父は逝ってしまった。\n遺言によれば、私はレインボー号とその乗組員、そして船を一年間維持できるだけの資金を相続したんだ。";
			link.l1 = "「それで、乗組員たちはあんたを船長として認めてくれたの？」";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "おとぎ話の中で生きてるわけじゃないのよ、私のキャプテン。父の遺言に反発した者もいて――事態は嫌な方向に進んだの。\nもし一人でもレインボウ号の水夫が、私の指揮下で働くのを拒んで船を降りていたら、私の評判は地に落ちていたわ。 でもスヴェンソンが介入して、みんなをまとめてくれた。あの時は、誰も公然と乗組員を辞めなかった……その時はね。七年間、私は自慢の船を指揮して、フォレスト・デビルのために怪しい品を運び、宝を探し、 人生を謳歌してきた……でも、今となっては全部過去のことよ。";
			link.l1 = "昔はそうじゃなかった。でも、あなたはきっとまた自分の旗の下で航海する運命だと思うよ！それを祝って乾杯しよう！";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "船は取り戻せないかもしれないけど、あなたのレイピアはまだ手元にあるわ。";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "そう言われると、あたしも信じたくなるよ。飲もう！";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "「でも、俺のレイピアが幸せをもたらしてくれるのか？その答えはたぶん、このマグの底にあるんだろうな。飲もうぜ！」 ";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "ヨーロッパでのあなたの暮らしについて考えていたの…ねえ、あなたは都会の伊達男で、あたしはただの普通の女の子。でも、 もう私たちは世界で一番危険な場所で名を上げたじゃない。";
			link.l1 = "乾杯の音頭みたいだね！それで、私たちを結びつけるものって何かあるの？";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "まあ、私は父の背中の上に立っているんだよ。あなたのことは知らないけど、 あなたも家族から少なからぬ影響を受けてきたんじゃない？まだ気づいていないだけかもしれないね？";
			link.l1 = "兄上を牢屋から出したら、聞いてみるわ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "さて、これで終わりだよ、私のキャプテン。お互いに話もしたし、今夜はもう休もうか。";
			link.l1 = "ふむ、今夜はもう少し違う結末を期待していたんだけど。";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "夜はまだ終わっていないよ。\n一つ提案があるんだ――ゲームをしよう。うまく立ち回れば、もしかしたら願いが叶うかもしれないよ。";
			link.l1 = "カードをやるの？あたしも入るよ！";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "落ち着いて、海の狼さん。あたしはあんたとストリップポーカーなんてしないよ。";
			link.l1 = "ああ、ヘレン、その通りだよ。ここじゃプライバシーなんてないな。";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "それだけじゃないんだよ、シャルル……これはカードゲームじゃないけど、心配しないで、きっとあんたはこういうのも得意なんだろうね。『私は今まで～ したことがない』ってゲーム、知ってる？\n";
			link.l1 = "懐かしいわ。前世からのものね。それで、よく弾くの？";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "ずっとやってみたかったけど、一緒に遊ぶ相手がいなかったんだ。";
			link.l1 = "最初の一杯でそんな大胆な賭けをするなんてね。本当にいいの？";
			link.l1.go = "drinking_game_5";
			link.l2 = "ところで、みんなどこに行ったの？ここには私たちだけ？";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "ええ、最近の出来事の後だから、少しは人生を楽しみたいの。ちょっと馬鹿なことでもしてみたいって、わかるでしょ？";
			link.l1 = "いいえ、いつも結末はひどいものになるんだよ、ルンバ。";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "始めよう！レディーファーストだよ！";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "全員帰らせたよ――よそ者に聞かれる必要はないからね。";
			link.l1 = "いいえ、いつも結末はひどいものになるのよ、ルンバ。";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "やろうぜ！レディーファーストだ！";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "残念だけど、あなたの言う通りかもね。じゃあ、もう一杯どう？";
			link.l1 = "始めよう！レディーが先だよ！";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "手配しておいたよ――二階の部屋はあんたのものだ。さっきまで偉そうなフランスの将校が使ってたけど、 森の悪魔の連中が丁寧にどいてもらったんだ。\n少し休んでおいで――このまま通りをうろつかせたり、ましてや海に出させたりなんて、あたしが許さないよ。";
			link.l1 = "「はい、姐さん！」";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "ははっ！ひっく！つまり、あんたが最初ってことだな！";
			link.l1 = "気をつけて、ダーリン！うーん。あたし、船倉でネズミを追いかけたことなんてないよ！";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "そういうことかい？あんたには気を抜けないね！（飲む）";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "ぶるっ！あの記憶だけで……まあ、覚悟してよ、イケメンさん：あたしは一度も帆桁から落ちたことなんてないんだから！";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "見事だ！マドモアゼル、あなたに乾杯させてくれ！（飲む）";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "あたしは迷信なんて信じたことないよ。";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "それでよく自分を船乗りだなんて言えるわね！私たちがどんな連中か、あんたもよく知ってるでしょ。 航海が何をもたらすかなんて誰にも分からないし、いつどこで陸地が見えるかも分からない、 もしかしたら一生見えないかもしれないのよ。地図や航海器具だけじゃ答えは見つからないんだから！\nあんたの健康に乾杯！（飲む）";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "それで、実際に描いた女の子たちは……仕上がりを気に入ってくれたの？";
			link.l1 = "絵そのものはいつも気に入られたわけじゃないけど、えっと……出来上がったものは、いつも評価されたの。";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "シャルル！あの頃に出会っていたら、あんたを撃つか、身代金目当てで人質にしてたよ。それとね、 私は一度も絵筆なんて握ったことないんだ。";
			link.l1 = "おい！まあ、それはまったくありきたりだな。親愛なるエレン、君がまだ手を出したことのないものを挙げ始めたら……";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "わかったわ、いいでしょう。正々堂々とやるわよ。次はあなたの番、私のキャプテン。";
			link.l1 = "（すする）ひっく！うーん……モデルにピストルのグリップで頭を殴られたのは初めてだな。";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "（すする）うっ。あたしたち、全然違う遊び方してるじゃない、あなた。 てっきり一緒に飲みながらお互いのことを知り合うのかと思ったのに、実際は皮肉の応酬ばっかりで……で……ひっ。くそっ！";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "もっと面白くしようよ！できれば、さっき一時間前に話してたこと以外でお願い！";
			link.l1 = "飲み明かした後に見知らぬ場所で目覚めたことなんて、一度もないよ。";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "痛っ！くそっ、シャルル！ （飲む）";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "あたし…ひっく…信じられないよ。認める、悪かった――ルンバは昔から酒に手を出してた。でも、牢屋に入ったことなんて一度もないんだよ！";
			link.l1 = "どうやって……？";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "ははは！飲め、飲め！";
			link.l1 = "これは後悔するわね。（飲む）";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "さあ、あたしの大事な人。最後の質問よ、そしてあたしを出し抜く最後のチャンスだよ！";
			link.l1 = "いや…あたし…ちょっと外の空気を吸いに行こう。";
			link.l1.go = "drinking_game_enough";
			link.l2 = "俺は今まで何度も酒を飲んできたけど、こんなのは初めてだ……女の子とこんなに酔っ払ったのは初めてだよ。俺の誓いにかけて言うけど、酒を飲むのは本当に大きな罪だな……";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "えっ！";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "ま、待って……飲まないの？";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "あははは！それはおかしいね！あんた、目標が高いよ、私のキャプテン。まあ……ひっく……覚えておいて……";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "あたしは不運にも男ばかりの乗組員の中で暮らしているから、気をつけて振る舞わなきゃいけないの。 あたしは正直な女の子だよ。";
			link.l1 = "「よ、よかったね、ヘレン。」";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "もっと嬉しくなるよ、だって俺が勝ったんだから！でも、正直に言うと、男とこんなに酔っぱらったのは初めてだよ。";
			link.l1 = "（黙って酒をあおる）き、君に。おめでとう……ひっく……";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "おいおいおい！船長、どこへ行くの？もしかして、怒ってるのかい？";
			link.l1 = "わ、私……ちょっと休憩が……？剣を探しに行くだけ……";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "キャプテン、準備はいい？もう後戻りはできないよ。もし何か失敗したら、あんたに無理やり結婚してもらうからね。";
			link.l1 = "ふう！せめて息を整えさせてくれよ！本当にこれでいいのか、エレン？";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "ああ、くそっ、ぼーっと突っ立ってるんじゃないよ！今夜だけでも、あたしは全部忘れてはじけたいんだよ！";
			link.l1 = "今夜のことの後は、あたしの方こそ自分を見失いたくなりそうだよ。\nさあ、町中を起こす前に行こう。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "キャプテン、鍵を持って上の階に行って。\nそこに宝箱があるはずだよ、スヴェンソンが持ってたときにたぶん見たでしょ。\n樽を取って、すぐ戻ってきて。";
			link.l1 = "待ってよ、あなた、どうして私があなたのボスを盗まなきゃいけないの？";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "馬鹿なこと言わないでよ。あたしは子供の頃からここにいるんだもの。もし持ち主が戻ってきても、 ちゃんと対応できるし、あんたのこともかばってあげるよ。さあ、今さら帆を下ろすんじゃないよ！";
			link.l1 = "ナイフのように鋭い、本物の密輸業者だね！ちょっと待ってて、すぐに済ませるよ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "わかった？";
			link.l1 = "もちろんさ！俺が空にした宝箱はこれが初めてじゃねえし、これが最後でもねえぜ！";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "あんたを誇りに思うよ！ははっ！一流のアイリッシュウイスキー、『ブッシュミルズ』だよ！こんな酒、 酒場じゃ出してくれないからね。";
			link.l1 = "いい考えだけど、スヴェンソンに無くなったことがバレないかな？";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "彼はきっと気づくけど、自分では飲まないみたい。 どうやら海賊仲間のドッドソンへの贈り物として取っておいたらしいけど、そのドッドソンは行方不明か、 誰かを殺したとか……";
			link.l1 = "それはひどいよ！そんな贈り物、無駄にしちゃだめだ。樽を持って、場所を変えよう！";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "よく言ったね、キャプテン。でも、もう一つだけ聞かせて――他にその箱から何か取った？正直に答えて。";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "何かを持っていった、癖みたいなものよ、わかるでしょ。";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "いいえ。自分が海賊かどうかは分からないけど、盗人じゃないのは確かだよ。";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				Notification_Approve(false, "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "どういうわけか、あんたのこと信じちゃうんだよ……あたしもバカだね！";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "行って、何かを間違って持ち出していないか確認してきて。";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "おいおい、ダーリン！しっかりして！海風にキスされたあたしの顔、ここにあるよ！";
			link.l1 = "ふう、いやあ、その衣装はすごいね！布代をかなり節約したんじゃない？あたしは……ひっく……いろんなものを見てきたよ！でもこれは……でもこれは今までで一番すごいよ。";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "みんなそう言うけど、なぜかあんたの言葉は信じられるんだよ！本気で言ってるの？";
			link.l1 = "もちろん、それはあなたの体のラインをとても美しく引き立てているけれど……";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "「ああ、これで全部台無しじゃない！」";
			link.l1 = "…でも、庶民の間では畏敬の念を抱かせることに疑いはないわ！";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "この暑さの中で、庶民もそうでない人たちも重たいヨーロッパの服を着るという奇妙で広まった習慣には、 正直ちょっと驚いてるよ。\nそのせいで、私たちの村がますます滑稽に見えるんだよね……。\nあたしは自分の服が好きだよ、シャルル。この服を着ていると美しくなった気がするし、 それって女にとって大事なことなんだ。";
			link.l1 = "その服がなくても、ヘレン、君は変わらず美しいよ。";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "気をつけて、私のキャプテン！そんな甘いことを言われたら、あたしみたいな娘は堕落しちゃうよ！";
			link.l1 = "彼女が反対じゃないなら、俺も反対じゃないさ。";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "えへへ！他のことを聞いたほうがいいよ。あんたが好奇心を見せるの、あたし好きなんだ。";
			link.l1 = "それじゃあ、君の衣装について一つ質問を挟ませてもらおうか。そんな格好じゃ、 海の荒くれ者たちも船長としてまともに見てくれないだろう。";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "それに、一般的に海の男たちは女が船長になることを受け入れられないと思うの。だから、 私の服装も問題を増やしたわけじゃないと思う。あるいは、まだ新しいから問題になる暇もなかったのかも。これ、 自分で縫ったのよ！\nあはは！昔はああいうのを着てたわ……なんて言うんだっけ？今でも軍隊が着てるやつ！うう……今あれを見ると気分が悪くなるわ。";
			link.l1 = "制服？";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "ああ、そうそう、制服よ！赤い制服！あの男が着ているようなやつ。";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "ああ、ごめんなさい、少佐。お詫びに極上のアイリッシュウイスキーをご馳走させてください…ひっく…お詫びとして。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "シャルルは困ったことにならないよね、少佐？そうだって言って、お願い！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "嬉しいよ！一杯やろう！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "うっ…。見てよ、あたしが手に入れたものを！";
			link.l1 = "エレン……まさか、それで気を紛らわせようとしてるのか！？…絶対にやめてくれ！ダチュラは人を完全に支配して、力を奪い、意志を砕くんだ！気がついた時には生ける屍、 そしてすぐに死体になっちまう……";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "シャルル、でも…今は…";
			link.l1 = "言い訳はなしよ。厳しくして悪いけど、これは冗談じゃないんだ。これはあんたから取り上げるよ。 いったい何を考えてたのか信じられない……ほら、これを飲んでしっかりしな。";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "ごめんなさい、シャルル。あなたの言う通りよ、本当に。ほんの一瞬、心が弱くなっただけ。 もう二度とこんなことはしないわ。悪魔の誘惑から救ってくれて、ありがとう…";
			link.l1 = "その話はもう忘れよう……さて、教えてくれ、どうやって町で尊敬を集め、駐屯地の将校たちと良好な関係を保ち、 さらに現地人たちと親しくなったの？";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "ヤン・スヴェンソンは尊敬されていて、その敬意の一部が私にも及んでいるの。\n私たちの小さな町は、ヤンの取引だけでなんとか生き延びているわ。 彼は自分のカカオ農園の利益の一部を赤服兵たちと分け合っているし、 ミスキート族も彼に生活のすべてを頼っているのよ。";
			link.l1 = "どうしてそんなことになったの？";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "カスティーリャ人が支配していた頃は、インディオたちにあまり干渉しなかったんだよ。でも、 貴族ヒダルゴたちを追い出した後、うちの連中がこの土地の森を支配しようと決めたのさ。その時、 ヤンがこの問題をきっぱり解決した――ロンドンにまで人を送ったくらいだ！もちろん、善意からじゃないよ。どの茂みも敵意を持つ森でカカオを採るなんて、 絶望的な話だからね。だけど今じゃ、 インディオたちはヤンの密輸をポルトベロからブルーヴェルドまで手伝うだけじゃなく、 自分たちの森まで二束三文で伐採している。さすがだな、森の悪魔、見事だよ！";
			link.l1 = "彼のやり方を完全には認めていないようだね。";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "あたしはミスキート族を愛し、敬っているけど、ヤンの戦略も尊重してるんだ。\nおとぎ話の中で生きてるわけじゃないよ、私のキャプテン。";
			link.l1 = "ふむ……スヴェンソンとの関係は一見したよりもずっと複雑みたいだね……";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "あなたが思っている以上よ。あの奥さんが私に辛く当たるのも、ちゃんと理由があるんだ……ヤンはね、私が十五歳くらいの頃からずっと私を気にしていたの。 ちょうど私がレインボウ号の甲板を他の皆と同じ立場で歩き始めた頃で、 その時に森の悪魔の頭の中で何かが切り替わったみたい……でも、もう言い過ぎたわね、私のキャプテン。これ以上この話題には触れないでおきましょう。後ろ盾の噂話なんて、 あまり品のいいことじゃないもの。";
			link.l1 = "では話題を変えましょう。あなたはこの仲間たちによく馴染んでいるし、彼らもあなたを仲間の一人だと思っているのよ。 ";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "あたしはインディアンやジプシー、そして他のまともなはみ出し者たちと一緒にいる方が、ずっと気楽なんだよ。\n母さんのシチュー、浜辺の焚き火、レインボウ号の舷門――あたしなりの小さな居場所を作り上げてきたんだ、キャプテン。\n全部がうまくいきそうだと思った矢先に、その世界が音を立てて崩れちまったのは残念だけどね。";
			link.l1 = "樽はもうほとんど空っぽだよ……最後にもう一杯どう？";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "とても幸せ……一緒に過ごしてくれて嬉しいよ、キャプテン。あたし、本当にこういう時間が必要だったんだ。きっとあなたも、 そうだったでしょ。";
			link.l1 = "ああ、こんなふうにくつろぐのは久しぶりだよ。これはきっと忘れられない思い出になるね！";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "今のあたしのこと、チャールズ、きっと何を考えてるかわからないって思ってるでしょ。あたし、 もともとすごく心を閉ざしてる人間なんだよ。あたしは…くそっ、生きてるって感じたかっただけなんだ！誰かと話したかっただけ！";
			link.l1 = "グラディスは？ヤンは？";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "母さんは泣いてばかりだし、ヤンも今じゃまるで別人みたい。私の思い過ごしかもしれないけど、 なんだか私のことを恥じてるみたいで……ごめんね、私……（すすり泣き）。\nもういいよ、あたし。ごめん、ちょっと感情的になっちゃった。";
			link.l1 = "謝る必要はないよ。あたし、全部分かってるつもり。少なくとも、そう思ってる。";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "こんなことを言うのは、あたしたちが出会ったばかりだからだよ。長い付き合いの人にだって、 こんなに素直になるのは慣れてないんだ。みんなはあたしのことを「ルンバ」って呼ぶけど、 性格がそうだからってことらしい。でも見ての通り、全然そんな感じじゃないよね。酒、もう全部なくなっちゃった？";
			link.l1 = "少し前のことだよ、もう夜明けが近いね。";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "ごめんなさい、私のキャプテン。もし今夜に他の期待があったなら……あたしにはできない。今日は……無理なの。";
			} else {
				dialog.text = "今夜はありがとう、キャプテン。またこんな夜を過ごせるかもしれないね。";
			}
			link.l1 = "もちろん、エレン。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "ここまで連れてきてくれてありがとう、船長。\nさあ、周りを見てみましょうか？\nあたしの遺産を調べてみましょう。";
			link.l1 = "ここに来たことはないの？";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "いいえ、ここからはかなり遠いし、あたしは海賊じゃないよ。ここはもともと特に面白い場所でもなかったし、 ブレーズが殺された後は……ここに長居しない方がいいんだ。";
			link.l1 = "しないよ。もうあなたをここに連れてきたことを後悔してるんだ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "本当にやる必要があったの、船長？どうしてそんなにすぐ戦うの？まあ、勝者を責めるのも野暮だよね。さあ、 邸宅を見に行こうよ。ここには他に見る価値のあるものなんてないし。\n";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						Notification_Approve(false, "Helena");
					} else {
						dialog.text = "さすがだよ、私のキャプテン。戦う前に賢く問題を解決しようとしたんだね。\nさあ、邸宅を見に行こうよ。どうせ他に見る価値のあるものなんてないしね。";
					}
					
					link.l1 = "あの岸に引き上げられた巨大な船はどうしたの？";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "あたしのキャプテン、あんた、あのバカどもを見事に騙したね！本当に、もう少しで吹き出すところだったよ、 正直言って！さあ、屋敷を見に行こうよ。どうせ他に見る価値のあるものなんて、ここにはないしね。\n";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "あの岸に引き上げられた巨大な船はどうしたの？";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "ちょっと待ってよ、女の子にも息つく暇をちょうだい！本当にあなたがあのチャーリー・プリンスなの？";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "そんな時期もあったよ、確かに。感心した？";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "そうね、その通りだよ。探検してみたい気持ちはあるけど、正直に言うと、シャルル、ちょっと怖いんだ。行こう。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "ああ、神様、そうよ！後で全部ちゃんと話してね、いい？だって、あたしが聞いたのは……すごくいかがわしい噂話ばっかりなんだから！";
			link.l1 = "全部話すよ……いや、ほとんど全部だけどね。";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "楽しみに待ってるよ！さあ、邸宅を見に行こう。どうせここには他に見る価値のあるものなんてないしね。";
			link.l1 = "あの岸に引き上げられた巨大な船はどうしたの？";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "狭くて寒いあばら家に、ばかげた要求ばかり。もう罠にかかった気分だよ！";
			link.l1 = "今のところ、あなたはこの見込みの財産に満足していないのね？";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "いいえ、シャルル。たぶん私が神経質すぎるのかもしれないけど、今はそれが私の恐れと嫌悪のすべてを象徴しているの。 \n貸し出せたらいいなと思ってるけど……そのお金をどこで使えばいいのか、正直わからないわ。";
			link.l1 = "家賃の価値を甘く見ないでよ。あたしは家賃なんて払ってないし、 しょっちゅう乗組員への支払い方法を考えなきゃいけないんだ。あんたは新しい船を買うんでしょ、『レインボーII』――いい響きじゃない？";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "自分のためにお金を使う方法はいくらでもあるよ。まずは自分だけの剣と極上のワインを手に入れることから始めよう。 自分にご褒美をあげな、エレン。君にはその価値があるんだから。";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "ありがとう、私のキャプテン。そう言ってもらえて嬉しいよ。二度目に聞くと、なおさら心地いいね。 あなたはあたしのこと、よく分かってるんだね。";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				Notification_Approve(true, "Helena");
			} else {
				dialog.text = "ありがとう、私のキャプテン。そう言ってもらえて嬉しいよ。";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "あたしにそれだけの価値があると思う？こんな些細なことにお金を使ったことなんて一度もないけど、 何事にも初めてはあるものね。あなたはどうしてもあたしに海のことを忘れさせたいみたいだね、キャプテン？ もしかしたら、あなたの言う通りかも……";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				Notification_Approve(false, "Helena");
			} else {
				dialog.text = "あたしにその価値があると思う？こんな些細なことにお金を使ったことは一度もないけど、 何事にも初めてってあるものね。";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "いずれにせよ、検分は終わったわ。ここにはもう貴重品はなさそうね――下っ端どもがすでに全部盗んでいったみたいだし、きっと二階も同じ有様でしょうね。";
			link.l1 = "まるで変わったみたいだよ、エレン。前に一緒にいた時は……なんていうか、もっと心を開いていたんじゃないか？";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "何も変わってないよ、私のキャプテン。でも可哀想な女の子の肩には色々重くのしかかってきたんだ、はは！ 傷つけるつもりはなかったの。ただ、今は色々考えなきゃいけないことが多くてね。人生でこんな急展開、 毎日起きるわけじゃないでしょ。それに、私たちにはまだたっぷり時間があるんだから！\n";
				link.l1 = "それは良かった！さあ、ここを出よう。";
			} else {
				dialog.text = "色々と変わったのよ、船長。今はもっと大人になって、人生を違う目で見なきゃいけないと思ってる。\nお姫様と遺産の物語なんかじゃなくて、これは大きな政治なの。\nそして、私はまだ自分の立場を理解しなきゃいけないし、家族の立場も同じよ。";
				link.l1 = "それがはっきりしてよかったわ。ここを出ましょう。";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "はい？";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "おい、全部が盗まれたわけじゃないぞ！見てみろ、エレン！このサーベルは伝説級みたいだぜ、 地元のチンピラですら手を出すのをためらったくらいだ。";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "いいえ、何もないよ。";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "「うわぁ、こりゃ驚いた……これがあのブレーズ本人の伝説のカトラスじゃねえか！奴が死んだ後ですら、 海賊どもはこのカトラスを家から持ち出すのを恐れたほど、奴を敬ってたんだ。金や財宝はもちろん持っていったが、 たとえ未来の絞首台送りの野郎どもでも、名誉のかけらくらいは残ってたってわけさ……」";
			link.l1 = "ここは誰かが明らかに片付けているみたいだね。まるで持ち主が戻ってくるかのように……ここは家じゃない、記念碑だよ！";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "鋭い観察力に感謝するよ、シャルル。おかげでこの場所が台無しになっちゃったじゃない、はは！";
			link.l1 = "このカトラスは今やあんたのものだと思うよ。ブレーズは、いわゆるあんたの叔父さんなんだろう…";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "もっと怖くなっちゃうよ、私のキャプテン。あたし……できない。もし受け入れたら、あたしのこれまでの人生が本当に全部終わっちゃいそうで、怖いんだ。";
			link.l1 = "「それなら、遺産の一部じゃなくて、イケメンからの贈り物として受け取ってくれ。」";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "誰かと思ったら…なんてね！暗い考えを吹き飛ばしてくれてありがとう、船長。必ずこの剣にふさわしい自分になるよう、 しっかり鍛えると約束するよ！";
			link.l1 = "「君は最高の武器にふさわしいよ、エレン。さあ、行こう。ここはもう終わりだ。」";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "うおっ、こりゃ驚いた…これが…あのブレーズ本人の伝説のカトラスじゃねえか！奴の死後でさえ、 海賊どもはこのサーベルを家から持ち出すのを恐れたほど、奴を敬ってたんだ。金や宝はもちろん奪ったが、 どんな絞首台行きの悪党にも、まだ名誉のかけらくらいは残ってるもんさ\nあたしには…できないよ。もしこれを受け取ったら、今までの自分が完全に終わっちまう気がするんだ。";
			link.l1 = "それなら、遺産の一部じゃなくて、ハンサムな男からの贈り物として受け取ってくれ。";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "それは誰かしら？冗談よ！あたしの暗い考えを吹き飛ばしてくれてありがとう、私のキャプテン。";
			link.l1 = "ヘレン、君には最高の武器がふさわしいよ。気に入ってくれて嬉しい。";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "この剣にふさわしい者になるため、一生懸命鍛錬すると約束するよ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "私のキャプテン！チャーリー！";
			link.l1 = "「チャーリー？それは新しい呼び方ね！会えて嬉しいわ、あなた。」";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "うっかりミスしちゃったよ、はは！あんたに会えて嬉しいよ…";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "姉妹の連帯なんてこの程度か！私のキャプテン、あたし……本当に心配して、すごく会いたかったんだよ！";
			link.l1 = "「それで、どうして家に帰らなきゃいけなかったの？」";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "えっと…あっ、そうだ！あなたにちょっとした贈り物があるんだ、はい！";
			link.l1 = "三つの護符……エレン、どうして？あたしの後を追いたかったの？";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "こっちに来な、この馬鹿！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "この瞬間を台無しにしないでよ――あたし、ずっと夢見てきたんだから！";
			link.l1 = "しないよ、エレン。";
			link.l1.go = "after_kiss_a";
			link.l2 = "あたしに会うために一生待ってたの？光栄だよ！";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "エレン、ちょっと話が……ジャスティス島で、ある女性に会って、それで……";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "そのとおりだよ！全部、ぜんぶ話してもらうからね！あたしは船で待ってるよ、キャプテン！";
			link.l1 = "待って…";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "バカね！あたしを怒らせたいの？いいわ、もう怒ったから！ははっ！ダニーにこれ以上からかわれる前に、 ちょっと船に戻るわ…";
			link.l1 = "待って…";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "馬鹿ね！せっかくの雰囲気を壊さないでって言ったでしょ！会った…まあ、会ったのは分かったけど、まだ指輪はしてないみたいね。でも、逃げられると思わないで。 船に戻ったら詳しく話を聞かせてもらうからね。";
			link.l1 = "待って…";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "私のキャプテン、何か知らせ？その青ざめた顔を見れば、弁護士が助けるどころか、 また面倒を押し付けてきたってすぐわかるよ。";
			link.l1 = "ヘレン、君の言う通りだ。ロクスリーはかなりの前金を要求したし、この件自体も俺にはかなりの金がかかる。 もう我慢できない、ヤンを揺さぶってくる！まるで兄弟団が全部の出費を俺に押し付けてきたみたいじゃないか！";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "悪意はないのよ、シャルル。あの人たちはそういうもの――必要がない限り自分からは動かないだけ。ヤンもきっとあなたを助けてくれるし、 あたしも黙って見ているつもりはないわ。";
			link.l1 = "わかってるよ、エレン。君の考えを聞かせてくれ。";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "昔はヤンのために働いてたんだ――メイン中に貴重な木材を密輸してね。でも、あたしは抜け目ない女だから、 その航海の合間に自分のためにもしっかり蓄えを作っておいたよ。";
			link.l1 = "それでヤンにはバレなかったの？賢いね！";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "腕のいい財務官がいたのよ。つまり、そこそこの金額を集めて、ここからそう遠くない場所に隠しておいたの。\n今からヤンのところへ行くの？それならサン・フアン・デル・ノルテに寄りましょう。近くに洞窟があるし、 あとは何人か水夫を連れていけば、自分たちで全部運ばなくて済むわ。";
			link.l1 = "もう全部お見通しなんだな、ヘレン。ありがとう、時間があれば必ず訪ねるよ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "私のキャプテン、何か知らせ？その青ざめた顔を見れば、弁護士が助けるどころか、 また面倒を押し付けてきたってすぐ分かるよ。";
			link.l1 = "ヘレン、君の言う通りだ。ロクスリーはかなりの前金を要求してきたし、この件自体も相当な金がかかる。 もう我慢できないから、ヤンを問い詰めに行くよ！まるで海賊同盟が全部の出費を俺に押し付けてるみたいじゃないか！";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "おとぎ話の中にいるとでも思った？心配しないで、ここではみんな同じ立場だし、あたしが助けてあげるよ。だって、 あたしにもちゃんと相続権があるんだから、そうでしょ？";
			link.l1 = "そうだね……ねえ、何を考えているのか教えてよ！";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "サン・フアン・デル・ノルテに隠してある物があるんだ。近くに洞窟があるから、 全部自分たちで運ばなくて済むように水夫を何人か集めるだけでいいよ。";
			link.l1 = "もう全部お見通しなんだろう、ヘレン。ありがとう、時間があれば必ず寄らせてもらうよ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "ここがそうよ、シャルル！でも、あなた一人で行ってもらわなきゃ――あたし、洞窟は大嫌いなの！";
			link.l1 = "ヘレン、閉ざされた場所は誰でも苦手だよな。ここで待っていてくれ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "問題だよ！兵士の一隊がこっちに向かってきてる、しかも様子が物騒だよ。気をつけて、シャルル、 あれはただの沿岸警備隊じゃない――フランスの士官が混じってる！お願い、どうか無茶だけはしないで！";
			link.l1 = "あたしが今までに何か馬鹿なことをしたことがある！？";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "はは、二つ目の選択肢の方が魅力的だけど、シャルル、自惚れてないといいけど？";
			} else {
				dialog.text = "驚きはしないよ、シャルル…";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "終わった？今度はあたしの番だよ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "あたしの名はエレン・マッカーサーだよ！船長、あんたはあたしが誰で、誰のために働いてるか知ってるでしょ！ あんたの仲間たちに、特にそこに寝転がってる気取った馬鹿に、今日の結果を今から発表するって伝えな！\n";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "抗議？クロムウェル本人に手紙を書こうが、あたしは気にしないよ。まず第一に、ド・モール旦那は今日、 自分の名誉を失ってなんかいない。";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "二つ目は、タヴァン大佐が、派手な格好をした娘に売春婦呼ばわりしたせいで撃たれたことだ。";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "三つ目は、すぐに兵を引き上げて、今回のことは忘れること。さもないと、森の悪魔にこの話が伝わるかもしれないわよ。 ";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "質問はないようね。良い一日を、キャプテン。";
			link.l1 = "なんてこった、エレン、君はまるで火がついたようだ！";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "あとでね、シャルル。奴らがショックから立ち直る前に、ここを出よう。あたしも全身が震えてるよ。 ブルーヴェルドで話さない？";
			link.l1 = "同意するよ。";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "ここを出よう、あいつらがショックから立ち直る前に。まだアイアンウッドを回収しなきゃいけないでしょ？ 話はブルーヴェルドでできるよ。";
			link.l1 = "なんてこった！お祝いの言葉もなし？まあいい、行こう。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "やっと帰ってきた……";
			link.l1 = "起きたことについて、どう思う？";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "決闘なんて理解できないよ。男たちの道楽で、たいていは二人の死体が転がる羽目になるし、 運が良ければもっと増えることもある。\nそれに名誉ってやつも……あたしはね、名誉っていうのは、できる限り争いを避けようとする気持ちから生まれるものだと思うの。だって、 名誉なんて滅多に本当に価値のあるものじゃないから。\nははっ！何言ってるんだろ、あたしったら――くだらないことばっかり口走ってるよね！";
			link.l1 = "面白い考え方だね、エレン。でも、誰もがそう思うわけじゃないよ。";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "あいつらの思うつぼにはまっちゃったのは残念だね。大佐は明らかに取り憑かれてたし、 他の連中はただ騒ぎと噂話のネタが欲しかっただけさ。まあ、これ以上は言わないよ――今日はもう十分つらい目にあったでしょ。";
			link.l1 = "そうね、決闘の後はいつも虚しさが残るわ。今日はもう十分冒険したでしょ。次はどうしたい？";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "ううっ！ただ、あたしたちのことを誇りに思ってるって言いたかったんだよ。今日、あんたは本当に勇気を見せてくれた、 私のキャプテン。船員たちのヒステリーに流されず、彼らが一度くらいあんたを指揮したがってたのに負けなかった。 赤い制服の見せかけにも、青い制服の執着にも、しっかり立ち向かったじゃない。 あの大佐は明らかに死にたがってたけど、結局は妙な場所に傷を負っただけだったね、ははっ！";
			link.l1 = "ありがとう、エレン。君は本物の海軍士官のように見事に私たちを危機から導いてくれたね。自分のこと、 誇りに思っているかい？";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "ああ、今のは必要だったよ。残念なのは、青い制服だったことだね、赤いのだったらもっとよかったのに。でも、 少なくとも着てた奴は報いを受けたわけだし。";
			link.l1 = "あの人は確かに取るに足らない存在だと認めるよ。今日はもう十分冒険したわね。次は何をしたい？";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "あたしは帰るよ、私のキャプテン。モ…グラディスが恋しくてさ。今は家にいるから残念だけど、そうじゃなきゃあんたを招待したのにね！";
			link.l1 = "本当に、それは残念だね！";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "そんなに落ち込まないで。すぐだよ、私の大切な人。今はその間に……";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "んんん、これは最初の時よりもさらにいいね。覚えてる？あの偶像のそばでのこと。";
				link.l1 = "そんなこと、忘れられるわけないよ、あなた。";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "この瞬間を台無しにしないでよ――あたし、ずっとこんな時を夢見てきたんだから！";
				link.l1 = "しないよ、エレン。";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "あなたは一生ずっと私に会うのを待っていたの？光栄だよ！";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "あっ！しっかりしなよ、あたし！また会おうね、私のキャプテン。";
			link.l1 = "それまで、エレン。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "その通りだよ！すぐにまた会おう、私のキャプテン。";
			link.l1 = "また会おう、エレン。ああ、なんて素晴らしい女なんだ……";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "馬鹿ね！あたしを怒らせたいの？いいわ、もう怒った！ははっ！すぐにまた会いましょう、私のキャプテン。";
			link.l1 = "また会おう、エレン。ああ、なんて素晴らしい女なんだ……";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "家に戻るよ、キャプテン。弁護士との金の問題はもう片付いたんだろう？これからは厳しい障害が待ってるから、 できるだけ面倒ごとは避けよう。でも、どうせ向こうからトラブルがやってくるさ。";
			link.l1 = "「おったまげたぜ、本当かよ？」";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "ぶしつけで悪いね、キャプテン。あたしの運命も今、決まろうとしてるんだよ。";
			link.l1 = "分かっている、できるだけ品位を保って対処してみるよ。船で会おう、エレン。";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "了解だよ、キャプテン！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "次は何？あたしが見せてあげるよ。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "んんん、これは最初のよりもさらにいいわね。覚えてる？あの偶像のそばでのやつよ。";
				link.l1 = "そんなこと、忘れられるわけないよ、あなた。";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "この瞬間を台無しにしないでよ――あたし、ずっと夢見てきたんだから！";
				link.l1 = "あたしはしないよ、エレン。";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "あたしに会うために一生待ってたの？光栄だよ！";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "まったくだぜ！びっくりしたか！？グラディスはいま家にいねえ。中に入りたいか？";
			link.l1 = "私を招待するの？それで、何をするつもりなの？";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "いいや、エレン。ジャスティス島で俺を待っている女がいるんだ。あの子を裏切ることはできない。";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "また今度ね、あなた。ほんとはすごく会いたいけど、今日は本当に限界だったんだ。\n今度会うときは、失った時間の十倍取り戻そう。";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "そのとおりだよ！ちきしょう、驚いたかい！グラディスはいま家にいないよ。中に入りたい？";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "いいや、エレン。ジャスティス島で俺を待っている女がいるんだ。あの子を裏切るわけにはいかない。";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "また今度ね、あなた。ほんとはすごく会いたいけど、今日は本当に限界だったんだ。\nまた会ったときは、失った時間の何倍も取り戻そう。";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "あたしを招待するの？それで、何をするつもり？";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "馬鹿ね！あたしを怒らせたいの？いいわよ、怒ったわ！ははっ！償ってもらうからね、私のキャプテン。さてと！ グラディスはいま家にいないよ。入ってく？";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "いいや、エレン。ジャスティス島には俺を待っている別の女性がいるんだ。君にそんなことはできない。";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "また今度ね、あなた。あたしも本当はそうしたいけど、今日は本当に限界だったんだ。\nまた会えたら、失った時間の何倍も取り戻そうよ。";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "あたしを招待するの？それで、何をするつもりなの？";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "あら、私には誘惑の技が足りないってこと？それで、彼女はどうなの？その「彼女」って誰？";
			link.l1 = "彼女の名前はメアリー・キャスパー、そしてあたしは彼女を愛しているんだ。";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "赤い制服の赤毛のこと？赤い制服の……まあ、もし運命の印が必要だったなら、これがそうだね。つまり、縁がなかったってことさ。心配しないで、船長、 あたしの働きぶりには何の影響もないよ。";
			link.l1 = "ごめん、エレン。";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "ああ、私のキャプテン！女をこんな状態で放っておくなんて危険だよ！約束はちゃんと守ってもらうからね、さあ行って…あたしは一人になって、自分の問題を…自分でなんとかしなきゃ！\n船で会おう！";
			link.l1 = "なんて女の子だ！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "心配しないで、あなたが迷ったら、あたしがちゃんと導いてあげるよ。";
			link.l1 = "それじゃあ……案内して！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "何も言わないで、お願いだよ。";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "……もっとも、今日までは、この話題についてのあたしの知識は『レインボー』号の船員たちの下品な会話――会話と呼べるかどうかも怪しいけど――それだけだったんだよ。";
			link.l1 = "どうだった？現実は期待通りだった？";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "とても楽しかったけど、まだ完全に味わい尽くしていない気がするわ。どうしてかしら……";
			link.l1 = "見せてあげるよ！続けようか？";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "ああ、今やっとわかったよ！本当に素晴らしかったわ、私のキャプテン！";
			link.l1 = "少なくとも、あなたには驚かされたわ！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "あははは！それは面白いな、間違いない！あの子は今ごろ耳に蝋を詰めるか、 砦の一番高い見張り台まで逃げてるだろうよ！";
			link.l1 = "それは予想外だったけど、とても面白かったよ、あはは！";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "準備はいい、私のキャプテン？";
			link.l1 = "もう！？いやだ、エレン、どうか勘弁してくれよ。グラディスが急に現れたせいで、雰囲気がますます悪くなったんだ。";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "まあ、仕方ないね……でも……";
			link.l1 = "だめ、だめ、帆を下ろして！";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "じゃあ、しばらく一緒にいようよ。私たちの未来は本当に曇っていて怖いけど、久しぶりに、何も怖くないって思えるの。 きっとまた新しい不安が忍び寄ってくるかもしれないけど、今日は違う。今日は違うよ、私のキャプテン。";
			link.l1 = "今日はだめよ、あなた。今日は無理なの。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "「お話してもよろしいですか、船長？」";
			link.l1 = "「どうしたの、エレン？」";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "あのスネークアイのことは知ってるよ――いい奴だけど、ちょっと変わってるんだ。何のためか分からない依頼をよく人に押し付けるのさ。\nどうやら、あんたもその怪しげな“名誉”を受けたみたいだね。";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "そうなんだ、あいつに三つのお守りを持っていかないと、ホークの所へ行く手助けはしてくれないってさ。\nでもね、面白いことに、もう最初からお守りは全部持ってたんだよ！もしかして、 あいつは最初からそれを知ってたんじゃない？";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "そう、その通りだよ。あいつに三つのお守りを持っていかないと、ホークの所へ行く手助けはしてもらえないんだ。 今はどこで手に入るのか見当もつかないし、時間もどんどん無くなっていく。";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "ああ、残念だよ！灯台守たちからお守りを集めて回る羽目にならなくてよかったけど、 たまにはあんたの役に立てるかもって、あたし自身を証明したかったんだ。";
			link.l1 = "馬鹿なこと言うなよ、エレン。君は俺に何も証明する必要なんてないんだ。";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "手伝うよ！正直に言うと、一度くらいはあなたの役に立てたらと思ってたんだ、自分の力を証明したくて。";
			link.l1 = "ばかばかしいよ、エレン。君は俺に何も証明する必要なんてない。";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "それでも、あたしはあなたを助けたいんだよ。ほら、これ、あたしの部屋の鍵を――いや、部屋の中の箱の鍵を渡すよ！大したものは入ってないけど、役に立つかもしれないから。\nそれと……シャルル、今ここで笑い出したら承知しないからね！";
			link.l1 = "ええと、そんなつもりはなかったよ。君もこういうことに興味があるのかい？";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "あたしも船乗りだよ、船長、あんたと同じさ。この稼業じゃ、 運命の女神を味方につけるためにできることは全部やらなきゃね。";
			link.l1 = "ありがとう、エレン。本当に感謝してるよ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "ダーリン、あなたにプレゼントがあるの！";
			link.l1 = "なるほど、あそこにいる――立って微笑んでる！";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "あはは、やめてよ！昔、この辺の船大工に上等な絹を届けたことがあってね、 そのおかげで船の大改修を一度やってもらえる借りがあるんだ。最初は“レインボー”を任せようと思ってたけど、それは叶わなかった。でも、あなたの船なら、そういう手入れがすごく役立つと思わない？";
			link.l1 = "まさに素晴らしい贈り物だな、エレン――君の得意分野そのものだ！";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "気に入ってくれて嬉しいよ。いつでも彼のところに行って、あたしの紹介だと言って。 きっと最高の仕事をしてくれるから。";
			link.l1 = "もちろん！";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "「お話ししてもよろしいですか、私のキャプテン？」";
			link.l1 = "もちろんよ、あなた。";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("あんたの奥方が寂しがっていて、あんたの相手を求めてるよ。彼女のために部屋を用意して、 少し時間を割いてあげてくれないか\n","報告です：地元の酒場のベッドであなたのご臨席を賜りたいとのことです。たった五分だけでも結構ですが、 乗組員一同はもう少し長くいてほしいと願っています！","船で反乱が起きました、船長！あんたに内々でブラックマークを渡すよう命じられてるんだ。すぐに俺についてきてくれ！ ");
			link.l1 = "へへっ、えへん！ご要望どおりにいたします、シャープ士官！";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "今日は無理よ、あなた。今は色々ありすぎて。";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "あら、で、あたしみたいな可哀想な女の子にどうしろって言うの？\nわかったわ、あなた、また今度ね。";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "ははっ！そんなの聞くまでもないよ！もちろん、行こう！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "今すぐお前を海に放り込んでやるよ！";
			link.l1 = "おいおいおい！落ち着いて、ねえ！";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "こっちに来な、この悪党！";
			link.l1 = "冗談だよ、エレン！傷つけるつもりはなかったんだ！";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "へえ、本当に？冗談好きなんだね……";
			link.l1 = "あなたは一番美しくて、あたしはあなたに夢中だよ！";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "消えな、シャルル。";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "ふざけるな、尻軽女はお前だろうが！ヤンがちゃんとした女にしてくれたことを感謝しろよ、 じゃなきゃ今頃も通りすがりの男に股を開いてただろうが！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "娼婦め！行くよ、シャルル！";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "このカトラス、手にぴったりなんだよ！どう説明したらいいかわからないけど……他の剣やレイピアだと、いつも苦労してたの。でも、このカトラスは全然違う！すごくしっくりくるの！ありがとう、 シャルル！";
			link.l1 = "運命というものは、私たちを見つけ出すものだよ。ヘレン、君のことを嬉しく思う！";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "その手の話は他の誰かにしてよ、私には通じないから。私が純情で恋に夢中な馬鹿に見える？まあ、 確かにあなたに夢中なのは認めるけど、馬鹿呼ばわりはやめてほしいわね\n いい？あなたの好きにすればいいけど、私よりいい女なんて見つからないってことは覚えておいて。 もし娼館で探すつもりなら、どうぞご自由に。でもその時は、私はあなたの人生からきっぱり消えるから。";
			link.l1 = "エレン、俺は……";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "すべて分かっているわ、シャルル。あなたが愛しているのは私だけで、あれはただの本能的な衝動よね。\nでも、私の本能的な衝動が何か分かる？それは、自分の男からの尊敬よ。女は愛だけじゃ満たされないこともあるの、 あなた。\n今はこの誤解を忘れましょう。でも、私の言葉を少し考えてみて。いい？";
			link.l1 = "わかったよ、エレン。";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "どういうものか分かるでしょ。まずは女の子に少し頭を冷やさせてあげて。";
			link.l1 = "「はぁ……」";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "フランシス……彼のことは覚えているよ。いつもポートロイヤルで私の到着を待っていて、どうしようもないロマンチストだった。 海とは無縁の人と過ごす時間は新鮮で楽しかった――あの詩やセレナーデの数々……すべてが新しい体験だった。私が知らなかった世界を少しだけ垣間見た気がした。フランシスは裕福で、知的で、 しかもハンサム――まさに理想の相手だった。地元の娘なら誰でも彼に夢中になっただろうけど、 あの頃の私はレインボー号を沈めないことの方が大事だったんだ。";
			link.l1 = "詩人の繊細な心は、あなたの拒絶に耐えられなかったようね。彼の手紙には、あなたのことばかりが書かれていて、 二人が出会った場所を思い返していたわ。もし望むなら、彼が残したものは全部あなたに渡せるわよ。";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "彼が病気だったなんて知らなかったわ。今となっては、全部が馬鹿らしく感じる。彼の贈り物についてだけど……遺言や相続にはもううんざりなの。信じて、あたしには必要なものは全部あるし、それ以上もあるわ。だから、 あなたが持っていたほうがいいよ。";
			link.l1 = "どう転んでも、結局は彼の遺志があなたの役に立つことになる――つまり、私は知らず知らずのうちに彼の最後の願いを叶えてしまったというわけね。なかなか面白い話じゃない。";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}
