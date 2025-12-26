void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Captain","Lady")+"！お願いだ、助けてくれ！頼む、俺を守ってくれ！","助けて！ "+GetSexPhrase("Stranger","お嬢さん")+"「助けてくれ、頼む！」");
			link.l1 = LinkRandPhrase("何があった？","「何が起きてるんだ？」",RandPhraseSimple("「どうしたんだ？」","「何が起きてるんだ？」"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("船長！船長","娘っ子！娘っ子")+"、お願いだから待ってくれ！","「待て、」 "+GetSexPhrase("Captain","お嬢さん")+"！お願いだ。");
			link.l1 = LinkRandPhrase("「何があった？」","どうした？",RandPhraseSimple("「どうしたんだ？」","「何が起きてるんだ？」"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "「ああ、m」"+GetSexPhrase("「ister」","「iss」")+"！お願いです、かわいそうなあたしを助けてください、お願いします！あの人たち、 あたしにひどいことをしようとしてるんです！";
			link.l1 = LinkRandPhrase("「何があった？」","どうした？",RandPhraseSimple("「どうしたんだ？」","「何が起きてるんだ？」"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("こいつらが私を犯そうとしてるの！お願い、どうか止めて！","お願いだ、神よ、こんな化け物どもから俺を守ってくれ！あいつら、俺の名誉を汚すつもりだ！");
			link.l1 = "慌てるな"+GetSexPhrase("、美女","")+"。ここで何があったんだ？";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("「強姦魔たちが私を追いかけてくる！」"+GetSexPhrase(" 「淑女の名誉を守ってくれるか？」","")+"","「船長、」 "+GetSexPhrase("男になれ","「お前も女だろ」")+" 娘を恥から救ってやらねえのか！");
			link.l1 = "慌てるな"+GetSexPhrase("、美女","")+"。ここで何があったんだ？";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "奴らが俺を追いかけてくる！盗賊どもだ！あいつらに俺を放っておけって言ってくれ！";
			link.l1 = "慌てるな"+GetSexPhrase("、美女よ","")+"。ここで何があったんだ？";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("助けて！助けてくれ！追いかけられてるんだ！助けてくれ！","ああっ！助けてくれ、 "+GetSexPhrase("見知らぬ者","お嬢さん")+"「助けてくれ！こいつら悪党から俺を救ってくれ！」","情けをかけて、この悪党どもから私をお守りください！お願いします！");
			Link.l1 = LinkRandPhrase("「何が起きてるんだ？」","どうした？","「何があった？」");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("奴ら…奴らが私を犯そうとしてる！お願いだから、どうか止めて！頼む！","こいつら……何か恐ろしいことを企んでいる……お願いだ、奴らから私を守ってくれ！","我らが主の御名において、どうかこの欲望に満ちた獣どもから私をお救いください！ 彼らは私の名誉を汚そうとしているのです！");
			Link.l1 = "それじゃあ、全部はっきりさせようぜ。";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("ありがとうございます。 "+GetSexPhrase("Captain","お嬢さん")+"……とても怖かった！","助けてくれてありがとう！本当に感謝しているよ！");
					link.l1 = "「よし、」 "+GetSexPhrase("美しさ","親愛なる")+"落ち着け、もう過ぎたことだ。";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "「ああ、ありがとう」 "+GetSexPhrase("「貴族の方！あなたは本物の紳士です！」","お嬢様！助けてくださってありがとうございます！")+"";
					link.l1 = "他にどうしようもなかったんだ。";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "「ああ、ありがとう」 "+GetSexPhrase("貴族の方！あなたは本物の紳士です！","見知らぬ人よ！助けてくれてありがとう！")+"";
					link.l1 = "他にどうしようもなかったんだ。";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "お前は何をしたんだ？なぜあいつらを殺したんだ！？これで今度は俺を探しに来るじゃねえか！神よ、 俺が何をしたっていうんだ！";
					link.l1 = "「これが感謝ってやつかよ！」";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "「何をしたんだ、」 "+GetSexPhrase("船長","お嬢さん")+"？！なぜ彼らを殺したの？実は父が送り込んだ人たちだったのに……ああ、今度はきっと父に殺されるわ……";
				link.l1 = "それは驚きだぜ！で、どういうつもりで「盗賊に追われてる！」なんて叫んだんだ！？";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "少しばかりですがお金があります。どうか感謝の印として受け取ってください。これから皆に伝えます。 "+GetSexPhrase("なんて立派で高貴な方なんでしょう","なんて立派で気高い女性なんだ")+".";
			link.l1 = "もちろんだろう。ありがとう……さあ、もう帰りな。";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "まだ気持ちが落ち着かないんだ。どうか持ってきてくれないか "+GetSexPhrase("貴婦人","俺")+" 「入植地」へ "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"？なあ、今じゃ茂みの陰にはどこにでも強姦魔が隠れてるような気がしてきたぜ。";
			link.l1 = RandPhraseSimple("そんなに心配するなって、本当に……よし、行こうぜ。","お前は本当に臆病者だな、そうじゃねえか？\nよし、俺がそこまで連れてってやるよ。");
			link.l1.go = "Node_121Next";
			link.l2 = "ごめんなさいね、あなた。でも、どうしても時間がないの。とても忙しいのよ。";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "奴らを脅して追い払ってくれるだけだと思ってたのに！今すぐ私をその居住地の酒場まで連れて行きなさい "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"、他に頼れるのはあなただけなんだ。";
			link.l1 = "「くそっ！よし、行くぞ。ただし、遅れるんじゃねえぞ。」";
			link.l1.go = "Node_122Next";
			link.l2 = "「いや、それだけだ」 "+GetSexPhrase("美しさ","親愛なる")+"！今日はもう驚きはたくさんだ。他の奴に頼んでくれ。";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "「じゃあ、私はどうすればよかったの？！父は私に高利貸しの息子――あの腑抜けと結婚させたがってるのよ…あいつの親父が金庫に財産を持ってるってだけで！でも、私が愛してるのは別の人なの！お願い、 あの人のもとへ連れて行って…」";
			link.l1 = "なんて厄介な奴だ！まあ、仕方ねえ、行くぞ。今さらここに置いていけるわけねえだろ？…お前の相手の名前は何だ、どこに連れていけばいいんだ？";
			link.l1.go = "Node_32";
			link.l2 = "いや、それだけだ。 "+GetSexPhrase("美しさ","親愛なる")+"！今日はもう驚きは十分だ。他の誰かに頼んでくれ。";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "彼の名前は "+pchar.GenQuest.EncGirl.sLoverId+"「今は新参者だ。今は の居住地に滞在している」 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"、そこで仕事を探そうとしたが、今は厳しい時代だ。みんなが危機だ危機だと言っている……それに、もう俺は故郷に戻ることもできねえんだよ。";
			link.l1 = "危機だと？はは…本物の海賊にとっちゃ、危機ってのは地平線に交易船団が見えてるのに、 帆を膨らませる風がまったく吹いてねえ時のことさ…";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("「知ってるか、」 "+GetSexPhrase("船長","お嬢さん")+"？すごく怖かったから、まだ足が少し震えてるんだ。","ああ、ご存じですか、私はとても怖かったんです。 神様があなたを私のもとに遣わしてくださったのは本当に素晴らしいことですわ。");
			link.l1 = RandPhraseSimple("「神に感謝だ、まだ生きていてくれて。」","気にするなよ。こうなってよかったんだぜ、わかるだろ。");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("ありがとうございます。 "+GetSexPhrase("船長","お嬢さん")+"、またしても。本当に、あなたには大変お世話になりました。","「本当にありがとうございます。」 "+GetSexPhrase("船長","お嬢さん")+"。あなたの助けがなければ、俺はどうしていいかわからなかったぜ。");
			link.l1 = RandPhraseSimple("それが教訓になるだろう。よし、幸運を祈る…","次はもっと気をつけるんだな……さあ、家に帰りな。俺にはやることがあるんだ。");
			link.l1.go = "Node_1End";
			link.l2 = "どうしてそんなに不注意なんだ？なぜ一人でジャングルに入ったんだ？";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("気が変わったのか？","船長、考えを改めてくださって素晴らしいです！");
			link.l1 = RandPhraseSimple("いやいや、あたしは遠慮しておくわ。","…無駄な期待はするな…");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "きっと笑われるかもしれませんが……実は恋の媚薬の材料を集めていたんです……。ある魔女が、心の悩みに効く根っこがあると教えてくれたんです。";
						link.l1 = "なんてこった！何が "+GetSexPhrase("この女たちは何を考えているんだ","考えていたのか")+"！？どうやら、かなり集めたようだな。お前を追いかける求婚者が大勢いて、全部追い払うのは大変だったぜ。ハハハハ……じゃあな。";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "ちょっと散歩に出て薬草を集めたり、新鮮な空気を吸ったりしていただけなんだ。\nどうやら、散歩には最悪のタイミングだったみたいだな。";
						link.l1 = "なんて不注意なんだ！間一髪で俺が来てよかったぜ。まあ、幸運を祈るぜ。";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "ご主人様が散歩中に、このあたりで首飾りの真珠を落とされたんです。家に戻られたとき、私を怒鳴りつけて 「全部見つけるまで戻ってくるな！」と命じられました。でも、正確な場所なんて分かりませんし、 こんなに草が生い茂っている中でどうやって探せばいいんでしょう？真珠はとても小さいし……だから、どうしたらいいのか全然分からなくて、ただここをうろうろしているだけなんです……";
					link.l1 = "それで、どんな首飾りだったんだ？ジャングルをさまようより、新しいのを買ったほうが早いんじゃねえか？ お前の旦那様は真珠をいくつなくしたんだ？";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "亡き父が地図を遺してくれたんだが、父の仲間たちはそれを俺から奪おうとした。父が生きていた頃は、 みんな父の前で震え上がっていたくせに、俺が父を埋葬した途端、厄介な時代が始まった。 最初はこの地図を買い取ろうとしてきたが、俺が断ったら、今度は脅しにかかってきたんだ。";
					link.l1 = "「じゃあ、なぜそれをただ売らなかったんだ？その地図の何がそんなに特別で、海賊どもが探し回ってるんだ？」";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "あの首飾りは選び抜かれた真珠で作られていたんだ、そんなものは安くは手に入らねえ。あれには "+sti(pchar.GenQuest.EncGirl.BigCoins)+" 大きな真珠や "+sti(pchar.GenQuest.EncGirl.SmallCoins)+" 小粒のものさ。もしその真珠が見つかれば、あのネックレスのようなものをもう一つ作らせることもできるだろう。";
			link.l1 = "きっとこれは簡単な仕事じゃねえだろうな……まあ、ご主人様に命令されたんなら、仕方ねえさ。真珠を探してみな。幸運を祈るぜ。";
			link.l1.go = "Node_131End";
			link.l2 = "無駄だぜ。この深い草むらで真珠を探すなんて、干し草の山から針を見つける方がまだ簡単だ。\nましてや、お前は真珠をなくした場所すら知らねえんだろう……";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "父がその地図に財宝を隠した場所を記してくれたんだ。あの有名な海賊のことを聞いたことがあるか？ "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_VOC)+"?";
			link.l1 = "いや、そんな奴は聞いたことねえな。";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "「さて、」 "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_NOM)+" 俺の親父だった。みんな親父を恐れていて、誰も一言も口にできなかった。今じゃやつらも図々しくなったもんだ。 俺が地図を売るのを断ったら、自分たちも宝の分け前をもらう権利があるって言い出しやがった。 地図を隠そうとしたんだが、それでも結局見つけ出されちまったんだよ…";
			link.l1 = "そもそも、なぜ隠す必要があったんだ？船を雇って行き、自分の財宝を手に入れればいいじゃねえか。 お前の父親が理由もなくそれを隠すはずがねえ。";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "言うは易く行うは難しだよ。船を雇う金もないし……それに、怖いんだ……どうやって全部掘り出して、船まで運ぶんだよ……その後、宝をどこへ持っていけばいいんだ？途中で誰かに簡単に獲物にされちまうじゃねえか……";
			link.l1 = "なるほどな……よし、それじゃあ地図を隠してこい。ただし、ちゃんといい場所に置くんだぞ。";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "ふむ……それはたしかにそうだな。だからこそ、お前はそれを売るべきだったんだぜ。";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "仲間を探そうとしたことはあるか？";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "こんな機会を逃すなんて悔しいよ……親父があそこに隠した財宝の話をしてくれたんだ。あんな大金、誰も俺には払ってくれやしない……";
			link.l1 = "まあ、安売りしすぎるなよ。それに、金は命ほどの価値はねえんだぜ。ましてや、 これはお前にとっちゃ一番楽な方法だろう――金を受け取って、全部の厄介ごとから足を洗えるんだからな……";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "それは魅力的な話だな……で、俺にいくら払ってくれるんだ？";
			link.l1 = "それがそれ以上の価値があるとは思えない "+sti(pchar.GenQuest.EncGirl.mapPrice)+" ペソ。";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "へっ、女でいるのは楽じゃないよ……まあ、わかったよ。やっとこの悪夢も終わるんだね……たぶん、この地図はあんたのものになった方がいいんだろうね。"+GetSexPhrase(" 高貴な紳士","")+"、あの悪党どもよりもな。";
				link.l1 = "よし。ほら、金だ……一度に全部使い果たすなよ。";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "「いいや」 "+GetSexPhrase("船長","お嬢さん")+"。私はそれを売らないわ。良い男と結婚して、それから一緒に宝を手に入れるのよ。";
				link.l1 = "さて、それはお前が決めることだ。どうせその紙切れも、もう価値はねえよ。";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap, "");
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "「で、どこでそいつらを見つければいいんだ？若い連中は信用ならねえし、お宝より他のことに夢中だ。 年寄り連中はもっと怖い、みんな親父の仲間を思い出させるんだよ。ずる賢くて裏切り者ばかりで、 何をしでかすか分かったもんじゃねえ。」";
			link.l1 = "ハハハ……よし、でも俺も連れてってくれるのか？";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "お前か？お前が行くのか？だが、その後は俺をここ、入植地まで連れ戻さなきゃならねえぞ "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"、いいな？";
			link.l1 = "わかった、約束する。道を教えてくれ。";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "財宝はの洞窟に隠されている "+XI_ConvertString(pchar.GenQuest.EncGirl.islandId+"Acc")+"、俺たちは上陸しなきゃならねえ場所は "+XI_ConvertString(pchar.GenQuest.EncGirl.shoreId+"Gen")+"…俺が姿を見せる場所だ…だが忘れるな、報酬は半分しかやらねえぞ！";
			link.l1 = "わかった、浮気なんてしねえよ、約束する。ついて来い、遅れるんじゃねえぞ。";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "船長、今こそ洞窟を見つけなければならない。";
			link.l1 = "よし、今から見てみよう。";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "船長、洞窟を見つけなければなりません。";
			link.l1 = "よし、今見てみよう。";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "ここだ！見つけたぞ！親父が言った通りだ！山ほどの財宝だ！約束通り、半分はお前のものだ。";
			link.l1 = "ほら？そんなに難しくなかっただろう、だから怖がることなんてなかったんだ。";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "ハハハ！これで俺は金持ちだぜ！お前も今、取り分を受け取るか？";
			link.l1 = "そうだな。";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "それじゃあ、これを持っていって、それから全部の荷物を船まで運ぶのを手伝ってくれ。\nまだ私を家まで連れて帰るって約束、覚えてる？";
			link.l1 = "忘れてないさ！もちろん、連れて行くぜ。";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "金持ちになるって本当に素晴らしいわ！今はまるで別人の気分よ。"; 
			link.l1 = "あなたのことを嬉しく思うよ。";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "わかった、船長。俺の旅はこれで終わりだ。助けてくれてありがとう。";
			link.l1 = "どういたしまして……それで、新たに手に入れた財宝で何をするつもりだ？奴隷付きのプランテーションでも買うのか？";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "わからない、まだ決めていない。もしかしたらヨーロッパに移るかもしれない…";
			link.l1 = "よし、それじゃあ！幸運を祈るぜ。";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "待ってくれ……この小物は親父の宝物の中にあったんだ。俺には必要ねえが、お前なら気に入るかもしれねえ。頼む、 俺にしてくれたことへの個人的な感謝の印として受け取ってくれ。俺の取り分からだぜ、ははは！";
			link.l1 = "おったまげたぜ、こいつぁ本当に素晴らしい贈り物だ。ありがとう"+GetSexPhrase("、お嬢さん","")+"…いい婿を見つけてくれよな…";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = "しかし、どうすればいいんだ？ご主人様の命令を無視するわけにはいかない、あの方に生きたまま皮を剥がれてしまう。";
			link.l1 = "「その入植地の教会で俺を待っていろ」 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"、新しい首飾りを作るために真珠を持ってきてやるよ。";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "ほら、これを持っていけ。1万5千ペソだ。これだけあれば首飾り用の真珠を選ぶにも、新しいものを買うにも十分すぎるだろう。";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Captain","お嬢さん")+"、また会えて本当に嬉しいわ！ネックレス用の真珠は集められたかしら？","やあ、船長！真珠を持ってきてくれたか？ご存知の通り、私の奥方がかなりそわそわしているんだ……");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "はい。これがあんたの真珠だ。女主人に渡して、次はもっと気をつけるように伝えてくれ。";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "まだだ。そんなに簡単じゃねえんだよ……でも必ず連れてくるさ、待ってな。";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "「ああ、」 "+GetSexPhrase("Captain","お嬢さん")+"、あなたに出会えて本当に嬉しいです！これまでしてくださったことへの感謝の印として、 この小物と宝石を差し上げたいと思います。お役に立てば幸いです。";
			link.l1 = "おったまげたぜ！まあ、お前にも礼を言うよ"+GetSexPhrase("、美女よ","")+"……思いもしませんでした……。さようなら、お幸せに。";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "「ああ」 "+GetSexPhrase("船長","お嬢さん")+"、頼りにしているぞ。";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "「ああ、」 "+GetSexPhrase("船長","お嬢さん")+"、今日は二度も助けてくれたな。本当にありがとう。あなたの親切は決して忘れないよ。";
			link.l1 = "どういたしまして。ご主人様によろしく伝えてくれ……";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("奴らに金なんか渡すべきじゃなかったんだ。あいつらは嘘をついてたんだぜ。","奴らの言うことなんか信じるな。嘘つきどもだ。金なんか渡すんじゃなかったんだぜ。");
					link.l1 = "奴らを殺すべきだったか？";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "ああ、なんと高貴な行いだ！すぐにあなたがそうだと分かったよ "+GetSexPhrase("本物の紳士","貴婦人")+"！どうか、心からの感謝をお受け取りください。あのならず者たちの言うことを信じてはいませんよね？";
					link.l1 = "そんなことはどうでもいいさ。女の子とガキどもがジャングルでうろつくなんて、まるで当たり前のことじゃねえか…";
					link.l1.go = "Node_210";
					link.l2 = "「何を言ってるんだ、 "+GetSexPhrase("美しさ","親愛なる")+"？どうして俺がそんなことできるんだ？";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "ありがとうございます、船長。こんな不愉快な事件にあなたを巻き込んでしまい申し訳ありませんが、 他に選択肢がなかったのです。";
					link.l1 = "ふむ、君もずいぶん困っているようだな。どうしてこんなことになったんだ？";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "もしかして……これでもう奴らは俺を放っておかねえだろうな。";
				link.l1 = "おいおい、もう帰れよ。今はもう何も怖がることはねえぞ。";
				link.l1.go = "Node_200End";
				link.l2 = "おったまげたぜ！なんでそんなに男が苦手なんだ？";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "もちろん違う！だが、あいつらはどうせ俺を放っておかないんだ。俺をその入植地まで連れて行ってくれないか "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"、お願いしますか？";
				link.l1 = "家に帰れよ、あいつらはお前には手を出さねえさ。今ごろは楽に稼いだ金を使いに酒場へ向かってるはずだぜ。";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("そんなに心配するなって、本当に……よし、行こうぜ。","お前は本当に臆病者だな？まあいい、俺がそこまで連れてってやるよ。。");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "おいおい、何を言ってるんだ？俺はあいつら悪党どもをよく知ってるんだぜ。やつらは親父の昔の仲間だったんだ。 親父が財宝を隠した場所を探そうとしてるんだよ。";
			link.l1 = "「それで、お前の親父はどうしたんだ？」";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "彼はかつて海賊船の船長だった。最近亡くなったんだ……埋葬の時はみんな礼儀正しかったが、時が経つにつれて彼のことも忘れ、やがて誇りや誠実さまでも失ってしまった。\nあいつらに気づいてよかったよ。宝のありかを知られたら、俺は終わりだ。";
			link.l1 = "それは悲しい話だな。で、これからも奴らから隠れ続けるつもりか？";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "家に宝石を置いておけないの、私を守ってくれる人がいないから。だから夜になると洞窟へ行くの、 お金がなくなった時に……\nお願い、私を洞窟まで連れて行って。そしたら、あなたがあの人たちに渡したお金を返すわ……あなたが一緒なら、海賊たちも私たちを追う勇気はないと思うの。";
			link.l1 = "悪いね、坊や。でも他に用事があるんだ。お宝はまた今度にしてくれよ。";
			link.l1.go = "Node_200End";
			link.l2 = "よし、行くぞ。俺が怖くねえならな。";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "なあ、どういうわけか、俺は……";
			link.l1 = "そうか、それは良かったな。";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "船長、俺を洞窟に連れて行くって約束したじゃねえか。";
			link.l1 = "行こう……";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "よし、船長、必要な分はもう取ったぜ。これで戻れるな。";
			link.l1 = "仲間たちはいないようだな。";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "神に感謝するぜ。これ以上面倒ごとはごめんだ……ほら、この延べ棒を持っていけ……これで費用は足りるはずだ。一人で行け、俺は別の道を行く……";
			link.l1 = "よし、怖くないなら幸運を祈るぜ。";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "ふむ、 "+GetSexPhrase("船長","お嬢さん")+"、俺はあんたの皮肉が気に入らねえ。";
			link.l1 = "「もう行っていいぜ。」 "+GetSexPhrase("美しさ","親愛なる")+"。 それと、また追われる前に急いで町へ行ったほうがいいぜ。";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "私はとても動揺していました！どうかその入植地の酒場まで連れて行っていただけませんか "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"「そうでなければ、また奴らに追いかけられちまうぜ。」";
			link.l1 = "もしかしたらお前の言う通りかもしれねえ。行こう……";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "ああ、船長、それは長い話でして、あなたが興味を持つかどうかも分かりません。ですが……今となってはあなたの助けなしでは無理でしょう。どうか、この集落の酒場まで連れて行ってもらえませんか\n "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"「？あいつらがどうしても俺を放してくれなかったんだ。」";
			link.l1 = "悪いね、あんた、今はそんな暇ないんだ。やることがあるんでね。";
			link.l1.go = "Node_221";
			link.l2 = "なんでそんなに秘密主義なんだ？";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "「みんなが俺の不幸から一儲けしようとしているのに、どうして俺が秘密主義にならずにいられるんだ？」";
			link.l1 = "よし、それじゃあ…";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "船長、あんたは俺をその居住地の酒場に連れて行くって約束したじゃねえか "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("覚えている。","心配するな、俺がちゃんとそこに行くからな。");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "あそこは人が多すぎる。\n個室へ行こう。\n話したいことがあるんだ。";
					link.l1 = LinkRandPhrase("もうお前には十分すぎるほど尽くしたぜ、だからこれでお別れだ。","私の好意を悪用しないでくれよ。またな、ダーリン。","これからはお前の話なんて必要ねえ、自分で全部考えろよ。");
					link.l1.go = "Node_226";
					link.l2 = "ふむ、わかった。じゃあ酒場の主人から鍵をもらってくるぜ。";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "ご協力いただき、本当にありがとうございます、船長。決して忘れません。";
					link.l1 = "ああ、気にしなくていいよ。これからはもっと気をつけてくれ。";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "ご協力いただき、本当にありがとうございます、船長。決して忘れません。";
					link.l1 = "ああ、気にしないでくれ。これからはもっと気をつけてくれよ。";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "あそこは人が多すぎる。\n個室に行こう。\n話したいことがあるんだ。";
					link.l1 = LinkRandPhrase("もうお前には十分すぎるほどしてやったからな、これでお別れだ。","私の好意につけ込むべきじゃないよ。じゃあね、ダーリン。","これからはお前の話なんて必要ねえ、自分で全部考えろよ。");
					link.l1.go = "Node_226";
					link.l2 = "ふむ、わかった。じゃあ酒場の主人から鍵をもらってくるぜ。";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "それで、まだ俺の話を聞きたいのか？";
				link.l1 = "ふむ……そろそろ行く時間だな。じゃあな！";
				link.l1.go = "Node_232";
				link.l2 = "さあ、早く言えよ。";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "ああ、私の高貴な救い主様、ついに女としてできる唯一の方法でお礼ができますわ\nあなたをジャングルで見かけたとき、私の中のすべてが変わりましたの。暴漢たちや、 頬を打つ鋭いヤシの葉のことも忘れてしまいました。どこに逃げるか、なぜ逃げるかも忘れて……私にはあなただけが見えていました。そして、欲しかったのはあなただけ……あなたが私のためにしてくださったことの後では……";
				link.l1 = "うわぁ、びっくりしたぜ！なんて気性だ！お前を追っかけてた連中は、相手が誰かちゃんと分かってたんだろうな…";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "聞いてくれ、美人さん、俺にはよくわかるが、頼むから自分の怒りは抑えてくれよ。";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "今すぐ私のもとへ来て、私の英雄よ…";
			link.l1 = "「ああ、あなた…」";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "おおっ！なんて…なんてことをしやがるんだ！？この野郎！女の子が心から感謝したっていうのに、お前は…";
			link.l1 = "まあ、そんなに男に色目を使って、出会った最初の男にすぐ夢中になるから、面倒ごとが増えるんだぜ。俺はもう、 そんな浮ついたやつをジャングルで助けたりしねえからな…";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "こんな言葉、今まで誰からも聞いたことがねえ！絶対に許さねえぞ！俺のことを忘れられなくしてやるからな！";
			link.l1 = "もう行けよ、いいな？それと、また助けられたくなけりゃ、少しはしゃきっとしろよ……";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "私の家族は、植民地の町に住んでいる "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.Parents_City)+"。私は偶然ここに来ることになりました。婚約者が両親に会わせるために連れて行ってくれる船に乗っていたのですが、 その船が海賊に襲われてしまったのです。船は奪われ、乗客たちはこの近くの入り江に上陸させられました。 乗り込まれたときに婚約者は殺され、私はジャングルを抜ける途中で重い病にかかりました\n地元の娼館の女主人が私を看病してくれて回復しましたが、立てるようになった途端、 治療にかかったお金を働いて返せと要求されました。私は娼婦になりましたが、女主人の気に入らず、 せめて少しでも金を取り戻そうと盗賊たちに売られてしまいました。あとの話はご存じの通りです。";
			link.l1 = "だからもうやめて家に帰れよ！なんであいつらに奴隷みたいに扱われてるんだ！？";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "できないんだ！持ち物は全部――まともな服も、金も、書類も……全部売春宿にあるんだ、旅行鞄の中に。あのデート部屋に隠してあるんだよ。こんな格好じゃ、 港の水夫どもがみんな俺を追いかけてくるさ。それに、書類も金もなけりゃ、誰が俺を船に乗せてくれる？ 今じゃ町にも顔を出せない、出たら牢屋にぶち込まれるだけだ……";
			link.l1 = "問題ないさ。行こう。俺が自分でお前を家まで送ってやる。";
			link.l1.go = "Node_235";
			link.l2 = "ここで待っていろ。俺が旅行鞄を持ってきてやる。";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "お前の書類なんてどうでもいいだろ？家に帰るのにいくら必要なんだ？";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "ああ、ありがとうございます、船長…。でも…ご存じの通り、お支払いできるものが何もありません。";
			link.l1 = "何の支払いのことだ？見つかる前に行こう……";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "ああ、船長、知っての通り、俺は決して頼もうなんて思わねえんだが……";
			link.l1 = "心配するな。すぐに戻るからな。";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "ああ、あなたに何かあったのではと心配していたところです。";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "何が起こるっていうんだ？ほら、お前の物を持っていけ。";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "聞けよ、そこでは何も見つからなかったぜ。本当にあんたは待合室に旅行鞄を置き忘れたのか？";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "ありがとうございます。 "+GetSexPhrase("高貴な船長","貴族のお嬢様")+"。あなたがしてくれたことは決して忘れません。多くは持っていませんが、このお守りをどうか受け取ってください。 もしかしたら、この小さな飾りが海賊の襲撃の時に私の命を救ってくれたのかもしれません。";
			link.l1 = "ありがとうございます、ご無事をお祈りします！それでは、ごきげんよう…";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "本当に俺の袋を見つけたのか？";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "家に帰るのにいくら必要なんだ？";
				link.l1.go = "Node_237";
			}
			link.l2 = "もしかしたらそうだったかもしれねえ。とにかく、ここで俺たちの道は分かれる。じゃあな！";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "ありがとうございます、船長。やっと家に帰ってきたなんて、まだ信じられません。どうぞ、一緒に来てください、 両親にご紹介します。";
			link.l1 = "「聞け、」 "+GetSexPhrase("美しさ","おチビちゃん")+"、本当にそんな時間はないんだ。また今度にしてくれないか？";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "なんと残念な……では、お別れです。主があなたを見守ってくださいますように。お返しできるものは何もありませんが、 このお守りをどうぞお受け取りください。";
			link.l1 = "ありがとう！さあ、早く家に帰って、両親を喜ばせてあげな！";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "うーん、どうだろうな……通りかかった船に乗せてもらうしかないかもしれねえ。でも、あんたに金を頼むわけにはいかねえんだ。";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "なるほど。よし、5000ペソを持っていけ。それで十分だろう。";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "なるほど。よし、2万5千ペソ持って帰れ。";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "なるほど。よし、3万5千ペソ持っていけ。それだけあれば船で一番いい船室が買えるはずだ。";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "ありがとうございます。 "+GetSexPhrase("高貴な船長","貴族の娘")+"。あなたがしてくれたことは決して忘れない。";
			link.l1 = "では、良い航海を。さらば……";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "ありがとうございます。 "+GetSexPhrase("高貴な船長","貴族の娘")+"。あなたがしてくれたことは決して忘れない。";
			link.l1 = "それじゃあ、良い航海を。さらば……";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "ありがとうございます。 "+GetSexPhrase("高貴な船長","貴族のお嬢様")+"。あなたがしてくれたことは決して忘れない。";
			link.l1 = "では、良い航海を。さらば……";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Have you heard? A whore was trying to sneak on board of a ship without documents, but she was caught and taken back to the brothel. They say she owed the madam quite a sum.",  
				"Have you heard? A whore without documents was caught at the port. They say she had cleaned out madam's coffers before attempting to flee from the brothel. I say, that source of filth and thievery must have been closed off long ago. Our kids are even seeing this and what can they learn from such an example?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "俺の人生を台無しにしないでくれ、船長！父さんは俺に高利貸しの息子――あの汚らしい甘ったれ――と結婚させたがってるんだ…ただあいつの親父が金庫に財産を持ってるって理由だけでさ！だったら、 俺はむしろジャングルに残って野獣に食われる方が、あいつと一生を過ごすよりマシだ！";
			link.l1 = "「お前たちの結婚にどんな問題があるんだ」 "+GetSexPhrase("美しさ","おちびさん")+"？お前に結婚を申し込む奴をしっかり捕まえて、幸せになるんだ。\n時が経てば、その青二才と結婚できてよかったと思うかもしれねえが、その時にはもう遅いかもしれねえぞ……";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "いやだ！いやだ、船長、俺は愛してる "+pchar.GenQuest.EncGirl.sLoverId+" 他の男とは絶対に結婚しないわ！それにお父様は何も聞きたくないって！お父様はこう言っているのよ\n "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+" ここではただの訪問者にすぎないから、決して仕事なんて見つからないし、貧困のうちに死ぬ運命なのよ、私も一緒に！ それでも彼のそばにいるためなら、世界の果てまでもついていくわ！お願い、彼のところへ連れて行って！";
			link.l1 = "よし、行くぞ。さて、お前をどうするか考えるとするか…";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "船長、私をその居留地まで連れて行くと約束したじゃないか "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("覚えている。","心配するな、俺がそこまで連れて行ってやる。");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("ありがとうございます。 "+GetSexPhrase("船長","お嬢さん")+"、またしても。本当に、あなたには大変お世話になりました。","本当にありがとうございます。 "+GetSexPhrase("船長","お嬢さん")+"。あなたの助けがなければ、俺はどうしていいかわからなかったぜ。");
				link.l1 = RandPhraseSimple("それが教訓になるはずだ。さて、幸運を祈るぞ…","次はもっと気をつけるんだな……さあ、家に帰りな。俺にはやることがあるんだ。");
				link.l1.go = "Node_260End";
				link.l2 = "どうしてそんなに不注意なんだ？なぜ一人でジャングルに入ったんだ？";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetSexPhrase("船長","お嬢さん")+"、本当にどう感謝してよいかわかりません。";
				link.l1 = "たいしたことじゃねえさ。いつでも助けてやるぜ……";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "酒場まで連れて行ってくれる？叔母を待たなきゃいけないし、少し休みたいの。この「冒険」で、 もうすっかり疲れちゃった……";
			link.l1 = "「いや、」 "+GetSexPhrase("美しさ","おチビちゃん")+"、それで俺には十分だ。やることは山ほどあるからな。";
			link.l1.go = "Node_262";
			link.l2 = ""+GetSexPhrase("ああ、女ってやつは！男の助けなしでできないことなんてあるのか？","「どうしてそんなに無力なんだ？」")+" 行こう……";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "少しばかり金があります……どうか、感謝のしるしとして受け取ってください！";
				Link.l1 = "ありがとうございます。次はもっと気をつけてください。";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "俺を助けてくれたって、みんなに伝えるぜ！みんなに知らせてやるんだ、 "+GetSexPhrase("なんて勇敢で勇ましい男なんだ","なんて勇敢で度胸のあるお嬢さんなんだ")+"!";
					Link.l1 = "ありがとうございます。さて、もう家に帰ったほうがいいですよ。";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "少しばかり金があります……どうか、感謝のしるしとして受け取ってください！";
					Link.l1 = "ありがとう。次はもっと気をつけてくれよ。";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "俺を助けてくれたって、みんなに伝えるぜ！みんなに知らせてやる、 "+GetSexPhrase("なんて勇敢で勇気ある男なんだ","なんて勇敢で度胸のある女性なんだ")+"!";
			Link.l1 = "ありがとうございます。さて、もう家に帰ったほうがいいですよ。";
			Link.l1.go = "exit";
		break;
	}
}
