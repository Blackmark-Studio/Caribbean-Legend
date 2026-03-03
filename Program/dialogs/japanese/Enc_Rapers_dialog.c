void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("「自分の道を行け」 "+GetSexPhrase("相棒","娘")+"。最終的には彼女も俺たちに感謝するさ、わかるだろう。","失せろ！旦那方に楽しく過ごさせてやれ。","「お前には関係ねえことだ」 "+GetSexPhrase("見知らぬ者","娘")+"。ちょっと楽しむだけさ、それだけだぜ！");
				link.l1 = LinkRandPhrase("俺はこんなこと許さねえぞ！","今すぐその悪だくみをやめろ！","俺はどんな暴力も許さねえぞ！");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("わかった、もう行くよ。邪魔して悪かったな。","もう二度とお邪魔しません。ご迷惑をおかけしてすみませんでした。");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("「自分の道を行け」 "+GetSexPhrase("相棒","娘")+"。最終的には彼女も俺たちに感謝するさ、わかるだろう。","消え失せろ！旦那たちに楽しく過ごさせてやれ。","「お前には関係ねえことだ」 "+GetSexPhrase("見知らぬ者","娘")+"。ちょっと楽しむだけだ、それだけさ！！");
					link.l1 = LinkRandPhrase("俺はこんなこと許さねえぞ！","今すぐその悪だくみをやめろ！","俺はどんな暴力も絶対に許さねえぞ！");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("わかった、もう行くよ。邪魔して悪かったな。","もう二度とお邪魔しません。ご迷惑をおかけしてすみませんでした。");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("「おい、」 "+GetSexPhrase("見知らぬ者","お嬢さん")+"、なんで揉め事を探してるんだ？この娘はうちの居住地で「有名」な存在だ。俺たちはもう彼女に金を払ったが、 あんたに気づいて金を持って逃げることにしたんだ。","「おい、」 "+GetSexPhrase("相棒","娘")+"、さっさと自分の道を行け、俺たちのことに首を突っ込むな。この娘はサイコロ勝負で手に入れたんだが、 ちょっと素早すぎて逃げ出しやがった。もう一時間もこのジャングルで追いかけてるんだぜ。");
					link.l1 = "俺は気にしねえ、あいつに手出しはさせねえぞ！";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("ああ、そうか！あやうくあの女の言葉を信じるところだったぜ！あんなあばずれめ……","ああ、そういうことなら話は別だな。じゃあ、楽しんでくれよ、みんな！");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "「自分の道を行け」 "+GetSexPhrase("いい男","お嬢さん")+"。お前がいなくても俺たちで何とかするさ。";
					link.l1 = "俺は暴力は絶対に許さねえぞ！";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("「おい、」 "+GetSexPhrase("見知らぬ者","お嬢さん")+"「なあ、なんで揉め事を起こそうとしてるんだ？この娘はうちの居住地じゃ“有名人”なんだぜ。もう金は払ったんだが、あんたに気づいて俺たちの金を持って逃げることにしたんだ。」","「おい、」 "+GetSexPhrase("相棒","娘")+"、さっさと自分の道を行け、俺たちのことに首を突っ込むな。こいつはサイコロ勝負で手に入れた娘だが、 逃げ足が速くてな、もう一時間も追いかけてるんだ。");
					link.l1 = "俺はどうでもいいが、あいつには指一本触れさせねえぞ！";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("ああ、そういうことか！あやうくあの女の言葉を信じるところだったぜ！とんだあばずれめ……","ああ、そういうことなら話は別だな。じゃあ、楽しんでくれよ、みんな！");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("「まあ、散歩にはまさにうってつけの時を選んだな……」","そうか、英雄になるつもりか？")+" 「奴を片付けろ」"+GetSexPhrase("俺","「えー」")+"「野郎ども！」","You "+GetSexPhrase("スライム","汚物")+"！俺たちの邪魔をするつもりか？！斬り捨ててやる"+GetSexPhrase("俺","「えー」")+"!");
			link.l1 = "もっと怖そうな奴らを見たことがあるぜ！";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "あんたも知っておくべきだが、あの女はかなり金がかかったんだぜ！もしあんたがそんなに高貴なお方なら、 あの女をあんたに渡してやってもいいぜ "+sti(pchar.GenQuest.EncGirl.price)+" ペソ。"+GetSexPhrase(" 彼女と一緒なら楽しい時間を過ごせるぜ、へへ……","")+"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("ほら、金だ。あの女は俺が連れていく。","歯を食いしばるのはやめろ。俺はこの娘を連れていくぜ。ほら、金だ。");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("つまり、金が欲しいのか？それとも冷たい刃の方がいいか？","それが面白いと思ってるのか、この娘を見ろ、この馬鹿野郎！怯えてるじゃねえか！","誰を騙そうってんだ、このろくでなしめ！");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "そもそも、なぜあいつの言うことを信じるんだ？どんな暴力だって？あいつは家出しただけで、 俺たちは親分に頼まれて探しに来ただけだぜ。";
			link.l1 = RandPhraseSimple("なるほど、それなら話は別だな。行け、逃げた奴を追いかけろ。","ああ、なるほど。じゃあ、その娘を追い続けな。……俺には片付けなきゃならねえ用事があるんだ。");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("そんなおとぎ話は、自分の孫ができるまで長生きしたら聞かせてやれよ！","誰を騙そうってんだ、この野郎！？");
			link.l2.go = "Node_6";
			link.l3 = "面倒を避けるために、俺が自分で彼女を家まで送るぜ。彼女の親は誰だ？";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "死にたいのか？それがお前の選択だな……";
			link.l1 = "「どの口が言うんだ。」";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "is a store owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a store owner";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "serves in the port office";
					pchar.GenQuest.EncGirl.FatherGen = "who serves in the port office";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "serves as the prison's commandant";
					pchar.GenQuest.EncGirl.FatherGen = "of a prison's commandant";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "is a shipyard owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a shipyard owner";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "彼女の父 "+pchar.GenQuest.EncGirl.FatherNom+"、居住地で "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"。しかし、どうか私たちを裏切らないでください、あの人は冗談の通じる相手じゃありません、 全員生きたまま皮を剥がされますよ……";
			link.l1 = "心配するな。俺が彼のもとへ彼女を届けてやる。";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "また会ったな。お前の仲間はどこだ？まあ、いいさ。お前がいれば、あの女はいらねえよ。";
			link.l1 = "諸君、もう十分な金を受け取っただろうから、その娘にはもう手を出すな。";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "a leg";
				break;
				case 1:
					sTemp = "an arm";
				break;
				case 2:
					sTemp = "an ear";
				break;
				case 3:
					sTemp = "a nose";
				break;
				case 4:
					sTemp = "an eye";
				break;
			}
			dialog.text = "お前の金など、の財宝に比べれば何でもない "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_GEN)+"? "+"あいつはケチでな、自分の娘さえ嫁にやりたがらなかったんだ、余計な出費を避けたくてな……\nだが、俺たちの取り分はしっかり自分の箱にしまい込んでやがる！ "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.PirateName2,NAME_NOM)+" 白兵戦で敗北した "+sTemp+"！それと、お前は代わりに何を持ってるんだ？ "+"「哀れな銀貨のひと握りだと？」 "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_NOM)+" いつも戦利品を全部自分の隠し場所に持っていきやがった。\nだが今度は俺たちは引き下がらねえ！奴の宝箱がどこにあるか教えろ！";
			link.l1 = "まあ、俺はあんたの船長の宝を守るために雇われたわけじゃねえが、場所を教えることはできねえ……なぜなら、俺もどこにあるのか知らねえからだ。";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "嘘をついてやがるな！！！この洞窟から金の匂いがぷんぷんするぜ！死にたくなけりゃ場所を教えろ！";
			link.l1 = "私の言葉ではあなたを納得させられなかったようだな。\nならば、この剣で語るとしようか？";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "You "+GetSexPhrase("野良犬","汚物")+"「どけ、邪魔だ！」";
			link.l1 = "「アルグ！」";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "こんにちは、良い "+GetSexPhrase("男","ご婦人")+"。お前について苦情が届いているぞ。";
			link.l1 = "誰からの文句だ？あの売女からか？";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "言葉に気をつけろ、いいな？俺の妹を侮辱するのは許さねえ！最初はジャングルで彼女を襲い、 それからここに連れてきたんだ "+GetSexPhrase("さらなる不品行のために","そして俺を襲って奪った")+".";
			link.l1 = "おい相棒、俺は本当に全部聞かなきゃいけねえのか？";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "いいや。わずかな額でたった "+sti(pchar.GenQuest.EncGirl.BerglarSum)+" ペソがあんたをすべての面倒から救ってくれるぜ。";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "まあ、最近は高貴な行いも結構金がかかるもんだな。よし、持っていけ…";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "お前の腹に穴を開けて、出口への邪魔をさせない方が安上がりだと思うぜ。";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "いやだ。だが、お前もポケットの中身を全部出せ、さもねえと刺すぞ！";
				link.l1 = "よし、持っていけ、この野郎！だが、ただじゃ済まさねえぞ……";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "お前の腹に穴を開けて、出口への邪魔をさせねえ方が楽だと思うぜ。";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "とてもいい。せいせいしたぜ。";
			link.l1 = "幸運を祈る。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "もちろんしないさ、もちろん……さて、それじゃあ、さようならだ、 "+GetSexPhrase("相棒","娘")+"."+GetSexPhrase(" それと覚えておけよ、お前はそんなにイケてる顔じゃねえから、女が一目見てすぐ惚れるなんてことはねえんだぜ。 これが俺からの教訓だ。","")+"";
			link.l1 = ""+GetSexPhrase("それは間違いねえぜ！..","さっさと失せろ！")+"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "「～のように見える」 "+GetSexPhrase("「そんな高貴な男」","「とても上品に育てられたご婦人」")+"、なんだその汚い言葉遣いは？";
			link.l1 = "俺にはこれが一番合ってるんだ…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "さあ、望みどおりだぜ！くすぐってやるか？"+GetSexPhrase("俺","「えー」")+" 鉄でいくか、野郎ども？";
			Link.l1 = "死ぬ前に祈れ！";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "それで、参加したいのか、したくないのか？ "+GetSexPhrase("消えろ、みんなに行き渡るほど残ってねえんだ","消え失せな、こっちは女は一人で十分だぜ")+"!";
			Link.l1 = "それでは、お邪魔はしません。";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "俺は絶対に暴力を許さねえぞ！";
			Link.l2.go = "Node_2";
		break;				
	}
}
