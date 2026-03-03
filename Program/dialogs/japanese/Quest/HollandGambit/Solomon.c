// Соломон Шнеур - старый еврей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "「この年寄りユダヤ人に何の用だ、若造？」";
					link.l1 = "ソロモン、よく考えて、遭難したあの失われた島を思い出してくれ。お前はそこに隠し財産を埋めたはずだ。 娘さんとも話をした。俺の上司ルーカス・ローデンブルクは、 お前の家族のために最善を尽くすよう俺に全権を与えてくれている。 今のお前にとって一番大事なのは家族の資本を取り戻すことだろう。そして俺の助けなしじゃ、 その金の匂いすら嗅げねえぞ。";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "おお、若いの、あんたかい？何かいい知らせはないのかい？ またキリスト教徒がこの哀れな年寄りユダヤ人を質問攻めにしに来たのか？\n";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "島は見つけたぞ、かなり苦労したがな。金の入ったお前の箱と、この頭蓋骨も見つけた。 これが例の祖父であり家長だったとかいう頭蓋骨なんだろう？";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "島は見つけたが、決して簡単なことではなかった。それに、金の入ったお前の箱も見つけた。\nだが、その箱の中に頭蓋骨はなかったぞ。";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "いいえ、今のところ質問はありません。";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "おやおや、若旦那、あなただったのかい？何か良い知らせでも持ってきてくれたのかい？それとも、 またこの哀れな年寄りユダヤ人を質問攻めにするつもりかい？";
					link.l1 = "島を見つけましたが、かなり苦労しました。それに、あなたの金庫も見つけました。どうぞ。";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "やあ、若いの。こんな哀れなユダヤの爺さんに何の用だい？";
				link.l1 = "こんにちは。いや、何もありません、ご挨拶に来ただけです。";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "こんにちは、若者よ。何か用があって来たんだろう……何の用だ？俺に得があるのか、それとも何か見落としてるのか？";
					link.l1 = "こんにちは、ソロモン。アビゲイルと話したいのだが。";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "やあ、若いの。こんな貧乏なユダヤ爺さんに何の用だい？";
				link.l1 = "こんにちは、ソロモン。別に用はない、ただ挨拶しに来ただけだ。";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "こんにちは、若者よ。何か用があってここに来たんだろう……何の用だ？俺に得があるのか、それとも何か見落としてるのか？";
					link.l1 = "アビゲイルと話す必要がある。彼女宛ての手紙を預かっているんだ。";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "やあ、若造。何の用だ？また娘への手紙か？";
					link.l1 = "いいや。アビゲイルはどこだ？";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "おい…俺の金のことを言ってるのか、若造？";
					link.l1 = "ああ、旦那。あんたがどこかの島に隠した金のことだが、本当にあんたもアビゲイルも場所を思い出せないのか？";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "わかった。そのフリュート船と船長のことは覚えている。アムステルダムで一度だけ彼を見かけたこともある。 そのフリュート船の名前は「ライデン」で、船長の名前はトフ・ケラーだった。";
					link.l1 = "いいぞ！これで手がかりができたな。";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "おお、またこの哀れなユダヤの爺さんに何の用だい？";
				link.l1 = "こんにちは。いや、何もありません、ご挨拶に来ただけです。";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "おお、今度はこの哀れなユダヤの爺さんに何の用だい？";
			link.l1 = "こんにちは。いや、何もありません、ただご挨拶に来ただけです。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "それで、俺に何の用だ？俺が何か知ってるような顔に見えるか？どうしてこんな神に見放された日に、 あんな場所に商品と金が転がってるなんて分かるんだ？考えてみろよ、外を歩いてる異教徒どもは、 俺みたいなユダヤ人を出し抜いて金を奪おうと狙ってるんだぜ！\n島がある。そこには誰もいない、アビと俺以外はな。一人もいない。本当に誰も。島の真ん中に洞窟があった。 俺はあの海賊ゴイ、アマレクから守るために、宝箱をそこに隠したんだ！中身は金でいっぱい、 ガラクタなんか一つもねえ。全部、故郷から苦労して運んできたんだ！俺が汗水流して稼いだものが全部そこにある。 それに、じいさんの頭蓋骨もな……信じてくれ、あれが俺たちを救ってくれたんだ、そうそう\nおおお、あれは古代の護符で、タルムードの魔法が込められてるんだ！神よ、アマレクからお守りください！オイヴェイ、 この異教徒の時代に一からやり直すのは本当に大変だよ！若いの、お前にも分かってほしい！ああ、 本当に分かってほしいよ！";
			link.l1 = "一体何をわけのわからんこと言ってやがる、この狂人め。どうでもいいさ。自分で片付けるぜ。じゃあな！";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "おい、神はいるもんだな、あんたは本物の男だぜ！俺の金だけじゃなく、シュネウル家の名誉まで取り戻してくれた！ あんたが防いでくれたこの恥、どれほどのものか！ローデンブルク旦那も、 あんたみたいな船長が配下にいることを誇りに思うだろう。ドクロはローデンブルク旦那に渡すよ、 あの人はそれに見合う大金を払うと約束してくれたからな。個人的にも礼を言いたい、あんたは立派なシャボス・ゴイだ――このユダヤ人からのささやかな感謝のしるしとして、このお守りを受け取ってくれ。";
			link.l1 = "ええと、まあ、ありがとうございます。";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "おお、神はいるもんだ、そしてあんたは本物の義侠だぜ！金だけじゃなく、シュネウル家の名誉まで取り戻してくれた！ あんたが防いでくれた恥は計り知れねえ！頭蓋骨の件は……まあ、気にすんな、あいつは元々イカれたバカ野郎だったしな！ローデンブルク旦那も、 あんたみてえな船長を部下に持てて誇りに思うだろうよ。心から礼を言わせてくれ、あんたは立派なシャボス・ゴイだ――どうか、このお守りを記念に受け取ってくれ。";
			link.l1 = "ええと、まあ、ありがとうございます。";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "何だと？何を言っているんだ、若造？本当なのか？ちょっと見せてくれ…… ";
			link.l1 = "これがあなたとアビゲイルのためのお金です。ですが、残念ながらお祖父様の頭蓋骨はまだ見つかっていません。";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "ああ、お金、お金、お金、素晴らしいお金……ふむ、でもこれは私のお金には見えないな……私の愛しい金貨の匂いもしない。だが、結局のところ、お金はどれも同じだろう、坊や？文句は言わないさ。 「もらい物にケチをつけるな」ってね、我々の間ではそう言うんだ！貯金を返してくれて本当にありがとう。 私からもお礼をしたい、どうぞこのお守りを受け取ってくれ。さあ、アビに良い知らせを伝えておいで。 私はこれを数えないといけないからな。";
			link.l1 = "「お帰りなさい、ソロモン。」";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "おいおい、気をつけな！ローデンブルク旦那はもう少しで俺の義理の婿になるところなんだぜ。 助けを呼べば駐屯地の兵隊どもがすぐにここへ駆けつけてくるからな！";
			link.l1 = "てめえ、何者だ？";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "聞いてくれ、船長。私はあの娘の父親、ソロモンだ。正しいことをしてくれ、私の失くしたコインと、 あの子の曾祖父の翡翠の髑髏を持ってきてくれ。この年老いたユダヤ人はお前ほどずる賢くはないが、 それでもお前が娘に何かを求めているのは分かっている。\nもしかしたら誰かに、私を知る船長に頼まれて来たのかもしれんな。アビにはすべて話すつもりだ、心配するな。 今は家にいない、異教徒のお前のような罪人の魂のために祈っているのだ。";
			link.l1 = "ほとんど意味がわからなかったぜ……くそっ、お前は本当に厄介な奴だな。じゃあな、ケチなじじい。";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "手紙だと？そりゃ驚いたな！いいか、坊や、ローデンブルク旦那はもうすぐ俺の娘婿になるんだ。 だからお前はさっさとここから失せな、俺はあいつが気に入ってるんでな！";
			link.l1 = "聞けよ、俺はあんたの婿が誰だろうと知ったこっちゃねえ。この手紙はアビゲイルに渡さなきゃならねえんだ。 あいつがどこにいるか知ってるか？それと、あんた一体何者だ？";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "俺が誰かって？俺はあの娘の父親、ソロモンだ……それに、俺はお前が気に入らねえ、ゴイ。";
			link.l1 = "もし俺のことが好きだなんて言われたら、もっと心配になるぜ。さて、まだ俺を見下すつもりか、 それともアビゲイルを呼んでくれるのか？もう一度言うが、俺は使者だ！お嬢さん宛ての手紙を持ってきたんだ！";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "この手紙を私に渡しなさい。私が娘に届けます。";
			link.l1 = "この手紙を渡す前に、お前の髪を剃って鼻をひねってやるぜ。俺はこの伝言をあの女本人に届けるよう命じられてるんだ。 親父のことなんざ一言も聞いてねえし、興味もねえ。アビゲイルはどこにいる？";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "俺が叫んだらすぐに、坊や、この町の兵士全員が一斉に駆けつけてくるぞ。\nそんなに意地を張るなよ、俺が全てを握っているのは分かってるだろう。";
			link.l1 = "イエス様、マリア様、ヨセフ様！本当かよ？それでどうなるってんだ？ 手紙を届けただけで俺を縛り上げるとでも思ってんのか？馬鹿言うなよ！";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "お前は気が狂ったのか？お前の手紙でうちの娘は半分死にそうなほど興奮してしまったじゃないか……あのイギリス野郎の船長を追いかけると決めて、最初に出航する船で旅立ってしまったんだ！オイヴェイ、可哀想な娘よ！ この老ユダヤ人はこれからどうすればいいんだ？わしの人生はもうおしまいだ！なんて恥さらしだ！ わしをこのまま悲しみに沈ませてくれ、あるいはここに残ってほくそ笑むがいい、もうどうでもいい！ああ、 哀れなアビゲイルよ！お前は父親の白髪頭を絶望のうちにシェオルへと導いたのだぞ！";
			link.l1 = "へえ、そう来たか！あの娘、もう一瞬も待てなかったんだな。じゃあな、ソロモン！";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "どう見えるって？俺とアビゲイル以外誰もいない、ただの島さ。そこで俺は自分の箱を隠したんだ、 あの海賊野郎アマレクに奪われないようにな。俺が汗水垂らして正直に稼いだものは全部その箱の中にあるんだよ…";
			link.l1 = "教えてくれ、ソロモン。君の娘さんが話していたフリュート船の名前を思い出せるか？それと、 その船長の名前は何だった？";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "ふむ……さて、わしには分からんのう。この哀れな年寄りユダヤ人の頭は、 まるでゲフィルテフィッシュの鍋みたいにごちゃごちゃじゃ！それに、なぜそんなことを聞くんじゃ、若いの？";
			link.l1 = "私はただソロモン、あなたの娘さんを助けたいだけです。何も約束はできませんが、できる限りやってみたいと思います。 以前の雇い主が彼女にひどい仕打ちをしたので、その後始末として彼女が落ち着けるよう手助けしたいのです。";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "おお、そういうことなら……";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "若者よ！待て！";
			link.l1 = "はい？";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "若者よ！私と娘のために尽くしてくれたこと、心から感謝したい。君は私たちを救ってくれた。最初に会ったとき、 冷たく接し、君の誠意を疑ったことを申し訳なく思っている。どうか、この老いたユダヤ人を許してくれ。 君は本当に異邦人の中でも祝福された人だ。さて、洞窟で私の金以外に何か見つけなかったか？";
			link.l1 = "いいや、ソロモン。金以外には何もなかった。俺はヴァン・ベルクの殺し屋どもと戦わなきゃならなかった――お前の船を数か月前に沈めたのはあいつだ。やつらがすでに何かを盗んでいたのかもしれねえ……他に何があるはずだったんだ？";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "ああ、大したことじゃない……ただの古い家宝さ……まあ、気にするな！どうせあいつは馬鹿だったんだ！それと……もう一つだけだ、若造…… ";
			link.l1 = "続けてくれ。";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "お前さん…いや、実はお前さんについて少し調べさせてもらったんだ。うちの総督はお前さんを高く評価しているし、 名のある船長だとも聞いている。\nひとつ秘密を教えてやろう…うちの娘がお前さんのことをとても気に入っているんだ。本人がそう言っていたよ。もしかしたら…考えてみてくれないか？アビゲイルは本当にいい娘だ、保証する。旅の途中で出会ったどんな異国の女よりも、ずっとな。 ";
			link.l1 = "おいおい……そんなに簡単な話じゃねえぞ、ソロモン。あんたの娘さんは本当に貴重な宝石みたいなもんだ。大事にしてやれよ。";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "よく考えてみなさい、若者よ。\nもう一度考え直して、また戻ってきてください！\nまたお会いできるのを楽しみにしていますよ！";
			link.l1 = "ああ……じゃあな、ソロモン。";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "おおい……新しい人生を始めるのは時に無理なんだよ、若造。\n貧乏暮らしなんて、年寄りの馬鹿にはこれ以上つらいことはねえよ。";
			link.l1 = "すまない、ソロモン。しっかり立ってキリストを求めなさい。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("あなたは "+GetSexPhrase("泥棒だ、旦那！衛兵、そいつを捕まえろ","泥棒だ、あの娘だ！衛兵ども、あいつを捕まえろ")+"!!!","見てよ！僕が物思いにふけっていた隙に、君は僕の胸を探ったんだね！泥棒だ！誰か捕まえてくれ！！","衛兵！強盗だ！泥棒を捕まえろ！！！");
			link.l1 = "くそっ！";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
