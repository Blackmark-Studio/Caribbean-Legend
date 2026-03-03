void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			link.l1 = "何でもありません。";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "お部屋にお邪魔して申し訳ありません、旦那船長。しかし、これは非常に重要なことなのです。";
			link.l1 = "そうだといいがな、アロンソ。お前たち全員が自分の部屋みたいにここにずかずか入ってくるようじゃ、困るぜ。で、 どうしたんだ？";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "あなたのロッカーが荒らされていたのを見つけました。";
			link.l1 = "「何だって！？ちょっと待て……どうやってそれを知ったんだ？それに、お前たちは俺の船室で一体何をしていたんだ？」";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "あなたが外出している時や、ベッドで休んでいる時に、時々あなたの部屋を掃除していますよ。\n気づかなかったんですか？それとも、ただ忘れてしまったんですか？";
			link.l1 = "ああ、そうだったな。さて、もう行っていいぞ。";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "チャールズ船長、見てください！誰かがあなたの大きな引き出しを漁っていました。";
			link.l1 = "何？いつそれに気づいたんだ？誰がやったか知っているのか？";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "少し前、あなたに会いに来る途中でした。\nそれが誰なのか、精霊たちは何も語ってくれません。";
			link.l1 = "いい演出だな、Tichingitu。さて、失礼するが、何か盗まれていないか確認しないといけない。";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "おい、船長、何を見てるんだ？誰かがお前の持ち物を漁ってたぜ。俺でも気づいたくらいだ。";
			link.l1 = "お前じゃなかったのか？結局、俺はフランソワほど気前よく報酬を払ってはいないからな。";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "へっ、もし俺が盗人だったら、お前に言うわけないだろ？貴重品を持ち去って、証拠も残さずきれいに片付けるさ。 こんな散らかし方、俺のやり方じゃねえよ。";
			link.l1 = "認めたくはないが、お前の言う通りだ。\nさて、クロード、皮肉は後にしてくれ。盗人が何を盗んだか確認しなければならない。";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "船長、今日あなたのロッカーが誰かに荒らされていたのに気付きました。お気付きになりませんでしたか？";
			link.l1 = "何だって？俺はいつもロッカーを確認してるわけじゃないし、フォルケ、ずっと船室にいるわけでもないんだ。 正直に言ってくれ――お前なのか？またやらかして、前に上陸したときにさらに銀行から借金したんじゃないのか？";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "とんでもございません、船長。私のポケットにもロッカーにも、あなたの物は何一つありません。そして、 これからも絶対にありません。";
			link.l1 = "そうでないことを願いたいですね。君は行っていい、私は何が足りないか確認する。";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_0");
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "シャルル・ド・モール、そうだな？";
			link.l1 = "その顔つきを見れば、もう答えは分かっているようだな。で、何の用だ？";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "あなたの頭だ。";
			link.l1 = "興味深いですね！この会話の始まり方、私としては気に入りました。しかし、これ以上進む前に、 私が一体誰に害を与えたのか、せめて教えていただけませんか？もしかしたら交渉できるかもしれません。";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "俺たちは素人じゃねえんだ、ド・モール旦那。たとえ教えたところで、あんたには何の役にも立たねえよ――雇い主はもう諸島を離れちまったんだ。あんたはそいつに害を与えることも、謝罪することもできねえ。 報酬はもう受け取った、あとは約束を果たすだけだ。";
			link.l1 = "すでに報酬を受け取ったのなら、なぜこれ以上血を流す必要があるんだ？";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "俺たちは素人じゃねえ。評判を大事にしてるんだ。";
			link.l1 = "残念ですが、今回はそれを果たすことはできないでしょう。";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "それはどうかな。終わったらあいつの死体を調べろ！見つけたものは全部燃やせ！";
			link.l1 = "何を燃やすんだ……";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "仮面の男が言っていたこと……まさか……？";
			link.l1 = "どうした、ロンウェイ？俺に賞金稼ぎが追ってくるのは初めてじゃないが、今回はお前、やけに気にしてるようだな。";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "ロンウェイは、誰がこれらの男たちをあなたに差し向けたのか知っていると思います、ロードキャプテン。";
			link.l1 = "私が知っておくべきことですか？";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "これがローデンブルク卿のやり方だ――自分を助けた者でも、知りすぎた者は排除するのだ。";
			link.l1 = "本当に……あの仮面の男は、雇い主が最近群島を離れたと言っていたよな。まさにルーカスが企んでいたことだ！ もっと襲撃があると思うか？";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "何事にも備えておくのが賢明でございます、My Lord Captain。";
			link.l1 = "賢いお言葉です。気をつけます。\nしかし、ルーカスは何を狙っていたのでしょう？私が何か持っていると思ったのですか？\n何か心当たりはありますか、ロンウェイ？";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "うーん、いいえ、ロンウェイにはそれが何か全く分かりません。";
			link.l1 = "それは残念だね。でも、でしょ？さあ、ここを出よう。";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			ReturnOfficer_Longway();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "旦那船長、ロンウェイがお話ししたいことがございます。とても重要な件です。";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "どうした、ロングウェイ？ルーカスの別れ方が気になるのか、それとも新しい発見でもあったのか？";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "もちろん！どうしたんだ？";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "残念ですが、違います。";
			link.l1 = "「それなら何なんだ、ロンウェイ？」";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "ロンウェイは言えません。しかし…退出の許可を願いたいとのことです。";
			link.l1 = "去るって？本当に？どうして、ロンウェイ？私があなたの船長として、その理由を知る権利があるわ。";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "その通りでございます、旦那船長。しかし、ロンウェイは労働者でも召使いでもありません。 自らの意志でお手伝いに参りましたし、同じく自らの意志で去ることもできます。永遠ではございません――大事な用事がございますので。それが済みましたら、ロンウェイは戻ることを願っております。";
			link.l1 = "これは何のことですか？話してください――もし船長としてでなくても、あなたと多くを共にした者として。";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "ロンウェイが言えるのは、ただ一つ――昔、誓いを立てたことだけです。\nその誓いを果たす時が来ました。\nさもなければ……ロンウェイの人生には意味がありません。";
			link.l1 = "お前の言う通りだ、ロンウェイ――お前は囚人じゃないし、俺は看守じゃない。好きにしろ。幸運を祈る。";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "行ってもいいが、せめてどこへ向かうのか教えてくれ。あまり詮索せずに手を貸せるかもしれない。";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "私にも大事な任務がある――兄弟を救うことだ。そのためには全員の力が必要だ、ロンウェイ、お前も含めてな。お前なしでは成し遂げられないんだ。 ";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "私の哀れみや義務感に訴えようとしないでください。私はすべて理解しています。\n誓いを立てたことがありますか、My Lord Captain？";
			link.l1 = "もちろんだ。だから、ありのままをすべて話してくれれば、私と部下たちが必ず力になる。";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "ロンウェイにはできません。ただ……できないのです。これは大いなる謎であり、しかも私が語るべきものでもありません。";
			link.l1 = "それは残念だ。俺たちの間には信頼があると思っていた。お前は船を降りられない――今や全ての士官は俺の味方だ。";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "お前の言う通りだ、ロンウェイ——お前は囚人じゃないし、俺は看守でもない。好きに行け。幸運を祈る。";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "そんなことはできません！";
			link.l1 = "残念だが、できるよ、ロングウェイ。さあ、自分の任務に戻れ。";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "こんなに簡単に解放してくれるとは思いませんでした。ありがとうございます、My Lord Captain。";
			link.l1 = "ああ、たいしたことじゃありません。しかし、教えてください――用事が済んだら、どこでお会いできますか？";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "ロンウェイは本当はどれだけ言いたくても、どうしても言えません。しかし、 ロードキャプテンが助けようとしてくださるお気持ちには感謝しております。";
			link.l1 = "よろしい。誓いを果たしたら、どこであなたを探せばよいのですか？";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "私は一ヶ月で用事を終える予定だ。その後、ロングウェイはバステールの酒場でさらに一週間あなたを待つだろう。";
			link.l1 = "まあ、どう言おうと、友よ。\nこれは別れじゃない。またバステールで会おう。";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "やあ、船長。";
			link.l1 = "旦那、その薄笑いが気に入らない。";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "私は打ちひしがれています。やっとあなたが自由になったことを伝えに来ました。\nですが、この豪華な船室にもう少し滞在したいのであれば、ご自由にどうぞ。";
			link.l1 = "とんでもない。で、ロンウェイが見つかったの？どこにいるの？牢の中かい？";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "別の世界だったら、奴は誰とも口をきかず、いきなり戦いに突入しただろう。";
			link.l1 = "くそっ！捕まえるだけでよかったのに。";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "「捕らえるより殺す方がずっと簡単な人間もいるって、知ってるだろう？ お前に恨みを持っていないことを感謝すべきだな――お前の中国人がまた虐殺を引き起こしたから、そいつを抑えるために狙撃兵付きの部隊を何組も追加で必要だったんだ。」 ";
			link.l1 = "ええ、確かに。感謝いたします。";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "そういえば、あいつはお前の友人だったからな、奴の持ち物から何枚か書類を見つけたんだ。\n俺たちには何のことか分からなかったが、お前なら分かるだろう。血で汚れていない部分には、 何やら意味不明な文字が書かれていたぜ。";
			link.l1 = "それは…くそっ。返してくれてありがとう。さようなら、士官殿。";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "一緒に来い、司令官があなたと話したがっている。";
			link.l1 = "これは私が中国人を探している件に関係しているのでしょうか？";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "ご自分の目で確かめてください、旦那。";
			link.l1 = "私は何か罪に問われているのですか？";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "全くそんなことはありません。誰もあなたを逮捕したり拘束したりしようとはしていません。今のところは。\n私が「司令官があなたと話したい」と言ったのは、まさにその意味です。";
			link.l1 = "ああ、まあ……";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "何か考えはあるか？この黄色い肌の男はとんでもなく危険だ。ここに送り込まれたのは俺たちが最初の部隊じゃない。 命令は命令だが、しっかりした策もなく無駄死にするのはごめんだ。";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "あいつは中で一人きりだ、そして俺はお前と一緒にいる。俺があいつを片付ける――お前たちは俺の援護に集中しろ。何とかなるさ。";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "俺にはある。お前ら全員、ここで死ぬんだ。";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "心配しないで、ただ話をしに行くだけだ。";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "申し訳ないが、今日はお前たち全員が死ぬ日だ。\nしかも、それは中国人の手によるものではない。";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "お前は賞金稼ぎじゃねえのか……だが、たとえそうでも、あの忌々しい中国野郎の仲間だろうが！";
				link.l1 = "その通りだ。どうせお前を始末しなきゃならないんだ、避けられぬ運命を先延ばしにする意味はない。";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "どういう意味だ！？助けてくれるって約束したじゃないか！";
				link.l1 = "どうせあなたは俺たちに穏便な道を用意してくれなかったと思う。\n個人的な感情はない。";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "そう信じたいですね。";
				link.l1 = "もっとひどい目にも遭ってきたぜ。中国人一人くらいで俺たちが終わるわけねえだろ。行くぞ、野郎ども！";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "もし話し合いが計画通りに進まなかったらどうしますか？";
				link.l1 = "それは嫌だが、そうなれば自分を守らねばならん。行こう。";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "旦那船長！？ロンウェイにはあなたが奴らと一緒にいるなんて信じられません！";
			link.l1 = "違うよ、ロンウェイ、俺はただ話しに来ただけだ！君が思っているようなことじゃないんだ！";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "なら、お前は一人で来たはずだ。こいつら兵士の助けを借りて俺を油断させ、襲おうとしているんだな！";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "できるなら、そうしている。俺がいるから、まだ奴らはお前を襲っていないんだ。落ち着け、話そう、でしょ？";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "くだらねえこと言うな！俺がその気なら、とっくにお前を殺してる。武器を捨てろ、話をしよう。 これはお前の船長からの命令だ。";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "ああ。ロングウェイはあなたを信じております、我がロードキャプテン。";
			link.l1 = "そこだ、これでいい。さて、話してくれ…";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "旦那、何が起きているんです？これは……感動的な再会ですか？あなたはあの中国の野蛮人を始末する手助けをしてくれるはずだったんじゃありませんか？";
				link.l1 = "そうだ。俺が彼を連れて行く、これで殺し合いは終わりだ。お前は司令官に、俺たちが一緒に彼を殺したと伝えるんだ。 いいな？";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "よくやったぞ、船長！奴は武器を捨てた。君がいてくれて心強い。さあ、あいつを司令官のところへ連れて行こう。";
				link.l1 = "なぜ私がそんなことをしなければならないんだ？ロングウェイの行動については、私は罰金を金貨で支払った――しかも十分すぎる額だ。あなたの同僚の士官たちもその場にいた――彼らが証言してくれるさ。司令官も私が部下を連れて船に戻ることを許可したんだ。";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "司令官殿はこの血塗られた金にもううんざりかもしれませんが、俺は違います。 あの血まみれの洞窟で奴が殺した連中の中には、俺の友もいましたからね。それに、 どうせ俺たちがあの中国人を殺しても、司令官殿は気にも留めないでしょう。";
			link.l1 = "本当に知りたいのか？それと、お前の殺された仲間たちのことも……あの図々しい盗賊団の噂を聞いたことはあるか？きっと奴らの仕業だ。";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "「ロンウェイ、お前、本当にあいつらが言うほど兵士を殺したわけじゃないだろう？」";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "その通りでございます、旦那船長。ロンウェイはその一味を見ました。彼らに気づかれぬよう、 洞窟の奥へと身を隠しました。そしてロンウェイは、盗賊たちと兵士たちが話し、罵り合い、争う音を聞きました。";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "見たでしょ？全部辻褄が合うのよ。ロングウェイは怒りっぽいかもしれないけど、正直な男よ。私たちは行くわ。 もし手を出したら、あなたたちの制服に泥を塗ることになるわよ。さようなら、諸君。";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "ありえねえよ、旦那！あいつは俺たちの仲間を何人も殺したんだぞ、なのにあんたは見逃すつもりか！？ あのクソ野郎を殺すのを手伝うか、せめて邪魔だけはすんなよ！";
			link.l1 = "申し訳ありませんが、口を挟まねばなりません。本当にすみません。";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "話をしたいだけなら、俺に武装解除を求めたりしないだろう。\nだが、爪を引っ込めても虎は虎だ。\nお前はとっくにロンウェイを裏切ると決めていたはずだ――嘘をつくな。\n覚悟しろ、船長！";
			link.l1 = "くそっ！";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "あいつと一緒に切り抜けられたなんて信じられないよ！でも教えて、どうして彼はあなたのことを船長って呼んだの？";
				link.l1 = "見た目よりずっと複雑なんだぜ、相棒。お前の司令官を安心させる必要があったんだ。大事なのは結果だろ？ そして結果としてロンウェイは死んだ、俺はその手助けをしたってわけだ。";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "お前がいても役に立たなかったな――あいつは結局、俺たちに襲いかかってきた。くそったれ野蛮人め……";
				link.l1 = "彼のことをそんなふうに言うべきじゃないよ。\n彼が私たちを襲ったのは、気が立っていて、私があなたと一緒にいると思い込んだからなんだ。";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "「そうかもな。その場合は、さようなら、旦那。中国人がついに死んだことは、自分たちで司令官に伝えるさ。」";
				link.l1 = "かしこまりました、ありがとうございます。さようなら、みんな。";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "まあ、怒っていようが、野蛮だろうが、関係ない――あいつは前に俺たちの仲間を何人も殺した、最初に血を流したのはあいつだ。";
				link.l1 = "何かが彼をあのような状態に追い込んだに違いありません。\nしかし、それについては深く考えないことにしましょう。\n私はこれで失礼しますので、 のところへは好きな時に戻ってください。\nそれでは。";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "「ロードキャプテン？」";
			link.l1 = "ああ！ロングウェイ、お前を探して町中を歩き回ったぞ。お前のせいで町は大騒ぎだ。話すことが山ほどある、 すぐに船へ戻ろう。";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "「あそこだ！」";
			link.l1 = "客人が来たようだな。どうやら少し遅れそうだ。";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "まだ来るぞ！";
			link.l1 = "頑固な野郎どもだな、そこは認めてやる。ここじゃあまりにも無防備だ。洞窟へ向かおう――そっちの方が守りやすい。";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "ここにいつまでも留まるわけにはいきません。";
			link.l1 = "「それが、今までのこと全部あった後で最初に言いたいことなの、ロンウェイ？ そろそろ何が起きてるのか説明してくれてもいいんじゃない？」";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "「ロードキャプテン、ロンウェイ…」";
			link.l1 = "しかし、おっしゃる通りです――ここにはいられません。\nもう一隊が現れる前に動きましょう。\n出航したら船で話しましょう。";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "白人の狡猾さと悪意には限りがありません。";
			link.l1 = "おい、俺も白人だぜ！それに、お前はあいつらの仲間や兵士を殺したんだ――怒る権利はあるさ。";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "「彼らを赦しますか、My Lord Captain？」";
			link.l1 = "お前を赦す、ロンウェイ。それから、人を肌の色で判断しないようにしてくれ。お前こそ、その意味がわかるはずだ。\n話の途中だったな……どこまで話していたっけ……？";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "船長！後ろだ！";
			link.l1 = "ああ、今日はまともに話をさせてくれそうにないな……";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "「了解です、My Lord Captain。」";
			link.l1 = "それは良いが、ここで長居は無用だ。\nお前と俺は話すことが山ほどある。\nついて来い――船に戻るぞ。";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
		
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "ロードキャプテン、本当にあなたですか……？";
			link.l1 = "ああ、ロングウェイ。大丈夫か？";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "ロングウェイは大丈夫です。ありがとうございます。\nしかし、船長！見てください！";
			link.l1 = "洞窟へ走れ、急げ！あそこは防御に適した場所だ！";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "ロンウェイが兵士たちがまだ来ているか確認する。";
			link.l1 = "一緒に行こう――全守備隊を相手に防衛はできない。";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "はい、My Lord Captain？";
			link.l1 = "話すことが山ほどあります。\nさあ、ついてきてください――今すぐ錨を上げなければなりません。";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "再び手を貸していただき、感謝いたします、我が主君船長。きっと多くのご質問がおありでしょう。";
			link.l1 = "控えめに言ってもそうだな。なぜあの兵士たちを殺したんだ？お前は快楽のために人を殺す奴じゃないって、 俺は知ってる。";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "いいえ、ロンウェイはしません。兵士たちはロンウェイを止めようとした、牢屋に入る選択肢などなかった。 彼らは中国人の話など聞かない――そんな礼儀は白人にしか与えられないのです。";
			link.l1 = "奴らは他の白人の言うことも必ずしも聞くわけじゃないが、言いたいことは分かるよ。だが、 それでも街中で家畜みたいに皆殺しにするなんて？バステールで何をしていたんだ？";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "白人たちは私の話を聞かないことが多いだけでなく、時には口もきいてくれないことさえある。\n話しかけてくる時は、衛兵を呼ぶためだ。\nロンウェイは自分の肌や目を選んだわけじゃないが、自分自身を誇りに思っている。\n兵士たちが嘲り、脅してくる時、ロンウェイは疲れ……そして怒りを覚える。";
			link.l1 = "これからは一緒にやっていこう。人々は衛兵を呼ぶ代わりに俺に話しかけてくる……たいていはな。\nだが、本気で聞くが、お前の任務について教えてくれ。俺にも手伝わせてくれよ。";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "どうか、主君船長、ロンウェイのことをお分かりください。ロンウェイはこれを一人でやると誓いを立てました。 無理に押し付けないでください。それくらいの恩義はロンウェイにあるはずです。";
			link.l1 = "本当に感謝しているよ、でもあの時のファン・メルデンなら自分で何とかできたはずだ。だが、 最初から俺たちは五分だった——お前は俺の顔を救ったと言い、俺はお前に命を救われた。今度はまた俺が助けたぞ。";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "ふむ……おっしゃる通りですな、My Lord Captain。ロンウェイは、白人の中であなただけが本当の友だと信じております。かつて、そう思ったことがありましたが、 ひどく裏切られました。ジョン・マードックを覚えておいでですか？ヨハン・ファン・メルデンも？";
			link.l1 = "ファン・メルデンのことを話すとは奇妙ですね。最近、誰かが私の目の前で彼の記録から数ページを破り取ったのです。\nそれはあなたの件と関係がありましたか？犯人を見つけましたか？";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "やりました。盗んだのは……ロンウェイです。大変申し訳ありません、我が主君船長。あの時、 彼はあなたを完全に信じていいのか分かりませんでした。";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "友情を語りながら、俺の目を盗んで盗みを働くのか？これが最初で最後だ、ロンウェイ。わかったか？";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				Notification_Reputation(false, 61, "low");
			}
			else
			{
				link.l1 = "「それで、どうやってやり遂げたんだ、ロンウェイ？」";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				Notification_Reputation(true, 61, "low");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "ロンウェイは理解しています。本気です。";
			link.l1 = "そう願いたいものです。さて、あなたがどうしてこの道を選んだのか教えてください——どんな約束を、いつ、誰にしたのか。";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "はい、ロードキャプテン\nロングウェイは自分にとって残された最も大切な生きている者――チャン・シンを探し求めております。";
			link.l1 = "「チャン・シン、彼はあなたの親友なのか？」";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "あなたのご親切のおかげで、他の乗組員たちもすぐに私に慣れ、信頼してくれるようになりました。";
			link.l1 = "なるほどね。褒め言葉は好きじゃないんだろうけど、よくやったよ、ロンウェイ……お前の乱入で残った後始末をちゃんと片付けていれば、だけどな。";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "そうだ。しかし、そんなことをしている時間はない。";
			link.l1 = "そうじゃないと思う。でも、もう二度とそんなことはしないで、でしょ？何か必要なら、遠慮なく言って。 あたしを信じていいよ。さあ、あなたの誓いについて話して。";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "もちろん、ロンウェイはその重荷をあなたと分かち合えて嬉しいのです、我がロードキャプテン。\nロンウェイが探し求めるのは、彼にとって残された最も大切な生きている人物――チャン・シンです。";
			link.l1 = "「Chang Xing――彼はあなたの親友ですか？」";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "張星は私の家族、妹です。何年も前に行方不明になりました。彼女を探すために、 ロンウェイは彼女の居場所を知っているかもしれない者たちを探しています。";
			link.l1 = "これはファン・メルデンの文書庫と何の関係がある？君の妹の失踪と繋がっているのか？";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "そうだ。そのすべてが繋がっている。ロングウェイとヨハンは何年も前、お前たちがフォルモサと呼ぶ土地で出会った――私がこの諸島に来るずっと前のことだ。";
			link.l1 = "そんなに長い付き合いだったのですか？それにファン・メルデンも関わっていたのですか？なんて話だ！ 彼はあなたの妹の失踪とどう関係していたのですか？";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "彼は私の捜索を手伝ってくれた、白人の基準ですら極悪な連中を探すために。オリヴェイロ・フェルメンテロス、 アントーン・ファン・ディーメン、そしてヨープ・ファン・デル・フィンクだ。";
			link.l1 = "名前から判断すると、一人はポルトガル人で、他の二人はオランダ人だ。";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "はい、その通りです。しかし、捜索は成功しませんでした。ロンウェイは天の導きを辛抱強く待っていました。だから、 あなたがファン・メルデンの記録を手に入れたとき、私はそれを調べることにしたのです。 最初のページにオリヴェイロの名前を見つけたとき、私はそれを破り取り、小屋から逃げ出しました。";
			link.l1 = "すべてがついに物語に収まった。";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "しかし、物語そのものはまだ始まったばかりでございます。\n旦那船長、ロンウェイの探索の最初からお話ししてもよろしいでしょうか？\n腰を落ち着けてお聞きになるご覚悟はおありですか？";
			link.l1 = "それがまさにあなたを船室に呼んだ理由です。どうぞ。";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "ここは中国人立入禁止だ。ここはちゃんとした人間のためのまともな店だ、お前みたいな奴のためじゃねえ。";
			link.l1 = "質問が一つだけある。聞かせてくれ、それだけで立ち去る。";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "まずはちゃんと話せるようになれ！言っただろう―お前みたいな奴はここじゃ歓迎されねえんだ。";
			link.l1 = "オリヴェイロ・フェルメンテロスはどこにいる？教えてくれれば、すぐに立ち去る。";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "お前も耳が聞こえねえのか？俺の我慢を試すな、この部屋中がすぐに臓物の黄色い臭いで満たされることになるぞ。";
			link.l1 = "我々の民は何千年もここで生きてきた。この島は我々のものだ。それなのに、ただの酒場にすら入れないのか？";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "ほう、大口を叩くじゃねえか？その口のせいで絞首刑になるかもな。出て行け！";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "お前の大きな問題について聞いたぜ、小さな友よ。声がでかすぎたな――名前も場所も間違えちまった。";
			link.l1 = "この男について何か知っているのか！？教えろ！";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "落ち着け、相棒。";
			link.l1 = "申し訳ありません。";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "謝罪なんていらねえが、金は欲しいな。そしたら手を貸してやってもいいぜ。俺はマルセロ・シュルテだ。で、お前は？ 金、持ってるんだろうな？";
			link.l1 = "私の名はChang Tuだ。金はある。それで十分か？";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "（口笛）エスクード、ペソ、ギルダー、ドゥブロン……それにあんたたちの変なコインまで。これで十分だ。\nよし、チュンチュン、その男について何かわかったら知らせるよ。心配すんな、俺はほぼ毎日ここにいるから、 金は安全だ。毎日様子を見に来な、きっとまた会えるさ。";
			link.l1 = "願うしかない。もう金は一文も残っていない……";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "ああ、Chang-Chang！もう来ていたのですね。";
			link.l1 = "「チャン・トゥだ。」";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "関係ねえよ、相棒。";
			link.l1 = "オリヴェイロがどこにいるか分かりましたか？";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "いや、全く見当もつかない。";
			link.l1 = "俺の金だ！";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "そんなにビクビクするなよ！何も掴めてなかったら、またお前に近づく度胸なんて俺にあると思うか？ 知ってる奴を紹介してやるよ。しかも運がいいな、あいつはお前らアジア人が大好きなんだ。召使いも揃えてるし――しかも女の召使いまでいるぞ。お前らの汚い言葉も勉強中だ。名前はヨハン・ファン・メルデン。 役所の近くの二階建ての家でお前を待ってるさ。";
			link.l1 = "私の感謝を。";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "お前がチャン・チャンか？遠慮せずに中へ入れ。";
			link.l1 = "「チャン・トゥだ。」";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "そうですか？申し訳ありません。あのマルセロと彼の冗談の行進……あなたの文化に興味を持つ者が少ないのは残念です。すべては言葉が違うことと、あなたの目の形のせいで。ですが、 あなたは賢いですね。黒人どもとは違って、へへへ。";
			link.l1 = "（中国語で）なるほど、あの密輸業者は嘘をついていなかったんだな――あなたは本当に教養のある方だ。それに、本当に私たちの言葉を話せるのか？";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "私の文化について温かい言葉をいただき、感謝いたします。あなたはヨハン・ファン・メルデン様でいらっしゃいますか？ ";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "ああ……少ししか分かりませんでした。まだ勉強中でして。オランダ語で続けていただけますか？";
			link.l1 = "かしこまりました。あなたがヨハン・ファン・メルデンですか？";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "ああ、チュン・トゥ、それは私だ。オリヴェイロ・フェルメンテロスを探していると聞いた。彼の居場所は知っているが、 まず教えてくれ——なぜ彼を探す？君の答え次第で、私の返事も決まる。";
			link.l1 = "彼は……俺の最後で最愛の家族――妹のチャン・シンをさらったんだ。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "それなら、残念ですが、Chang Tu。もう彼女には望みはないでしょう。おそらく裕福なプランターか売春宿に奴隷として売られたはずです。どちらにせよ、 あなたには彼女を救うことはできません。";
			link.l1 = "張興はまだ生きていると私は信じている。オリヴェイロが彼女に目をつけた。彼女は誇り高く彼を拒んだ。 私が家にいない時、彼は彼女を奪った。そして……両親を殺した。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "私……本当に申し訳ありません。それが事実なら、チャン・シン――そうですよね？――まだ生きているかもしれません。こうしましょう：オリヴェイロが今どこにいるのか、正確に突き止める時間をください。 一週間ほどでどうでしょう。その時にまたお会いしましょう。街の門の外で待ち合わせましょう――ここでは誰があなたを見ているかわかりませんから。これ以上深入りしたくはありません、ご理解いただけると幸いです。 ";
			link.l1 = "私は…私は心より感謝しております、ファン・メルデン旦那。次にお会いできるのを楽しみにしております。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "やあ、Chung Tu。あなたの目に炎が見える。知らせはあるが、良いものじゃない。";
			link.l1 = "どんな知らせでも私には非常に重要です。どうか教えてください、ファン・メルデン旦那。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "ああ……フェルメンテロスは一ヶ月ほど前にバタヴィアへ向かった。俺が掴んでる手がかりはそれだけだ。\nいい知らせとしては、あいつはしばらくあそこに滞在するつもりらしい。今すぐ向かえば間に合うだろう。\n悪い知らせ？あいつは総督アンソニー・ファン・ディーメンの親しい友人だ。近づくことはできねえよ。";
			link.l1 = "この知らせで十分です。謹んで感謝いたします、ファン・メルデン旦那。すぐに出発いたします。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "何となくそう言うだろうと思って、君とチャン・シンのために少し公平になるよう手を打っておいた。\n昔の友人、オリバー・トラストに手紙を書いたんだ。彼はバタヴィアで店を経営している。俺には借りがあるから、 君の力になってくれるはずだ。";
			link.l1 = "俺……何と言えばいいのかわからない……";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "「ありがとう」だけで十分だ。もし街でオリヴェイロを見つけられなければ、モーニングスター号を探せ。 奴の船をたどれば、必ず見つけられるはずだ。幸運を祈るよ、友よ――君と君の妹にはそれが必要だろう。";
			link.l1 = "心の底から感謝します、ファン・メルデン様。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "お前は誰だ、ここで何をしている？俺はお前らみたいな奴とは取引しねえ。";
			link.l1 = "あなたに手紙を預かっています。";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "ああ、使者か！今日は手紙が来るとは思っていなかったが。ここで待て！俺が見てくる。";
			link.l1 = "お前がオリバー・トラストか？ヴァン・メルデンが俺をお前のところに寄越したんだ。";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "俺、字は読めるんだぜ。普通ならお前を追い返すところだが、ヴァン・メルデンみたいな奴は「ノー」 じゃ済まないからな。ついにヴァン・ディーメンとの決着をつける時が来たってわけだ。";
			link.l1 = "私の標的はフェルメンテロスだ。ヴァン・ディーメンはどうする？";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "それはお前には関係ない。俺が手を貸してやってるだけでも感謝すべきだろう。さて、よく聞け、 俺がこれをやめると決める前にな。フェルメンテロスのことは知っている。あいつはしばらくここにいたが、もういない。 モーニングスター号は数週間前に出航した。いつ戻るかなんて神のみぞ知る、だ。だからお前の標的は変わった。 今はフェルメンテロスの友人が相手だ……\n";
			link.l1 = "…ファン・ディーメン。";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "ああ。お前もそれを知っているのか？ヨハンが話したんだろう？おい、ファン・メルデン……お前は本当に大胆な野郎だな。だが、すでにファン・ディーメンのことを知っているなら、 あいつの高い地位も分かっているはずだろう？総督にどうやって近づくつもりだ？ まさか屋敷に突撃するつもりじゃないだろうな！\n";
			link.l1 = "Chang Tuは腕の立つ戦士だ。";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "腕の立つ戦士か、ふん？今や俺たちはすっかり巻き込まれてしまったんだぞ？もしお前が捕まったら、俺はどうなる？ お前のためにも自分のためにも、助けざるを得ないだろう。\nそれに、ヴァン・ディーメンは自宅に住んでいるだけじゃなく、 街の外のプランテーションや愛人のヴェッテのもとにも定期的に通っているんだ。";
			link.l1 = "「私を助けると言っていましたね。」";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "誰もが情熱や趣味を持つべきだと私は思う。私の場合は、珍しくて高価な武器を集めている。時には歴史があるものも、 ないものもあるが、どれも常に致命的だ。私のコレクションは、あなたの十字軍に役立つかもしれない。\nそれで、教えてくれ、どこでヴァン・ディーメンを待ち伏せするつもりだ？";
			link.l1 = "（邸宅）良い武器がこんなに揃っているなら、一番の刀をいただくぞ。これさえあれば、 チャン・トゥは白人どもの中で無敵だ。";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "（プランテーション）プランテーションへの道で待ち伏せする。奴らには逃げ場がない。";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "（奥方）奥方のところ――あそこなら人は少ないから、護衛もすぐには反応できないでしょう。";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "良い選択だ！感心したよ。これを最大限に活かすには、良い火器が必要だな。さて、チャン・トゥ、 お前はどれくらい遠くまで狙えるんだ？";
			link.l1 = "正直に言うと……あまり遠くはない、外さないようにしなければならないから。"
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "遠くから攻撃するつもりだ――敵はどこから斬られたのかすら気づかないだろう。";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification(GetConvertStr("Sniper", "AbilityDescribe.txt")+" Unlocked", "Longway");
			SetCharacterPerk(pchar, "Sniper");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "なるほど。ならば、これを受け取れ！古いポルトガル製のタワーブランダーバスだ。大口径の弾丸を撃てる。 こんなものは、もはや旧世界でも作られていないぞ。";
			link.l1 = "子供の頃に一度見たことがある……";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "それで、使い方は分かるのか？";
			link.l1 = "……いや……";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "覚えておいてください、交換式の仕掛けは長い年月で錆びついてしまいました。\nどんな油を差しても直りません――もう完全に壊れています。\n充填は難しいので、今やってしまいましょう。\nよく見ていてください――少し力を入れて、こうやるんです。\nでも、あまり強くやりすぎると壊れてしまいますよ。";
			link.l1 = "こうですか？";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "まさしく、その通りです。";
			link.l1 = "承知しました。ありがとうございます！";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "bullet", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "bullet");
			
			dialog.text = "本物のイェーガーだな！気をつけろ、これは贈り物なんだ。\n装飾的でありながら殺傷力もある、珍しい武器のひとつだ。\n二連発の狩猟用ライフルだぞ！持つには重いが、扱いは簡単だ。\nもう撃ち方は分かったか？";
			link.l1 = "承知しました。ありがとうございます！";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "護衛についてはおっしゃる通りですが、危険を侮ってはいけません。ヴァン・ディーメンは街中を移動する時、 必ず右腕のヨープ・ファン・デル・フィンクを連れて行きます。";
			link.l1 = "つまり、あいつらはヴェットと一緒にいるのか……？";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "何だと？ははっ！お前は想像力が豊かだな、中国人！アントーンは臆病者で、誰かが奴らの「密会」を邪魔しないように、 ファン・デル・ヴィンクが護衛してるんだ。\nヨープはいつも重い塹壕鎧を着てる――普通の刃物じゃ歯が立たねえ。だからお前にも特別な物が必要だ。これを持っていけ、このレイピアだ。 他の剣より長くて、強くて、しかも良い刀身の重みがあるぜ。";
			link.l1 = "鎧を着た敵と戦うためのレイピア……？";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "鎧そのものを狙うな――これはエストックじゃない。隙間や弱点、股間や脇の下、喉を狙え。相手を消耗させて、主導権を握るんだ。 ヨープは重い斧も使うから、受け止めようとせずに避けろ\nもし隙を見つけられなかった時のために、このブランダーバスを持っていけ。普段は散弾が入っているが、 今回は鋼鉄の矢弾を用意しておいた。";
			link.l1 = "マスケット銃に矢……？";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "珍しいだろう？古いものと新しいものが混ざっている。一方の手で撃てるように作られているが、重ければ両手で使え。 多くの者がそうしている\nそれから、これを着てみろ。この籠編みの鎧はヨープの胸甲より軽いが、それでも十分な防御力がある。ただし、 あいつの斧をまともに受けるな――ミラノ製の鎧でも、あんな武器には耐えられない。わかったか？";
			link.l1 = "はい、わかりました。ありがとうございます、トラストさん！";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "自信過剰か？私がコレクションの話をしたのは早すぎたかもしれないな。だが……もう後戻りはできない。真昼間に屋敷を襲うとは、大胆な手だ。誰も予想しないだろう。\nこの刃はお前に合うはずだ。世界一の品ではないが、突くにも斬るにも叩き切るにも最適だ。";
			link.l1 = "クリワン！この刃は見覚えがある。近くの島々の者たちがよく使うものだ。";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification(GetConvertStr("TannedLeather", "AbilityDescribe.txt") +" Unlocked", "Longway");
			SetCharacterPerk(pchar, "TannedLeather");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "以前に使ったことはありますか？\nよろしい。時間はほとんどなく、敵は多いでしょう。これも持っていきなさい――三連発の美しい装飾が施された拳銃です。今、私の前で装填してください。後でそんな余裕はありませんから。それから、 この決闘用の胴着も着てください。軽くて、必要な速さを与えてくれますし、多少の防御にもなります。";
			link.l1 = "ありがとうございます、Trust様！";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "待て、まだ終わっていない。我々双方のためにも、お前が生き残ることが重要だ。これを持っていけ、 戦いの後で傷を癒す薬だ。\nそれからこの霊薬もだ。味も臭いもひどいが、体内の毒をすべて消してくれる。ジョープ・ファン・デル・ヴィンク、 ヴァン・ディーメンの用心棒は、あのクソを武器に塗っている。生意気な野郎だが、これでお前が有利になる。";
			link.l1 = "お礼をどれだけ言っても足りるか分かりません、トラスト旦那…";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "一番の感謝の気持ちは、もし捕まっても俺を密告しないことだ。\nまあ、たぶんその場でお前は殺されるだけだろうがな。\nだが、もし生き延びたら、ヴァン・ディーメンに「お前の死は俺のおかげだ」と伝えてくれ。できるか？";
			link.l1 = "問題ありません。改めてありがとうございます、Trust旦那。さようなら！";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "止まれ！どこへ行くつもりだ、中国人？";
			link.l1 = "邸宅へ。";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "それは修辞的な質問だ、天才さん。誰があんたみたいな奴を中に入れると思うんだ？";
			link.l1 = "「マインヘール・ファン・ディーメンに用がある。通してくれ、頼む。」";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "総督の名前を知っているのか？さて……用件を言え。伝えて返事を持ってくる。";
			link.l1 = "私の話はマインヘール・ファン・ディーメンだけにある。彼が私を待っているんだ。どけ、さもないと後悔するぞ。";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "ほうほう、調子に乗るなよ、細目野郎。俺のやり方に従うか、さもなくば何もないぞ。";
			link.l1 = "では、俺のやり方でいこう。";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "くそったれ百姓め！誰に雇われたんだ？その報酬より多く払ってやる！";
			link.l1 = "お前たち白人は金のことしか考えていない。竜たちがお前らの種族に呪いをかけるがいい。俺は情報を求めて来たが、 お前らの仲間は俺を中に入れようとしない。";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "何の用だ！？";
			link.l1 = "フェルメンテロス。今どこにいる？";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "オリヴェイロ？だが、なんであいつが欲しいんだよ？俺は何も教えねえぞ！";
			link.l1 = "奴は俺の家族を殺し、妹をさらった。\n俺からの忠告だ、話し始めたほうがいい。\n自分のためにな。";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "私に何をするつもりなの？すぐに守備隊全員がここに来るわよ。";
			link.l1 = "リンチーのことを聞いたことがありますか？私の文化の罰です。「千の切り傷による死」を意味します。";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "俺にそんなにたくさん傷をつける暇なんてねえぞ、この間抜けが！";
			link.l1 = "比喩表現だ。死刑執行人は一つずつ傷をつける。あるいは体の一部を切り落とす。\n話し始めない限り、時間の許す限りそれを続けるだけだ。";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "あ、あ、あ！！！やめろ！やめてくれ、この汚い野獣め。言う、全部話すから。だからやめてくれ。\nジョープ！やっと来たか！今まで一体どこにいやがったんだ！？";
			link.l1 = "なんて悪いタイミングだ……";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "アントーン？すぐに医者に診てもらわないといけないよ。ここが片付いたらすぐ連れて行くからね。\nお前！何してるんだ、この黄色い殺し屋め！？";
			link.l1 = "「イエローブッチャー？それ、ちょっと気に入ったよ。\nただ一つだけ知りたいことがあるんだが、誰も答えようとしないんだ……」";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "「何の質問だ！？」";
			link.l1 = "オリヴェイロ・フェルメンテロスはどこだ？それくらい教えられないのか？";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "フェルメンテロスなんかどうでもいい！誰が金と情報を渡したんだ！？";
			link.l1 = "オリバー・トラストだ。ちなみに、彼は「お前は自分の死を俺に借りている」と伝えてほしいそうだ。";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "信頼だと？！ハハハハハハハハ！あの守銭奴め、 自分のプランテーションを奪われたからって復讐できると思ってやがるのか？お前を片付けたら、 あいつの店も命もすぐにいただくぜ。\n";
			link.l1 = "俺の時間を無駄にしている。";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "（中国語で）では、良い待ち伏せ場所を探しましょう。";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "（中国語で）この錆びた武器じゃ、近づくしかないな。素早く一斉射撃――鋭く、容赦なく。恐怖と混乱が残りを片付けてくれる。";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "（中国語で）ここだ。最初は奴ら、俺のことに気づきもしない。始まらない戦い、 あるいは血をほとんど流さずにすぐ終わる戦いこそが、最高の戦だ……";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "忌々しい野郎め……逃げた奴隷だろう？どうやってそんな武器を手に入れた？誰かに雇われたのか……？";
				link.l1 = "時間がない！オリヴェイロ・フェルメンテロスがどこにいるか、今すぐ教えろ！";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "へへへ、おかしいな……時間がない、腹から血が噴き出してる。地獄で焼かれろ、異教徒め……";
			link.l1 = "（中国語で）いやだ！！！";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "（中国語で）なぜだ、なぜだ、なぜなんだ！？これでどうやってフェルメンテロスを探せばいいんだ！？";
			link.l1 = "だがまず、隠れなければならない……この虐殺のことは、もう誰かが報告したに違いない……";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "ひっく！中国人か！こんな場所にお前みたいなのが招かれるとは思わなかったぜ。見物が好きなんだろ、へへ。";
			link.l1 = "なぜここにこんなにも人がいるんだ……？それに、お前は誰だ？";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "俺の服装でわからねえのか？それに、総督閣下に話すときは口の利き方に気をつけろよ！…ひっ！";
			link.l1 = "そうか、あなたがファン・ディーメン旦那だな。無知をお詫びする。ここでは祭りでもやっているのか？";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "その通りだよ、いい男！他に道はない！女装のカーニバルだ！ハハハ！悪くないじゃないか、百姓！ ルーサーズならきっとヴェットのドレスを着るのが大好きだろうな、ハハハ！";
			link.l1 = "ルーサーズか……";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "あの情けない旦那、愛しい奥さんが他の男に抱かれているのをタンスの中から覗くのが大好きなんだ。 奥さんの方は全然気にしてないぞ！";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "そうだろ、ヴェット、あたしの可愛い子？へへっ。";
			link.l1 = "（中国語で）ここは一体どうなっているんだ……";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "ひっく！何を言ったのかさっぱり分からねえけど、その目つきと声の調子からして、俺に同意してるんだな！ ファン・ハーンはとんでもねえ変態野郎だ。で、お前は何者だ？労働者か？ヴェットに誘われて来たのか？\n";
			link.l1 = "「私……」";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "ここに労働者を呼ぶなんて、いくらヴェットでもやりすぎだ。こいつは明らかに迷い込んで、場違いだ。おい、 そこのお前。ここから出て行け。そして見たことはすべて忘れろ。お前の主人は誰だ？我々がそいつに連絡する。 黙っていれば、二人とも報酬をもらえるだろう。もしかしたら大陸の家族のもとに戻ることも許されるかもしれん。 答えて、そして立ち去れ。";
			link.l1 = "実は、私は仕事でここに来たのです。";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "へっ、商売か。ここで「商売」をするのはミニール・ファン・ディーメンだけだ。俺の仕事は、 あんたみたいな連中からあいつを守ることさ。ルーサーズは……まあ、いつも通りのルーサーズだ。\nそれとも……ヴェッテが本当にあんたをここに招いたのか？";
			link.l1 = " いいえ、私はここに……";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "俺の最愛のヴェットが、こんな黄色野郎をここに招くわけねえだろ！？さっさと失せろ！！！";
			link.l1 = "哀れな寝取られ男め……";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "誰もお前に話しかけてねえ。黙れ。ちんぽも誇りもあるふりすんじゃねえ。";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "「こ、こ、間男だと！？違う、俺は自分自身よりも彼女を愛してるんだ。はっ、 お前みたいな愚かな中国人にはそんなこと分かるまい！」";
			link.l1 = "（中国語で）病んだ野郎だ。";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "こ、こ、こけっ？！別にいいんだよ！うん！他の男たちが俺の愛しいヴェットをもっと満足させてるって、 ただそれだけのことさ！";
			link.l1 = "私の故郷の言葉で言えば、人は指が一本しか残らなくなっても、まだ男だ。もしあなたが本当に男なら、 その意味がわかるはずだ。";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "もちろん、私が彼を招待したわけじゃないけど、でも、ほら、彼はなかなかいい人よ。みんなが帰った後も、 ここに残るかもしれないわね。うちの犬ではもう試したことがあるけど、人間とはまだ……";
			link.l1 = "黙れ、男たちが話している時に口を挟むな、娼婦め！ここで動物なのはお前だけだ。俺は仕事で来ている。 オリヴェイロ・フェルメンテロスを探しているんだ。お前たちは彼の仲間だろう。どこにいるか教えてくれないか、 ヴァン・ディーメン旦那？";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "アントーン、あいつは俺を侮辱したんだ！侮辱だぞ！このまま黙ってるつもりじゃないよな！？";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "へへ、悪いな、相棒。でもお嬢さんが怒ってるんだ。お前に礼儀ってもんを教えてやらなきゃな。第一課だぜ。";
			link.l1 = "しかし、私のオリヴェイロ探しを手伝っていただけますか？";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "死んだ労働者には何の役にも立たない。";
			link.l1 = "（中国語で）くたばれ、貴様らめ……";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "（中国語で）くそっ！何もわからなかった！";
			link.l1 = "（中国語で）この日を決して忘れない……看守が来る前にここを出なければ。どうせこの狂人の巣から聞こえる物音なんて、あいつら気にもしないだろうが……";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "（中国語で）神々がこの日を呪った！俺が手下を片付けている間に、ファン・ディーメンは血を流して死んじまった…！";
			link.l1 = "（中国語で）衛兵たちが来る。ここから戦って脱出しなければならない。";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "おや、チャン・チャンじゃないか！今回は何を手伝えばいいんだい、ちっちゃな友よ？";
			link.l1 = "チャン・トゥだが……どういう意味だ？";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "俺に対する軽蔑が滲み出てるな、そうだろう？何か用がなきゃ、ここには来ないはずだ。";
			link.l1 = "ヴァン・メルデンがどこにいるか知っているか？\n町にいるのか？\n家にはいなかった。\n彼と話す必要があるんだ。";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "男が一日中家で、たった一人の黄色い肌の男が現れるのを待っていられるはずがないだろう。 島でやるべきことがあるんだ。今夜には町に戻ってくるから、心配するな、Chang Chang！";
			link.l1 = "ありがとうございます。さようなら。";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "おい、細目野郎！こんな時間に何をそんなに急いでるんだ？まともな奴らはもう寝てるぜ。";
			link.l1 = "それでは、あなたはどうなのですか？";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "よく言った！俺たちは見回り中だ！噂じゃ、町で小柄な黄色い奴がうろついて、敬虔な人々を困らせてるらしいぞ。";
			link.l1 = "「それは一体どなたでございましょうか？」";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "もう話は十分だ――遅くなってきたし、眠くなってきた。";
			link.l1 = "まもなくあなたの眠りは永遠となる。";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "「Chang Tu、大丈夫か？」";
			link.l1 = "マイネール・ファン・メルデン！あなたのおかげで、私は無事です。\nご無事ですか？それが一番大事なことです。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "いつも他人のことを考えているんだね？その点は、私も同じだ。君がやつらに襲われているのを見て、 黙って見ていられなかったよ。君なら大丈夫だと分かっていてもね。質問の答えだけど、私は大丈夫、 ただ少し疲れているだけだ。足がちょっと震えている。もしよければ、中に入りましょう。そこで話そう。";
			link.l1 = "もちろん、van Merden旦那、ここはあなたの家ですから。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "さて、今は急ぐこともなく、静かに話せますね。\nさあ、何の用で私のところへ来たのですか、Chang Tu？";
			link.l1 = "おっしゃる通りです、ファン・メルデン旦那。私は今バタヴィアから戻ったばかりで……";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "待ってください。まさか、哀れなチャン・シンでは……？";
			link.l1 = "いいえ、全くそんなことはありません！そうでないことを願っています。天はまだ彼女の運命を私に隠しています。 そしてフェルメンテロスについてですが…彼はバタヴィアにはいません。ファン・ディーメンも何の助けにもなりませんでした。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "彼はそんなことしないだろう、なぜなら彼とオリヴェイロは古い友人だからだ。\n英語で言うところの「悪事を共にする仲間」ってやつさ。\n役に立つ情報をくれるなんて、むしろ驚きだよ。";
			link.l1 = "はい、あなたとトラストのおかげで、私は強力な武器を手に入れました。\nヴァン・ディーメンを襲って尋問し、フェルメンテロスの居場所を探ろうとしました。\nしかし、何も聞き出せないまま、彼は死んでしまいました……";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "見事ですね。人は自分の知っていることを必ずしも話したがらない、と気づいたようですね。だから他にも……説得の手段がある、というわけです。あなたが妹の死について知って、それで暴走したのかと思っていました。しかし、 今なぜ私のところへ？フェルメンテロスの行き先は知らないと、バタヴィアに時々行く以外は何も知らないと、 すでに伝えました。ヴァン・ディーメンもいなくなり、最後の手がかりも失われましたよ。";
			link.l1 = "しかし、あなたは多くのことを知っていて、多くの人々とも知り合いです。\nまた助けてくれるかもしれないと思いました。前のようにフェルメンテロスについて誰かに聞いてもらえませんか。\nあなたは私によくしてくれた最初の白人でした。最初の……白い友でした。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "それは……感動的ですね。";
			link.l1 = "メルデン様、なぜ微笑んでいるのですか……？";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "え？ああ、すまない、Chang Tu。年を取ると、どうも感傷的で物思いにふけりがちなんだ。これは心からの笑顔さ――隠せなかったよ。君が私を友だちだと思ってくれて嬉しいよ。友だち同士なんだから、ときどき助け合うのは当然だろう？ その代わり、Fermentelosの件は必ず力になる。心配しなくていい――罠なんかじゃないさ。";
			link.l1 = "ふむ、どうやってお助けすればよろしいのでしょうか？";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "前回お会いしてから、私はあなた方の言語と文化、特に医学についてさらに学びを深めました。\n時々、特定の遺物の銘板を探してきてほしいのです。そのたびに、他の仕事と同じように十分な報酬をお支払いします。\nそして、時々中国語で会話の練習もできればと思っています。\n召使いに頼むのは恥ずかしいですが、友人には……";
			link.l1 = "チャン・トゥは最善を尽くします、ヴァン・メルデン様。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "よろしい。これからお前と俺には長い道のりが待っている、友よ。長い道のりだ。ははっ！それ、 お前の偽名にちょうどいいかもしれないな。俺の仕事の腕の見せ所だ。オランダ語では「Lange Afstand」。英語なら「Long Way」。どっちが気に入る？";
			link.l1 = "英語版のほうが好きだ。ロング。ウェイ。ロングウェイ。私の言葉ではとても合っている響きだ。\n聞いてくれてありがとう、ヴァン・メルデン旦那。ロングウェイはあなたのご命令をお待ちし、 助力とご要望の遂行に備える。";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "ところで、アーカイブのことですが、我が主君たる船長よ、それをお持ちですか？私に必要なのはそれだけです――暗号はすべて暗記しております。";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingL", 50);
				AddCharacterExpToSkill(npchar, "FencingS", 50);
				AddCharacterExpToSkill(npchar, "FencingH", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "はい、いつか役に立つかもしれないと思って取っておきました。";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "残念ですが、違います。妹を見つけることが最後の望みでしたか？";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "ロンウェイは旦那船長が気にかけてくれて、とても嬉しいです。\n今のところ、まだ希望はあります。グアドループで新しい手がかりを見つけました。";
			link.l1 = "わかった。それで、そこで何があったのか話してくれ。";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "賢明なご判断でございます。もしかすると、あの中で張星（チャン・シン） 探しの助けとなる何かが見つかるかもしれません。";
			link.l1 = "それが理想的です。今すぐ調べましょう。";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "はい、一緒に調べましょう。年は……1637年。アントーン・ファン・ディーメンが売った……売った……";
			link.l1 = "奴隷たち、そうだろう？";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "私の民の女たちが、裕福な白人どもに売られた。";
			link.l1 = "それはひどい。";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "旦那船長、驚いていないようですね。あの女たちの運命が、少しも気にならないのですか？";
			link.l1 = "ロンウェイ、もちろん本当に心を痛めているよ。俺はこの汚物を内側から見てきたんだ。でも、 俺は昔から女性の味方でね……正直言って、ちょっと女好きでもある。ヴァン・ディーメンを殺してくれてよかったよ。あいつはそれだけのことをした。 ほかに何かあるか？";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "ヴァン・ディーメンが完全に信頼していた者としか組まなかった――右腕のヨープ・ファン・デル・フィンク、そしてあの忌々しいオリヴェイロ・フェルメンテロス。それから……それから……";
			link.l1 = "どうしたんだ？顔色が真っ青だぞ、ロンウェイ。";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "ヨハン・ファン・メルデン……";
			link.l1 = "本当にごめんなさい。それはひどい話だけど、なぜそんなに驚いているの？ さっきフェルメンテロスについて書かれたページを全部破り捨てたって言ってたよね。じゃあ、 その時にファン・メルデンのことも見つけなかったの？";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "ロンウェイは急いでいて、この大事な品を見落としたに違いありません。";
			link.l1 = "なるほど。準備ができたら、引き続き探しましょう。今すぐ使えるものを見つけるのです。";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "フェルメンテロスが自分の手下を送り込んで女たちを捕らえ、入れ替えて記録を抹消していたと書かれている。\nその後、メルデンが彼女たちをバタヴィアへ送り、そこでファン・デル・ヴィンクとファン・ディーメンが我々 の女たちを白人どもに売り払っていた。\nもっと早くこのことを知っていれば……";
			link.l1 = "つまり、結局はみんなが協力したんだな。自分を責めるな、ロンウェイ。君には分かるはずがなかった。 記録が君の手に渡ったのも最近のことだろう。他に何かあるか？";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "そうです。もう十年近くも続いています。多くの女たちが家族も、名誉も、希望も失いました……。\nしかしフェルメンテロスはヴァン・メルデンとの協力をやめました。それだけが、彼が私を助けてくれた理由です――彼が望んでいたのは、元の相棒を排除することだけでした。";
			link.l1 = "ここには奴らの汚い所業の他にどんな詳細が記されている？";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "またファン・メルデンの陰鬱な考えだ。彼はファン・ディーメンに金を騙し取られていると知った。 だから俺をバタヴィアに送り込んだんだ、俺がそこで死ぬことを望みつつ、 ファン・ディーメンも道連れにすることを期待してな。";
			link.l1 = "冷たい。しかし、同時に驚くほど賢い。";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "もっとひどいことになっていたかもしれません。 私を殺すためにあの家に暴漢どもを送り込んだのはファン・メルデンです。 私が自力で奴らを倒すかもしれないと気づいた時になって、初めて彼は助けに入ったのです。";
			link.l1 = "間違いなく、彼はすべて考え抜いていた。";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "生きて戻った俺を見て、あいつはきっと俺が本当の目的に気づいて復讐に来たと思ったんだろう。\n話している間、あいつはテーブルの下で銃をこちらに向けていた。\nでも俺が「初めてできた白人の友だ」と呼んだら……あいつ、笑いをこらえきれずに吹き出しそうになってた……";
			link.l1 = "それはひどいな、ロンウェイ。自分たちが友だちだと思っていた連中が、ずっと陰で俺たちを嘲笑っていたなんて……本当に苦い現実だ。";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "ロンウェイはこの諸島に来る少し前、ずっと昔に何かを学んだ。\n俺はポルトガル人に捕まって、絞首刑にされそうになった。ローデンブルク卿が俺の命を救ってくれたんだ。";
			link.l1 = "それであなたは彼の下僕になったのか？ルーカスもフォルモサにいたのか？";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "そう、その通りよ。しかも彼だけじゃない——ヴァン・ベルグもよ。ヴァン・メルデンが言ってた、ローデンブルクに私を助けるよう進言したのは彼だって。 でもしばらくしてから、ロングウェイが怪しい筋から聞いたの、 本当はヨハンが私を追わせるためにポルトガル人を差し向けたって。その時は信じられなかった……でも今は、それが本当かもしれないって思うの。";
			link.l1 = "おぞましい。";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "それでも、あの日、私の心には疑念が巣くったのです。\nだからこそ、正義の島の旦那様とファン・メルデンが対決したと知ったとき、ロンウェイはあなたのご厚意を思い出し、 あなたの側についたのです。";
			link.l1 = "それが正しい決断だったな、ロンウェイ。へっ、結局のところ、この間ずっと、 お前の最初の本当の白人の友達は俺だったってわけだな。";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "そういうことだったのですね、ロードキャプテン。今、理解しました。 ファン・メルデンは私のことを友人だと言いました。しかし実際には、ロンウェイは彼にとって他の労働者と変わらず――ただ、少し役に立つだけでした\nそれだけのことです。他のページは会計や、 ファン・ベルクとローデンブルクの間の商取引の詳細について書かれています。";
			link.l1 = "なるほど。さて、そろそろグアドループで何をしたのか話してもらおうか。";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "私はモーニングスターを探していた。破り取られた記録の一枚に、 最後にそれが見られたのはセントクリストファーの近くだと書かれていた。";
			link.l1 = "なぜそこなんだ？グアドループで会うと約束したし、そこでお前を見つけたんだぞ。";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "なぜなら、セントクリストファーはジョルジュ・グラヴェルの故郷だからだ。彼はヴァン・メルデンの密偵の一人だ。 ジョルジュは、私がいまだにヨハンのために働いていると思っている。さらに、 グラヴェルはかつてヴァン・メルデンに対して重大な罪を犯した。そしてロンウェイがその隠蔽を手伝ったのだ。";
			link.l1 = "「それは、どんな罪だったのですか？」";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "それは重要じゃない。重要なのは、ジョルジュがロングウェイに借りがあったということだ。だから、 俺はグラヴェルが助祭として働いている教会に行ったんだ。\n正義の島の旦那、続きを聞く準備はできているか？少し気が散っているように見えるぞ。";
			link.l1 = "すまない、ちょっと気が散ってた。ああ、もちろんだ、どうぞ、ロンウェイ。";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "よかった、まだ間に合ったね。必要以上にここにいたくないからさ！今回は何が必要なんだ、ロンウェイ？";
			link.l1 = "口の利き方に気をつけろ、Gravel。組織はお前の働きを必要としている。";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "正直に申し上げますが、長い間あの者たちから何の便りもありませんでした。私のことを忘れてしまったのでしょうか？";
			link.l1 = "思い出させることはできます。例えば、あなたがしたことをヴァン・メルデン卿に話すことでね。";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "はいはい、そんなに怒らなくてもいいでしょ？私に何をしてほしいの？";
			link.l1 = "モーニングスター号についての情報が必要だ。何でもいい、手に入るものはすべてだ。多ければ多いほどいい。";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "もちろんですが、時間がかかります！最低でも二日です！";
			link.l1 = "なぜそんなに時間がかかる？";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "普段なら、情報屋たちの口を割らせるために献金箱から金を使うんだが、最近盗まれてしまったんだ！\nもちろん神父様が新しい寄付金集めを告知するだろうが、屋根も直さなきゃならない――雨漏りしてるんだ！\n修理にはかなりの寄付が必要になるぞ。";
			link.l1 = "二日だ。ここにいつまでもいられない。そんな時間はない。ロンウェイは忍耐強いことで有名じゃない。 ヴァン・メルデン卿はなおさらだ。思い出させてやろうか、グラベル？";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "俺の手の届かないことはどうにもできねえ！できることをやるさ。だがな、 もしあんたがあの盗賊どもを見つけて寄付金を取り戻してくれたら、もっと早く分かるだろうよ！";
			link.l1 = "考えておく。お前は捜索を始めろ。二日だ。それ以上はない。同じ時間、同じ場所で会うぞ。";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A Day Later..."+ NewStr() +"In Search of the Church Robbers.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "おやおや、見ろよ！この島に細い目の男がいるじゃねえか！ご主人様から逃げてきたのか？もしよかったら、 誰から隠れてるんだ？";
			link.l1 = "俺は自由な男だ。";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "はっ！そうかい。でもお前、目がちょっと吊り上がってても、力も頭もありそうだな。俺たちの仲間にならねえか？ どうせ他に行く場所もねえだろうしよ。";
			link.l1 = "ロンウェイは、あなたが自分を仲間に引き入れるよりも、 むしろ自分を襲って奪い取ろうとしているのではないかと思っている。";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "へっ、運が良かったな。俺たちは最近、この町の教会を襲ったんだぜ、信じられるか？\nなぜって？盗人から盗むのは、本当の盗みじゃねえからさ。";
			link.l1 = "お前を追い回すつもりはなかったが、見つけられてよかった。";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "俺たちを追ってきたのか？ああ、つまりお前は逃げ出した労働者じゃなくて、傭兵ってわけだな。そりゃあ、 お前にとっちゃ悪い話だな。";
			link.l1 = "まさにその通りです。";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "くそっ……なぜすぐに俺を殺さなかった？何が目的だ？俺を牢屋に引きずっていくつもりか？";
				link.l1 = "それには興味はない。ただ金をどこに隠したか教えろ。";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "へっ……この黄色い肌の野郎め……";
			link.l1 = "ロンウェイの我慢も限界に近い。\nどうせ俺が突き止める。\n問題は、お前がどれだけ苦しむかだけだ。";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "わかった、いいよ……洞窟の中だ。全部そこにある。金はあんたのものだ。だから……だから殺さないでくれ、頼むよ？";
			link.l1 = "「苦しみが全くないとは言っていません……」";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "（中国語で）ここが盗賊たちの隠れ家です。";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "（中国語で）たくさんある！";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "（中国語で）足音が聞こえる……";
			link.l1 = "（中国語で）誰か他にもここにいる……";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "俺たちは一体ここで何をしてるんだ？もう誰も残っちゃいねえ――盗賊どもは全部片付けたはずだろ。";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "それが狙いだ、この馬鹿野郎！奴らは戻ってくるさ、そしたら俺たちが手厚く迎えてやるぜ。";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "辺りを見てくる、誰かが隠れていないか確認するよ。どうせ退屈だしな…";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "（中国語で）兵士たちよ！なんと不運な……私はこれからどうすればいいのだ？";
			link.l1 = "（中国語で）俺はこの金が白人の兵隊どもよりずっと必要なんだ！これを手に入れずには絶対に帰らんぞ！";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "ああ、ロングウェイ旦那、お戻りになったのですね！";
			link.l1 = "もちろんです。疑いでもありましたか？モーニングスターについて何か見つけましたか、ジョルジュ？";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "はい、旦那。重いガレオン船で、船長はスペイン人だとか……";
			link.l1 = "あいつはポルトガル人だ。お前ら白人は自分たちの区別もつかないんだな。";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "ああ、そうだった。私の間違いだ。ともかく、 奴がそのガレオン船を商船に見せかけるために大幅に改造していたことがわかった。小口径の大砲と少人数の乗組員でな。 しかし、船倉は拡張され、隙間なく荷が詰め込まれている――あまりに重くて、ほとんど航行できないほどだ。";
			link.l1 = "それで彼は新しい人生を始めることにしたんだな。いいだろう。さて、彼はどこにいる？";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "それはもっと厄介だな。奴は我々の植民地とイギリスの植民地の間を絶えず移動しているが、 ウィンドワード諸島の中だけだ。\nだが、今は大量のワインを積んでバステールへ向かっていると聞いた。";
			link.l1 = "どうやって早くそこに行けるか考えないといけません。";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "それはお前の問題だ、ロンウェイ旦那。俺には自分のことで手一杯だ……あの忌々しい屋根を直すとかよ。";
			link.l1 = "ご心配の件ですが、あの教会泥棒どもを見つけました。これが寄付金です。屋根を直してください――神様が屋根なしではお困りでしょうから。";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "本当にありがとうございます、Longway様！まさかあなたがそれをやってくれるなんて思いませんでした。";
			link.l1 = "俺もそうは思わなかった。しかし、その二日間、何かしなければならなかったんだ。";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "それで、グアドループに行きたいんだな？そっちに向かう船を探してやるよ。すぐに連絡するから待っててくれ！";
			link.l1 = "それは助かります。ありがとうございます、Georges。";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("The Next Morning..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "ジョルジュの知り合いか？彼に頼まれてこれを渡すよう言われた。";
			link.l1 = "手紙ですか？感謝いたします。どうして私宛だと分かったのですか？";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "本気ですか？";
			link.l1 = "ああ、そうだ。";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "（手紙を読む）ロンウェイ旦那、「プロヴァンス」ピナスは明朝バステールへ出航する。 船長のマチュー・テルュニーは酒場にいる。ヴァン・メルデン旦那によろしく伝えてくれ。- ジョルジュ・グラヴェル";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "ここではお前らみたいな奴には酒は出さねえ。\nそれに、ノミの苦情なんざ聞きたくもねえから、部屋も貸さねえぞ。";
			link.l1 = "酒も部屋もいらない。それに…ロングウェイにはノミなんていない。";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "俺が知るわけねえだろうが。\nさあ、言えよ。何の用だ？\nなら、とっとと出て行け。";
			link.l1 = "承知しました。マチュー・テルニー船長を探していますが、見つかりません。どこにいるかご存知ですか？";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "あいつは地元の店で自分の船を出航の準備で忙しいんだ。お前みたいな中国人とおしゃべりするより、 よっぽど大事なことさ。でもお前にはそれが分かってないようだな。";
			link.l1 = "実は、俺は昔……いや、今はどうでもいいことだ。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "何の用だ、中国人？忙しいのが見えないのか？俺は自分の船の準備をしなきゃならないんだ。";
			link.l1 = "マチュー・テルニー船長？";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "これはもう冗談じゃ済まされないな。どうしてお前みたいな奴が俺のことを知ってるんだ？誰かに頼まれて来たのか？";
			link.l1 = "心配はいりません。バステールへ航海すると聞きました。乗客として乗せていただけませんか？お金は払います。";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "どんどん面白くなってきたな。俺はサン・ピエールに向かうつもりだったが、バステールはちょっとした寄り道だ。\nそれは都合がいい、必要以上にお前を船に乗せておかなくて済むからな。五千ペソだ。三時間後に出航する。 支払いは桟橋でだ。\n俺は商人だが、値切りはなしだ。わかったか？";
			link.l1 = "はい。ありがとうございます。埠頭でお会いしましょう、Terugny船長。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "結局来やがったな、チンク。どうせ来ねえと思ってたぜ――お前らみたいな奴に自分から本物の金を渡すやつなんて、普通いねえからな。";
			link.l1 = "ご要望通り、五千ペソをご用意しました。出航の準備はできていますか？";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "いや、いや！それは俺が聞くべきことだ。でも、準備はできてるんだろうな。さあ、行くぞ。お前がボートを漕げ。 ちゃんとした船室なんて期待するなよ！この寄り道をするのは、お前のせいなんだからな。";
			link.l1 = "慰めはいらない。そこに連れて行ってくれ。";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "…だからロングウェイにはモーニングスター号が正確にどこへ向かっているのか分からなかったんだ。";
			link.l1 = "うん、あんたがあんな面倒に巻き込まれたのもわかるよ。";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "グアドループの海域でブリッグ船を見かけました。もしかするとバンテン号かもしれません。調べてみます。\nさて、もう行っていいぞ、ロンウェイ。私のところに持ってきてくれ " + sStr + ".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "私のキャプテン、すべて順調ですか？ロングウェイがあなたがお呼びだと言ったので、すぐに来ました。";
				link.l1 = "私はただ物事をつなぎ合わせようとしているだけです。\nあの島の沖で見かけたブリッグの名前、覚えていますか？";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "私に会いたかったのですか？";
				link.l1 = "ああ。最近見かけたブリッグを覚えているか？その所在と名前を調べてくれ。";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "覚えているが、なぜ急にブリッグに興味を？調べるには少し時間がかかるかもしれない。";
			link.l1 = "エレン、頼むからやってくれ。\nそれに、時間がかかるかもしれないのは分かってる。\n俺は待ってるよ。";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "いいえ、確認していません。\nなぜですか？重要なのですか？";
			link.l1 = "うん。もっと調べてくれる？今どこに停泊しているのか知りたいんだ、もしまだグアドループの海域を離れていないなら。 ";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "もちろんです。ただ、少し時間がかかるかもしれませんので、ご了承ください。 私が小舟と何人か連れて手伝いに行きます、でしょ、Charles？";
			link.l1 = "もちろん、エレン、ありがとう。待っているよ。";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "旦那船長、お呼びですか？";
			link.l1 = "はい、アロンソ。ロングウェイを迎えに戻ったとき、島の沖合でブリッグ船とすれ違ったよ。名前を確認できたかい？";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "いいえ、私の役目は新入りを見張って、斬り込み隊に加わることです。それに、望遠鏡なんて持っていませんし、 あいつとそこまで親しかったわけでもありません。";
			link.l1 = "確かに。しかし、それでも調べなければならない。やれ。";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "あいよ、船長。半日でできると思います。";
			link.l1 = "急げ。待っているぞ。";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "すべて学びました。私がいない間、何も問題なかったですか、私のキャプテン？";
				link.l1 = "ええ、大丈夫です、ありがとう、ヘレン。話してください。";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "ふう、戻ったよ。君のブリッグを見つけた。";
				link.l1 = "お帰りなさい。彼女の居場所と名前は？";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "バンテン号。その名前、あなたには何か意味があるんじゃないですか？\n今は灯台に停泊していて、乗組員の何人かが上陸しています。\nあの船を襲撃するつもりですか？";
			link.l1 = "いや、誰が上陸したのか正確に突き止める必要がある。陸路で灯台へ向かおう。すでに時間を食っていることを考えれば、 もう港を出発すべきだ。人目につかない場所に錨を下ろそう。キャップスター・ビーチがいいだろう。急ごう、ヘレン。";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "さて、そのブリッグはバンテン号と言って、灯台に停泊しています。何人かの乗組員はそこに上陸しています。\nどうなさるおつもりですか？";
			link.l1 = "確かめるには、灯台まで誰にも気づかれずに行かなくてはならない。歩いて行くしかないんだ。\n船はどこか安全な場所に停泊させる必要がある。カプスター・ビーチはどうだ？";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "いい考えだ。チャールズ、一緒に灯台へ行こうか？";
			link.l1 = "船を動かしながら考えるよ――君はもう十分に疲れているからな。";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "用が済んだらすぐ戻ってきた、旦那船長。";
			link.l1 = "よろしい。報告しろ、アロンソ。";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "ブリッグ船はまだ島の沖にいる――正確には灯台のそばだ。船尾には「バンテン」と名前が書かれている。乗組員の何人かは上陸したようだ。";
			link.l1 = "よくやった、Alonso。すぐに錨を上げる準備を乗組員にさせろ。";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "お前も突入の準備をするのか？";
			link.l1 = "まだだ。もしあいつらの船長が灯台に向かっているなら、俺たちが海で攻撃すれば、やつは町に隠れるかもしれねえ。\nまずはキャプスタービーチで船を確保してから、徒歩で灯台に近づこう。";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "旦那船長、見てください！灯台の中に誰かいます。";
			link.l1 = "よし、間に合った！急いで奴らを捕まえよう。今日はアロンソが大忙しになるぞ。";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "「しかし、その過程で死んでしまったらどうするのですか？」";
			link.l1 = "ご提案は何でしょうか？";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "静かに忍び込んで、まずは奴らの会話を盗み聞きします。";
			link.l1 = "窓から見られずにそれができるとは思えませんが、やってみましょう。";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "HiddenImmortality");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "私の言ったことを考えてみろ。よく考えるんだ。金は問題じゃない――もちろん、ある程度の範囲内だがな。だが、その範囲ですらお前には金山のように思えるはずだ――あの中国人は死ななければならん！以前にも奴を追わせたが、何の成果もなかった。だが今回は、 お前の部下と手を組めば……\n";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "見ろ、俺たちは見張られてるぞ！あいつだ！あいつと、あの忌々しい船長だ！";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "くたばれ、この汚いアジア野郎……お前のせいで俺はどれだけ苦しんだことか。なのに、結局こんな仕打ちで死ぬのか……";
				link.l1 = "我々が医師のところへお連れします、司令官殿。\n誰と話していたのか教えてください――とても重要なことなのです。";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "彼の名は……ヨープ・ファン・デル・フィンク、彼は……カッ……";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "死んだか……まあ、少なくとも名前は分かったな。ロングウェイ……？";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "そんなはずが……";
			link.l1 = "「ちょっと顔色が悪いな、ロンウェイ。」";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "ロンウェイは十年前にファン・デル・ヴィンクを確かに殺したと思っていた\n逃げていくぞ！あいつらの船は速い！";
			link.l1 = "ああ、素晴らしいブリッグだ……我々にとっては不運だがな。\nたとえ急いで船に戻れたとしても、帆を上げて風をつかむ頃には、やつらはもういなくなっているだろう。";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "これで終わりかもしれません……";
			link.l1 = "いいや、ロングウェイ。私の話を聞いてくれ。もし奴らが諸島に留まるつもりなら、遅かれ早かれ必ずまた出くわす――この世界は狭いし、カリブは特にそうだ。奴らの痕跡を再び掴んだら、私はすべてを投げ出してでも追いかける。 約束する。聞こえたか？";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "はい、ロードキャプテン。ありがとうございます。";
			link.l1 = "顔を上げて、ロンウェイ。急いで船に戻らないといけない――司令官の死はすぐに大きなニュースになるぞ。";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			ReturnOfficer_Longway();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "旦那！少しお時間を！あなたは船長ですか？";
			link.l1 = "そうかもな。どうして分かった？それで、何の用だ？";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "ここは山と深いジャングルしかない――町へ続く道もないのに、あなたはここにいる。観光だけじゃないんでしょう？";
			link.l1 = "良い観察力ですね。しかし、まだあなたが何を望んでいるのか教えてくれていません。";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "あっ、そうだ！船長、俺たちの船はこの入り江のすぐそばで座礁しちまったんだ。生き残ったのは俺たちだけだ……";
			link.l1 = "申し訳ありません。どこかにお連れすればよろしいのですね？";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "ああ……俺たちは絶対に面倒を起こさない、誓うよ。ベリーズで降ろしてくれれば、あとは自分たちでなんとかするから。";
			link.l1 = "遠くはないんだろう？それなら、ようこそ乗船を。";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "申し訳ありませんが、私は反対方向へ向かっています。";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "ありがとうございます、船長！あなたがいなければ、私たちがどれだけ長く足止めされていたかわかりません。";
			link.l1 = "確かに。その時間、無駄にしませんぞ！";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "でもベリーズはすぐ近くじゃないか！きっと時間はかからないでしょ？";
			link.l1 = "急いでいる。寄り道している暇はない。";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "「短い航海でもダメ？ベリーズまででも？お願い、船長、私たちを置き去りにしないで！」";
			link.l1 = "よし、後悔しないといいけど。全員乗り込んで！";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "仕方がないさ。良い一日を、お前たち。";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "改めてありがとうございます、船長！俺たちはただの水夫だから、あなたに差し上げられるものはあまりありません。";
			link.l1 = "まあ、少なくともあまり遠回りせずに済みましたね。";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "あなたの健康を祝って酒を酌み交わし、教会であなたのためにろうそくを灯そう。";
			link.l1 = "それは何もないよりマシだな。乾杯だ、野郎ども！";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "聞いたか？ついに奴を捕まえたんだ！これで俺たちの海もやっと安全になったな！";
			link.l1 = "それは……良い知らせですか？でも、誰を捕まえたんですか？";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "「マシュー・ラター、大口叩きの本人だ！」";
			link.l1 = "よく知りません――彼は何をしたんですか？";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "知らないの！？まあ、あんたがイングランド人じゃないのは一目で分かるよ。あいつは「カモメ号」 で何年も私たちやスペイン人を襲ってきた海賊さ。";
			link.l1 = "イギリス人もスペイン人も両方略奪するのか？それは珍しいな。";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "確かに。沿岸警備隊は奴を決して捕まえられなかったが、結局は自分の手に負えない相手に手を出してしまった――信じられるなら、なんと妙な商船に負けたんだ。";
			link.l1 = "それは面白いですね。その商人の何がそんなに奇妙だったのですか？";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "まあ、ただの大きくて不器用なガレオン船が護衛もなしでいたんだよ！でも、あの狂った船長のおかげで、 ルッターは今日が最後の歌になる――もうすぐ絞首刑さ。見に来たほうがいいぜ！";
			link.l1 = "今はそうかもしれませんが、今は他に片付けるべき用事があります。";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "旦那船長！";
			link.l1 = "大胆な海賊を打ち負かすスペインの商人……あなたもロンウェイと同じことを考えているのでしょう？";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "暁の明星……";
			link.l1 = "たぶん、あの男のような商船の船長は、この群島中どこを探しても他にいませんよ。";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "すぐにあいつを見つけなければなりません！";
			link.l1 = "そうだな。しかし港には大型ガレオン船なんて見当たらないな。\n吊るされる前にあのおしゃべり野郎と話してみようぜ。\nあいつがそのあだ名にふさわしいか確かめてやろうじゃねえか。";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			ReturnOfficer_Longway();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "まだ生きているのか？話すことはできるのか？";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "何だって？ああ、そうだ。あいつはまだ生きてる――処刑はまだ行われていない。話したければ会いに行けばいいさ――今までになくよく喋るぞ。だが最近は、ほとんど独り言ばかりで、訳の分からないことを口走ってる。 あの大口野郎はもう狂っちまった……あいつの終わりのないおしゃべりで俺たちまで気が狂う前に、早く首を吊ってやりたいもんだ。";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "ありがとうございます。";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			ReturnOfficer_Longway();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "「俺の宝を盗みやがった！」";
			link.l1 = "「マシュー・ラッター？」";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "俺の宝はもうあいつに縛られてるんだ、わかるか、あいつにだ！\n俺たちにできることなんて何もない！何が望みだ！？まだ俺たちから何か奪うつもりか？もう何も残っちゃいねえ！ あの子は死ぬんだ！それか、もっとひどい目に遭う！";
			link.l1 = "誰が死ぬって？どんな財宝だ？まあいい、自業自得だ――攻撃したのはお前たちの方だろう、あのガレオン船を。";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "違う！逆だったんだ！くそったれのイダルゴめ！あいつのせいで俺たちはこんな目に遭ってるんだ！ あいつが真っ直ぐこっちに突っ込んできて、至近距離で撃ちやがった！それから、あいつが彼女を奪っていったんだ！";
			link.l1 = "本当か？それは別に驚かないな。彼について他に何か知っていることは？それと……何を奪われたんだ？「彼女」って誰のことだ？";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "あああっ！！！ああああっ！！！";
			link.l1 = "なるほど、俺は時間を無駄にしているんだな……";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "船長、もしお許しを……ルッター！出ろ！ここが終点だ、相棒。";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "船長、SottaとLutterについてもっと調べる必要があります。周りに聞いてみましょう。";
			link.l1 = "いい考えだな、ロングウェイ。叫んでいた男からは結局あまり情報も得られなかったしな。";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "しかし、まずはソッタから始めたほうがいい。";
			link.l1 = "そうだ、奴が俺たちの狙いだ。行こう。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "奴らは何も知らねえ！";
			link.l1 = "当然です。しかし、我々には自分で考える材料が十分にあります。私の聞いたところによれば、 ソッタは褒美として手に入れたあの戦略物資を、近いうちに売りさばこうとするでしょう。";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "まさにその通りです！";
			link.l1 = "奴を途中で捕まえるなら、ポートロイヤルかキャップスタービルだな。問題は、どちらに向かうのか、 そしてどこで仕掛けるべきかってことだ。\nあるいは、外洋で奴を捉えることになるかもしれねえ。";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "違う！ロンウェイが言いたかったのは……フェルメンテロスは百戦錬磨の船長だ。外洋で戦えば、どちらが勝つかわからない。港で待ち伏せした方が、勝算が高い。 ";
			link.l1 = "おっしゃる通りでしょうね。マットと彼の間で何があったにせよ、ソッタは危険で、決して侮れません。";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "俺たちも待ちきれないぜ！";
			link.l1 = "また正解だな、ロンウェイ。\nじゃあ、すぐに錨を上げて、それから次の行動を考えよう。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "旦那船長、モーニングスター号が港に入っています！";
			link.l1 = "「はい、すでに気づいております。」";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "ご計画は？";
			link.l1 = "まだ決めていない。砦の大砲の下で乗り込もうとするのは自殺行為だ。たとえあの大型ガレオンを奪えたとしても、 あれで逃げ切ることはできない。\n何か考えはあるか、ロンウェイ？";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "はい。安全な入り江に錨を下ろし、夜の闇に紛れてボートでガレオン船に近づくことができます。";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "「ハーフムーン湾はどうだ、ロンウェイ？」";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "ポートランド湾がちょうどいいと思います――近いし、比較的安全です。どう思いますか？";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "良い選択です。";
			link.l1 = "よし、これで決まりだな。何か抜けてないか？";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "そうは思いません、旦那船長。しっかり準備を整えるだけです。";
			link.l1 = "まったくその通りです。";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "てめえは何者だ、何が起きてやがる！？ホルムズ旦那！";
			link.l1 = "ホルムズ旦那はもうここで働いていません。それに、全てのハッチはしっかり封鎖しました。\nですから、しばらくは邪魔されることもないでしょう、フェルメンテロス旦那。";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "何だと？フェルメンテロスだと？俺の名はエドガルド・ソッタだ！";
			link.l1 = "うん、その話は前にも聞いたことあるよ。あなたの本当の名前じゃないって、私たち知ってるんだから、オリヴェイロ。";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "フェルメンテロスは死んだ！";
			link.l1 = "考え直してみると、やっぱり君は若すぎるな。十年前にモーニングスター号の船長だったはずがない。\nそれで、オリヴェイロはどうなったんだ？";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "俺たちはあいつを片付けた。あいつも、ただの厄介ごとだった――お前の隣に立ってる奴と同じようにな。";
			link.l1 = "さて、あんたがフェルメンテロスじゃないなら、まだ俺たちの質問に答えられるかもしれねえな。俺の友の大事な人を、 あいつが連れ去ったんだ。その人物を探してる。";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "俺は何も話さない！これをやったら、あいつは絶対に俺を許さないんだ。";
			link.l1 = "今は、我々があなたを許すかどうかを心配したほうがいい……";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "ついに奴は死んだ……";
			link.l1 = "その通りです。そして、あなたはどなたですか、奥様？彼に無理やりここにいさせられていたのですか？お気の毒に……きっとひどい目に遭われたのでしょう……";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "私はアナベル・ラターです。\nそして、神に感謝します、私はあまり苦しまずに済みました。でも、ご心配いただきありがとうございます、旦那…？";
			link.l1 = "シャルル・ド・モール船長。リュッター、そう言ったな……";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "ああ、マットのことを聞いたことがあるのでしょう？哀れな愚か者……私は彼の愛人でした。";
			link.l1 = "ご愁傷様です、ルッター夫人。あなたはもう未亡人ですね。もし差し支えなければ、旧姓を教えていただけますか？";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "私には名前なんてなかった。俺のことをよく見てみろ。俺の哀れな母親は、海賊たちの黒い肌の奴隷娘だったんだ。 父親が誰かなんて誰も知らないし、だからちゃんとした名前を付けてもらうこともなかったんだ。";
			link.l1 = "なぜその時、誰もお前に手を出さなかったんだ？\n誤解しないでくれ――そうならなくて本当に良かったと思ってる。\nだが、それでも……普通じゃないな。";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "おっしゃる通りです。でも、物事は正しく呼びましょう。私は甘やかされた貴婦人じゃない、奴隷の娘です。 重い話くらいで気絶したりしません。";
			link.l1 = "ええと、私も甘やかされるのは苦手です。しかし、どうぞ続けてください。 なぜ乗組員たちは奴隷女の娘に指一本触れなかったのですか？あなたは父親を知らず、 彼も気にかけていなかったようですね。";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "そうかもしれませんね。マットのことをご存知なら、彼がしばらくレヴァスールの下で働いていたことも知っていますか？ ";
			link.l1 = "ああ、「暁の星」を探している時にその話は聞いたよ。でも、それがどう関係あるんだ？全部話してくれ、お願いだ。";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "まだ分かっていないのか？どうやらレヴァスールの……趣味について聞いたことがないようだな？";
			link.l1 = "私は見ていませんが、でも、それが一体何の関係が……？";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "ああ、全部話さなきゃいけないみたいだね。もし気が弱いなら座って、旦那。実はね、あいつは女と寝まくっててさ、 それで…";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "彼の妻も彼の近くにいて、ほとんど誰とでも寝ている。";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "ああ、なんてことだ。";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " そうだな、よく言うだろ……夫婦は似るってな。\nだが、いや、あいつはそれどころじゃなかったはずだ。";
			link.l1 = "それで、どれくらい遠いのですか？";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "ここで皮肉を言うのは見当違いですよ、旦那。あなたには我々が何について話しているのか全く分かっていません。";
			link.l1 = "わかった、わかった、ごめん。続けて、どうぞ。";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "それは単なる浮気じゃない。奴は女たちを無理やり連れていくんだ。\nしかも一度きりの暴力じゃない。奴は娘たちを誘拐して、自分の持っているワインセラーの一つに閉じ込めているんだ。";
			link.l1 = "つまり、あいつは定期的に奴隷の少女たちを手に入れているってことか？そして君もその一人になるはずだったのか？";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "後者についてはその通りだ。しかし、残念ながら最初の点は違う。奴は奴隷を必要としていない。 ルヴァスールは狂っている――自分なりのやり方で、俺のマットとは違う。フランソワは女を完全に支配したいんだ、肉体も魂もな。 もちろん愛なんかじゃない。意志を砕くために自由な女が必要だった。奴は、女たちの目つきや振る舞い、 話し方が時と共にどう変わっていくかを見るのを楽しんでいたんだ……\n";
			link.l1 = "…おぞましい…";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "もうすでに少し気分が悪いだろう。では、あの女たちがどんな目に遭ったか想像してみてくれ。俺はこの話を聞いたんだ、 マットだけじゃなくてな。ルヴァスールはかつてポルトガルの貴婦人を…";
			link.l1 = "お前は目をそらして黙っていたな。全部話せ。俺は旧世界でも、この諸島でもいろんなものを見てきた。 今さら何も驚かねえよ。";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "止めてくれ、彼女に何があったか知りたくない。あの女たちが奴の手で長く苦しまなかったことを願う。";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "だが、こんな話は聞いたことがないだろう。そして、できれば一生見ることもないよう願う。彼女はまだ誇り高く、 屈していないまま連れてこられた。マットが言っていたが、 ルヴァスールの手下どもはカンペチェ近くの夫のプランテーションを奪った後、 トルトゥーガまでの道中ずっと彼女を凌辱した――夫は両膝を撃たれた挙句、出血多量で死んだそうだ……";
			link.l1 = "強い女……だが、あなたは言った、レヴァスールは自分が欲しい女には普通は手を出さないと。";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "彼が特に要求した者たちは手を付けられなかった。\nだが、レオンティナ夫人は贈り物だった。彼ら全員にとって予想外で、そして心地よい贈り物だった。\nだから、彼らは好き勝手にした……";
			link.l1 = "なるほど……";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "たぶん……マットはフランソワのお気に入りの一人になっていたんだろう。彼はルヴァスールの秘密の夜会に招かれた……宴の最中、ある海賊が女が足りないと文句を言った。ルヴァスールは笑って、それから……";
			link.l1 = "それで？何が起きたんだ？";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "…それから彼女は引きずり出されたんです。\n首輪をつけられて！殴られ、背中には引っかき傷、目隠しされて口も塞がれていた。\n猿轡を外されたとき、彼女が言ったのは…";
			link.l1 = "恐ろしいことだったのでしょうね。彼女は持てる限りの呪いを彼に浴びせたのですか？";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "もしも……ドナ・レオンティナはただささやいた。「ご主人様は何をお望みですか？」";
			link.l1 = "吐きそうだ。マットはその後彼女に何が起きたか、旦那に話したか？";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "殺されたのです、もちろん。しかし、それはルヴァスールの手によるものではありません。 彼は彼女を捨て犬のように放り出しました。彼の部下の一人が彼女を撃ちました。死ぬ前に、 彼女はただ一言だけを口にしました…";
			link.l1 = "呪いか？祈りか？";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "いいえ。「ありがとう…」";
			link.l1 = "このような苦しみの果てに死に感謝するとは……彼女はいったいどれほどの地獄を味わったのか……あの怪物の巣で、彼女のような者たちが……";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "ルヴァスールは特に奴隷や肌の黒い女たちを嫌悪していた――「壊す価値もない」と言っていた。彼のもとでは彼女たちもインディオたちも長くは生きられなかった――特に頑固な者を除いては。だが、野性や反抗心も救いにはならなかった――彼は、早くに媚びようとした者も、長く逆らい続けた者も、どちらも殺したのだ。";
			link.l1 = "それは恐ろしいことだ……教えてくれ、ルヴァスールはアジアの女を抱いたことがあるか？";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "いいえ、少なくとも私が聞いた限りではありません。私のことについては……前にも言った通り、あの人は色の黒い女が好きじゃなかった。だからマットがフランソワの下で働いていた時は、 私と一緒に堂々とトルトゥーガの街を歩いていたわ。一度は屋敷にも連れて行ってくれたの。";
			link.l1 = "「だがルヴァスールは結局、お前を自分の奴隷にしようとしたのだな…」";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "まさに……なぜあの人が私のことをそんなに気に入ったのか、私には分からない……マットがそのことを知った時、知らせを受けるや否や島から逃げ出したの。二度とトルトゥーガには戻らなかった。 少し頭がおかしかったかもしれないけど、私を愛してくれていた。私のことを「宝物」って呼んでくれた……";
			link.l1 = "「それで、ソッタが自分の宝を奪ったと言ったとき、彼が言いたかったのはそういうことだったのか！」";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "へえ、そんなこと言ったの？ああ、マット……でも、私たちは一緒に年を重ねる運命じゃなかったみたいね。ルヴァスールが女に目をつけたら、どんな素性だろうと、 どんな代償を払おうと、手に入れるためなら何でもしたわ。ソッタは彼の船長の一人で、言われた通りに動いたのよ。";
			link.l1 = "なるほど。それで、これからどうするつもりなんだ、Annabel？";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "逃げるんだ。ルヴァスールの手下たちが俺に届かない場所へ。名前を変える。姿を隠す……";
			link.l1 = "ご成功をお祈りします。どうかうまくいきますように、アナベル。";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "通行の手配には金が必要だろう。これを持っていけ。ここに一万ペソある。";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "少しばかりの金じゃ足りないぞ。肌の黒い娘、たとえ混血でも、助けてくれる者はそう多くない。ほら、 百ドゥブロンやる――船を探して、身を隠せ。";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "あなたも！さようなら、船長。";
			link.l1 = "さようなら。";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "俺……俺には何と言えばいいのかわからない。マット以外に、こんな優しさを見せてくれた者はいなかった。";
			link.l1 = "もしかしたら、それは兆しかもしれません。結局どこかで幸せに年を重ねるという。\nさようなら。";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "おっしゃる通りです。本当にありがとうございます。このご恩は一生忘れず、祈りの中であなたを思い続けます。";
			link.l1 = "ありがとうございます。ご武運を。";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "あの男……いや、もう男じゃない。獣だ。化け物だ。女たちをあんなふうに拷問するなんて……";
			link.l1 = "お前が何を考えているか分かってるぞ、ロンウェイ。だが聞いただろう――あいつは黄色い肌の女を一度も抱いたことがないんだ。";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "でも彼は全員を知っていたんだ！ファン・デル・ヴィンク、フェルメンテロス、ソッタ…さっき彼の日誌で読んだばかりだろう。もしその「彼女」が…あの人だったら？";
			link.l1 = "誰にも分かりません……フェルメンテロスへの復讐に燃える女――そう考えるのは自然でしょう。しかし、オリヴェイロによって人生を壊された女なら誰でもあり得るのです。\nあなたの妹である必要はありません。黄色い肌の女である必要すらないのです。";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "やりますか…やらないのですか、我が主君船長？この土壇場で……？";
			link.l1 = "いいや、ロンウェイ。でも、どうするつもりなんだ？ルヴァスールが俺たちの質問に答えるとは思えないし、 こんなふうにトルトゥーガで嗅ぎ回るのは危険すぎるぞ。";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "それで、どうするつもりですか？";
			link.l1 = "待とう。ルヴァスールはお前の姉上のような女は好みじゃないと分かっている。だから今は力を温存できる。 忍耐と強さだ。フランソワは簡単には落ちない、特にあの“亀”がいるからな。でもスヴェンソンの助けがあれば、こちらの条件で話ができるはずだ。 お前の姉上を探す手伝いをすると約束したし、それを守るつもりだ。俺を信じているか、ロンウェイ？\n";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "ふむ……了解でございます、My Lord Captain。しかし、ロンウェイからもう一つお願いがございます。";
			link.l1 = "何だい？また一人で勝手に行くつもりじゃないよね？前回はあまりうまくいかなかったでしょ？";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "とんでもありません、ロードキャプテン。今になってようやく気づきましたが、残念ながら、 この白人どもが支配する世界で、私のような男が独りでできることなど何もありません。\nロンウェイはあなたにキャップスターヴィルへ寄港し、ジョルジュ・グラヴェルに手紙を届けて、 あなたが準備している間に何か分かったことがあれば調べてくれるよう頼んでほしいと申しております。";
			link.l1 = "賢明な考えだな、ロンウェイ。その通りにしよう。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "旦那船長、ロンウェイからお伺いしたいことがございます…";
			link.l1 = "手紙を書くのを忘れたのか？グラベルに直接話せばいいんだ。";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "いいえ、手紙はもう用意できています。でも、ロンウェイは一人で町をうろつかない方がいいと考えました。 ロードキャプテン……ジョルジュにこの手紙を届けていただけませんか？お願いします。";
			link.l1 = "俺が使いっ走りに見えるか？それとも、ここで船長なのはお前か？";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "旦那船長…";
			link.l1 = "ははは、冗談だよ、ロンウェイ！お前のそのグラベルとやらはどこで見つければいいんだったか、教えてくれよ？";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "彼は教会で働いている。";
			link.l1 = "わかった、あたしがやるよ、でしょ？";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "チャールズ、親愛なるチャールズ、どうかしたの？心配そうだし……疲れてるみたい、でしょ。";
			link.l1 = "ああ、いやいや、Mary、私は大丈夫だ。ただ……このトルトゥーガでの私の探索がさ、また行き詰まったみたいなんだよ。あと、Sharpの遺言も正直、私にはかなり堪えたよ、まったく。でも、気にしないでくれ。";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "何？何の依頼だ？それにシャープがどう関係してるんだ？俺には全然わからねえ！";
			link.l1 = "質問が多すぎるぞ、Mary。ここはそんな話をする場所じゃない。酒場の部屋で話そうか？君の好きなように、人目も気にせず、 何も考えずに済む場所で。\nこの一年間、俺が何をしていたか教えてやるよ。";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "でしょ！でも、警告しておくよ。もし何か隠してるなら……";
			link.l1 = "絶対に違います！行きましょう、どうせ暇なんですから……";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "不思議だと思わないか、チャールズ？この島は本来なら俺のもののはずなのに、全然そんな気がしないんだ。";
			link.l1 = "そう思いますか？";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "あら、その笑顔……女の扱い方、わかってるじゃない。でもどうしたの？顔が全然違うよ！";
			link.l1 = "なぜですか？これが私のいつもの顔ですし、とてもハンサムですよ。";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "チャールズ、あなたの声からわかります――最近、気が沈んでいるようですね。";
			link.l1 = "私にはやることが山ほどあるの、特にロンウェイのこともあって。本当にもう疲れ切ってるわ。\nでも、今さら諦めるなんてできない。彼にも父にも約束したんだから。";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "わからない……ロンウェイがこれにどう関係しているの？それに、あなたはどんな約束をしたの？";
			link.l1 = "話し合うなら、酒場で部屋を借りてやりましょう。\n他の人間から離れて。";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "よし、行こう。どうせ他にやることもないし、せめて一緒に過ごせるでしょ？";
			link.l1 = "案内して、ダーリン！";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "なんて愛らしいんだろう、互いの腕の中でこんなに穏やかに眠っている！素敵だ！";
				link.l1 = "嫉妬してるのか？";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "起きて、朝だぜ！恋人たち、よく眠れたか？";
				link.l1 = "ええ、聞いてくれてありがとう。で、君たちはよく眠れたかい？";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "それは愚かな質問だと思いませんか？";
				link.l1 = "そうだ。そして、あなたのしたことは愚かだ。理由を知りたいか？";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "「チャールズ・ド・モール、あなたは口が達者だと言われている。」";
				link.l1 = "俺の舌だけじゃないぜ。試してみるか？でも教えてくれ、なぜ俺たちが寝ている間に襲わなかったんだ？";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "それはなぜですか？";
				link.l1 = "朝にMaryを怒らせないほうがいいぞ。すぐにその理由がわかるからな。";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "簡単なことだ！暗かったからな、どっちが女か分からなかったんだよ。";
				link.l1 = "ろくでなし。";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "お前と違って、俺は女なんか怖くねえよ。さて――おい、野郎ども、あの女を無事に連れて行け。じゃねえと、ユグノー野郎に俺たちが女にされちまうぞ！";
				link.l1 = "ふっ…誰だ？";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "少なくとも俺は男の格好をしている。\nお前ら、金髪の女は生け捕りにしろ――ユグノーが待ってるぞ。";
				link.l1 = "フ…誰だ？";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "あれは誰だ、チャールズ？あのユグノーはいったい何者だ？まさか……？";
				link.l1 = "一つしかないんだ、Mary。だから俺たちは……";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "シャルル……今のは何だ？ユグノーか？俺の思っているあの男なのか？";
				link.l1 = "残念ながら、その通りだ、エレン。俺たちは……";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "聞こえるか？誰かが来るよ、でしょ？たぶんこの死体たちの仲間だね。";
				link.l1 = "それなら、奴らもあいつらの仲間入りさせてやろう。準備しろ…";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "聞こえますか？足音です。";
				link.l1 = "ええ、そうです。私の後ろに立ってください。";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "旦那船長、奥方 " + sStr + ".";
			link.l1 = "ロンウェイ？！お前、勝手に俺たちの部屋に入ってきていいと思ってるのか？もし俺たちが……だったらどうするつもりだ？";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "ふむ、失礼いたします、我が主君たる船長殿。そういうお忙しいご様子なら、扉を閉めておられるかと思いました。 しかし、ロンウェイが開いているのを見つけました。";
			link.l1 = "壊れている、開いてはいない。だが教えてくれ、友よ、なぜそんなにも落ち着いているんだ？床には死体が転がっていて、 俺たちは武装している、そしてお前は……";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "まあ、慣れております。";
			link.l1 = "それに反論できないよな、でしょ？でもさ、本当にここに来る途中で戦いの音が聞こえなかったの？ この乱暴者たちが酒場に入って、君の目の前で階段を上がっていくのを見なかったの？ ";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "いいえ、旦那船長。ここに来る途中、広間で見知らぬ者は見かけませんでした。";
			link.l1 = "それは馬鹿げた偶然だな。で、何の用だ、ロンウェイ？";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "至急、船と乗組員が必要です、My Lord Captain。";
			link.l1 = "何？どうして？ついに張星（チャン・シン）の手がかりを掴んだの？\nそれなら、今すぐ一緒に行こうよ。";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "残念ながら、張興ではありません……ヨープ・ファン・デル・フィンクです。ジョルジュ・グラヴェルが伝言を寄越しまして、 私が村をぶらついていた時に受け取りました、My Lord Captain。あなたは……ご婦人とお休みになっていた時に。";
			link.l1 = "ああ、しっかり休めたぜ、それだけは言っておく。だが、今ここで別れる理由なんてないだろう、ロンウェイ？ 俺たちにはまだ山ほどの重要な仕事と、始末しなきゃならねえ危険な連中がいるんだ。";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "ファン・デル・ヴィンクはルヴァスールほど危険ではありません。それに、私はすでに一度あいつを倒しました。 そしてまた倒します。今度こそ、確実に息の根を止めます。 私たち全員があいつのために貴重な時間を無駄にするのは嫌です。あなたはトルトゥーガへ行き、 重要な人物たちに必要なことを聞いてください。ファン・デル・ヴィンクは私が自分で捕らえます。My Lord Captain、あなたの時間を無駄にする価値はありませんし、私もかつては船長でした。私に任せてください。";
			link.l1 = "ふむ、確かに一理あるな、ロンウェイ。ヴァン・デル・ヴィンクはそれほど危険じゃないかもしれないが、「バンテン」 は諸島でも最速級の船だ。あれを追いかけるには、どんな船でもいいってわけじゃない。\nそれに、乗組員はどうするつもりだ？そんなに早く、しかも一人で人を集める方法は？";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "俺は正しい場所を知っているし、そこでのカンパニーの地位もある。いや、少なくともジョルジュの時みたいに、 そう装うことはできる。カンパニー……マインヘール・ローデンブルクは、急ぎで戦える男たちや、余計な詮索をしないプロの乗組員が必要だった時、 やつらの力を使ったんだ。";
			link.l1 = "雇われる船の乗組員か……そういうものがあってもおかしくないな。それで、いくらかかるんだ？";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "二千五百だ。今すぐ、ただちにだ。";
			link.l1 = "それだけか？大きな船に正規の水夫を酒場から揃えるには、もっと金がかかるもんだ。 どうやらローデンブルクとその手下たちは、特別な場所で特別な値段を持っているらしいな。";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "ドゥブロン金貨のことを言ったんだ、Lord Captain。";
			link.l1 = "「何だと！？」";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "お聞きになった通りでございます、ロードキャプテン。重要なことです。 些細なことでこのような額をお願いすることはございません。";
			link.l1 = "ああ、聞こえたよ、でもまだ信じられないな。本当に特別価格なのか。ペソでも受け取ってくれるのか？";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "そうだ……白人たちからだ。ロンウェイはそれで苦労するかもしれないが……私が必死に頼めば、きっと説得できると思う。道は、いつだってあるさ。";
			link.l1 = "ふうん、そりゃ大したもんだな。しかもそれは乗組員の分だけか……それに、あんたも自分の船に行かなきゃならねえんだろ？どうせまた“特別な場所”とか言うんだろうな？俺たちにいくらかかるのか、聞くのも怖いぜ……";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "そうではありません、My Lord Captain。乗組員は自分たちの船と共に来ます。";
			link.l1 = "しかし？";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "「『梅鳳（メイフェン）』。あの船は決定的な切り札になり得ます――諸島であれより速い船はありません。そして、あれは……いや、あれ“だった”のは私のもの、だからよく知っています。貸していただけますか、My Lord Captain？」";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "ここだ。二千五百ドゥブロンだ。ヴァン・デル・ヴィンクの首を純金の皿に載せて持ってくる限りはな、はははは！";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "そんなに多くのドゥブロン金貨は持ち歩いていないぞ、ロングウェイ。\nそれに、船の中にもそんな大金はないと思う――お前が言っているのは山ほどの金だ。\nだが、ペソならある。三十万ペソなら、ちょうどお前の必要な額だろう。";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "なあ、ロンウェイ……まさかお前のために、ただのチンピラと戦うためだけに包囲艦隊を装備できるほどの金を払えって言うのか！？";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "ああ……ロンウェイは心の底から感謝します、我が主君キャプテン！しかし、それでも「メイフェン」はどうなりますか？";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "彼女のことか？旦那、ここに来る途中で頭でも打ったのか？彼女は今、俺たちの艦隊にいるんだぞ！";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "考えさせてくれ、ロングウェイ。\nヴァン・デル・ヴィンクを捕まえるまで、どれくらい時間が残っている？";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "旦那船長、少し間違えましたね。二十五万ペソでございます。";
			link.l1 = "俺じゃないよ。これはシャルル・ド・モールの特別な交換レートさ、友達が助けを必要とするときのな。はは。 多めに渡してるんだ、全部に足りるようにな。";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "ありがとうございます、旦那。船長……しかし、「メイフェン」はどうなりますか？";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "彼女のことか？友よ、ここに来る途中で頭でも打ったのか？彼女は今、俺たちの艦隊にいるぞ！";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "考えさせてくれ、ロンウェイ。\nヴァン・デル・ヴィンクを捕まえるまで、どれくらい時間がある？";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "他に道はありません、ロードキャプテン、どうか落ち着いてください…";
			link.l1 = "ああ、まだ始めていないんだ。話はこうだ。五万ペソ。ちょうどそれで造船所からブリッグを一隻買い、 戦闘の準備をして、さらに乗組員まで雇える額だ。";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "しかし、旦那船長。白人の船長にはそれで十分かもしれませんが、 ロングウェイと取引することに同意する者ばかりではありません！私に何かを売る前に、 きっと厳しい条件を突きつけてくるでしょう！";
			link.l1 = "だから、もっと説得力を見せなさい！最初の…提案を見る限り、交渉は得意なようだな。まだここにいるのか？そんなに急ぎだと言うなら、この金を持って行け、 さあ行け！";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "了解しました、旦那船長……";
			link.l1 = "そんな目で俺を見るな。\nまたトルトゥーガで会おう。\n幸運を祈る。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "ええと、違いますよ、ロードキャプテン。もちろん、覚えています。ロンウェイはただ、 あなたが彼女を私と分かち合う準備ができているかどうかを尋ねていただけです。";
			link.l1 = "そうだ。結局のところ、ヴァン・デル・ヴィンクも我々のリストに載っている他の連中と同じくらい、 お前の妹の不幸に関わっている。だから、あいつを捕まえるのは本当に重要だ。メイフェン号の指揮をお前に任せる。";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "信じられません……ありがとうございます、旦那船長！";
			link.l1 = "ああ、なんでもないさ。あれはもともとお前の船だった、俺はそれをずっと覚えているぜ。さあ、行け。 あのクソ野郎を殺してこい。俺はトルトゥーガへ行く。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			Notification_Approve(true, "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "時間がありません、My Lord Captain。無駄にしてはいけません……チャン・シンが助けを必要としているかもしれません……";
			link.l1 = "それは分かっている、ロンウェイ。\nそれでも、ヴァン・デル・ヴィンクを捕まえるまで正確にどれくらい時間が残っているんだ？";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "数か月ほど――彼はそのくらい定期航路を回った後、しばらく姿を消すんだ。そういうやり方だと、グラヴェルが手紙で教えてくれた。";
			link.l1 = "よし。じゃあ、船に行こうか……";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "申し訳ありませんが、準備をすぐに始めなければなりません、ロードキャプテン。\nメイフェンを手に入れたらすぐに始められるように。\n事前に男たちと交渉しておく必要があります。 ";
			link.l1 = "それで、どこで会うんだ？";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "ここです。しかし、ご都合がよろしければ造船所でお会いしましょう。";
				link.l1 = "なぜ私だけが、ここで金さえ払えば戦う男たちを丸ごと雇えるって知らなかったんだ？";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "あの傭兵どもは以前イスラ・テソロに居場所があったが、ここに追いやられたんだ。";
				link.l1 = "なるほど、理由は分かるよ。それで、ラ・ベガではどこで君を探せばいいんだ？";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "それは知っている者がほとんどいないからです。そして、手に入れられる者はさらに少ない。 ローデンブルク旦那は長い間、彼らの唯一の依頼人でした。";
			link.l1 = "なるほど。わかったよ、ロンウェイ。そこで会おう。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "酒場でございます、My Lord Captain。他に私がいる場所などございますか？";
			link.l1 = "そうだね。それじゃあ、またね、ロンウェイ！自分の身は大事にしてよ。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "旦那船長、乗組員の準備が整いましたことをお伝えします。\n最後に処理すべき事が一つ残っています。「メイフェン」の件はどうなさいますか？";
			link.l1 = "今のところ、お前にふさわしい船はまだ選んでいないな、ロンウェイ。";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "「」" + sStr + "「』はあなたのものです。」";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "「『梅鳳』はどうした？私があの船を無駄にすると思ったのか？」";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "お前のために…特別な船を用意したぞ、ロンウェイ。速い船だ。それに、メイフェンよりもさらに恐ろしい。戦争用ガレオン、『 フライング・ハート』だ。";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "ロンウェイ、お前はシーベックが好きだな。ポラカもどうだ？特にこの「トレロ」ってやつ。 もちろんレガッタ用に作られた船じゃないが、かなりの力を持ってるぞ。\n";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "正直に言うと、これがいつか役に立つとは思っていませんでした。\nこのガレオン、どう思いますか？偉大なる『エル・カサドール』ですよ！";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "「『メイフェン』じゃありません、我が主君船長！『メイフェン』に何があったのですか？」";
			link.l1 = "「ロンウェイ！」 " + sStr + " 危険なんだよ！あなたの妹も同じく危ないんだよ！それなのに、こんな船がないって不機嫌になってるの？！こんな船、 誰だって喜ぶでしょ？この船を指揮して、ヴァン・デル・ヴィンクにあなたの実力を見せてやりなよ。";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "……よろしい……天が俺に幸運を授けてくれることを願う。トルトゥーガでの"+GetSexPhrase("君","あなた")+"にも同じ幸運があるよう祈っている。さらばだ、My Lord Captain。";
			link.l1 = "私は確信している。さようなら、ロンウェイ。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "ええと、違いますよ、旦那船長。もちろん、覚えています。ロンウェイはただ、 あなたが彼女を私と分かち合う準備ができているかどうか、尋ねていただけです。";
			link.l1 = "そうです。結局のところ、ファン・デル・ヴィンクも我々のリストに載っている他の連中と同じくらい、 あなたの妹の不幸に関わっていますからね。だから、奴を捕まえるのは本当に重要です。『美風号』 の指揮権をあなたに託します。";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "信じられません……ありがとうございます、ロードキャプテン！";
			link.l1 = "ああ、なんでもない。あれは元々お前の船だった、俺はそれをずっと覚えてるさ。さあ、行け。あのクソ野郎を殺せ。 俺はトルトゥーガへ向かう。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "俺……俺にはこれを指揮できません、My Lord Captain。ロングウェイはまだ自分の命も魂も正気も気にしています。";
			link.l1 = "ははは、ロンウェイ！さあ、そんなに迷信深いとは知らなかったよ。でもまあ、呪いはもう解けたんだから、 もう何も怖がることはないさ。";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "ああ…しかし、それをファン・デル・ヴィンクは知っているのか？あいつはあの船を見た途端、 怯えた兎のように逃げ出すだろう。";
			link.l1 = "その通りだな。よし、他にお前のためになることを探そう。";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "自分で船長をやっていた時にポラッカ船には乗ったことがない。\n面白い船だが、今は力よりも速さが一番大事だ。";
			link.l1 = "それは確かにそうだけど、所詮はポラッカ船だよ。『バンテン』ほど速くはないかもしれないけど、 あいつらが無理な角度でも帆に風を受けられるんだ。『メイフェン』本人よりも、もっとね。だから、 その強みを活かして。";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "それでも……「メイフェン」の方が良かった……惜しいことをしたな、我がロードキャプテン。トルトゥーガでの幸運を祈る。";
			link.l1 = "「あなたもだ、ロンウェイ。ありがとう。」";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "それは諸島で最も風変わりなガレオンかもしれません、我が主君船長。しかし、私が扱えますが、「バンテン」 より遅いのです…";
			link.l1 = "「まあ、ジョープとレガッタで競争してるわけじゃないでしょ？」";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "ご随意に。しかし「メイフェン」の方が良かった……惜しいことをしましたね、My Lord Captain。トルトゥーガでのご武運を。";
			link.l1 = "あなたもだ、ロンウェイ。ありがとう。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "ご心配ありがとうございます、My Lord Captain。しかし急いでください――時間があまりありません。";
			link.l1 = "分かってるよ。でも、無駄足を踏みたくないでしょ？でしょ？\nよし、ちゃんとした船を探してあげるね。";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "もうすぐだ、チャールズ。どこから始めるか決めたか？もしかしたら、通りの人々に聞いてみるのがいいかもしれないな…";
			link.l1 = "そうかもしれない。しかし、それは俺たち――いや、俺のためじゃない。ヘレン、お前は船に残れ。";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "シャルル、もちろん、あの悪党どもの言葉や行動にはまだ不安が残っているし、 乗組員たちの保護下にいるのは理にかなっていると思うけど…\nでも、あなたがひとりであの獣の巣窟に向かうのを見ていても、私の不安は消えないわ。";
			link.l1 = "わかった。しかし、もし事態が悪化したら、お前が無事だとわかっていれば、俺一人で逃げる方がずっと楽だ。命令だ、Helen。ここで待っていてくれ、あまり心配しすぎるな。\n";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "ここがトルトゥーガだよ、チャールズ、でしょ？早くどこかの扉を叩いて、 あのデブ野郎が私に何を求めてたのか聞き出したくてたまらないよ…";
			link.l1 = "「だからこそ、君は船に残るんだよ、私の愛しい人。」";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "ありえないよ！あんたを一人で上陸させるなんて、私が許すと思ってるの？";
			link.l1 = "ルヴァスールが自分の傭兵たちがやり損ねたことを自ら仕上げると決めたら、我々には反撃の余地はないと思う。\n無用に彼を刺激したくはない、特に私の標的は彼ではなく、ヨープ・ファン・デル・ヴィンクだからだ。";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "じゃあ、今は俺が閉じ込められてるってわけ、でしょ？";
			link.l1 = " 命令しているんじゃない、頼んでいるんだ、Mary。";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "あのクソみたいな島の裏路地で、あなたに何かあったらどうするんですか？";
			link.l1 = "じゃあ、無茶はしないって約束するよ。君が無事だと思えば、もっと速く走れるから。だから船で待ってて、 お願いだから、何があっても絶対に上陸しないで。\n";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "お前は誰だ？浜辺を歩いてきたのは、ただ話をしに来たわけじゃなかろう。";
			link.l1 = "そうだ。その通り、シャルル・ド・モール。ロベール・マルテン？";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "シャルル・ド・モール？くそっ、俺を怪しいことに巻き込まないでくれよ。\nああ、俺だ。で、何の用だ？";
			link.l1 = "「あなたはヨープ・ファン・デル・フィンクと友人だと聞きましたが、それで…」";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "誰がそんなことを言った？そいつの腹を裂いてやる。まあ、俺たちは顔見知りってだけだ。それだけだよ。 あんたに逆らったからって、揉め事はごめんだ。";
			link.l1 = "へぇ、仲間を見捨てるのがずいぶん早いんだな……";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "そう思わないでください。私はあなたを恐れていません。しかし、なぜわざわざ面倒なことをしたり、 それを作り出したりするのですか？あなたが聞かされたほど、私はJoepと親しいわけではありません。彼を探しているのですか？";
			link.l1 = "まあ、そんな感じかな。やつはもうトルトゥーガを離れたのは知ってるけど、もっと情報を集めて損はないでしょ？ どこに行ったか、誰と話したかとか。手伝ってくれる？";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "どうせ役に立たないだろうから……まあ、いいだろう？あいつは売春宿にいた。あの売春宿だ。あんたなら払えるだろうから、教えてやるよ。";
			link.l1 = "新しい売春宿か？もう一軒じゃ足りなくなったのか？";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "まあ、新しいってわけじゃないが、知ってる奴は少ないんだ。それに、手が届くのもほんの一握りさ。どうやら、 旦那の番が来たみたいだな。だが、警告しておくぜ――受け取るのはドゥブロン金貨だけだ。銀貨なんか出したら、尻を蹴飛ばされるぞ。";
			link.l1 = "そうだと思った。で、その売春宿はどこにあると言った？";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "あの柱のある建物、知ってるだろ？あそこだよ。それに、あそこの女主人がまたすごいんだ！黄色い肌で、 すごく美人だぜ！おい、もうよだれ垂らしてるじゃねえか？";
			link.l1 = "へへっ、まあ、そんなところかな。ありがとう、ロベール。今日は面倒ごとはなしだよ――君は本当に助けてくれたからね。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "やっと戻ってきたね、チャールズ！あたし、居場所がなくて落ち着かなかったよ、でしょ！";
			link.l1 = "すぐ戻るよ、Mary。ちょっと用事があるんだ……焦らさないよ、Longwayの件さ。地元の娼館に行く必要があるんだ。";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "一人で上陸させるんじゃなかったって分かってたよ。帽子をかぶるのを忘れて、頭が熱くなったのか……それともどこかにぶつけたんでしょ、でしょ！？";
			link.l1 = "メアリー、聞いてくれ。この店の主人はロンウェイの妹かもしれない。確かめるには彼女に会わなきゃならないが、 それだけだ。中に入らないと無理だ。でも、君に余計な心配はさせたくないんだ。";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "チャールズ、本当に俺に嘘をついていないのか？";
			link.l1 = "メアリー、こう考えてみてくれ……愛する人にこんな警告をする男の話、聞いたことあるか……？";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "そこで止まって、Charles。そんなこと考えたくもないよ。私はあなたを信じてるし、頼りにもしてる。だから、 必要以上にそこに長く留まらないでほしいんだ。";
			link.l1 = "もう一分も待たせないよ、ダーリン。約束する。すぐに終わるから、見てて。";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "「チャールズ！思ったよりも早く戻ってきたね。しかし、どうしたんだい？顔色が良くないよ……ヨープ・ファン・デル・フィンクについて何か分かったのかい？」";
			link.l1 = "まだです。いくつかのことは分かりましたが、これ以上進むには……娼館に行く必要があります。もちろん、あなたが考えているような理由ではありません。\n";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "売春宿？こういう場所は、あからさまなこと以外に何かあるなんて知らなかった。";
			link.l1 = "店主と話がしたいだけだ。それだけさ。\nしかも、ただの売春宿じゃないらしい。噂によれば――とても高級な店で、上流階級の人間しか入れないとか……";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "じゃあ、あなたにはぴったりね、ダーリン。\nあ、冗談よ。\nでも、あなたがそこに行くのはやっぱり心配だわ。\nでも……";
			link.l1 = "私はロングウェイの用事だけで行くと約束するよ。\nあそこの持ち主が彼の妹かもしれないんだ。\n長居はしない。";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "ご希望のままに。そういうことを私に知らせる義務はありません。 私が他の男と寝ないと約束したことは一度もありません。それでも、私はしません。なぜなら、 それが当然のことだと思っているからです。";
			link.l1 = "他の状況なら、あなたを連れて行ったでしょうが…";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;
		
		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "ありがとう、でも遠慮しておくよ。\nチャールズ、心配しないで。あたし、バカなヤキモチ焼きの女の子じゃないから。\nまあ、ヤキモチは焼くかもしれないけど、バカじゃないよ。\nそれに、あたしはあなたを信じてる。\nバカだよね、あたし！";
			link.l1 = "ありがとう、エレン。すぐ戻るよ。";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "おや、当店に新しい顔ですね？ようこそ、旦那。料理、熟成ワイン、熱い風呂――どれもお金と時間を惜しまなければ、私たちと一緒に楽しめますよ。";
			link.l1 = "歓迎していただき、ありがとうございます、お嬢さん。しかし、それが私のここに来た理由ではありません。 私はある人を探しています…";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "本当に大切なものは目には見えない、心でしか正しく見ることができないのです。";
			link.l1 = "美しいですね。その台詞は今まで聞いたことがありませんでした。";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "私たちはここで教養を身につけているの。ただの人形じゃないわ。女主人は、 それがこの店にとって不可欠だと思っているのよ。";
			link.l1 = "女将だ！俺が探してるのはその人だ。黄色い肌だって聞いたんだが、本当か？それと、名前は何て言うんだ？";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "確かにそうだ。しかし、彼女は多くの白人女よりも商才がある。名はベル・エトワールだ。だが、もう話は十分だろう。";
			link.l1 = "話はもう十分だとおっしゃいますか？私は話をしに来たのです。あと少し質問して、それから立ち去ります。";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "それで、この店にとって何の得があるっていうの？ここで払うのは身体じゃなくて時間だよ。話したいなら、 どうぞご自由に。でも先払いだ。部屋で、誰にも聞かれないように小声で話そう。そこで何をしようが私には関係ない――ろうそくを灯して祈ったってかまわない。ある客は詩を書くのを手伝ってほしいと言ったし、別の客は悩みを打ち明けて 「親友」だなんて呼んできた。三人目は――ただろうそくを灯して、それから……\n";
			link.l1 = "まあ、知りたくないよ――最近、すでに嫌な話を聞いたばかりだからな。いくら払えばいい？";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "二百五十ドゥブロンだ。値切りは一切なしだぜ。もし相手が金のない見せかけ野郎だとわかれば、容赦なく叩き出す。 逆に金持ちでケチなら、値段を吊り上げる――どうせ払わせるからな。";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "はい、どうぞ。二百五十枚の金貨です。";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "うわっ、ここはジャマイカのあの売春宿より高いじゃねえか。金を手に入れてからまた来てもいいか？";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "よろしい。どこから始めましょうか？ディナー、キャンドルはありかなしか、お風呂、それとも会話ですか？";
			link.l1 = "時間があまりないから、早速質問に入ろう。案内してくれ。";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "もちろんできますわ。忍耐は高級娼婦の美徳のひとつですもの。物乞いを追い出すのとは訳が違います。 あなたのような裕福な紳士が、お金を取りに行ったり、あるいは借りてきたりするのを待つのは、まったく別の話ですわ。 ";
			link.l1 = "高級娼婦の美徳か……皮肉なものだな。すぐ戻る。";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "お帰りなさいませ、旦那！さて、あなたはどちらですか？裕福な紳士、それとも見せかけだけの者ですか？";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "もちろん、私は裕福な紳士でございます、お嬢さん。こちらがあなたの金貨――全部で二百五十ドゥブロンです。数える必要はありませんよ。";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "まだ足りませんが、我慢してください。";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "ここでは数えない。ふむ、何枚かのコインは曲がっていたり壊れていたりするな――女主人はあまり気に入らないだろうが、少なくとも全部本物の金貨だ。";
			link.l1 = "なんと…優雅なお方だ。";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "その通りだ。エトワール女主人は優しく思いやりもあれば、厳しくもなれるし、容赦もない。だからこそ、 俺たちは数に入らないんだよ。ちなみに、女主人はいつもすぐに報酬を受け取るわけじゃないが、 必ず自分の分は手に入れる。金じゃなければ、血でな。\nどんな娼館にも守る者や後ろ盾が必要だ。そして、うちの連中はこの店の格にふさわしい連中さ。";
			link.l1 = "金は払った、案内しろ。";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "それで、どんなご質問がありますか、旦那？あなたの…好奇心を満たせるよう努めましょう。";
			link.l1 = "お嬢さん、私が興味あるのは――あなたのご主人様、エトワール夫人のことだ。";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "彼女について何を言えばいいのでしょうか？彼女は私たちにとっても謎のままです。\n私たちの幸福や健康、安全を気遣ってくれてはいますが、誰とも親しくなろうとせず、交流もしません。";
			link.l1 = "もしかすると、彼女は長い会話が好きじゃないのかもしれませんね。\n教えてください、彼女は訛りがありますか？";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "いいえ、なぜそう思うのですか？ただ彼女が黄色い肌だからですか？彼女は純粋なフランス語を話し、 他にもいくつかの言語を使えます。そして、どんな話題でも客人や将来の利害関係者と一時間でも会話を続けられます。";
			link.l1 = "ほう、そうか。面白いな……彼女は今ここにいるのか？もしそうなら、俺は中に入って彼女に会うだけだ。これ以上お前の本当に……高価な時間を無駄にしないようにしてやるよ、さっさと仕事に戻れ。";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "戻るべきものはあまり多くありません――とはいえ、女主人の目標はこの場所を諸島一の場所にすることです。\n商人も、貴族も、教養ある者も恥じることなく訪れることができる、選ばれた者のための場所――なぜなら、私たちは身体以上のものを提供しているからです。";
			link.l1 = "でも、彼女はあまりうまくやれていないんじゃないか？";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "どう言えばいいか……彼女は私たち一人一人を、ただの商品としてではなく、まるで一つの「プロジェクト」として見ているんです。高価な服、 薬、教育――彼女は私たち全員に投資してくれる。でも、もしここが旧世界の大都市だったら、きっと彼女は成功していたでしょう！ でも、ここでは……いくら腕のある商人でも、商品が高すぎて誰も買えなければ稼げません。たとえ値段を下げても、 結局いつか破産する運命なんです。";
			link.l1 = "それはお気の毒です。\nそれで、あなたのご主人様は今どこにいらっしゃるのですか？";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "ここでの暮らしは今のところ悪くないよ、断言できる。もちろん、その分だけ努力して、 彼女の基準に応え続けなきゃならないけどな……。\nさて、ご婦人のことだが、彼女はエスパニョーラへ行ったよ。 俺たち全員をポルトープランスへ移す可能性について話し合うためさ――結局のところ、あそこならもっと多くの交易路が交差しているし、商売も停滞せず、 ほぼ絶え間ない損失に苦しむこともないからな。 ";
			link.l1 = "そうですか？ルヴァスールはこの場所の安定のために投資したのではありませんか？";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "あまり多くはないよ。彼が来て、「時々自分の屋敷に来るなら大金を出す」と言ったんだ。でも、 あのご婦人はきっぱりと断った。あまりにもはっきりとね。それで閣下も一瞬驚いてたよ。 あんな彼女も彼も見たことがない。";
			link.l1 = "へっへっ、見てみろよ。あの娘、分かってるみたいだな……勇敢だ、実に勇敢だぜ。";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "知ってるか？でもな、こうやってちゃんと話してるから、もう一つ教えてやるよ。ただし、これは大きな秘密だ。 誰にも話すんじゃないぞ！";
			link.l1 = "おやおや、マドモワゼル。ご安心ください、あなたのお嬢様に危害を加えるつもりはまったくありません。 どうぞお続けください。";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "彼女に危害を加えられるかどうかさえ分からないよ、なぜならベル・エトワールは毎日剣術の稽古をしていて、 この街には彼女にふさわしい相手が一人もいないんだ。\nそれにポルトープランスだけじゃなく、彼女はあのマーカス・タイレックス本人に投資を頼むつもりなんだ！いや、 むしろ彼から借金をするつもりらしい。想像できるかい？";
			link.l1 = "はい、そして今日は定期的にフェンシングをしているもう一人の女性と、 とても厳しい話をすることになりそうな気がします……。\nさて、話してくれてありがとう、お嬢さん。良い一日と、気前のいいお客さんに恵まれますように。";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "ありがとうございます。でも、そんなに急いでどうしたの？お代はちゃんといただいたし、 まだそんなに長く話してもいないわ。それに、あなたにはどこか上品なところがある、旦那様。ただの金持ちとは違う、 もっと特別な何かを感じるの。ねえ、本当に二人きりの時間を楽しんでみない？";
			link.l1 = "なあ…なんだよこれ？なんで俺、自分に嘘ついてまで欲しくないふりしてるんだ？あんたみたいな女とチャンスなんて、 滅多にないんだぜ。";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "ああ、申し訳ありません、お嬢さん。私はここに話をしに来ただけです。それに……私を待っている者がいます。";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "そんなことで誰かが止まると思うか。\nそれなら、あなたは敬意に値します、旦那。\nあなたの「誰か」のために、私はとても嬉しいです。";
			link.l1 = "改めてありがとうございます、お嬢さん。さようなら。";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "ありがとうございます。まずは一緒に熱い風呂でもどうですか？";
			link.l1 = "両手を挙げて賛成です。";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "それはまるで魔法のような体験でしたわ、旦那。男の人にあんなふうに驚かされるなんて思いませんでした。あなた、 本当に女性を喜ばせる方法をご存知なのね……";
			link.l1 = "女による。";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "後悔していますか？";
			link.l1 = "今は絶対に無理です。さようなら、お嬢さん。";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "足元に気をつけろ、この見せかけ野郎！";
			link.l1 = "口の利き方に気をつけろ！";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "お前がカラスの数を数えている間、私はちゃんと前を見ていたぞ。";
			link.l1 = "探していたなら、回り道できたはずだろう、そうじゃないか？";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "なぜお前の回りを回らなきゃならないんだ！？";
			link.l1 = "街の外で、誰が誰に何を借りているのか、調べてみることを提案します。";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "んん、違いますよ。お貴族様がただの男のうっかりした接触にそこまで嫌悪感を抱くとは、知りませんでした。";
			link.l1 = "もう一度言ってくれませんか？";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "うむ、すまない。押しつけるつもりはなかった。";
			link.l1 = "それでいい。";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "もしあと三十分遅れてたら、Charles、あたしたちの砲弾でこの汚い巣穴を木っ端微塵にしてたんだから、でしょ！\n探してたものは見つけた？あれがLongwayの妹なの？見たの、でしょ？";
			link.l1 = "しっ、Mary、そんなふうに話すな。いや、Chang Xingには会えなかったんだ…";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "じゃあ、一体何をぐずぐずしてたんだ！？そこで何をしてたんだ？";
			link.l1 = "ご心配には及びません。できる限りのことを調べたら、すぐにあの場所を離れました、約束どおりに。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "はっきり言えよ、でしょ！";
			link.l1 = "今、トルトゥーガにはその店主はいません。ここでは彼女の店の需要が低いのです。なぜなら、 彼女は高価な服を着た教養ある女性たちを雇っていて、支払いも金貨しか受け付けないからです……";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "「お前も奴らに金を払ったのか！？」";
			link.l1 = "そうでもしなければ、奴らは俺と話そうともしなかっただろう。あんな態度じゃ、客が寄りつかないのも当然だ。\nマダムはもっと金持ちの客を狙って、商売をポルトープランスに移すことにしたらしい。\nだが、資金が足りないのは明らかだ――マーカス・タイレックスに借金を頼もうとしているくらいだからな……";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "彼は彼女のことを知っているのか？";
			link.l1 = "ラ・ベガに着けば分かるだろう。\nそれに、無駄なおしゃべりで時間を浪費せず急げば、そのアジア女が誰であろうと捕まえられるはずだ。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "あの売春宿に行く必要なんてなかったでしょ、チャールズ。頑張れば酒場や街中でも全部わかったはずだよ、でしょ。";
			link.l1 = "次はお前も連れて行ってやるよ、そうすりゃその可愛い赤毛の頭にくだらないこと詰め込まずに済むだろ？\nさあ、本題に入ろうぜ。";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "ああ、ちょっと遅れちゃったみたい、でしょ！まあ、待ってなよ、このろくでなし…";
			link.l1 = "メアリー、いったい何してるんだ！？船にいろって言っただろう！";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "じゃあ、あんたが娼婦たちと楽しむのを止めたりしないってこと？！否定するつもりなんてないでしょ、チャールズ！ 船員たちがあんたをそこで見たんだから、でしょ！どうしてそんなことできるの？！";
			link.l1 = "そう思っていたんだ。連れて行けばよかったのかもしれないな、私が何をしていたか――いや、むしろ何もしていなかったか――を見せて、大げさに騒がれずに済んだかもしれない…";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "俺たちの仲間が嘘をついてるって言うのか？自分がやったことを棚に上げて、この野郎。";
			link.l1 = "私は彼らを比類なき愚かさで非難しているだけです。状況も理解せずに、あなたは……";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "おっと、チャールズ、お前とお前の娼婦どもは、もし俺があの穴に間に合ってたら、 俺がどう状況を理解したか気に入らなかっただろうな。だが運が良かったな――このクソみたいなボートを一人で漕がなきゃならなかったんだよ…";
			link.l1 = "重労働は余計な考えを頭から追い出すと言うが、My Lord Captainにはまだ考えが山ほど残っているようだ。だから、あんたもまた漕いで戻るんだな。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "俺は動かない、でしょ！";
			link.l1 = "メアリー、ここでルヴァスールの手下たちの前でこの話はしない。落ち着いて、周りをよく見て、自分で判断してくれ。 今は時も場所も違うんだ。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "くたばっちまえ。まだ船室に私の荷物が残ってるんだ……でも、もう一度オールを漕ぐつもりはないからね、でしょ！お前の中にもまだ貴族の誇りが少しは残ってるはずだろう！";
			link.l1 = "俺は悪党で乱暴者だって、覚えてるか？船に着いたら、それを証明してやるよ。だが、まずはそこに行かねえとな。 だから、お前の懇願なんて無駄だぜ。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "お前のこと、乗組員全員が笑ってるよ、でしょ！";
			link.l1 = "まあ、あんたにもだろうな。あんな見世物は久しぶりだったんだろう。\nさて、少し落ち着いたみたいだから、何があったか話してやるよ。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "チャールズ、もう全部聞きました。\nただ一つだけ聞かせてください。私はあなたにとって十分じゃなかったのですか？私に何か足りないものがあるのですか？ ";
			link.l1 = "失礼ですが、質問で返させていただきます、My Lord Captain。私があなたの信頼を裏切るような理由を、これまで一度でも示したことがありましたか？え？私は覚えていません。 ですから、深呼吸して私の話を聞いてください。ヨープ・ファン・デル・フィンクについては、 娼館に行ったということ以外、ほとんど何も分かりませんでした。「歌うカラス」の近くの店ではなく、 波止場のそばの別の店です。私はその店のことを今まで知りませんでした……どうやら、うちの水夫たちは知っていたようで、あなたにも教えたようですが。もっとも、 あいつらがそこに行くのは本来許されていなかったはずですが……";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "水夫を入れない娼館なんて、どういうこと、でしょ？";
			link.l1 = "絹をまとった才色兼備の女たちが働く娼館だ。そこのサービスは金のドゥブロンでしか支払えない。 これは誰かの気まぐれじゃなく、謎めいた女主人ベル・エトワールの命令なんだ。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "不思議だね、でしょ？";
			link.l1 = "それだけじゃない。彼女はアジア人だ。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "アジア人？トルトゥーガの売春宿の女主人のことか？";
			link.l1 = "張興かもしれません。だからこそ、私はそこへ行ったのです――自分の目で彼女を確かめたかった。それだけです。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "彼女はどんな人ですか？";
			link.l1 = "わかりませんでした。彼女はいなかったので、代わりに別の……星と話すしかありませんでした。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "彼女もアジア人だったんでしょ？";
			link.l1 = "いいえ、彼女は白人だったよ。最近ベル・エトワールの調子が良くないから、 ポルトープランスへ移ることにしたって言ってた。あそこなら住民も裕福だし、理にかなってるな。 マダムはエスパニョーラで商売を始めるために資金が必要で、タイレックスから借金するつもりらしい。 だから急いでラ・ベガへ行けば、マーカスが会う前に彼女を捕まえられるぞ。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "あの女のことも、マーカスのことも、他の誰のこともどうでもいいんだ、でしょ？\nチャールズ、一つだけ教えてよ――あの女の娼館の女の子たちと寝たことある？";
			link.l1 = "そんなものはいらないよ、Mary。俺にはお前がいる、世界一の女の子がな。どうして自分がそうだって気づかないんだ？";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "実はね、本当のことを見抜くのはすごく簡単なんだ、でしょ？えへへ。誰とも一緒にいたことがないなら、 今めちゃくちゃ元気なはずでしょ？それを今から確かめるんだよ、でしょ！";
			link.l1 = "メアリー、お願いだ……";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					Notification_Perk(true, "Medic");
					dialog.text = "（絶好調）うっ……チャールズ、嘘じゃなかったみたいだね、でしょ……";
					link.l1 = "私にはあなたを欺く必要はありません、親愛なる方よ…";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					Notification_Perk(false, "Medic");
					dialog.text = "チャールズ、本気なのか……！？今のは一体何だったんだ？";
					link.l1 = "ああ、この暑さは私には堪えますね。ゴホン。";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "うっ…チャールズ、嘘じゃなかったみたいだね、でしょ…";
				link.l1 = "私にはあなたを欺く必要などありませんよ、親愛なる方……";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "でも、あの小舟での移動はしばらく忘れられそうにないよ！";
			link.l1 = "「はっ！」";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "今までそれについて文句を言ったことはなかったよな？";
			link.l1 = "この血塗られた島を走り回ってみろよ……";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "そして売春宿も、でしょ！本当にあなた……";
			link.l1 = "メアリー、ごめん。";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "「何だって！？じゃあ、お前は…」";
			link.l1 = "それについては後悔してない。くそっ。いや、あんた以外とは誰ともいなかったって言ったでしょ。私はただ……気持ちが落ち着かなかっただけ、それだけ。ラ・ロシュの大砲がこっちを睨んでる中じゃ、 心を落ち着けるなんて難しいんだよ、わかるでしょ？";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "いい言い訳じゃない、チャールズ。\nまあ、信じてあげるよ。今回だけは……\nでもね、私はまだ怒ってるんだから、でしょ！";
			link.l1 = "必ずあなたの許しを得てみせます、約束します。";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "さて、色男さん、何が分かったのか教えてくれる？私のご機嫌を損ねてまで、調べる価値はあったのかしら？";
			link.l1 = "冗談なのか本気なのか、本当にわかりません。\nでも、結果的にはうまくいきました――私はその女主人を自分の目で見たわけではありませんが。\n彼女はアジア人で、名前はベル・エトワール――素晴らしい星という意味です。\nもちろん、それが本名ではありませんが……";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "それで、わざわざ売春宿に行く必要があったのか？宿屋じゃその情報は手に入らなかったのか？";
			link.l1 = "町ではこの場所についてあまり語られていないんだ。\nなぜかって？いい質問だ。\n自分でベル・エトワール本人に聞いてみればいい――彼女はエスパニョーラへ行ったよ。";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "トルトゥーガだけじゃ足りなかったのか？";
			link.l1 = "どうやら、ここでの商売はうまくいっていないようです。\n彼女が雇っているのは普通の港の女たちではなく、豪華な服を着た教養ある女性たちです。";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "「それで、なぜ奴らがそんなことを？」";
			link.l1 = "それもまた良い質問ですね。ともかく、我々の小鳥はポルトープランス、ド・ミュサックの領地へ飛ぶことを決めました。 \nしかし、この企てのための借金は、他ならぬタイレックスから得ることになっていました。";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "この話が早く終わってほしい。無駄な時間は使わず、すぐにラ・ベガへ進路を取ろう。";
			link.l1 = "そうしよう。";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "チャールズ、あなたは勇敢な男ですね、それは認めますよ。何事もなかったかのように、平然と現れるとは。";
			link.l1 = "乗組員の誰かが余計なことをしゃべったんでしょうか？もちろん、何の説明もなく。実際には何も起きていません――少なくとも、あなたが考えているようなことは。";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "否定しなかったこと、嬉しく思います、チャールズ。";
			link.l1 = "すべて話すつもりだったんだ、エレン。";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "やめて、チャールズ。細かいことにはあまり興味がないんだ。\nでも、理由には興味がある。教えてくれ、俺に何か問題があるのか？";
			link.l1 = "理由から始めましょう。トルトゥーガには娼館が二つあると分かりました。一つは有名です。もう一つは……人々は存在を知っていますが、話したがる者はほとんどいません。アジア人の女が経営しているのです…";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "即興で話しているのですか？";
			link.l1 = "なんで俺がそんなことしなきゃいけねえんだよ、エレン！？信じられねえなら、現地で確認すりゃいいだろ！";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "まず、上陸するなとおっしゃったので、そこに行けるわけがありません。\n次に、俺を誰だと思ってるんですか！？あんな場所には絶対近づきません！\n三つ目は……もういいです、続けてください。";
			link.l1 = "よろしい。俺は自分の目でマダム・エトワールを確かめに行くと決めたんだ。それだけが俺の唯一の目的だったんだ、 くそっ！";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "そうかもしれません。彼女に会いましたか？";
			link.l1 = "いいえ。彼女はエスパニョーラへ行ったんだ。ここではうまくいっていないから、 ポルトープランスで運を試すことにしたのさ。あそこなら、彼女の店で働く絹の服を着た教養ある女性たちが、 トルトゥーガよりも多くの利益をもたらしてくれるだろうからな…";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "着飾って、教養まで身につけたのか？おお、人生は何をもたらすかわからないもんだな。だが、 そのままの彼らを好きでいてやるべきだ。";
			link.l1 = "ヘレン、やめてくれ。俺は君の不信を買うようなことは何もしていない。";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "確かに。もし私を騙そうとしたなら、そんなに落ち着いていられなかったはずだ。しかし、 計画については事前に知らせておくべきだった、チャールズ。";
			link.l1 = "おっしゃる通りだよ、ダーリン。\nでも、ちょっと時間を節約しようと思ったんだ。\nそれが間違いだったね。";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "わかりました。さて、これからどうしますか、ポルトープランスへの航路を計画しますか？";
			link.l1 = "ラ・ベガだ。驚かないでくれ、エレン。マダム・ベル・エトワールの具合が悪いんだ。 商売をポルトープランスに移すために借金が必要で、マーカスから借りることにしたらしい。急げば、 そこで彼女に追いつける。だから、一分も無駄にしないようにしよう。";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ_1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ_1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Mary();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Helena();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "貴様みたいなクズとその下衆どもに俺たちが負けたなんて信じられねえ！";
			link.l1 = "あなた……";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "「おや、私のことを知っているのですか？」";
			link.l1 = "お会いしましたか？";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "「はぁ？！ふざけてんのか、てめえ！？」";
			link.l1 = "俺は会った野蛮なクズどものことなんて全部覚えちゃいねえ。\n誰が俺たちを殺しにお前を送り込んだのか、さっさと言ったほうがいいぜ。\nそれとも、ただお前を厄介払いしたかっただけか？";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "お前みたいな奴には何も言わねえよ。自分をどれだけ偉いと思ってるんだ！\nここで少し休んだ後で、もう一度その自信を見せてみろよ。";
			link.l1 = "残念だな。お前は本当に気持ち悪いが、他の島に置き去りにすることもできたんだ。だが今となっては、 あの世に送るしかない。";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "「お呼びですか、My Lord Captain？」";
			link.l1 = "ああ、相棒。被害状況を報告しろ。";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "激しい嵐だ。船がきしみ、軋んでいる。ひどく揺れているぞ。";
			link.l1 = "ああ、気づいているよ。ティチンギトゥ、友よ。俺とその " + sStr + " 上陸する。お前は指揮を執れ。すぐに修理を始めろ――嵐が収まるまでは造船所に行っても無駄だ。それに、ここに長居はしない。";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "すべてをもっと良く見せてみせます。";
			link.l1 = "素晴らしい、ありがとう。これで安心して町へ向かえるな。";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "ムッシュ船長？光栄でございます。しかし、こういう時は普段アロンソを呼ばれるのでは？もし差し支えなければ、 何か問題でも？";
			link.l1 = "ええ、大丈夫よ。でも、うちのアロンソは何かを直すより壊す方が得意なの。あらゆる意味でね。\n船の損傷はどれくらいひどいの？";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "「アルフォンソなら、沈まなくてもひどいって言うだろうな。修理のことを言ってたよね――始めようか？」";
			link.l1 = "ああ、できることをやってくれ。しかし、本格的に長期の作業を計画しないでくれよ――俺が町での用事を済ませたら、すぐに錨を上げて出航するつもりだからな。俺と\n " + sStr + " 私はいないから、何かあった場合はすべて自分で決めてくれ。\n何事もアロンソの言うことを聞くんだ。";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "ご命令のままに、ムッシュ・ル・キャピテン。";
			link.l1 = "楽にしてくれ。";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "ごきげんよう、旦那！ポルトープランスへようこそ。";
			link.l1 = "「ごきげんよう、旦那。あなたは誰で、どうしてこんな歓迎を受けているのですか？この雨と嵐の後では、 長話をする気分ではありませんが。」";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "ああ、あなたの時間をあまり取らせません、ド・モール様。";
			link.l1 = "お前を知っているか？";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "ああ、そんな、でも諸島中があなたのことを知っていますよ。あっ、これは失礼しました！アンリ・ティボー、 あなたのお役に立ちます。私は閣下、ムサック旦那の使者です。あなたの船を見つけるやいなや、 できる限りの歓待をするようにと命じられました、旦那。";
			link.l1 = "なるほど、それで色々納得だな。お会いできて光栄です、Thibaut旦那。";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "「光栄でございます、ド・モール旦那！どうぞこちらへお進みください。このような臭い酒場に、 あなたほどのご身分の方とその美しいご令嬢が閉じ込められているのは相応しくありません。 閣下は市内にお屋敷をご用意され、私にはあらゆる面でお手伝いするようご命令なさいました。後ほど、 ポワンシー閣下に閣下のご厚意をお伝えいただくこともお忘れなく。」";
			link.l1 = "実は、私の用事は慎ましやかなものです。ご存知でしょう、ティボー旦那、私が思うに……";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "チャールズ。私はめったにあなたに何かを頼んだり、ましてや邪魔したりしませんが、彼らの申し出を利用できませんか？ 雨に濡れるのはもううんざりです。吐き気もするし、めまいもしています。";
			link.l1 = "へっへっ、本当に雨のせいか？";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "舌を噛め、チャールズ！\nとにかく、休みたいんだ。大きなベッドで、波もないところでな。";
			link.l1 = "よし。体を乾かして、少し休んだら、すぐに仕事に戻ろう。";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "この家で休憩してもいい？体調が悪いし、それに……疲れてるの、チャールズ。でしょ？";
			link.l1 = "メアリー、可愛い人、わかるけど、でも酒場に行ったほうがいいかもしれない。この一件、なんだかきな臭いよね、 でしょ？";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "俺に何が起こるっていうんだ？ここはトルトゥーガですらないんだぞ。";
			link.l1 = "それが私を怯えさせるのです。";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "お願い、でしょ？何かあったら、部屋の中で防御を固めるから――あの時みたいに、でしょ。チャールズ、誰よりもあたしのこと知ってるでしょ？だから大丈夫だってわかるでしょ？";
			link.l1 = "わかった、わかった。今回はあの時みたいにならなきゃいいけど。";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "やっぱり考えを変えると思っていました、旦那！ご心配については、よく分かります。しかしですね、 ポワンシー閣下と総督は古くからの友人でして、ですからあなたは我が町の歓迎すべきお客様なのです、ド・モール旦那！ ";
			link.l1 = "ああ、そうか……では、私たちをその家に連れて行ってくれ。";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "かしこまりました、旦那！どうぞ、こちらへお進みください。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "旦那、総督がお待ちです。できるだけ早くお越しくださるよう頼まれました――内々にお話ししたいとのことです。";
			link.l1 = "彼はもうそれを知っているのか？";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "もちろん、彼は知っているさ！だからこそ、あんたを待っているんだ。愛しい人を甘く眠らせておいて、 ムサック旦那に会いに行ってきな。嵐ごときで有名なシャルル・ド・モールが止まるわけないだろ？でも、 旦那様はお察しの通り、予定の合間に割ける時間はあまりないんだよ…";
			link.l1 = "まあ、それは本当ですね、Thibaut様。";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "道案内はお任せください、船長。";
			link.l1 = "おや、名誉ある護衛までついてくれるのか……それじゃ、案内してくれ。";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "旦那船長！";
			link.l1 = "ロンウェイ！船へ！今すぐだ！";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "しかし、俺はChang Xingを見たんだ！";
			link.l1 = "何だって！？どこで？いつだ？彼女はあなたの船にいるのか？";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "いや！この街で、ロンウェイは彼女を遠くから見かけたんだ。追いつく時間はない――彼女はちょうど出航したガレオン船に乗り込んでいる！";
			link.l1 = "ガレオン船には追いつくぞ！だが教えてくれ――見たことがあるか " + sStr + " どこか？";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "いや！何かあったのか？";
			link.l1 = "ああ、何かが起こったんだ！彼女が危険にさらされている！レヴァスールの甥を見かけたか？名前はアンリ・ティボー！ 気味の悪い、痩せてて、長髪で、変な口ひげの若造だ！";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "（中国語で）おかしな口ひげの話はいらない、キャプテン……\n（下手なフランス語で）見た、俺！奴と傭兵たちも同じガレオン船に乗り込んだ。";
			link.l1 = "すぐに追いかけましょう！";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "船がひどく傷んでいる、My Lord Captain！";
			link.l1 = "俺はどうでもいい！ " + sStr + "「の命が危ない！」";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "私の……「あなたのメイフェン」が私たちを導いてくれる！";
				link.l1 = "ああ、きっと来るよ！急いで！";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "俺たちを自殺的な突撃に巻き込まないでくれ。前に渡してくれたあの船を使ってくれ！";
				link.l1 = "いい考えだ、ロンウェイ！急ごう！";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			AddDialogExitQuestFunction("PZ_Longway_78");
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "またお前か……やっぱり断って、誰か他の奴にお前の女を任せるべきだったな。";
			link.l1 = "彼女はどこだ？！言え！……いや、黙れ。話すのは船倉の中、鎖につながれてからだ！わかったか？！";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "彼女の刃だ。今すぐ歌い始めないと、その刃でお前をバラバラにしてやるぞ。";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "お前……正気じゃねえのかよ……！";
			link.l1 = "これから俺の不愉快な一面を見せることになるぞ……";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "それだけか？";
			link.l1 = "もう一度聞く！どこだ " + sStr + "？！中国人の女はどこだ？！アンリ・ティボーはどこにいる？！";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "（血を吐く）女みたいな殴り方だな。";
			link.l1 = "このアマめ！てめえの口から全部吐かせてやるぞ！";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "哀れだな。だが……言ってやろうか。どうせならな、はは。奴らはみんな別の船にいる、ちょうどトルトゥーガへ向かう途中だ。 お前はもう遅かったな。";
			link.l1 = "彼女の頭から一本でも髪が抜けたら……";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 1.00, 5.13, 7.23);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "それは誰のせいだっていうんだ！？エドガルド・ソッタを殺したのはお前だろう！ ルヴァスールが生まれて初めて女を欲しがったのに、すぐに手に入らなかったんだ！ 俺たちの仲間があいつの直命に背いたのも初めてだった！あの男は悪魔みたいに恐ろしいんだぞ…";
			link.l1 = "なら、俺は悪魔よりも恐ろしい存在になってやる。俺の知りたいことを言わなければ、お前に地獄を見せてやるぞ、 聞こえてるのか！？";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			else link.l1.go = "PZ_RobertMartin_Helena_1";
			//if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "お前の悲しみなんざ知ったことじゃねえ――どうせ俺はもう死んだも同然だ、お前のその狂った目を見りゃ分かる。だが、ひとつだけ認めてやるぜ、ド・モール。";
			link.l1 = "何を言っているんだ、いったい？";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "ルヴァスールは金髪が好みだ。でも俺はずっと赤毛の方が好きさ、あんたみたいにな、へへへ……ずいぶんと刺激的なのを連れてるじゃねえか！";
			link.l1 = "おっしゃる通りだ、この日を生き延びることはできないだろう……";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "俺はお前の望みなんざどうでもいいんだ。だがな、レヴァスールが何を欲しがってるか教えてやろう――可愛い金髪の娘さ、ははははははははは！まずは、あいつが彼女を手に入れたんだ…";
			link.l1 = "「あ、ああっ！」";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "武器も持たぬ男を泣き叫ばせて殴るだけ――哀れだな。それしかできぬのか。お前は負けたんだ、ド・モール！本当に負けた瞬間がいつか知りたいか、 この哀れなクズが？";
			link.l1 = "教えてみろ。だが、俺が感心しなけりゃ、指を一本失うことになるぜ。あるいは耳か、その腐った歯か、 その臭え口から引き抜いてやるかもな。もしくは他の何かかもしれねえ。選ぶのはお前だ……";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "へっへっ、俺にはお前にないものがあるぜ。ルヴァスールがあの老いぼれ狐ポワンシーの企みを知らなかったと思うのか？ フランソワはすべてを知っている、すべてだ！兄弟団の大物たちでさえ、彼には逆らえねえ。そしてお前は、利口ぶって、 それをやった。でもな…";
			link.l1 = "「だが、何だって？！ふざけるなよ、これ以上引き延ばすんじゃねえ！！さっさと話せ、 さもねえと指を一本ずつ折ってやるぞ！」";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "ハハッ、勇敢なるド・モール船長！だがまあ、いいだろう。俺とアンリ、それにあの黄色い肌の女は、 ここでお前を始末するのが最善だと決めたんだ。そんで全部タイレックスのせいにして、 バカなブラザーフッドの連中同士でまた戦争を始めさせてやる！あるいはド・ミュサックのせいにしてもいいな――あいつ、余計なことに首を突っ込んでやがるしな……みんな俺がガレオン船で航海するのを笑ってたが、嵐を軽々と乗り越えたぜ。お前のガラクタとは大違いだな。";
			link.l1 = "もう十分だ！ルヴァスールは犠牲者たちをどこに閉じ込めている？";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "あいつの秘密の場所、地下牢のことを知っているのか？ああ、そうさ、奴こそ本物のダンジョンマスターだ、ははは！ だが、本当に奴に挑めるのか？俺は疑わしいと思うぜ。獣を倒したいのか？なら、自分が獣になれ。 フランソワがあの娘たちを壊すように、俺を壊せるか試してみろ。奴がすぐにお前の女も壊すようにな……";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "アローンソーーー！！！";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "だからやめろって言っただろ、くそっ…";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "お任せください、ロードキャプテン。";
			link.l1 = "ロンウェイ？何を許すって？";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "白人は肉体を苦しめる。俺の民はまず哀れな魂を痛めつけることを知っている、少しずつ絶え間ない痛みで狂わせるんだ。 準備もなしにただ苦しめるなんてできねえ。いつだって特別なやり方が必要だ。ここで必要なのは……リンチーだ。";
			link.l1 = "リンチー？";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "はい、My Lord Captain。千の切り傷による死です。";
			link.l1 = "気は確かか！？頭でも打ったのか？どんな死のことをわめいてるんだ！？まずはあいつに口を割らせなきゃならねえんだ！ ";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "ロンウェイは分かっております、ロードキャプテン。どうすればいいかも心得ております。 このクソ野郎には全部吐かせます。少し時間をください…";
			link.l1 = "時間？時間だと！？……いいだろう、やれ。頼む、お願いだ、あいつから全部、すべてを吐かせてくれ！";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_LongwayKazn_3_1", -1);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "殺してくれ、お願いだ、もう殺してくれ……これ以上俺に何を望むんだ！？";
			link.l1 = "これ以上はない。黙って死ね。";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "見事な一撃でございます、ロードキャプテン。うまくいくと申しましたでしょう。";
			link.l1 = "ああ。よくやったな。じゃあ、地下牢へ行くぞ。全帆を上げろ！トルトゥーガへ針路を取れ。もしこの忌々 しい街で一本でも髪の毛が抜けたら、神よ、助けてやれよ\n " + sStr + " 頭……";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			AddQuestRecord("PZ", "39");
			pchar.questTemp.PZ_FlagMartinInfo = true;
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "ディオス・ミオ……あんな"+pchar.name+"船長を見たことも聞いたこともありません、旦那船長。";
			link.l1 = "アルフォンソ、そいつはお前のものだ！さあ、やってみろ、 聖なる異端審問がユグノー派とその手下に何をするのか見せてくれ…俺は見ている…その後は、好きにしていいぞ。";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "アイアイ、旦那船長…";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "すぐに終わります、旦那船長…";
			link.l1 = "頼む、お願いだからやってくれ！";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			//LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "起きろ、このクズ野郎。起きろって言ってるだろうが！";
			link.l1 = "死んだのか？死んだ！？";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "そうみたいだな、船長…";
			link.l1 = "一体何をしやがったんだ！？";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "こんな間抜けが、こんなにも腑抜けだったとはな！あいつ、ズボンまで汚しやがったぜ、この汚らわしいクズめ！くそっ、 火なんて必要なかったじゃねえか……";
			link.l1 = "お前……まあ、こいつは魚の餌にして海に放り込め。進路はトルトゥーガだ。必要なら、あの島を一つ一つ石ごとに壊してやる――まずはラ・ロシュ、それから……それから、もし彼女が生きていなかったら、神よ、俺をお救いください……";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			AddQuestRecord("PZ", "38");
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_Norman1":
			dialog.text = "ついに。この玉座は今や俺のものだ。この岩の上に俺は築き上げる……";
			link.l1 = "なんだよこれ……本気か？";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "…私の教会だ。今や私はローマ教皇である。神の家で誓うな！";
			link.l1 = "そして私は思っていたのですが…さて、聖下、忠実なる信徒たちにどこにあるのかお教えいただけませんか "+ sTemp +" 今か？";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "彼は聖なる使命に出かけたのです。新たな十字軍と言ってもいいでしょう。悪人どもから金を奪い、 私のもとへ持ってくるつもりですよ。";
			link.l1 = "あなたに、そうだな。彼はいつ戻ると言っていたか？";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "一ヶ月後だ。もう少しかかるかもしれない。私は他のみんなと一緒に、彼の帰りを待っている。";
			link.l1 = "なるほど、本当に海に出ているんだな。君が持っているものにうつされる前に、俺は退散した方がよさそうだ。";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "聖なる炎ですべてを清めてやる……";
			link.l1 = "お前の頭は少し清めた方がいいな……";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "with Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "「チャールズ！何かご用ですか？」";
					link.l1 = "こんにちは、エレン！話がしたいんだ "+ sTemp +"「……彼は二階にいるのか？それとも酒場にいるのか？」";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "「チャールズ！そして…ああ、これは素敵な驚きですね。お二人に何をして差し上げましょうか？」\n";
					link.l1 = "こんにちは、エレン。どこに "+ sTemp +"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting() + "「チャールズ。何の用でここに？」";
				link.l1 = TimeGreeting() + "、ヘレン。俺は探しているんだ "+ sTemp +"……彼がどこにいるか知っていますか？";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "彼は出かけていますが、残念ながら長い間戻らないでしょう――正確に言えば、海に出ているのです。";
			link.l1 = "くそっ。何かあったのか？いつ戻ると言っていた？";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "彼は戻っていませんが、大したことじゃありません――いつものように有力な手がかりを掴んでいます。たいてい一ヶ月、長くても二ヶ月で戻ってきます。わかりますよ、 時には私自身も船の甲板が恋しくなるものです……";
			link.l1 = "いつでも海に出られるよ。たまには一緒に行けたら素敵だね――君は『レインボー』で、私は……";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "そうかもしれません。しかし、あなたの…恋人はそれを喜ばないかもしれません。そして、私が邪魔者になるのは望みません。";
			link.l1 = "ええと、すまない、ヘレン、君を怒らせるつもりはなかったんだ。話してくれてありがとう。また後で会おう。";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "チャールズ、お戻りですね。ほかにお手伝いできることはありますか？";
			link.l1 = "いいえ、ありがとう、Helen。ただ、ちょっと確認したかっただけです。 "+ sTemp +" 現れた。";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "私を探しに来たら驚きますね。さて、 "+ sTemp +"「彼は海に出ています。」";
			link.l1 = "ああ、本当か？いつ戻るか聞いたのか？";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "どうやら、あの男はこの汚い巣窟を仕切るのにうんざりして、 自分がまだ船の船長だと自分に言い聞かせる必要があるらしい。\nこれが初めてじゃない。たいてい一ヶ月、長くても一ヶ月半で戻ってくる。";
			link.l1 = "くそ、バロンどもはいつもあんなに大人しくしてるわけじゃないんだな？ありがとう、エレン。じゃあな。";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+ sTemp +"「まだ戻っていません、Charles」";
			link.l1 = "なるほど、ただ確認しただけです。";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "彼は自由な人間だろう？好きな時に海へ出られるはずだ。";
			link.l1 = "もちろん、彼ならできますよ。で、彼はどこにいるんですか？";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "「でもチャールズ、もし彼が島にいないなら、今ごろスペイン人を略奪しに行ったんだろうな。それじゃ、失礼するよ。 やることが山ほどあるんだ。時々様子を見に来てくれ——たいてい、」 "+ sTemp +" だいたい一か月後に戻ってくるが、時にはもう少しかかることもある。";
			link.l1 = "ありがとう、エレン。大丈夫だ。俺たちは手を動かしておくよ。";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "今はそんな気分じゃないんだ。別の時にまた来てくれないか、チャールズ？";
			link.l1 = "もちろんだ、Helen。邪魔して悪かったな。気をつけて。";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "配置につきました、My Lord Captain。道順は覚えていますか？";
				link.l1 = "もちろんだ、ロンウェイ。あの呪われた地下牢で失くさないことを祈ろう…";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "配置につきました、我が主君船長。ご計画はございますか？";
				link.l1 = "まだ取り組んでいるところだ……どうした、何か考えがあるのか？";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "そうだな、もし俺たちが張興のところへ急げば…";
			link.l1 = "ロンウェイ……君がどれほど妹に会いたいか、私には分かる、でも\n " + sStr + " 今まさに命の危険にさらされています、比喩じゃありません！彼女を救うことが最優先だと理解してください！";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "旦那船長、あなたが本当に理解しているとは思えません、この十年間、私がどんな思いをしてきたか。\n今、私が何を味わっているのかも。";
			link.l1 = "そうだね、ある意味ではそうなんだ。私の兄は牢屋に捕らわれている。まだ危害は加えられていないけど、 いつでも好きなようにされるかもしれないんだ。";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "しかし、もしそれがただの女性だったら、どこへ行くつもりだったのですか " + sStr + " 誰が救出を必要としていた？";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "一つだけ場所がある……一人だけ人がいる……だが、そのことは気にしなくていい、ロンウェイ——これは自分で片付けなければならないんだ。";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "実のところ、どこへ行けばいいのかすら分かりません。\n下手にあちこち嗅ぎ回れば目立ってしまいますし、それから―― " + sStr + " もう確実に終わっている。だから……私には、もう分からない。";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "何？なぜだ？";
			link.l1 = "あそこには簡単に入れないぞ――上流社会だからな、くそっ。だから、俺が一人で行く。お前はその間に妹のところへ向かえ。できるだけ早く合流する。 健闘を祈る、ロンウェイ！";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "ああ！ありがとうございます、My Lord Captain。そして、あなたにも幸運を！";
			link.l1 = "ああ、ありがとう――今日は本当にそれが必要なんだ。私たちみんな、そうなんだよ。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "ロードキャプテン…";
			link.l1 = "気にするな。ロンウェイ、君の妹のところへ行こう。今ここで別れたら、俺たちは終わりだ。 急いで君の妹のもとへ行って、ルヴァスールの隠れ家がどこか突き止めよう。それからまた一緒に行動する――今はできる限りの助けが必要なんだ。間に合うといいが。\n";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "遅れません、My Lord Captain。これ以上遅らせたり、議論に時間を無駄にするのはやめましょう。張興のもとへ行きましょう！";
			link.l1 = "おっしゃる通りです、急ぎましょう。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "どこへ行くつもりだ？その扉がどこに通じているか、わかっているのか？";
			link.l1 = "よく分かっている。私は用事でそこへ行くんだ、暇つぶしでも盗みに行くんでもない。";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "何の用だ？ルヴァスール夫人は今お会いできない。\nそれに、彼女は既婚の女性だ――他人が彼女の家の周りをうろつくのは良くないぞ。";
			link.l1 = "結婚してる、でしょ？でも、たまにはレセプションも開くんだよね？しかも、プライベートなやつもあるんだって。 今回はその一つ。彼女は私を待ってるし、急いでるんだ、でしょ？";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "もしそうだったら、彼女は私に警告してくれたはずだ。";
			link.l1 = "俺は特別な客だ――わざわざ知らせる必要のない種類のな。";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "ああ、旦那様が俺を撃ち殺せと命じるような客だぜ。あるいは奥方様自らが俺の皮を剥ぐかもな。";
			link.l1 = "私は以前、マルセリーヌ夫人の客人だったことがある。安心しろ、兵士よ、その後お前に何も起こらないと保証する。";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "もちろんですとも、目をつぶって誰でも通す――それが市警の仕事でございます。";
			link.l1 = "こんなことに付き合ってる暇はないんだ、頑固なロバめ…";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "あなた……";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "ああ、奥様。あなたの騎士がまたお目にかかれて光栄です。\n私を見て驚いていらっしゃるようですね。\nこの再会の喜びは……私だけのものでしょうか？";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "はい、そうです。前回お会いした時におっしゃった通り、 私はこの島で一番の美男でも立派な男でもないと自覚していますが、 少なくとも私は正直者だということはご存知でしょう。どうかお聞きください、奥様――あなたの…貴重なお時間はあまり取りません。";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "お願いだから静かにしてくれ、奥様。そんなに叫ぶのはやめてくれ。\n 私は、あなたが騎士を騙して竜の財宝を持ち逃げしたことの仕返しに来たわけじゃない。\n それに、もしあなたを殺したいなら、ただ撃って逃げるだけだよ。ここはトルトゥーガだ、そうだろう？\n でも、そんな下劣な真似は私の品位に合わないって、あなたも分かっているはずだ。";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "ああ、いやだ！ちょっと考えただけで…まあ、もういいの！\nほら、悪意ある連中が私のことをあれこれと汚い噂で中傷してるのよ――私は、たとえ何かしたくても誰にも害を与えられないし、敵から自分を守ることもできない、哀れな女なのに。\nそれに、もうずいぶん昔のことだし…あなたが悪い気持ちで私のところに来たんじゃないかって思ってた。でも、それは間違いだったみたいで嬉しいわ。\n悪意に囲まれて生きるのは、本当に辛いのよ。";
			link.l1 = "どうしてそんなことができる？たとえそんな話を聞いたとしても、一言だって信じなかっただろう。しかし、 おっしゃる通りだ――私はあなたに会うためだけにここへ来たわけじゃない。でも、会えてよかったと思っている。 変に聞こえるかもしれないが……今回はあなたの騎士が、奥様、あなたの助けを必要としているんだ。";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "思ったよりずっと繊細なのね。でも、あなたも完璧じゃないわ、ド・モール旦那――もっと…洗練されていると思っていたのに。\n実際のところ…もともとこうだったのか、それとも群島で既に堕落したのかしら。淑女への話し方をもう一度学び直したほうがいいわよ。 でも、あなたの言う通り――あなたは正直な人だわ、ただし…単純だけど。";
			link.l1 = "そして、あなたは誇り高く、復讐心に燃える女性だ。あなたの目も、言葉も……行動も、それを物語っている。だからこそ、私のことを理解できるのはあなたしかいない。 かつて私があなたを理解したように。だから、もう過去にこだわるのはやめよう。手を貸してくれませんか、奥様？\n";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "ああ…あの時はあなたに冷たくしてしまったこと、認めます。でも、 それはあなたのことを完全に信じきれなかったからに過ぎません！あなたが私からダイヤを全部奪ってしまうのでは、 とか…それとも、私が夫から盗んだと使用人から聞いたと彼を連れてきて、あなた自身の関与を否定するのでは、とか…結局、みんなが求めているのは彼のご機嫌取りで、私のような哀れな女ではありませんから…でも今は、あなたを誤解していたと分かりました。どうか私の謝罪を受け取ってください…私の騎士様。";
			link.l1 = "今となっては、彼らが誠実かどうか分かりません。\nしかし、それは重要ではありません。\nマルセリーヌ夫人、あなたの助けが必要です。\nこれは生死に関わることなのです。どうか断らないでください。";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "私の助けを……？私は確かにこの町で最後の女というわけではありませんが、皆さんが思うほどの影響力はありません。 私は支配する女王ではなく、ただ君臨するだけの者です。でも、お話は伺いましょう。私のつまらぬ身で、 何をお手伝いできるでしょうか？";
			link.l1 = "これはあなたにとって不快な話題だと承知していますが、奥様、私はご主人を探しているのです、できるだけ早く。実は……";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "冗談ですか？今は邸宅にいない？それなら出張中でしょう。お力にはなれません、ド・モール旦那。";
			link.l1 = "あなたは目をそらした。知っているだろう。私も知っている。私はただ、そこに行くだけだ。どうか、 あの地下牢のことを初めて聞いたふりはしないでくれ——あなたほど賢い人が知らないはずがない。";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "ああ、この会話でまた白髪が一本増えそうだよ。もう初めてのシワだって十分あるのに。いったいフランソワ、 お前は俺たち全員に何をしてくれてるんだ……";
			link.l1 = "白髪が増えても、その気品は増すばかりで、美しさが損なわれることはありません。しかし、 善良で無垢な娘があなたの旦那の手に落ちてしまいました。今や彼女は美しさも、健康も、 命さえも失う危険にさらされています……！あそこに捕まった者がどうなるか、ご存知でしょう。どうか、奥様。マルセリーヌ……あなたの騎士を助けてください。";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "もう私の騎士じゃないよね？ねえ、私、バカじゃないんだから。\nでも……手伝うよ、ド・モール。結局、こんなのいつまでも続くわけないし。いつかは公になってたはず。\n今の私にとって大事なのは、ちゃんとしたやり方で、間に合ううちに抜け出すこと。\nそれに……私の“夫”があなたの……知り合いにすることで、あなたを永遠の苦しみに縛りつけるなんて、できないよ。";
			link.l1 = "私はもうあなたの騎士ではないかもしれません、奥方。\nしかし、あなたも最初から私のご婦人ではありませんでした。\nそれでも、私は生涯あなたに感謝いたします。\nそれで、ここはどこですか？";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "では、チャールズ、あなたの言葉を信じましょう。\n街の地下牢にあります。袋小路のひとつに大きな樽があり、その隣からこの怪物の巣へと続く通路が始まっています。\n中は覗きませんでした。昔、一度だけ彼の後をつけただけです。\nそして、あの哀れな者たちの人間とは思えぬ悲鳴を聞いたとき、私は恐怖を覚えました。";
			link.l1 = "本日、あなたは多くの命を救われました、奥様。私の大切な人だけでなく、 将来あなたのご主人に倒されていたかもしれない全ての者たちもです。感謝いたします。";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "ああ、その空虚な言葉はやめてください、旦那。あなたは私に多くを求めました。そして、私は大きな危険を冒しました。 今こそ、新たな冒険――竜の巣窟への挑戦――を成功させてみせてください……我が騎士殿。";
			link.l1 = "最善を尽くします。さようなら、Marceline。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "つまり、あなたは盗賊なの、旦那…？私たちはこんなふうに新しい女の子を雇ったりしないわ。みんな自分の意思でここに来たのよ。あなたとその…共犯者には出て行ってもらうわ。そしてこの子にはちゃんと治療を受けさせるから。さもないと当局に通報するわよ！";
				link.l1 = "俺たちは山賊じゃねえ。だが、この娘はどんな山賊にも負けねえぞ。あいつが刃物を持ってるのは飾りじゃねえ。 今はただ怪我してるだけだ。この男は俺の仲間であり、お前のご主人様の兄弟でもある。だから、彼女に会わせてくれ。";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "またお会いできて嬉しいです、旦那！\nですが、ご存知の通り、ここでは身分の低い客は受け入れておりません。\nたとえ誰かの保証や支払いがあってもです。特に黄色い肌の労働者や黒人奴隷はなおさらです。\n残念ですが、あなたのご友人にはお引き取りいただくことになります。";
				link.l1 = "ご主人様の前でそんなこと言うなよ。彼女も黄色い肌だろう。それに、こいつは労働者じゃなくて彼女の兄貴だ。 家族の再会に水を差すつもりか？";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "時間が経つごとに状況は悪化している。最初はあの狂った黄色い労働者、今度はあんたか。いや、旦那、 無理やり連れてこられた娘たちには金は払わん。ここにいる女たちは皆、自分の意思で来ているんだ。";
				link.l1 = "この娘は俺が救ったんだ。彼女が自分にふさわしくない場所で働くことなんて絶対にさせねえ。労働者だと？";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "ああ、旦那、なんて間の悪いことでしょう！本日はもうお客様をお受けできません――ここで何が起きたか、ご自身の目でお確かめください。";
				link.l1 = "だからここに来たのです。これを仕組んだのは黄色い肌の男だったのでしょう？";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "はい、旦那、労働者でした！何を言っているのかほとんど分かりませんでした！このみすぼらしい男が飛び込んできて、 あのご婦人に会わせろと騒いだのです。自分は彼女の兄だと断言していました。私たちは男たちを呼びましたが…";
			link.l1 = "それはあいつにとって障害じゃない。\nそれで、その後どうなった？";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "どうやら、彼は嘘をついていなかったようだ。\nあの女性が私たちの前に現れて、彼のことを認めた。\n実際、今も彼女の豪華な部屋で二人は話し続けている。";
			link.l1 = "だが、あいつの頭の中は誰にも分からん。俺たちは中に入るぞ――必要なら彼女を救い出す。騒ぎを起こすな――この場所の評判が台無しになる。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "その通りです、旦那。彼はあのご婦人の兄だと言っていました。";
			link.l1 = "そして、あなたは彼を中に入れなかったのですね…";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "もちろん違います！あのご婦人は見事な装いで、訛りもなく話されますよ。あの労働者とは大違いです。 追い払おうとしたら、彼は警備兵たちを全員倒してしまったんです、想像できますか！？";
			link.l1 = "容易に想像できます。そして、彼は今どこにいるのですか？";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "彼とあのご婦人はまだ何か話しているが、俺たちには何を言っているのか分からない――たぶん自分たちの言葉なんだろうな。";
			link.l1 = "俺が行く。もしかしたら旦那の奥方が助けを必要としているかもしれない。\n衛兵は呼ぶな――公になれば、もう誰も二度とこの家の門を叩かなくなるぞ。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "兄だと？奥方は気品があるが、その「兄」とやらには到底及ばぬな。彼女の心をかき乱したり、 この労働者で騙そうとする必要はない。そいつを連れて行け。";
			link.l1 = "ずっと前に二人は離れ離れになったって言っただろう。彼の方が運が悪かっただけだ。 俺たちの時間分の代金は自分たちで払う。今すぐ女主人に知らせろ。";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "お前に警戒する理由など彼女にはない。しつこいのは気に入らんぞ。\nおい！この労働者を叩き出せ！その愚かな主人も一緒にな！";
			link.l1 = "くそっ！娼婦のくせに、なんて傲慢なんだ！";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "ありえません！ご主人様をあなたのその奇妙な連れと二人きりにするなんて、とんでもないです。 行くならあなただけでどうぞ、旦那。あなたの…お仲間たちは外で待ってもらいます――ここはまともな店ですから。";
			link.l1 = "なぜ彼女のことを心配しているんだ？トルトゥーガで彼女が一番の剣士の一人だって、誰もが知っているだろう。\nそれに、俺の仲間たちはこの町の大半の連中よりよっぽどまともだぜ。";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "野郎ども！ここに傷を負った盗賊と汚い労働者がいるぞ！あいつらは俺たちの女主人に何か用があるらしい！ 片付けてやれ！\n";
			link.l1 = "なんて献身だ、くそ……";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "あなたがシャルル・ド・モール殿でございますか？そして、こちらは…ああ。";
				link.l1 = "そして、あなたがベル・エトワールか。いや、チャン・シンと言うべきか？そう、これがあなたの兄だ。 彼は十年以上もあなたを探していた。私と彼は、あなたに聞きたいことが山ほどある。\nだが、時間はあまりない。";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "まあ、よくぞ生き延びたわね。少し遅れたけど、なかなか頼もしい護衛がついてたじゃない。 私のことを守ってくれるつもりらしいのに、今はあなたの隣に立ってるあの人よりはずっとマシよ。 天もあなたに味方してるのね、可愛い子。";
				link.l1 = "知っているようですね。それなら話す必要もありません。\nですが、教えてください、チャン・シン、何を笑っているのですか？他の娘たちが苦しむのを見るのが楽しいのでしょう？ 結局、あなたは彼女たちを売っているのですから。";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "シャルル・ド・モール、だろう？私に会いたいと聞いたが。で、何かお困りか？前回来た時、 うちの店のサービスが気に入らなかったのか？";
				link.l1 = "私はちょうど別のあなたの店から来たところです、Chang Xing。 "+ sStr +"、私の恋人は死んだ。あなたもそれに関わっていたこと、私は知っている。";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "チャン・シン……その名前を聞くのは久しぶりね。ほんとうに、久しぶり。白人たちって……いつも急いでばかり。たまにはのんびり家族の再会でもどう？私には関係ないけど。もう何年も前から、 他人なんて頼りにしなくなったわ。どうして何も言わないの、お兄ちゃん？自分の妹に会えて嬉しくないの？ あんなに必死で私を探してたくせに。";
			link.l1 = "他にも急ぎで、もっと重要な用事があるんだ。ロングウェイ、お前の妹と話してこい。\nだが、まだ我々が向かわねばならない場所を忘れるな。急ぐ必要がある。それに、俺も彼女に聞きたいことがあるんだ。";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "（中国語で）ロンウェイか。名前以外はあまり変わってないな……チャン・トゥ。";
			link.l1 = "（中国語で）でも、姉さん、あなたはずいぶん変わったな。何があった？あなたのまなざしは昔、 真昼の太陽のように温かかった。今は冷たくて、軽蔑しか感じられない。そしてその声も？俺はあなたを笑わせて、 その銀の鈴のような笑い声を聞くのが大好きだった……今は冬のゴアンゴよりも冷たい。そしてあなたは奴らの服を着ている。自分で女たちを売っている。 かつてフェルメンテロスにさらわれたのに。";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "お前が俺に説教しに来たのか？かつて群島一の悪党ローデンブルクの下で働いていたくせに。 俺がお前のことを知らなかったとでも思ったか？最初から全部知っていたさ。俺がどうなったか、なぜこうなったか――それを裁く権利はお前にはないんだよ、道を誤った兄貴よ。";
			link.l1 = "だから、俺に教えてくれ、シン！そして話してくれ。俺が諸島にいると知っていたなら、 なぜ何年も経った今になっても会いたくなかったんだ？俺はお前を探すために人生のすべてを捧げてきたんだぞ…";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "なぜなら、あなたも天も、私をこの世で最も恐ろしい運命から守ってはくれなかったからです。\nそれで私は気づきました――この世界では誰も他人を必要としていないのだと。頼れるのは自分だけ。\nまあ、知りたいなら話しましょう。ただし、彼の言葉で語ります。彼もきっとそれを聞きたがるでしょうから。\nあなたはフランス語がわかりますね、Tu？";
			link.l1 = "（たどたどしいフランス語で）: はい、その言葉を話します。";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "ははは、ああ、天よ！お前の訛りはひどいな。だが、それは仕方ない。フランス語の発音と書き方は確かに難しいからな。 ";
			link.l1 = "今はもう、笑い方が違うな、姉さん……";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			ReturnOfficer_Longway();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "私の愛しい兄さんは、私にこの何年もの間何があったのか知りたいのね。\nあなたも聞いた方がいいと思うわ――あなたも言った通り、疑問があるんでしょう？\nだから心配しないで――全部フランス語で話してあげる。";
			link.l1 = "要点だけ教えてくれ。ロングウェイが自分の人生を語ったときは、何時間もかかったんだ。今は急いでいるんだよ。";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "我慢してもらうぞ。俺は一年以上も全部自分の胸にしまってきたんだ。\nそれに、口を挟んだら、お前の質問には一切答えないからな。";
			link.l1 = "……よろしい……それなら、進め。";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "礼儀はどこに行ったんだ、シャルル・ド・モール？あんたは礼儀正しくて、女たらしの見本だって聞いてたけどな。 噂だけで、実際は……失敗作か？やっぱりな。それに、あんたは間違ってる――俺は男も女も同じくらい憎んでる。実のところ、誰も信用しないし、驚かないし、何も期待しない。もし手が届くなら、 あんたの金玉を喜んで潰してやるさ。でも、こんなにも長い年月を経て本当の名前を聞いたのは……少しだけ、気分が晴れたよ。";
			link.l1 = "俺は女好きだけど、あんたみたいな魔女はごめんだぜ。\nそれに、俺が一番大事に思ってる奴を苦しめてるくせに、何を期待してたんだ？\n正直、あんたにも何かしてやりたくてたまらねえよ。\nそれも、あいつのためだ。\nロングウェイは俺の友達だ。そして、あんたはあいつの家族だろう。\nあいつは十年以上もあんたを探してきたんだ。\nあいつには、あんたと話す権利がある。";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "なんて感傷的なんだ。そして、俺がまったく気にしないのは悲しいことだな。だが、今さら簡単には逃がさないぞ、トゥ。 お前を殺したことも、お前たち全員が一度でも遅れたことも、理由じゃない。だが、知ること――そうだな、お前には知る資格がある。俺がこんなふうじゃなかった頃のおれを、お前は知っているからな、兄弟。";
			link.l1 = "何があろうと……お前には常に選択肢があったはずだ、Chang Xing。";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "お前はまだ若くて、この世界の仕組みを知らないな、シャルル・ド・モール。人生に本当の選択肢は一つしかない――生きるか死ぬかだ。お前にもすべてを知ってもらったほうがいいと思う。だから俺の話をフランス語でする。 お前も話せるだろ、トゥ？";
			link.l1 = "訛りがあります。しかし、よく理解しています。始めてください。";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "「それで、この間ずっとどこにいたんだ？エスパニョーラなんて一日か二日で来れるだろう。 あいつが死んだのもお前のせいだ。それにお前だって、十年以上も遅れてきやがって。俺たちの救い主、守護者様だとよ。 女はな、自分の身は自分で守るって早く知った方がいいんだ。間に合う奴もいれば、そうじゃない奴もいる。 考えが足りねえ奴は、いつまでも気づかねえ。」";
			link.l1 = "次に口にする言葉には十分気をつけろ。俺がまだお前を八つ裂きにしていないのは、友人でありお前の兄貴のためだけだ。 お前は、あいつがどれほどお前のために苦しんだか、何も分かっていない。";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "奴が俺の経験したことに少しでも似たような目に遭ったとは、とても思えません。";
			link.l1 = "それで、話してくれ。";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "そうだな、何と言えばいいか……あの頃の俺は若くて、愚かで、世間知らずだった。それに偏狭だった。トゥはもう話したか？ オリヴェリオ・フェルメンテロスに両親と俺を殺された後、俺が誘拐されたことを。\n";
			link.l1 = "その通りだ。";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "彼は私に言い寄ってきて、想いを打ち明けたけれど、私は彼を拒んだの。\nそれで、あの男は私たち家族を皆殺しにして、私を奪った。そして、その後は……";
			link.l1 = "察しがつきます。";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "できたらよかったのに。\nそれから彼はまた私に想いを打ち明けてきたの、熱く涙を流しながら。\n「これしか方法がない。君の家族は絶対に君を僕と一緒に行かせてくれないから」と言って。";
			link.l1 = "狂気……";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "へっ、それがあの時から俺の人生そのものを表す言葉だな。俺はまた奴を拒んだ。しばらくはそんなふうに続いた。\nだが、明らかにそれが永遠に続くはずもなかった――俺は完全に奴のなすがままだったからな。";
			link.l1 = "本当に起こったのか？";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "もちろんよ。彼は私を力ずくで、荒々しく、そして容赦なく奪ったの。 強姦者たちがそんなことを気にするはずもないけど、でも彼は以前、涙ながらに私への大きな愛を告白していたじゃない？ ふん！その愛なんて、もうどこかへ消えたみたいだったわ。こんなことが毎日、まるで日課のように繰り返されたの。 最初は叫んで抵抗したけど、やがてやめた――どうせ何の意味もなかったから……。";
			link.l1 = "だが、フェルメンテロスは自業自得だったし、あなたはここに辿り着いた。どうしてそうなったんだ？";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "まあ、やがて彼は私にうんざりしたのよ。おかしいでしょ？彼は私とトゥの両親を殺して、私をさらって、何度も辱めて、 最後には私を捨てたの。彼はこの諸島に来て、私をルヴァスールに奴隷として売り飛ばしたのよ。";
			link.l1 = "それは敵にさえ願いたくないことだ。\nそれで、どうやって生き延びたんだ？そもそもどうやって自由の身になれたんだ？\n俺の聞いた話じゃ、ルヴァスールは女を隠れ家から決して出さなかった。いつも始末していたらしい。";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "今はそういうことになっている。ルヴァスールは昔は違った……いや、最初から奴は獣だった。ただ、最初の頃は時々地元の若い植民者を誘拐して、地下室で犯して、 口止め料を払わないためにすぐに始末していたんだ。あの頃、数日以上生かしておくことは滅多になかった。\nだが、俺の場合は最初から違っていた。";
			link.l1 = "「お前は奴隷だったからだろ？」";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "その通りです。ルヴァスールの主な欲望は、単なる肉体的な快楽ではありませんでした。 被害者たちに対する一時的な支配感ですらない――何しろ、彼は島全体を支配しているのですから。しかし…";
			link.l1 = "…彼らが壊れていくのを見届ける悦び――意志も、顔つきも、声も、振る舞いも。";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "ええ。ちゃんと調べてきたのね、船長。でも、その点では、私はあの男にとって面白くなかったわ――フェルメンテロスが、すでに壊れた私を連れてきたから。そしてルヴァスールは私を美しいとは思わなかった――あの男はアジアの女が好きじゃないのよ。なぜか、それが私にはとても響いたの。自分が魅力的だとはわかっているけど、 本当に美しいとは思えない。誰かにそう言われても、信じられないの。今でも、運動して、絹をまとい、 上等な香水を振りかけても。\n別に、あの拷問者の承認が欲しいわけじゃないけど……";
			link.l1 = "では、もう一度聞こう——どうやって生き延びた？あいつは女に飽きたらすぐに始末するんだ。お前の場合、最初から退屈していたんだろう、 そう言っていたじゃないか。";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "最初から私が彼を退屈させたことも影響したんだろうね。それに、私は奴隷だった――どこにも行けないし、何も言えなかった。奴隷の女の子なんて、何千年もずっとそう扱われてきたんだよ。彼は、 私と過ごす時間をどうやって“自分にとって楽しいもの”にするか考え始めたの。";
			link.l1 = "それで彼の依存が今の形で生まれたのでしょう。";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "その通りです。最初は殴られ、唾を吐きかけられ、他にも屈辱的なことばかりでした。私の容姿や出自、 血筋まで嘲笑の的にされました。そして、最初の拷問が始まったのです――ナイフ、火箸、フライパン……。だから私はこんなに肌を隠す服を着ているのです。全身が傷だらけで、焼けただれ、無残な姿になってしまったから。 そして、もう二度と男の前で裸になるつもりはありません。絶対に。あの時、 フェルメンテロスにさらわれた時に気づくべきだったことを、ようやく悟りました。";
			link.l1 = "今のは何だ？";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "もはや無力な操り人形でいるべきではない。\nむしろ、自分の人生を自分で支配すべきなのだ。\n私の場合、女が自分の人生を変えるには、周囲の男たちを支配するしか方法がなかった。";
			link.l1 = "ルヴァスールを支配できるとは言えません。";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "そして、それは間違いではありません。しかし、慎重に彼に影響を与えることは可能です。ルヴァスールは、 最初からの完全な服従も、口論や懇願も、同じように嫌います。お世辞も同様です――自分がどれほどの豚かを自覚しているのでしょう。私はそれを、非常に苦痛な代償を払ってすぐに理解しました。しかし、 拷問と暴力の夜がまた終わり、彼がすべてに満足したときだけ、穏やかに話しかけることができました。 私は貴族の生まれではありませんが、知恵が足りないわけではありません。";
			link.l1 = "「それで、何を話したのですか？」";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "私は彼の興味を引いた。拷問のアイデアを提案し、どの拷問器具は使わない方がよいか、どれから始めるべきか助言した。 最初はもちろん、全部私で試した。\nだがその後……彼なりの歪んだやり方で、私を尊重し始めた。彼の頭の中で何が起きているのか？ どうしてこうなったのか探ろうとしたが、また半殺しにされた。\nそれから彼は、専属の医者を呼んだ。";
			link.l1 = "それは、私がすでに彼について聞いたことよりも、さらに奇妙でおぞましいです。";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "彼はもう私に身を捧げろとは要求しなくなった。私のことを「弟子」と呼ぶようになった。でも、彼はいつも 「自分の作品としてはお前は完全な失敗作だ」と言っていた。多分、私を油断させないためだったんだろう。それで、 彼は私に剣術や言語を教え始めた。地下室に閉じ込められていたけれど、 高価なドレスを与えられたのは奥さんじゃなくて、私だった。";
			link.l1 = "まさに一大事業ですね。\nあなたのこの場所の運営ぶりと、はっきりとした共通点が見えます。";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "その考えは思いつかなかったな、ふむ。だが、その例えは気に入らない。私は自分の女の従業員を拷問したりしないし、 客にもそんなことはさせない。あの女たちが大嫌いで、その美しさを妬んでいるとしてもだ。 私はあの豚とは何の共通点もない、それを覚えておけ。";
			link.l1 = "それで、この売春宿はどうやって手に入れたんだ？";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "もちろんルヴァスールからだ。しばらくの間、あいつの屋敷に閉じ込められていた。時々、どの女をどう壊すか、 私に助言を求めることさえあった。結局、私はあいつにとって特別な存在だったんだ、あいつが決して認めなくても。 私が最初だった。すべてを見た。";
			link.l1 = "「誰が誰から学んだんだったか、もう一度教えてくれるか？」";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "私はそんな人間じゃない！私は、何もかも最初から与えられた奴らが心の底から憎い！そんなの不公平だ！ この売春宿は私の発案だ！私の働き手たちは、時にルヴァスールと関わった商人や役人、貴族の娘たちだ。私は彼に、 彼女たちを私に渡すよう頼んだ。\n秘密の地下室での拷問や屈辱は一つのこと。でも、彼女たちのような者が公然と高級娼婦として働くのは、 まったく別の話よ！";
			link.l1 = "あなたの女の労働者たちが、そんなに屈辱的で、惨めで、壊れているようには見えないと言わせてもらおう。";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "やつらが一言でも口を開けば、ルヴァスールや俺が何をするか知っているからだ。しかし、君の言うことも一理ある。 ワイン、食事、絹、毎日の拷問がない生活――多くは俺を救世主のように見始めた。愚か者どもめ！ここにいるのが嬉しくない者はほんのわずかだ。何人かは、 あいつが重い心で手放した。そいつは笑いながら、俺が金に困ったらいつでも返してくれていいと言っていた。だが、 俺はいつも断った。せめて、その方が地下室で無駄死にするより、金を持ち帰ることになるからな。あいつらにとっては、 あまりにも簡単な逃げ道だ。";
			link.l1 = "皆が屈辱を感じなかったとは、なんと残念なことか……聖なる異端審問よりもひどい修道院を、あんたの売春宿みたいな金の鳥籠に変えただけなのに……";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "私を裁くのか？私はただ生き延びるだけじゃなく、成功した商売を築きたかったんだ。知らず知らずのうちに、 ルヴァスールは私に感謝していた。もう奴隷ではなかったが、彼は私を解放しなかった。 私は依然として彼のために働かされ、手下どもの手助けを強いられていた。特に、あの痩せこけた甥は、 私を見るたびによだれを垂らしていたが、私に手を出す勇気も、悪い言葉をかける勇気もなかった。気持ち悪い。 知っているか、彼は私を失望だと言ったが、私はティボーとマルテーヌを合わせたよりも役に立っていた。 私は彼の命令で、当時ポルトープランスでそうしたように、よく彼らに同行していたんだ。";
			link.l1 = "それで多くのことが説明できますね……";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "そうだ。その通りだ。聞け。俺はお前の恋人を拷問なんかしていない。この手で女を拷問したことは一度もない、 たとえ時々ルヴァスールに助言したことがあってもな。だが、この話題が出たついでに……";
			link.l1 = "何だ？";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "ご存じかもしれませんが、ルヴァスールは時々、トルトゥーガで目撃されたある娘を連れて来いと命じることがあります。 その娘はその後、島を離れました。\nあるいは、誰かが彼を驚かせようと見知らぬ女を連れてきて、彼のご機嫌を取ろうとすることもあります。 私の場合もそうでした。\nあなたの大切な人を誘拐したのは、私の発案です。";
			link.l1 = "今、何と言った……？";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "At first, we were considering capturing that blonde who used be so close to you. But since she is untouchable now, and because we have already promised him a girl, you redhead had to do.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "I heard rumors about your gorgeous companion who never leaves your side. Considering Levausser's love for blondes, I had very little trouble selling him this idea.";
			dialog.text = "ソッタとその犬っころは、ルターの妻であるムラート女をあいつのところに連れてくるはずだった。だが、 お前がソッタを殺したから、大男にはムラート女は渡らなかった。ルヴァスールは激怒した。ティボーも、マルテンも、 俺までもがぶちのめされた。俺をより怒らせたのはどっちだろうな……また俺を殴ったあいつか、それとも、その原因を作ったお前か…… "+ sStr +"";
			link.l1 = "じゃあ、あいつのせいでもないんだな……お前がやったんだ。";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "あなたの許しなど、最初から望んでいないし、そもそも必要とも思わない。\n血が欲しいのなら、血を見せてやる。だが、それをきっと激しく後悔することになるだろう。\nだが、理解を拒むつもりはない。十年ぶりに、理解というものが欲しいと思った。\n俺がしてきたことは、ただいつかトルトゥーガから抜け出すために必死で生きてきただけだ。\n何か聞きたいことがあるか、シャルル・ド・モール？";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "だが、お前は誘拐に関わっていた。そしてルヴァスールが犠牲者たちをどこに閉じ込めているか知っているはずだ。 場所を教えろ。もし最悪の事態がまだ起きていないなら――お前への報復を思いとどまることも考えてやる。";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "ようやく、すべてがまとまりつつあるな……";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "私が知っているのは、私がその場にいたからだ。\nそれに、もし私があいつに異常なほど執着しているとでも思っているなら――それは大きな間違いだ。\nあの豚を串刺しにしてくれる奴が現れるなら、私は大いに喜ぶだろう。";
			link.l1 = "時間がない、Chang Xing。それはどこだ？";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "街の地下道にあるあのダンジョンを知っているか？そこへ行くんだ。\n行き止まりの一つに大きなワイン樽があって、その隣からやつが時々「愉悦の間」と呼ぶ秘密の通路が始まっている。";
			link.l1 = "ようやく、すべてがまとまり始めたな……";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "よかったわね。さあ、出て行きなさい。\n何年も経ってようやく口にできたのはよかったけど、あなたが私のすべての秘密を知っていて、 私に何があったかも知っていると気づいたら――吐き気がするわ。\n今やあなたの顔を見るだけで腹が立つの。\nそれと、トゥは私のそばに残るから。";
				link.l1 = "なぜですか？";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "もしかして、私が彼の家族だから？それに、あなたと一緒にいる時の彼を見てるからよ――打ちひしがれて、惨めで、ろくに言葉も覚えきれていない、まともに話すことすらできない男。なのに、 あなたとは友達だって私に言ったのよ。あなたが彼にどんな影響を与えたか、一目瞭然だわ。少なくとも、 私が彼を一人前の男にしてみせる。";
			link.l1 = "そして、本当に自分自身に満足しているのですか？\nあなたは彼を何に変えてしまうつもりですか？\n命を売り買いする冷酷で苦々しい化け物にでも？";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "旦那船長、どうかお止めください。妹をそっとしておいてほしいのです。そして……私は彼女のそばに残ります。";
				link.l1 = "お前……なんだと？ロンウェイ……でも、なぜだ？彼女がどうなったか見えないのか？";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "お前は違うのか？時が経つにつれて変わったじゃないか。しかも悪い方にな。最初は礼儀正しくて、理解もあった。だが、 そのうちローデンブルクよりも無礼になった。 そして俺がヴァン・デル・ヴィンクを追うためにまともな船が必要だった時、お前がくれたのはガラクタだった！";
				link.l1 = "「ロンウェイ…」";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "俺はかつて海に出て、妹を探し救うためにこの何年も費やしてきた。\nそして今、妹はここにいて無事だ。俺の使命は果たされた。\nそれから……俺の名はチャン・トゥだ。ロンウェイというのは、裏切り者ヴァン・メルデンが俺につけた名だ、忘れたのならな。\nだがチャン・トゥは自由な男だ。チャン・トゥの長い旅路はついに終わった。";
			link.l1 = "彼女はローデンブルクがかつてそうしたように、お前を召使いにするだろう。\n家族だからといって、お前に重圧をかけてくる。\nそれで、お前は俺と—— " + sStr + " そんなにも苦しいのか？";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "今は、チャン・トゥに圧力をかけているのはあなたです。どうか、私を行かせてください。とても疲れました。 あなたは良い人です、キャプテン。天もそれを証明できるでしょう。しかし、あなたは私の家族ではありません。 彼女がそうです。私がここに残らなければ、これまでの年月がすべて無駄になります。今度は私が彼女の導きの星となり、 消えた炎を再び灯します――すべてを焼き尽くすのではなく、温かく、慰めとなるように。";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "ふむ、あなたの言う通りかもしれません。今は少し強引すぎたかもしれませんね。\nまあ、私はずっとあなたを尊敬してきました。あなたが長年待ち望んだ妹さんとの再会を果たせることを願っています。\nですが、警告しておきます――彼女と共に安らぎを得ることはできませんよ。";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "今は俺を置いていけない！まだ救わなきゃならないんだ " + sStr + " ルヴァスールのところへ行けって！？私ひとりで行けっていうの？助けてよ、ロンウェイ。そしたら君を自由にする。 約束するよ。";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "私に任せてください。もう私のことは心配なさらなくて結構です。ありがとうございます。";
				link.l1 = "どうやら、あなたの妹は我々が平和的に別れることを決めたことに怒っているようです。";
			}
			else
			{
				dialog.text = "お分かりになるでしょう、我が主君たる船長。あなたほど聡明なお方、私は見たことがありません。 女を苦しめることしか知らぬあの虫けらなど、あなたなら簡単に片付けられます。どうか、 無理強いはなさらないでください。姉には、私と語るべきことが山ほどあるのです！それと……私の名はチャン・トゥです。";
				link.l1 = "今ここで俺を見捨てるってことは、俺を裏切るってわかってるのか！？しかも、 すべての元凶であるあの女のそばに残るなんて！";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "恐れることはありません、船長。彼女が私のことを無礼に語っても、私は兄であり、彼女の最後の男の身内です。 行ってください。あなたを殺させはしません。さらばです。";
				link.l1 = "さらば……Chang Tu。";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "私が言うべきことはすべて言った。\nさようなら、船長。\nそして幸運を祈る。\nチャン・トゥはいつまでも自由な男だ。\nそれを忘れるな。";
				link.l1 = "これが、私がすべてを捨ててあなたの捜索を手伝った報いですか！？あいつらがやっていることの後で\n " + sStr + " 今か！？お前は裏切り者だ、Chang Tu。そしてその報いを受けて死ぬんだ、二人とも、このクソ蛇どもめ！";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "私の名はチャン・トゥ。ロンウェイは死んだ。お前が彼を殺した。もうお前は私の船長ではない。今度はお前が死ぬ番だ。 私の家族はついに安らぎを得て、我らの星は夜空に明るく輝くだろう。";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "（信頼） （指導力）ロングウェイ……チャン・トゥ。待て。俺が君にとって完璧な船長じゃなかったことは分かっている。だが、 それだけの理由で本当に俺を殺したいのか？俺たちがここまで一緒にやってきたことを思い出してくれ。 ローデンブルクの時も、今は君の妹を探しているのに。";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				Notification_Perk(true, "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "ロンウェイ、俺はお前の船長だ。家族でもなければ子守でもない。俺は命令を出す側であって、 お前をうっかり侮辱したかどうか気にする立場じゃない。まるで長年連れ添った夫婦みたいに要求してくるとは、 なんてこった……";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "ああ、今ならよくわかる。お前も自分のことしか考えない腐りきったクズだな……ロングウェイ。お前の妹と同じだ。俺の家族は今日を生き延びる。お前の家族は……無理だ。地獄へ落ちろ！";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "もし選ばなければならないのがあなたか私の家族かなら――たとえ辛い選択でも、私はやはり家族を選ぶ。";
			link.l1 = "「お前が何年も彼女を探している間、指一本動かさなかった家族だろう？ああ、でも“ちょうどいい時”が来たってわけか！俺はと言えば、すべてを捨ててお前を助けてきたんだぞ。今こうしてここに立っているお前は、 その結果だ。くそ、俺の方があいつよりよっぽどお前の家族だぜ、相棒！」";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "おっしゃる通りです。いつもながら、正しいです。許していただけますか、My Lord Captain？";
			link.l1 = "許しを乞うことなんて何もないよ！一つだけ君の言う通りだ——俺はいつも君にふさわしい船長じゃなかった。これでおあいこだな。\nところで、これからはどう呼べばいい？ロンウェイか？それともチャン・トゥか？";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "ロングウェイでいい。もう君がそう呼ぶのには慣れている。";
			link.l1 = "それでは、すべてのいさかいを忘れて、もう一度ロングウェイを歓迎しよう。";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "お前！何を言っている！？なぜ止まった！？殺せ！あいつにとってお前はいつまでもただの労働者だ！ お前の家族は俺だけ、俺しかいないんだ！";
			link.l1 = "彼女は本当に怒っているよね、ロンウェイ？シン、お前はもうあいつの家族じゃない。 ロンウェイが諸島に来たと知った時に、それを無視することを選んだ時点で終わったんだ。俺たちは行くぞ。";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "あいつの奴隷根性を根絶やしにするなんて、最初から無理だったんだろうな。\n俺には救えない。\nだったら、お前たち二人とも俺がこの手で殺してやる。";
			link.l1 = "ここで救いようがないのはあんただよ。わかる？私はあんたに対して、今まで優しすぎて、許しすぎてきた。でも、 こっちのほうがずっといいよ。ロングウェイでさえ、あんたがどれだけ卑劣な奴か気づいたと思う。彼も、 あんたのことをそんなに惜しまないだろうね。";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "冗談を言う時じゃない！お前は恐怖と失敗を冗談の陰に隠しているだけだ！それがますます俺を確信させる。\n覚悟しろ、ド・モール！チャン・トゥはお前を容赦するつもりはない。";
			link.l1 = "こんな結末になってしまい、申し訳ありません。しかし、それがあなたの望みなら、仕方ありません。その場合、 私からも容赦はしません。";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "「チャールズ、聞いてくれ…」";
				link.l1 = "「エレン？」";
			}
			else
			{
				dialog.text = "「チャールズ、ロンウェイ、やめて…」";
				link.l1 = "ヘレン、今は俺の後ろに下がった方がいい。もし奴らが襲ってきたら、その方が安心できるからな。";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "もう立っているのもやっとなくらい疲れたよ。ここから早く出たい。ロングウェイが戻りたくないなら、 無理やり船に連れて帰るつもりはないよね？私はあなたの航海士であり、副官よ、私のキャプテン。できれば、 あなたが一番信頼して愛してくれる存在にもなりたい。それに、彼の言うことも一理ある――私たちは彼の家族じゃない。家族なのは、あの人だけ。良くも悪くもね。";
				link.l1 = "でも、彼女はどうなんだ？お前が拷問されたのは彼女のせいだろう。全部、彼女の考えだったんだ。それに、 お前をさらったのも彼女だ。";
			}
			else
			{
				dialog.text = "でも、そんなことしないでしょ？もう行こうよ、それだけ。私たちがどれだけ彼のためにやってきたか考えても、 彼が私たちをこう思ってるなら、考えを変えさせる意味なんてないよ。言葉より行動が大事だもん。 彼が妹と一緒にいたいなら、そうさせてあげればいいよ。";
				link.l1 = "ヘレン、君は彼女のせいで本当に多くの苦しみを味わったんだな……";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "あの悪魔女は自分の悪魔たちと一緒に放っておけ。やつらがすぐに彼女の魂を食い尽くすだろう。俺たちの魂には、 しばしの安らぎが必要だ。行こう。";
				link.l1 = "ああ、そうだね。行こうか、私の天使。\nそれから、お前――ロンウェイか、チャン・トゥか――さよならだ。";
			}
			else
			{
				dialog.text = "でも俺は死ななかった。最悪の事態にもならなかった。俺はここにいる、あなたと一緒に。それが大事なんだ。 それにルヴァスールは死んだ。あいつがいなければ、あの女は何もない。あの店も金を失って、すぐに潰れるさ。 奴らも一緒に沈むだろう。行こう、私のキャプテン。ここでもう俺たちのやることはない。";
				link.l1 = "異論はありません、エレン。";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "どこへ行くのですか？";
			link.l1 = "どうした、ロングウェイ、お前と妹の腹をぶちまける気がないことに驚いたか？それが俺たちの違いだ。 なのにまだ俺が悪党だと思ってるんだな……だが、いいだろう、聞け。\nもし俺を殺したいなら、ヘレンも殺さなきゃならないぞ。彼女は傷ついて、怪我してる。本当にそれでいいのか？";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "うむ。";
			link.l1 = "お前の目に疑いが見えるぜ、俺に対していくら恨みがあってもな。だが、俺たちもヘレンを見習おうじゃねえか？ うちの仲間で彼女ほど優しくて許してくれる奴はいない。俺たちは行く。もしお前にまだ善意や分別が残ってるなら、 俺たちの邪魔はしないはずだ。\n";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "そうですか。お詫びします。しかし、あなたはもう私の船長ではありません。";
			link.l1 = "どうにか乗り越えるさ。君と君の妹に幸運を祈るよ、たとえ彼女が何をしたとしても。さようなら、ロンウェイ。";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "さあ、チャールズ、反乱を鎮圧する時だ。";
			link.l1 = "神のみぞ知る、私はそんなことをしたくなかった……今でも、したくはない。";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "わからないの？！チャールズ、私の話を聞いて。あなたは彼のためにあんなに尽くしたのに、 返ってきたのは裏切りとひどい言葉だけ、でしょ？本当にそれで許すつもりなの？";
			link.l1 = "俺はロングウェイの血を流したくない。かつて俺たちが友だったこと、忘れていないんだ。";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "そんな友達なんてクソくらえ、敵よりタチ悪いでしょ！\nチャールズ、あたしを見てよ。\nこのザマを見てよ――全部、あいつの妹のせいだよ。あたしをバカにして、侮辱して、辱めて、この血塗られた島まで来る道中ずっと、でしょ！ ？";
			link.l1 = "メアリー、わかるよ……今、君は本当に、本当に怒っているんだね……";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "ああ、違うよ、Charles、私はただ怒ってるだけじゃない、違う……私は激怒してるんだ！しかも、あの惨めなクソ野郎があなたに言ったことだけが理由じゃない！もう一度私を見て、Charles――もし私たちがここで終わらせなければ、どれだけ多くの女の子が同じ目に遭うか想像してみて。ここで、今、 終わらせるのよ。";
			link.l1 = "もう誰も傷つけることはない。ルヴァスールは死んだ。";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "シャルル、あの女が口にしていた異端の言葉を本当に聞いていたのか？あいつはあの地下室で起きたことに、 あの腐れ豚と同じくらい責任があるんだぞ。今のロングウェイを見てみろ――いや、今はもう別の名か。あの女がどれほど素早く彼を味方につけたか、見ただろ、でしょ？あの裏切り者の頭に、 これからどんな病んだ考えを吹き込むつもりか分かったもんじゃない。 あの悪魔女がロングウェイをルヴァスールの道へ誘うのに、どれほど手こずると思う？今の彼がどうかなんて考えるな、 シャルル。一年後、いや一ヶ月後にどんな怪物になるかを考えろ……。俺の言うことが正しいって、分かってるよな？";
			link.l1 = "認めたくはないが、俺には君に反論する材料が何もない、Mary…";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "ハハハ！面白い、見事な芝居だな。こんなに腹の底から笑ったのは久しぶりだ。それに、あの娘は根性がある。 認めてやるよ。";
			link.l1 = "黙れ、このアマ。";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "面白いじゃないか、ド・モール。俺は自分の目でトゥがあんたを倒すところを見てみたいもんだ。しかも、 あんたの女も俺と同じくらい血に飢えてるようだな。いいぞ。俺は黙って見てるつもりはない――ルヴァスールやトルトゥーガの大物たちと鍛錬を積んできたんだ。どっちのコンビが上か、勝負といこうじゃねえか。";
			link.l1 = "お前にはろくな師匠がいなかったんだな。それにMaryを怒らせちまった。もう終わりだ。俺がここにいなくても、お前たち二人じゃ彼女には到底敵わねえよ。";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "はい。ついに。ロングウェイ、もう一度姉と話してもよろしいですか、我が主船長？長くはかかりません。";
			link.l1 = "もちろんだ。ただし手短に頼む、時間があまりないからな。";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "ロンウェイが手早くやる。";
			link.l1 = "よろしい。";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "「それで、兄弟よ、あなたが私に伝えたかったことは何ですか？」";
			link.l1 = "「ロンウェイはあなたにとても失望していますよ、シン。」";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "（中国語で）なぜまた話したいと言ったのに、我々の言葉を話さないんだ、トゥ？彼のことが恥ずかしいのか？俺なら、 お前の訛りの方がよっぽど恥ずかしいがな。";
			link.l1 = "いいえ。ロンウェイはロードキャプテンに隠し事などありません。もう、何も。";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "（フランス語で）まずはローデンブルク、次はド・モール。お前はいつも「旦那」が必要だな。十年以上もここにいて、 何一つ成し遂げていない。やつらの言葉すら一つも覚えられない。しかもあんなに俺たちのより簡単なのに！ 失望すべきは、お前自身だ。";
			link.l1 = "だが、俺は女を売り買いしない。誘拐や拷問にも加担しない。";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "本気ですか？ローデンブルクのためにあなたがやってきたことを挙げましょうか？私がしてきたことなんて、 それに比べれば子供の遊びですよ。";
			link.l1 = "私は目的があった――あなたを見つけることだ。しかし、あなたは私に会うことすら望まなかった。\nそして私があなたを見つけた時、そこにいたのはかつて私の道を照らしてくれた温かな導きの星ではなく、化け物だった。 ";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "怪物？まあ、そうかもしれないわね。もうあなたが知っていたあの明るい少女じゃないのよ。もしあのままだったら、 人生に食い尽くされて捨てられてたはず。だから自分の牙を生やすしかなかった。私の星はもうとっくに消えてしまった。 でも、私はまだあなたの妹よ、トゥ。";
			link.l1 = "いいや。お前はもう俺の妹じゃない。";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "こんなにも長い年月が経ったのに、俺をそんな簡単に見捨てるのか？へっ……それに、もしあの日お前が間に合ってフェルメンテロスを殺していたら、俺はいまだに同じままだったかもしれねえぞ？";
			link.l1 = "おっしゃる通りです。私にも責任があります。これは私の務めです。そして、私が終わらせます。 あなたを苦しみから解放します。この惨めな生を終わらせます。";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "本当に自分の妹を殺すつもりか、Chung Tu？どうせうまくいかないだろうが、問題はそこじゃない……";
			link.l1 = "お前はもう俺の妹じゃない。シンは十年前に死んだ。そして今日こそ、チュントゥもついに死ぬ日だ。これから先、 永遠に俺の名は……ロンウェイだ。";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "まずは、チャン・シンを救出します。";
			link.l1 = "「何だと！？お前は分かっていないようだな、友よ。お前の妹は今すぐ危険というわけじゃないが」 " + sStr + " そうです。そして、張興もマルタンやティボーと同じくらいこの件の責任があることを、 改めて申し上げる必要がありますか？";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "そんなはずない！彼女は……";
			link.l1 = "ルヴァスールが何をしているか、あなたには見当がつきますか " + sStr + " 俺たちがここで言い争っている間にか？";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "「でも、チャン・シンしか俺にはもう残っていないんだ、My Lord Captain…。あなたの家族はまだ無事だろう…」";
			link.l1 = + sStr + " 「妻ではないが、私にとっては家族同然に大切な人だ。」";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "張星は俺の最後の導きの星だ、My Lord Captain。\nそれに、ロバート・マーテンから自白を引き出した借りがまだあるぞ。";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "お前の妹を追いかけに行く、約束するよ。\nだが、ルヴァスールは今まで彼女に手を出していないんだ。 " + sStr + " 張星よりも遥かに大きな危険にさらされているんだ。まず彼女を救うのを手伝ってくれ、そうしたら大きな借りを作るぞ。 ";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "（信頼） （指導力）君の妹を追いかけるよ、約束する。だが、ルヴァスールは今まで彼女に手を出していないんだ。 " + sStr + " 張星よりもはるかに大きな危険にさらされている。まず彼女を救うのを手伝ってくれ、そうしたら大きな借りを作るぞ。";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						Notification_Perk(true, "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "聞いてください！あなたの妹は無事です。しかし\n " + sStr + " 今や変態の手に渡っているんだぞ、今まさに彼女を拷問しているかもしれない――いや、それ以上かもしれない！\nレヴァスールが他の地下牢の哀れな娘たちと同じようにお前の妹を扱っていたら、あんな上等な店を持たせると思うか！？ ";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "無駄な議論に時間を割くつもりはない。\n俺たちにはそれぞれ優先すべきことがある。\nまた別れて行動しよう。\n俺の神が俺を助け、あんたの神があんたを助けてくれるように。";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "おっしゃる通りです。借りができましたね。わかりました、あなたのやり方でいきましょう。\nそれに、あなたがいなければレヴァスールや奴の手下どもを相手にできないかもしれませんから。\nですが、もし何かが起これば " + sStr + " 「お前の姉妹の件を片付けている間に…」";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "ご理解いただき感謝します、Lord Captain。ご武運を！";
			link.l1 = "「そして君にも、ロンウェイ。」";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "虚勢は無意味でございます、My Lord Captain。急がねばなりません、すべてに間に合わせるために。";
			link.l1 = "お前の神がそれを聞いてくれるといいな。行くぞ！";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "今回は敬意を表して見逃します、Lord Captain。これっきりです。次は殴ります。今から私は妹を追います、あなたの許しがあろうとなかろうと。";
			link.l1 = "これ以上お前と口論して時間を無駄にするつもりはない、ロンウェイ。\n結局、誰もが何よりも大切にしているものがあるんだ。";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "うん、でしょ？旦那船長。でも、それなら急がなきゃ。";
			link.l1 = "そうか。ありがとう、ロンウェイ。";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "ほうほう、ここにいるのは一体誰だ……くそっ。シャルル・ド・モールと、そのつり目の犬っころか。";
				link.l1 = "ここにいる雑種は一匹だけだ。見たけりゃ鏡を覗け、ユグノーのクソ野郎。それか甥っ子のツラでも見てみろ。もっとも、 あいつはノミだらけのネズミにしか見えねえがな。";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "邪魔するなと言っただろう！ああ、シャルル・ド・モールか、へへへ。なんてしつこい小さな害虫だ。";
				link.l1 = "それが俺なんだよ。さあ、黙りやがれ、そして…";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "自分の船じゃねえぞ、小僧！この島で男は一人だけ――それが俺だ！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "「よくもそんなことを、クズ野郎め！」";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "落ち着け、甥っ子よ！モール旦那にはこれから礼儀作法の手本を見せてやるところだ。";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "俺が泣き叫ぶ許可を出したか！？";
			}
			else
			{
				dialog.text = "その炎はどこに消えたんだ、なあ、可愛い子？ああ、分かった気がするな…";
			}
			link.l1 = "「彼女に手を出すな、この野郎！」";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "へっへっへ……どれだけ叫んで俺を罵ろうが構わねえが、風に揺れる葉っぱみてえに震えてるのが見えるぜ。お前の目に宿る恐怖、 俺にははっきり見える。お前とアンリはそこがそっくりだ。気を悪くするなよ、甥っ子。";
			link.l1 = "お前の言う通りだ、これは恐怖だ。だがな、クズ、お前なんかじゃない。";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "もちろん、もちろん。全部聞いたことがあるぞ――誰も恐れないってな、ド・モール。あの女がそう言ってた。「ああ、シャルルが来てくれる、 シャルルが私を救ってくれる……シャルルがこうだ、シャルルがああだ……」とな。さて、シャルルはここにいる。シャルルは特等席だ。アンリ、客人を快適にしてやれ。";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "そんなことは必要ありません、おじさん。今回はちょっとやりすぎたようですね……";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "おじさん、今回はあなたの助けが必要なんだ……";
				}
				else
				{
					dialog.text = "「叔父上、先にこいつを始末しましょうか、それともまず見物させますか？」";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "俺じゃねえよ、遅れて助けに来たのはそこのホワイトナイト旦那だろうが。\nどうやら見せ物は終わりみてえだな、ハハハハ！";
				link.l1 = "「神よ、いや……」";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "そう思った。どうやってこの歳まで生き延びたのだ？ところで、同じ質問を君にも、ド・モール。";
					link.l1 = "お前に聞きたいことが山ほどあるんだぞ、この人殺しめ！";
				}
				else
				{
					dialog.text = "俺たちの小芝居に観客がいればよかったんだが……\nだが、ここの頑固者の旦那は、その楽しみを与えてくれそうにないな。";
					link.l1 = "誰も楽しめやしないさ――俺だけだ、お前を腹から裂いてやることでな、殺人鬼め！";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "さあ、行けよ、彼女を拾い上げろ！ハハハ！";
			link.l1 = "くたばれ野郎ども、生まれてきたことを後悔させてやるぞ！";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "屠殺者？私はむしろ芸術家、画家だと思っている――せめて芸術として見ようと努力してくれないか…観察してごらん。\n私の作品、気に入ったか？まさに傑作の一つだ。正直に言えば、私は金髪の方が好みだが、彼女は…結局、この醜い髪色も許してやった。ただ髪だけじゃない――あの娘はまるで炎のようだった！危うく火傷しそうになったよ。必死に抵抗し、噛みつき、獣のように唸った！ まるで赤い肌の野蛮人を思い出したよ――あれも短い間だったが、随分と楽しませてもらったものだ…";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "屠殺者？私は自分をもっと芸術家、画家だと思っている——せめて芸術として見てみてくれないか…観察してごらん。\nほら、まだ彼女は完成していない——このキャンバスにはまだ空白がたくさん残っている。彼女は美しいだけでなく、岩のように頑丈で、氷のように冷たい。 叫ばせるために少し汗をかく羽目になったよ。彼女は最後まで耐え抜いた、 私がその美しい声を楽しむことができないように。";
			}
			link.l1 = "今すぐ彼女を解放しろ、この下劣な奴め。";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "どこへ行くつもりだ？この肉の塊は今や俺の所有物だ。周りのすべてと同じようにな――この町も、この要塞も……俺こそがトルトゥーガだ。お前も、あの臭い年寄りのポワンシーも、それを変えることは絶対にできねえ。";
			link.l1 = "ルヴァスール、お前……";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "お前のためのシニョール・ド・ルネ・ド・ブアデュフレ・ド・レットルだ。";
			link.l1 = "俺はどうでもいいんだ。剣を抜け、そして戦いで自分の価値を見せてみろ――相手は男だ、無力な娘じゃねえ。";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "なんて男なんだ！でも君の言う通りだ、俺もこのくだらないおしゃべりにはもううんざりしてる。早く……俺の女のもとに戻りたいんだ。しかし最後に一つだけ聞かせてくれ。どうやってここに来た？ この場所のことを知っているのはほんの一握りの人間だけだ。誰が居場所を漏らした？";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "共通の友人であるマルテンは、ナイチンゲールのように歌ったよ。いや、 実際は屠殺場の豚みたいに悲鳴を上げていたがな……";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "あなたには秘密にしておいたほうがいいかもしれませんね。あなたの自尊心を傷つけてしまうのが怖いのです、 ド・ルネ旦那……なんとか。";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "ルヴァスール、あなたの犠牲者の一人だ。";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "嘘つきめ、このろくでなし！この壁からは誰も出られんぞ！";
			link.l1 = "記憶を使ってください、さあ。いたはずです。チャン・シン。";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "ありえない。あの子じゃない。俺のアイデアのいくつかは、あの小悪魔から生まれたんだぜ。\nおっと、お互いにいろいろ教え合ったもんさ、へへ。最後には良心を清めるつもりになったのか？\nそんなわけないだろ。だって、俺がとっくに全部、あいつの中から消し去ってやったんだからな！";
			link.l1 = "今からお前を干からびるまで刻んでやる。一滴ずつ、ゆっくりとな。";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "「それで俺のことを虐殺者呼ばわりか、この哀れな偽善者め！へっへっ……だが、あいつが地獄で焼かれている限り、俺には恐れるものなど何もない。」";
			link.l1 = "あいつはそこであなたを待っている。あなたのろくでなしの甥っ子もな。がっかりさせるのはやめよう。";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "この玩具をもう少し痛めつけてやろうか？腹か喉を裂いて、あんたが彼女のところにたどり着こうとする間に、 血を流しながら死んでいくのを見物するんだよ…";
			link.l1 = "お好きなように、ルヴァスール、お好きなように……奥方からよろしくとのことだ。それと、別れの一礼もな。";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "何だと！？カッ、カッ…くそったれマルセリーヌ…この哀れな女め、クソ女、クソ女、クソ女！";
			link.l1 = "そうだな。お前たちはお似合いだよ。ただ、彼女の方が頭の回転は少し上だな。少なくとも一見したところはな。";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "あの女の鶏みたいな頭を槍の先に突き刺してやるつもりだ。\nだがその前に……おっと、あの尻軽女にはまだまだ色んなことが待ってるぜ……\n俺の新しいおもちゃも少しは休ませてやるさ。\n待てよ！もっといい考えがある。アンリに貸してやろう。もちろん、しばらくだけな。";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "本当に？ありがとう、おじさん！";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "まずはふさわしくなれ――これを手伝ってくれ、え？";
			link.l1 = "彼はもうすぐ理性を失いそうだ。";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "ロードキャプテン……ロンウェイよりお悔やみ申し上げます。私たちはできる限りのことをしました。";
			link.l1 = "すべてではない、全然足りない。";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "ロンウェイはチャン・シンを探しに行く。私と一緒に来てくれるか？";
			link.l1 = "ああ、一緒に行くぞ、ロンウェイ。だが覚えておけ――お前の妹もこの血まみれの茶番の主役だったんだ。俺が彼女を見逃すには、相当な努力を見せてもらわないとな。 お前が助け舟を出すことは許さない。さあ、終わらせる時だ。";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			ReturnOfficer_Longway();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "チャールズ、やっぱり来てくれるって思ってたよ、でしょ？絶対来てくれるって、わかってたもん！いつもそうだよね、 でしょ？";
					link.l1 = "四度目は試したくないな、Mary……あいつらのろくでなしどもめ、奴らは……";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "ああ、私のキャプテン、あなたがどれほど絶妙なタイミングで来てくれたか、わかっていませんね。あいつら…あの怪物たちが…";
					link.l1 = "もう終わったんだ、エレン。大丈夫、すべて終わったよ。ああ神よ、彼らは君に何をしたんだ……";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "チャールズ、来てくれたんだ！やっぱりね、やっぱりだよ、でしょ！";
					link.l1 = "全速で帆を張って、命からがら逃げていたんだ、Mary。君は…まさか、やつらに…？";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "私のキャプテン……来てくれたんですね……もう希望を失いかけていました……";
					link.l1 = "できるだけ急いで来たんだ、エレン。遅くなって本当にすまない。";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "違うよ、チャールズ、違うの。奴らはやろうとしたけど、あたしはできる限り抵抗したんだ。 だからこんなにひどく殴られたの……お願い、チャールズ、ここから出ようよ……でしょ？";
					link.l1 = "すぐに、あなた。最後にやることが一つある。";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "やってないんだ、Charles！あいつらじゃない。残りの傷は治るよ。お願い、ここから連れ出して。";
					link.l1 = "もちろんですよ、親愛なる方。ここでやるべきことが一つだけ残っています。";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "いいえ、Charles、違います。奴らはやろうとしたが、あなたが間一髪で間に合った。あの時のように。これで何度目だ？";
					link.l1 = "数えたことはない、Mary。これからも数えるつもりはない。";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "間に合った……最悪の事態にはならなかった。さあ、お願いだ、ここから出よう。どこでもいい。";
					link.l1 = "立て、エレン。上に行け。まずはこのクズを片付けなきゃならねえ。";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "そして、私は数えるのをやめません。さあ、この場所を離れましょう、お願いします。";
			link.l1 = "もちろんですよ、あなた。ここで私たちにできることはもう何もありません。ただ、一つだけ残っています。";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "それでどうした、カッカッ、根性なしの鼻たれめ？その黄色いケツのイノシシにでも手を貸してもらえよ…\nそれとも自分でやってみろよ、そうすりゃポワンシーに自慢できる理由ができるだろうが。";
				link.l1 = "むしろ、あんたがどれだけ臆病でクズだったか、みんなに言いふらしてやりたいね。";
			}
			else
			{
				dialog.text = "何だ、お前、本当に俺が血を流して死ぬのを見たいのか？楽しんでるんだろう？自分がどれだけ英雄か、 女に自慢するつもりか。あそこの壁にぶら下がってる骸骨が見えるか？あれはサンティアゴの銀行家の女房だ……あいつの旦那も自分を英雄だと思ってたが、結局はただの叫び声のうまい男だった――俺があの拷問車輪で回してやった時にな。\n";
				link.l1 = "てめえの死体をその上で転がしてやってもいいが、クズ、残念ながらお前のケツの重さには耐えられねえだろうな。";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "臆病だと？おお、カッカッ、やめてくれ…";
				link.l1 = "残酷さは臆病さの反対ではありません。しかし、あなたのような者にはその違いなど分かるはずもないでしょう。";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "それは実に賢いな。よく聞け、ド・モール。お前もあの大物と同じように死ぬことになるぞ――自分の叫びで声が枯れ、身内の悲鳴で耳が聞こえなくなりながらな…";
				link.l1 = "地獄で焼かれろ、このクズ。";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "ああ、俺は哲学者なんかじゃねえよ、認めるさ。見ろよ、あの壁の骸骨を、ド・モール。 あれがサンティアゴの銀行家の女房の成れの果てだ。あいつも偉そうな口をきいてたが、 俺があの車輪で体を締め上げ始めた途端、全部止まった。残ったのは叫び声だけでな、 あやうく耳が聞こえなくなるところだったぜ…";
			link.l1 = "さっさと片付けましょう。";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "少々お待ちを、My Lord Captain……そんなに急がないでください。";
			link.l1 = "どうした、ロンウェイ？";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "殺すな。\nそれじゃ簡単すぎる。\n奴にはもっと酷い罰がふさわしい。";
			link.l1 = "友よ、お前は妹のことで怒っているんだろう。俺は、あいつがやったことに激怒しているんだ。 " + sStr + "…そして、あいつが彼女に何をしたのかも考える。しかし、俺はあいつのような獣じゃない。あの火鉢の炭で焼くことも、 あの車輪で骨を砕くこともできる…鎖につないで血を流しながら死なせることもできる。だが、あいつの手下の誰かが助けに来る危険は冒せない。 その可能性は許せないんだ。";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "お待ちください、My Lord Captain。それは私の言いたかったことではありません。私が話しているのはポワンシーのことです。";
			link.l1 = "彼はどうする？";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "この獣を生け捕りにしてあいつに差し出したら、どれほどの褒美がもらえるか考えてみろ。 ドゥブロン金貨を雨のように浴びせてくれるだろう。\nそれに、あのクズはキャップスターヴィルの地下牢で朽ち果てるより、ここで死ぬ方を選ぶさ。";
			link.l1 = "お前の言うことも一理あるかもしれないな、ロンウェイ。だが、このクズとシュヴァリエの間に何があったのか、 俺には正確には分からない。信じてくれ、俺はお前よりもこの連中のことをよく知っている。もし噂通り金が全てなら、 この二人は手を組むこともあり得る。ポワンシーがこいつを解放し、そしてまた別の島や旧世界のどこかの都市に、 こんな部屋がもう一つ現れるかもしれないんだ。\n";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "悪くない考えだな、ロンウェイ。だが、シュヴァリエがそこまで気前よくするとは思えない……あいつの性分じゃないからな。\nだが俺にとっては、金が目的じゃない。\nさあ、あいつを起こせ！それと、死なれる前に傷の手当てをしてやれ。";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "だがまずは、お前を狙う。そしてお前の仲間もな。細目の男よ、お前には指一本触れない。 俺の時間を割く価値もないからな。";
			link.l1 = "見ただろう、ロンウェイ？もう終わりにしなきゃいけない。ここで、今すぐにだ。";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "「ちょっと待ってください、船長、ちょっと待ってください、カッ、カッ。」";
			link.l1 = "何の用だ、元総督旦那？";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "この部屋のどこかに俺の鍵がある。その鍵は俺の執務室の箱を開けるんだ。中には銀貨が二十万と上等な剣が入ってる。\nそれでも足りなければ、妻の寝室のタンスの中に高価な宝石のコレクションがあるぞ。";
			link.l1 = "ふむ、それで見返りに何が欲しいのですか？";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "弾丸をくれ。ここで、今、俺を終わらせろ。";
			link.l1 = "シュヴァリエ・ド・ポワンシーのことはどうする？\n昔からの友人だと聞いたが……会いたくはないのか？";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "ポワンシーなんかくたばっちまえ！それで、同意するのか、しないのか？";
			link.l1 = "いや、特にそうでもありません、ド・……。あなたのフルネームを言いたくはありません。";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "それで足りないのか？いいだろう、まだあるぞ……";
			link.l1 = "お前の犠牲者たちの悲鳴で耳が聞こえなくなったのか、ルヴァスール。言ったはずだ、金のためじゃない。 ポワンシーを恐れているのも理由があるんだろう、そうだろ？奴がお前に何をするかなんて知りたくもない。だが、 それがお前の…芸術へのささやかな報いになるなら、それでいいさ。";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "それが本当のお前か、カッカッ……俺と同じ、いや、それ以下だな。";
			link.l1 = "もういい。ロンウェイ、そいつを起こせ！";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) ReturnOfficer_Longway();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "俺たちの船……まさかこんなに嬉しく思うなんて……でしょ？\nやっと、この悪夢も終わったんだ。";
				}
				else
				{
					dialog.text = "ついに終わったな。これからどこへ行く、チャールズ？";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "もう全て終わってしまったなんて信じられない……これからどうするの、私のキャプテン？";
				}
				else
				{
					dialog.text = "さて、これで終わりだよ、私のキャプテン。\nこれからどうする？";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "ああ、まだ終わっていません。チャン・シン…この物語が本当に終わるのは、私が彼女から答えを得たときだけです。";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "カプスターヴィルへ進路を取れ。\nルヴァスール旦那には、歴史の一部になってもらう時だ。";
				}
				else
				{
					link.l1 = "シュヴァリエの任務は完了した。彼に報告しなければならない。だが、いくつかの詳細は伏せておこう。\n彼が約束を守り、ミシェルが解放されることを願うばかりだ……";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "あたしも、でしょ？だから一緒に行くよ。チャールズ、言い訳なんてしないでよね。\n";
				link.l1 = "メアリー、お願いだから休んで。もう少しで倒れそうだよ……";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "ご一緒します。";
				link.l1 = "ヘレン、あの悪魔の手で死にかけたんだぞ。立つのもやっとじゃないか…";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "私はあなたが必要だ、Charles。そしてあなたも私が必要だ。今夜気絶するのは誰かって？それはChang Xingだ。あの売春宿の床で、眉間に弾丸を受けてな！\n";
				link.l1 = "ああ、ルヴァスールはお前の闘志を叩き潰せなかったな。船に戻れと言っても、どうせ俺の後をついてくるんだろう……";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "だが、俺はまだ刃を握れる。チャールズ、俺もそこにいなければならないんだ。なぜ彼女があんなことをしたのか、 知る必要がある。\nこれが俺にとってどれほど大事かわかるか？";
				link.l1 = "お休みと癒しが必要なのですね。それも、長い時間をかけて。";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "チャールズ、あんたはあたしのことよく分かってるでしょ？だから、無駄話はやめてさっさと終わらせようよ。";
				link.l1 = "好きにしろ。しかし油断するな。外にはどんな驚きが待っているか誰にも分からないからな。";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "待たせてもいいさ。あなたが私を迎えに来てくれた、だから今度は私があなたと一緒に行くよ。\nあなたが望もうが望むまいが、ね。";
				link.l1 = "まだ度胸があるようだな、ヘレン。いいだろう。俺の後ろにいろ、そして頼むから、くれぐれも気をつけてくれ。";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "俺たちの船……また乗り込めるなんて信じられない、でしょ…";
					link.l1 = "メアリー、彼女が待ってるよ。たっぷりの食事と柔らかいベッドも用意してある……";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "うっ……自分の足で船までたどり着けるとは思わなかった。";
					link.l1 = "君ほど打たれ強い人間を、俺は今まで知らなかったよ、ヘレン。さあ、中に入って、それから寝てくれ…";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "俺たちの船…また乗り込めるなんて信じられないよ、でしょ…";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "うっ……自分の足で船までたどり着けるとは思わなかった。";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "カプスターヴィルへ進路を取れ。\nルヴァスール旦那には歴史の一部になってもらう時だ。";
				}
				else
				{
					link.l1 = "シュヴァリエの任務は完了した。彼に報告しなければならない。だが、いくつかの詳細は伏せておこう。\nただ、彼が約束を守り、ミシェルが解放されることを願うばかりだ……";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "それに、チャールズ……その顔は何だ？また何か企んでいるんじゃないか？";
				link.l1 = "チャン・シン。私も彼女のもとへ行かねばなりません。";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "そしてあなたは？どこへ行くのですか？";
				link.l1 = "張星（チャン・シン）に会いに行くのです。彼女こそがこの悪夢の最後の章です。";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "じゃあ、あたしも一緒に行くよ！あの子には大きな借りがあるんだから、でしょ！？";
				link.l1 = "メアリー、君はやっとのことで船までたどり着いたんだ。\n今の君じゃ刃物もまともに握れないだろう。\nあいつが君にしたこと、必ず償わせてやる、神に誓ってな。\nでも、君が船に残って無事でいてくれたら、俺もずっと安心できるんだ。";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "私のキャプテン、あなたと一緒に行きたいの…本当に。どうか気をつけて。彼女が他に何をするか、誰にも分からないわ。あの子犬みたいなティボーが…彼女は私を押さえつけていたのよ…";
				link.l1 = "最悪の時は過ぎた、エレン。もうすぐすべて終わる、約束するよ。";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "少なくとも、私がいない間はロンウェイがあなたを守ってくれるでしょう。\nでも、もしあなたに何かあったら、私が自分の手でロンウェイもチャン・シンも地獄に叩き込むからね！";
					link.l1 = "大丈夫だよ。さあ、休んで。すぐ戻ってくるからね。";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "「チャールズ、ロンウェイはどこへ行った？」";
					link.l1 = "俺を置いてチャン・シンを追いかけて行った。止められなかった、でも俺に何ができただろうか？";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "まあ、少なくともロンウェイが一緒に行くんだな。それだけでも、少しは心強いよ。";
					link.l1 = "ほらね？心配することはないよ。すぐ戻るから。";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "「ロンウェイはどこ？今気づいたけど、ここにいない。」";
					link.l1 = "彼は俺を置いて妹のもとへ行った。\n俺は責めない。\nこの瞬間をあいつはあまりにも長く待ち続けてきたからな。";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "チャールズ、俺は嫌な予感がする……";
				link.l1 = "わかっている。この悪夢はあまりにも長く続いたが、終わりが近い。最悪の時はもう過ぎた。";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "あいつが何を考えているかなんて、誰にも分からないよ、Charles。油断しないで、でしょ？";
				link.l1 = "わかった。すぐ戻るよ、ヘレン。"
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "何があっても備えると約束してください。";
			link.l1 = "私はそうだし、これからもそうでいる。すぐ戻るよ、Mary。";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "ロンウェイが手伝った、マイロードキャプテン。今度はあなたが約束を守る番です。";
			link.l1 = "すべて聞いていたな、ロンウェイ。さあ、お前の妹に会いに行こう。";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "旦那船長、ロンウェイから最後の願いがあります。チャン・シンに自分の言い分を話させてください。\n決断を下す前に、彼女の話を最後まで聞いてください。";
			link.l1 = "何が起こった " + sStr + " 彼女にかかっている。しかし、まずは彼女に説明する機会を与えるつもりだ。";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "ロンウェイはあなたの言葉と判断、そしてご親切を信じております。";
			link.l1 = "相棒、この血まみれの惨状に理性や優しさの入り込む余地はねえ。もう終わらせる時だ。";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "旦那船長……";
				link.l1 = + sStr + " 死んでいる。";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "船長、姐さん " + sStr + "、お会いできて光栄です。こちらは…チャン・シンです。";
					link.l1 = "察しがついたぞ、ロンウェイ。下がれ。お前は妹と話す時間を十分にもらっただろう。今度は彼女が答える番だ\n " + sStr + " ルヴァスールの手下が彼女を誘拐するのを手伝ったことで。";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "来たか……ご婦人はどこだ " + sStr + "？彼女は……？";
					link.l1 = "いいえ、ロンウェイ。神に感謝します、違います。私は彼女を船に連れて行きました。そうでなければ、 今こうして話していることすらできなかったでしょう。しかし、それでも簡単でも楽しいことでもありません。";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "チャン・シンと私からお悔やみを申し上げます…";
			link.l1 = "張興からの弔意だと！？ロングウェイ、お前がルヴァスールの名で弔意を述べるのと同じだろう！ あいつが誘拐に加担していたことはお前もよく知っているはずだ " + sStr + " 他の手下どもと一緒に！そして今、彼女はいなくなった……！";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "私…いや、私には今、あなたがどんなお気持ちか分かります、My Lord Captain。";
			link.l1 = "「本当ですか？」";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "ご存じの通り、私は両親を失いました。覚えていれば、ですが。しかも、拷問して殺したのは張興ではありませんでした。  " + sStr + "……あなたの苦しみも、怒りも、私には分かります。しかし、私の妹の罪は、あなたが考えるほど重くはありません。どうか、 私の話を聞いてください。";
			link.l1 = "覚えている。話を聞こう。だが手短にしろ！そして、こんなことを見逃すわけにはいかないと知れ！";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "それでは、もう一度すべてお話ししたほうがよさそうですね、ド・モール旦那。私たちのトゥはフランス語がひどくて、 もう少しであなたに襲われるところでした。";
			link.l1 = "黙っていればよかったんだ。俺はロングウェイを襲うつもりはなかったが、お前は……お前こそが彼女の死の責任者だ。";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "それには反論したいところだが、やめておくことにする。トゥはあなたのことを尊敬と理解のある人物だと言っていた。 だが本当にそうなのか？私が話し始める意味はあるのか？それとも、もう心は決まっているのか？";
			link.l1 = "あなたは人の心に入り込む術を知っているな、マドモワゼル。\n今さら議論する価値はない。\nだが、どうしても自分を正当化したいなら……まあ、好きにするがいい。\nロンウェイのために、話くらいは聞いてやろう。";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "彼女がすべてを説明できます、ロードキャプテン…。あなたが思っているようなことじゃありません…本当に…";
			link.l1 = "それなら説明してみろ。しかし、俺にはするな。 " + sStr + "。彼女の目を見ろ。彼女の痣や傷を見ろ。それでも「そんなことはなかった」と彼女に言ってみろ。";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "シンの代わりにお詫び申し上げます、船長…";
			link.l1 = "その嘲笑う顔を見る限り、あなたの謝罪は無駄でしょう。彼女に謝る価値はありません。";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "ムッシュ・ド・モール、あなたは彼に厳しすぎますよ。もっとも、あなたは彼をそう扱うのに慣れているのでしょう――典型的な黄色い肌の労働者のように。";
			link.l1 = "ロンウェイを俺に反抗させようとしているのか？無駄だよ。俺はずっと彼を敬意をもって扱ってきたし、 それは彼も分かっている。それだけで十分だ。今やお前に残されたのは、そうやって駆け引きすることだけだろう。";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "どうしたいんだ？かわいそうなトゥを家族から引き離すつもりか？十年ぶりにやっと家族を見つけたばかりなのに？";
			link.l1 = "血がつながっているからといって、家族とは限らない。しかし、どうすればいいとお考えですか？あなたがしたことを… " + sStr + " 罰を受けずに済むのか？それにロングウェイが、何のためらいもなく他の娘たちを売り飛ばす女のもとに時々 通うことになるのか？";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "まずは、聞いてくれ。あいつと違って、俺はさっきあいつに話したことを完璧なフランス語で語り直せるんだ。 俺の物語をな。君の目を、あるいは彼女の目をまっすぐ見つめながら。それも、 君がもううんざりしてるであろう訛りなしでな。結局のところ、俺たち全員、失うものなんて何もないだろう？";
			link.l1 = "私はロングウェイの訛りには慣れているよ。それも彼の一部だと思っているから。君の話も聞くけど、 それは友人のためだけだ。続けて。";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "なぜいけませんか、My Lord Captain…？";
			link.l1 = "本当に聞く必要があるのか？彼女は誘拐に関わっていたんだ " + sStr + "、彼女だったのでは？";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "……心よりお詫び申し上げます。\n十年前、妹を救えなかったのも、こんな目に遭わせてしまったのも、私の責任でございます。";
			link.l1 = "後悔のかけらもない者たちのために謝る必要はないぞ、ロンウェイ。\nここはもう終わったか？今度は私が彼女と話す番だ。";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "旦那船長、待ってください！張興はルヴァスールとは違います。全く同じではありません。 彼女はこの十年の人生を私に話してくれるでしょう。私にも話させてください。";
			link.l1 = "わかった、ロンウェイ。聞こう。お前の話次第で、色々と決まるんだ。";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "もしあなたが話すなら、みんな頭が痛くなるよ。失礼する、トゥ。シャルル・ド・モール殿で間違いないかな？";
			link.l1 = "そうか。お前がベル・エトワール、別名チャン・シンだな。ティボーやマルテンと一緒に、 俺の愛しい人を誘拐した張本人だ。俺がその話をすると、お前は笑うんだな。楽しい思い出か？";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "否定しても無駄よ。\nでも、それが今さら何？\n私の兄の目の前で拷問でもするつもり？それとも兄に手伝わせて私を痛めつける？\nそれとも、ただ殺すだけ？\n本当にそんなこと、兄にさせるの？";
			link.l1 = "言っただろう、今すぐにでもやりたいことが山ほどあるが、まだお前と話しているんだ。調子に乗るな。 さっきあいつに言ったことをもう一度言え。\nそれからどうなるか、みんなで見てみようじゃないか。";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "私はまだチャン・シンが……こんなものになってしまうなんて信じられません。";
				link.l1 = "人は変わるものだ、ロンウェイ。誰だって壊れるし、最後の優しさや信じる心さえも削り取られてしまうことがあるんだ。 ";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "ロングウェイは、いまだに妹がこんなものに変わってしまったことを信じられません。なぜ……なぜなんだ？あの日、もし俺が家にいたなら……";
				link.l1 = "「もしも」を考えて自分を責めるな。\nそれに、あんたは何年も何もしなかったわけじゃない――必死に状況を変えようとしたじゃないか。";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "ええ…そういうものなんでしょうね、My Lord Captain。";
			link.l1 = "ここを出ましょう。彼女が残した後始末を片付けて、まだ救わなければならない者がいる\n " + sStr + " できるだけ早く。";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "ああ。急がなきゃならねえ――俺のせいで、もうずいぶん遅れちまったからな。";
			link.l1 = "お前のせいじゃない、ロンウェイ。急ごう！";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "そうです。ご支援、感謝いたします、我が主君キャプテン。";
			link.l1 = "気にするな。そもそも、あの女はお前の献身に値しなかった――自分からお前を探そうともしなかったんだ、できたはずなのに。お前の星はとっくに消えているし、 あいつはずいぶん前からお前の家族じゃなくなっていた。今や俺たちが、お前の家族だ、ロンウェイ。";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "ああ……そうだな。俺は今までずっと、それに気づけなかった。";
			link.l1 = "遅くなっても来ないよりはましだ。さあ、帰ろう——俺たちの船が待っているぞ。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "わかった。どれだけこれを望んでいたか、あなたには分からないでしょ？";
			link.l1 = "そう思うよ。調子はどうだい、Mary？流血を避けたかった理由は、君がいつも通りしっかりと剣を握れるか確信が持てなかったからだ――俺が別の相手とやり合っている間に、誰かが優位に立つかもしれなかったからな。";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "私のこと、甘く見てるんじゃない？それに、怒りって最高の薬だよ。あなたが私を助けに飛び込んでくるって、 疑いもしなかった、でしょ。いつもそうだもんね。ねえ、Charles…あなたは私の「赤いお守り」って呼ぶけど、もしかして、あなたも私のお守りなのかも？一緒にいると、 いつも何かすごいことが起きるんだ、でしょ？";
			link.l1 = "俺があんたのお守り？ほう、それは気に入ったな。";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "ほら、もう笑ってるじゃない！さあ、こんな汚い場所から早く出よう、急いで、急いで、でしょ？";
			link.l1 = "えへへ、この騒ぎは俺にとってきつかったな。ほかの結末があればよかったのに。";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "俺は違う。彼女はもう救えなかったんだ、チャールズ。しかも彼女はロングウェイまで道連れにした。 ロングウェイは自分で選んだんだ、そして俺たちには他に道はなかった。今日俺たちが救った人々のことを思い出せよ。";
			link.l1 = "またしても、君に反論することは何もないよ、Mary。今回は、反論したい気持ちすらないんだ。さあ、おいで、俺の赤いお守りよ……";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "何があったんですか、旦那？罵声や叫び声が聞こえました。でも終わるまで、怖くて助けを呼ぶこともできませんでした。 ";
				link.l1 = "まさにその通りだ。あなたたちの女主人は死んだ。もう自由だ。もし俺があんたたちの立場なら、 この店の金庫を集めて山分けし、できるだけ早くこの島から逃げるだろう。あんたたちはただの娼婦じゃなく、 誇り高きご婦人方だと知っている。この惨めな場所を出ても、きっと未来があるさ。";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "ああ、あなたでしたか、旦那。女主人がいつ降りてくるかご存知ですか？";
				link.l1 = "すぐには戻らないさ。それに、俺ならその扉から離れておくぜ。今夜のことを彼女に話すのもやめておけ――何も話さないだろうし、詮索好きな猫は一瞬で命を落とすもんだ。どうやらあんたの奥方は、 自分の秘密を探られるのが大嫌いらしいな。";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "彼女を殺したのか！？";
			link.l1 = "俺がやった。もしここでぐずぐずしたり、衛兵を呼ぼうとしたら、それがあんたたちの最大の過ちになるぜ。 あの女は決してあんたたちの守護聖人なんかじゃなかった――どれだけ絹や教育を与えられても、あんたたちはここに閉じ込められ、 あの女が指差すどんな下衆にも身を差し出すことを強いられてきたんだ。ここから無事に出られるよう、幸運を祈るよ。 じゃあな、淑女たち。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "彼女は本当に無事なのか？中に入ってもいいのか？衛兵を呼ぶ必要があるのか？";
			link.l1 = "彼女が元通りになることは決してない。\n自分で彼女に聞いてみるといい……命が惜しくなければな。\n彼女はまだ兄と話している。\n邪魔をすれば、きっと二人とも喜ばないだろう。";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "そうか……まあ、またいつか私たちに会いに来てください、旦那。";
			link.l1 = "決して。ごきげんよう、淑女の皆さん。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "止まれ！マドモアゼル・エトワールの屋敷から叫び声と争いがあったと報告があった。 衛兵はお前が関与していると考えている。武器を渡して我々について来い、旦那。";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "確かに、でも俺たちが喧嘩を始めたわけじゃねえ、終わらせただけだ。雇われたチンピラどもが報酬の遅れに逆上して、 エトワール女将を襲って金を奪おうとしたんだ。傭兵なんて信用できるかよ、な？俺たちは勝ったが、 残念ながら彼女は生き残れなかった。";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "今日は人生の最愛の人を失ったんだ、だから通してくれ、役人。";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "あなたの言葉だけを信じるわけにはいかないのは分かっているだろう？\n拘束しなければならない。そして、女性従業員の中から証人が必要だ。\n彼女たちが何を言うか、聞かせてもらおう。";
			link.l1 = "俺の大切な人がひどく傷ついてるんだ。俺ももうくたくただ。頼むから、俺たちを行かせてくれないか？";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "できるだけ早くこの問題を解決しよう。\nさあ、俺たちについて来い。";
			link.l1 = "地獄へ行け…";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "お悔やみ申し上げます、旦那。それに、私はまだ士官じゃありませんが……まあ、とにかく気にしないでください。ご一緒に来て、そこで何があったのか教えていただけますか？";
			link.l1 = "話そう。娼館は金を失っていて、傭兵たちに払う現金も残っていなかった。だから、 あいつらは残り物を奪うことにしたんだ。ちょうど俺がそこにいた時にな。\nマダム・エトワールと俺は奴らと戦ったが、彼女は傷がもとで死んだ。\nさあ、もう通してくれ。";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "やりたいのですが、書類の手続きが山ほどありますし、そこで働いている女性たちにも話を聞かねばなりません。\nたとえあなたが本当のことを言っていたとしても、少なくとも一日は町に滞在してもらう必要があります、旦那。";
			link.l1 = "地獄へ行け…";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "ロンウェイがあなたに渡すものがあるそうです、旦那船長。";
			link.l1 = "なんて美しくて不思議なんだろう。こんなの見たことがないよ。これは何？";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "それは我が故郷の船長のお守りです。そして、ロンウェイはもう船長ではありませんから、あなたに差し上げます。";
			link.l1 = "ありがとう、ロンウェイ。ファン・デル・ヴィンクが死んだことで、お前が望んだ復讐はすべて果たされたな。 すべてがこうして終わって本当に良かったよ。";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "もしシンをもう一度善い人間に戻すよう説得できたなら……";
			link.l1 = "彼女はもう誰の言葉にも耳を貸そうとしなかった、兄である俺の言葉さえも。\nあなたはできる限りのことをした。俺たち皆そうだった。";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "ああ……本当にありがとうございます、My Lord Captain。ロンウェイは自由になり、再び家と仲間を持てるのです。";
			link.l1 = "どういたしまして、友よ。さて、今度は私と一緒に私の兄に会いに行かないか。ああ、なんという皮肉だ！";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			ReturnOfficer_Longway();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "また会ったな、フランソワ。人生にずいぶん揉まれたようだな、へへ。";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "ポワンシー、この強欲な野郎め……金で溢れかえった金庫に喉を詰まらせそうになっても、まだ足りねえのか？";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "フランソワ、お前にも少し分けてやるよ。十分にあるから、信じてくれ。";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "「な…何のことだ？」";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "総督閣下、あなたはこれから……";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "チャールズ、友よ、君は自分の役目を見事に果たした！この男にこれから何が起きるかは、君が気にすることではない……だが、念のために知っておいたほうがいい、船長。君の賢い頭がいつか愚かな考えを起こさぬようにな。いわば、我々 の共通の友人にはひどい消化不良が待っている。金は胃に良くないと聞く……これ以上説明はいらないだろう。";
			link.l1 = "いいえ、総督。";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "フランソワ旦那とは違って、シャルル、あなたには素晴らしい未来が待っているよ。\n野郎ども、あの豚を牢屋にぶち込め！";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "手を出すな、このクソ野郎ども！満足か、ド・モール？！くたばれ！ お前らも俺と同じ地獄のフライパンで焼かれるんだぞ！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "さて、旦那。私はお嬢様を調べました " + sStr + "...";
			link.l1 = "レイモンド、どれほどひどい状況なんだ？";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "ご心配なく、船長。もちろんMaryはひどく傷つきましたが、全体的には大丈夫です。数日間は寝ていなければなりませんが、 二週間もすればまた元気に動けるでしょう。";
					link.l1 = "なるほど。ありがとう、レイモンド。下がっていい。";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "メアリーはひどくやられました、船長。打撲に切り傷……それに何より、すべての衝撃が彼女を襲っています――もちろん、彼女はそれを隠そうとしていますが。";
					link.l1 = "彼女はいつも通り強がっている。しかし今は安静にしていた方がいいと、さすがに自覚していると思う。\nだが、それがいつまで続くか……";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "どんな職業軍人でも、彼女が経験したことを生き延びるのは難しいでしょう、船長。捻挫、筋違い、打撲――あの野郎どもが骨を折らなかったのは不幸中の幸いです。\nですが腱は傷んでいますから、少なくとも一ヶ月は剣を振るうことはできません。";
					link.l1 = "刃なんてどうでもいい。彼女はいつ自分の足で立てるようになるんだ？";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "ご心配なく、船長。ヘレンは怪我をしていますが、重傷ではありません。今はしばらく寝ていなければなりませんが、 二週間もすれば完全に回復すると思います。";
					link.l1 = "なるほど。ありがとう、レイモンド。下がっていい。";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "かなりひどい目に遭いましたよ、船長。それに、肉体的な傷は診断の一部に過ぎません……あの恐ろしい場所にいたことで、彼女はアルブトゥス号で体験した悪夢を思い出したのです。";
					link.l1 = "もちろん…くそっ！彼女はいつになったらまた立ち上がれるんだ？";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "ヘレンは剃刀の刃の上を歩いていたのです、船長。あれほどのことを経験して、よく生き延びたものだと驚いています。 内臓の裂傷や骨折はありませんが、捻挫や筋の損傷は多く見られます。";
					link.l1 = "お気の毒に。彼女の回復にはどれくらいかかるのでしょうか？";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "少なくとも一週間はかかります、旦那。\n私の指示に従えば、一ヶ月ほどでまた動けるようになるはずです。";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "「あと半月は無理です、旦那。その後なら、四分甲板で少し歩かせてもよいでしょう。 完全に回復するには少なくとも二ヶ月はかかります。」";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "少なくとも一週間は彼女に構うな、旦那。これは俺からの忠告だ。本当に回復するには一ヶ月ほどかかるぞ。";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "彼女は二週間は寝ていなければなりません。その後で、甲板を歩けるようになるかもしれません。\nですが、少なくとも二ヶ月は戦線復帰を期待しないでください。";
				}
			}
			link.l1 = "なるほど。ありがとう、レイモンド。下がっていい。";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "こんなに長く横になってた後で自分の足で立つのは、思ったよりずっと大変だね、でしょ！";
				link.l1 = "急に安静をやめないほうがいいんじゃない、あなた。";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "ああ……頭が……";
				link.l1 = "ヘレン！ちょっと早起きしすぎじゃないか？立つのもやっとだろう！";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "俺はもう二度とこの血塗られた寝床に横になりたくねえ——せめて船首から船尾まで歩いてからじゃないとな！";
				link.l1 = "快適でいいベッドだね。それに、この船も悪くないよ。だから、止めたりはしない。でも、 あなたが馬鹿なことをしないように、私はちゃんと見張ってるからね。";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "大丈夫です、船長。ただ、完全ではありません。まだ剣を振る準備はできていませんが、 このベッドが心の底から憎いのです。";
				link.l1 = "まあ、甲板を少し歩くくらいなら大丈夫だろう。\nだが、ロープの近くには絶対に近づくなよ！";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "チャールズ、私のことすっかり忘れちゃったんじゃない？最後に一緒に寝たの、いつだったか思い出してよ、でしょ！";
				link.l1 = "「その前に…その話はやめておこうか、Mary？」";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "私のキャプテン、私はもう女としてあなたの興味を引かなくなったのですか？";
				link.l1 = "それは意外だな、ヘレン。普段は俺がそういう話を切り出す役なんだが……でも、お前があの後で準備できているかどうか、俺には自信がなかったんだ……";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "じゃあ、せめてあたしのことでも話してよ、でしょ？それとも、あの二人のクズに殴られてから、 あたしのこと嫌いになっちゃった？";
				link.l1 = "俺が今まで聞いた中で一番馬鹿げた話だぜ。お前が準備できるまで邪魔したくなかっただけだ。で、今はもう……";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "大丈夫よ、Charles、本当に。私はあまり考えないようにしてるの。\nそれに、あなたが一番ひどい目から私を救ってくれたんだから。\nだからもう話すのはやめて……ただ、久しぶりにゆっくりしましょう。";
				link.l1 = "それは実にいい考えだな、ヘレン。";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "「チャールズ、俺はそれが欲しいんじゃない、要求してるんだ、でしょ！」";
				link.l1 = "あなたに逆らうなんて、私にはとてもできません……";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "チャールズ、話があるんだ、でしょ。";
				link.l1 = "どうしたんだ、Mary？なんだか不安そうな顔をしているな、普段そういう時はあまり良いことが起きないんだよな。";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "私のキャプテン、お話ししなければならないことがあります。";
				link.l1 = "そうなのか、エレン？聞いているぞ。";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "それがまさにそうなんだ！私が士官としての任務に戻る準備ができているのは、良いことじゃないか？";
				link.l1 = "そういうことか。まあ、自信があるなら、それは良いどころか、素晴らしいことだ。";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "乗組員たちが私を弱々しい年寄り女みたいにじろじろ見るのはもううんざりよ。早く舵を握って、 剣の稽古で腕を伸ばしたいわ…";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "もしやる気があるなら、私は反対しないわ、あなた。装備を持ってくるね。それに、喜んで舵も任せるわ。でも、 戦いでは気をつけて、でしょ？";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "ヘレン、艦橋では君のことが恋しかったよ。さて、その剣だけど、そろそろ君に返す時だと思う。";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "もちろんです、私のキャプテン。おっしゃる通りにします。";
			link.l1 = "「よろしい。」";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "素敵、でしょ！早く剣の稽古がしたくてたまらないよ…";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "それは良かった、Mary。でも、まだ無茶はしないでくれ……まあ、君に言っても無駄か。";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "そのパラッシュが鞘に戻るのを見て、お喜びになるのでしょう、My Lord Captain…";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "俺……俺には何と言えばいいのかわからない、Charles。今になってやっと、このカトラスが自分にとってどれほど大切か気づいたんだ……";
				link.l1 = "私はそれをずっと前から知っていました、だからこそ、あなたのために無事に待っていたのです。";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "私のイッカク、でしょ！！！チャールズ、あなたが助けてくれたのね！うれしいなんてもんじゃないよ、最高にハッピー！ ありがとう、ありがとう！マーティンの船に置き去りにされたんじゃないかって、すごく怖かったんだから…";
				link.l1 = "この刃はお前の手にあるべきだ、俺の赤いお守り。もう二度と失くすなよ……さて、お前たちの再会の邪魔はしないさ、ははっ！";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "ありがとう、Charles。ねえ、それがきっと私があなたを愛している理由なのよ……";
				link.l1 = "失われたものを取り戻すために？ははははは…";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "お前は笑っているが、俺は本気だ。";
			link.l1 = "分かってるよ、エレン。僕も君を愛してる、でもまだその理由は自分でもよく分からないんだ。";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "まだこのカットラスをお前に使っていないからかもしれないな。";
			link.l1 = "俺はボートの方へ行って自分を守るぜ。そこで待ってるからな、ヘレン。";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 