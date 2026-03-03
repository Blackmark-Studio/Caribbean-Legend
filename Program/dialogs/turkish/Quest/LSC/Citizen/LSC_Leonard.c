// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Defol git, dostum! Masumlara saldıran pisliklerle laklak edecek değilim.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "Dostum, tam zamanında geldin... Seninle biraz iş konuşmak istiyorum... önemli bir iş.";
				link.l1 = "Gerçekten mi? Leonard, inanılır gibi değil... Ayık olduğunu görüyorum! Ne nadir bir manzara!";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A-a... hık! Selam, dostum...";
				link.l1 = TimeGreeting()+". Görünüşe bakılırsa zaten yeterince içmişsin, 'dostum.'";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Hik! Ne istiyorsun?";
				link.l1 = LinkRandPhrase("Ne var ne yok, Leonard?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatacak mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Hoşça kal!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Evet! Yeter mi? Hayır! Hiç de yeterli değil, h-hıçk! Evet, Leonard Musket sarhoş ve olması gereken de bu!";
			link.l1 = "İçkileri seviyorsun, ha? Evet, adım "+GetFullName(pchar)+". Memnun oldum, şey... tanıştığımıza.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Eğer öyle diyorsan. Hepimiz - hık! - toplandık, şimdi... peki, şimdi ne olacak?";
			link.l1 = "Pekala, eğer konuşmak için çok... meşgulsen... O zaman başka bir zaman!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Burada neler yeni?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "A-ha ha, siktir git! Evet dostum, ben - neredeyse - ayığım. Ve bunun sebebi, bizim için bir fırsatım olması...";
			link.l1 = "Ne fırsatı? Konuş, vaktimi boşa harcama!";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "Dostum... biraz para kazanmak ister misin? Gümüş peso, altın doblon? Sana nasıl olduğunu anlatacağım. Ama benimle paylaşman gerekecek - birlikte çalışacağız.";
			link.l1 = "Para kazanmak için her zaman hazırım. Ama her şey senin teklifine bağlı: ne kadar kârlı ve ne kadar... yasal... olduğu önemli.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "The business is not really legal, sure, but it is profitable... and we'll be able to punish a miser for his greed. He won't end up poor; he has too much money.\nBesides, everyone shares with him, so it's his turn to return the favour. Tell me, can you hold your liquor? How much rum are you able to drink before going under table?";
			link.l1 = "Duruma bağlı. Aşırı içki içmek gibi bir alışkanlığım yok... Sonunda bana ayrıntıları anlatacak mısın?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "Pekâlâ. Açık konuşacağım. Adada şişman, çirkin bir herif var, Giuseppe Fazio. (tükürür) Narvalları, Rivadoları ve yerlileri soyup soğana çeviriyor. Bir süredir onu gözlüyorum ve bir şey öğrendim...\nCaroline'daki kamarasında iki sandık var: birinde belgeler, diğerinde altın ve gümüş var. İkisi de farklı anahtarla kilitli. Şişko herif anahtarları hep cebinde taşır.";
			link.l1 = "Yani, Fazio'yu soymayı mı planlıyorsun? Kusura bakma dostum, ben bu işe karışmam. Ve kimseye söylemeyeceğime de şükret. Başka bir ortak bul.";
			link.l1.go = "facio_exit";
			link.l2 = "Ha! İlginç! Devam et...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "Ne yazık, ne yazık... İkimize de yetecek kadar altın var aslında... Peki, öyle olsun. Görüşürüz.";
			link.l1 = "Elveda.";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "İki kapı kamarasına açılıyor. Bir tanesi her zaman kilitli, ama altın sandığı açan anahtar o kapıyı da açıyor. Onu bunu yaparken gördüm. Kabini de, altını da açmak için tek bir anahtar yeterli. Ama anahtarı nasıl ele geçireceğiz?\nBir planım var, hem de harika bir plan. Her şey yolunda giderse, Fazio olan bitenden habersiz kalacak, kimi suçlayacağını bilemeyecek. Bunu gizemli rom ve mücevher hırsızının işi sanacak. Sorun şu ki, bunu başarmak için demir gibi bir kafaya sahip bir ortağa ihtiyacım var. Anladın mı?";
			link.l1 = "Evet, devam et.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "Fazio loves to sit at Sancho's and have a good drink - and he can hold his liquor better than anyone I've ever seen! He knows it, too; he came up with a drinking game: a game where people try to drink him under the table.\nIf you ask him to play this game, I promise you he'll agree. And then comes the fun part.\nYou make a bet with him, go to the tavern, grab a bottle of rum, and drink until one of you kisses the table. If you pass out first then the whole plan is ruined; I won't be able to do it alone.\nThat's why I asked about your head. All you have to do is make sure he drops first. I'll be nearby, waiting. When he's down, I'll take his keys.\nThen we move the fat man to a bed upstairs and sneak into his cabin while he's asleep. I'll return the key right after we loot his chest - he won't even realize he's been robbed 'til he opens the chest, ha-ha!\nOnce we've got the key, you sneak into his cabin and take what you can. I'll stay on guard outside. We split the chest's contents, half-and-half, and go our separate ways. So, are you in?";
			link.l1 = "Şeytanca bir plan! Tabii, varım.";
			link.l1.go = "facio_6";
			link.l2 = "Hayır dostum. Ben almayayım. Korkarım içkiyi o kadar iyi kaldıramam. Kendine benden daha sağlam bir ortak bul.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "Yanılmadığıma sevindim. Şimdi, Fazio'ya git ve akşam dokuzdan sonra meyhanede bir buluşma ayarla. Umarım o domuzu kendi oyununda alt edersin! Bol şans, akşam görüşürüz!";
			link.l1 = "Elimden geleni yapacağım... hoşça kal!";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "Dostum, sana güveniyorum. Şu pinti herifi masanın altına içir...";
			link.l1 = "Tabii.";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "It's done, the pig is asleep upstairs. I've got the key. You're doing well; you seem to be sober enough!";
			link.l1 = " G-gerçekten mi? Uzun zamandır bu kadar... bu kadar sarhoş olmamıştım - hık! Biraz başım dönüyor... Hık! Gidelim mi?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "It's done, that fat pig is asleep upstairs. I have the key. You're doing good; you really managed to over drink that piggy...";
			link.l1 = "Oldum ama - hık! - bu kadar sarhoş olalı çok zaman oldu. Başım dönüyor... hadi gidelim, yoksa bayılacağım.";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "Eh, dostum, şişman adamı içkiyle alt edemedin... Ne yazık. Neyse, en azından denedik...";
			link.l1 = "L-lanet olsun, adam tam bir... dipsiz varil gibi. Ah, biraz d-dinlenmem lazım... Bitti, d-defol git! Hık!..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "Evet. Hadi gidelim! Beni Caroline'e kadar takip et! Ve sakın kaybolma, fazla vaktimiz yok!";
			link.l1 = "Evet, h-hadi!";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "Al işte. Anahtarı al. Aradığın sandık girişin solunda. Ne kadar alabiliyorsan, o kadar hızlı al. Sonra tekrar kilitlemeyi unutma! Bir şey görürsem kapıyı üç kez çalacağım. Arka galeriden kaç.";
			link.l1 = "Peki. Dikkatli ol!";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable haul... Why'd we even bother? Eh... fine, let's split what we've got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there'd be much more... Hardly worth the risk. Eh... fine, let's split what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought there'd be more. All right, let's split it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We've done well, partner! This is a lot of coin! Let's split it!";
						else
						{
							sTotalTemp = "Damn me! I never imagined the fat man's stash was so huge. Well done, partner! Let's split the loot!";
						}
					}
				}
			}
			dialog.text = "Sonunda! O cimriden ne almayı başardın? Göster bakalım!";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "Hiçbir şey yoktu. Sadece birkaç parça - muskalar falan.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "Buldum "+sPeso+" ve "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "Hayır! Görünen o ki, her şey boşunaymış... Belki de o alçak ganimetini başka bir sandığa koydu. Eh! Peki, anahtarı ver de geri götüreyim. Hoşça kal dostum... kahretsin...";
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "Paylaşalım.";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Pekâlâ, anahtarı ver, ben de geri götüreyim. Hoşça kal, dostum.";
			link.l1 = "Bol şans, dostum.";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone cleaned out his chest. It seems the mysterious thief did it.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Haven't you heard? Fazio was robbed! He was robbed while lying dead drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your feet! That's something.", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Gerçekten mi?... hık! Dinliyorum...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl düştün?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Her zaman içer misin? Ve içki için parayı nereden buluyorsun?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Buradaki yerliler hakkında bana ne anlatabilirsin?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Buradan ayrılıp İspanyol Ana Karası'na gitmek ister misin?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Eh! Biliyor musun, hatırlamıyorum. Gerçekten, hatırlamıyorum! Çok uzun zaman önceydi. Bir yerlere gidiyordum... bir şekilde... her neyse, sonunda kendimi burada buldum. Hık!";
			link.l1 = "Hm... Peki...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Evet, içiyorum. Sarhoşum ben... İçmek... kahretsin, çünkü yapacak başka hiçbir şeyim kalmadı! Bak dostum, bittim ben. Hayatta tek istediğim şey bu şişe rom. O yüzden içmeye devam edeceğim! Ve para... he-he, rom zaten pek pahalı değil.\nNeyse, ödemem bile gerekmiyor. Romla dolu bir yer var, ama oraya gitmek istiyorsan yüzmen gerek. O yüzden sadece yüzemeyecek kadar sarhoş olduğumda rom satın alıyorum... hık! Jizjezezejizeze... yok, sana nereye yüzmen gerektiğini söylemem, he-he, sorma bile...";
			link.l1 = "Ne hoş.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Ne diyebilirim ki - hık! - onlar hakkında? Sohbet etmek ve içmek için iyi insanlardır. Giuseppe Fazio önemli bir adam, büyük bir isim. Sandıkları altınla dolup taşıyor... pfuh! Cimri... ama yaşlı Leonard'a saygı duyar, meyhanede ona içki ısmarlar.\nYine de bazen karşılığında bir şey ister, ama önemsiz şeyler - hık!\nHeh, Fazio'nun kaç doblonu olduğunu biliyor musun? Aha-ha-ha! Karayipler'in en iyi meyhanesinde ömrünün sonuna kadar çalışmadan, dünyanın en iyi romunu içerek yaşayacak kadar. Ama o burada, adada kalıyor. Görünen o ki ona hâlâ para yetmiyor...";
			link.l1 = "Anladım...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "Gitmek mi? Hık! Neden? Hayır, ana karaya da gitmek istemiyorum, Avrupa'ya da, dünyanın başka herhangi bir zavallı adasına da. Orada beleş rom var mı? Yok! Hiçbir yerde... hiç beleş rom yok - hık! Yani orada bana göre hiçbir şey yok... Dostum, ben burada iyiyim. Hey, hey - hık! - insanlara sor, buradan gitmek isterler mi diye. Kimse istemez, iki ya da üç kişi dışında - hık!";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Hey, domuz, ellerini - hık! - ganimetimden çek!","Yoksul Leonard'ı içki içiyor diye soyabileceğini mi sanıyorsun, ha? Ha?! Sana göstereceğim!","Sandıklarımın yanından uzak dur! Seni kim gönderdi, o şişko domuz Fazio mu?!");
			link.l1 = "Sarhoş herif!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Sandığımdan uzak dur, seni haydut!";
			link.l1 = "Aptal kız!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Dostum, şu - hık! - kılıcını indir. Birini yaralayacaksın.","Henüz sarhoş değilsin... elinde kılıç tutacak kadar sarhoş değilsin. Onu bırak da gel bir içki içelim.","Kılıcını böyle sallayarak tam bir eşek herif gibi görünüyorsun. Koy - hık! - koy onu yerine.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Pislik... peki.");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, böyle - hık! - kılıcını sallayamazsın. Bırak şu işi.","Sen sarhoş değilsin... en azından elinde kılıç tutacak kadar sarhoş değilsin. Kılıcı bırak da gel bir içki içelim.");
				link.l1 = LinkRandPhrase("Pekala.","Pekâlâ.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dostum, şu - hık! - kılıcını indir. Birini yaralayacaksın.","Kılıcını böyle sallayarak tam bir eşek herif gibi görünüyorsun. Koy - hık! - koy onu yerine.");
				link.l1 = RandPhraseSimple("Üzgünüm.","Onu kaldırıyorum.");
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
