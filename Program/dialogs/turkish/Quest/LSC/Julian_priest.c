// брат Юлиан - священник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

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
				dialog.text = "Seninle konuşmak istemiyorum. Hiçbir sebep yokken huzurlu yerlilere saldırıyor, onları kavgaya kışkırtıyorsun. Defol git, kafir!";
				link.l1 = "Nasıl istersen...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Hayatta kalmana şaşırmadım. Rab'bin yolları gizemlidir. Yaşam ve ölüm O'nun ellerindedir.";
				link.l1 = "Sana tamamen katılıyorum, Kardeş Julian.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Adalet Adası'nın kutsal kilisesine hoş geldin, evladım. Kapılarımız sana her zaman açık. Ben Kardeş Julian, büyük Rabbimizin her hizmetkârını görmekten mutluluk duyarım.";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+". Tanıştığımıza memnun oldum, Kardeş Julian.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şey mi istiyorsun? ";
				link.l1 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "Senden biraz iksir satın alabilir miyim?";
				link.l2.go = "potion";
				link.l3 = "Kutsal eşyalarınız var mı satılık?";
				link.l3.go = "amulet";
				link.l5 = "Sadece burada dua etmek ve nasıl olduğunu görmek istedim. Görüşürüz!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "I hope that you will visit our church more often. Take care of your soul, my child. I am also able to heal your body; I work here not only as a pastor, but also as a doctor.";
			link.l1 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "Senden birkaç iksir satın alabilir miyim?";
			link.l2.go = "potion";
			link.l3 = "Kutsal bir eşyanız satılık mı?";
			link.l3.go = "amulet";
			link.l4 = "Gitmem lazım, Kardeş Julian. Görüşürüz!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "Elbette, oğlum. Hangi iksire ihtiyacın var?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Basit bir iyileştirme iksiri.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Şifalı bir iksir.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Bir panzehir.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Bitkisel bir karışım.";
				link.l4.go = "potion4";
			}
			link.l5 = "Üzgünüm, Kardeş Julian, fikrimi değiştirdim.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Bir iksir mi? 90 peso, evladım.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Al onları, Kardeş Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Şu anda yeterince param yok... Sonra tekrar geleceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Bir iksir mi? 500 peso, evladım.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Al onları, Julian Kardeş.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Şu anda yeterince param yok... Sonra tekrar geleceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Bir panzehir mi? 200 peso, evladım.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Al onları, Kardeş Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Şu anda yeterince param yok... Sonra tekrar geleceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Karışım mı? 900 peso, evladım.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Al onları, Julian Kardeş.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Şu anda yeterince param yok... Sonra tekrar geleceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Al bakalım. İlacını iç. Tanrı yardımcın olsun!";
			link.l1 = "Teşekkür ederim, Kardeş Julian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "Evet, sana yaralardan ve hastalıklardan koruyan kutsal muskalar verebilirim. Her muskanın fiyatı aynı - on altın dublon. Sana sunabileceğim "+XI_ConvertString(npchar.quest.amulet)+" bugün.";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "Evet, bu tılsımı almak istiyorum. Al altınını.";
					link.l1.go = "amulet_pay";
					link.l2 = "Bu muska bana lazım değil, Kardeş Julian. İhtiyacım olanı getirmeni bekleyeceğim.";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "Şu anda yeterince param yok... Sonra tekrar geleceğim.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hayır, oğlum, maalesef başka bir şeyim yok. Başka bir gün uğra, belki senin için bir şeyler bulurum.";
				link.l1 = "Anlaştık, Kardeş Julian.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("You have received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Teşekkür ederim, oğlum. Paranın büyük faydası dokunacak. Al tılsımını ve Tanrı seni korusun!";
			link.l1 = "Teşekkür ederim, Kardeş Julian.";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Dinliyorum.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin, Kardeş Julian?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Cemaatinizde kaç kişi var?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Burada kim mal satıyor?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Adanın yok olma riski var mı? Fırtınalar mesela?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Hiçbir sorum yok. Üzgünüm...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ben de buradaki birçok kişi gibi geldim, evladım. Gemim Havana'dan Yeni İspanya'ya yolculuğum sırasında bir fırtınada battı. Tanrı'ya şükür, hayatta kaldım ve şimdi burada O'na hizmet ediyorum, zavallı ruhlara gerçek yollarını bulmalarında yardımcı oluyorum.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "İstediğimden daha az. Narvallerin çoğu merhametten çok şiddeti tercih ediyor, Rivados ise yoksul, kaybolmuş koyunlar gibi. Körü körüne putperest ayinlerini yerine getiriyorlar, ölümsüz ruhlarını tehlikeye atıyorlar. Aralarında tehlikeli bir büyücü var ve Kutsal Engizisyon tarafından arındırılması şart.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sancho Carpentero owns a tavern on the Fleron, where you can find food, drinks, and a warm bed. Axel Yost sells a wide variety of goods on the 'Esmeralda'. Ask people on the streets, my son; many of them find interesting things in the outer ring.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Her şey Rabbimizin ellerinde, evladım. O'na inanır ve O'na güveniriz. Büyük dertler Adalet Adası'ndan hep uzak durdu – fırtınalar genellikle dışarıda kopar, ama burada her zaman huzur olur.";
			link.l1 = "Teşekkür ederim. Beni rahatlattın.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Orada ne yapıyorsun, ha? Hırsız!","Şuna bak! Ben dalgınlığa kapılmışken, sen de sandıklarımı karıştırmaya kalktın!","Sandıklarımı mı karıştırmaya karar verdin? Bunu yanına bırakmam!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandıklarımı mı kurcalamaya karar verdin? Bunu yanına bırakmam!";
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
			dialog.text = LinkRandPhrase("Dinle, silahını yerine koysan iyi olur. Bu beni tedirgin ediyor.","Biliyor musun, burada elinde bıçakla dolaşmana izin verilmez. Onu yerine koy.","Dinle, elinde kılıçla etrafta dolaşan bir ortaçağ şövalyesi gibi davranma. Kılıcını yerine koy, sana yakışmıyor...");
			link.l1 = LinkRandPhrase("Pekala.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını kınına sokmanı rica ediyorum.","Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını kınına sokmanı istiyorum.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol dostum, elinde silahla dolaşmak beni tedirgin ediyor...","İnsanların silahlarını çekmiş halde önümden geçmelerini sevmem. Korkutuyor beni...");
				link.l1 = RandPhraseSimple("Anladım.","Bunu alıp götürüyorum.");
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

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}
