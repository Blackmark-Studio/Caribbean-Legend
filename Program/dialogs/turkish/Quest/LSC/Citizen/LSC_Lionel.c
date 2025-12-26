// Лайонел Маскетт - мещанин
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
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Seninle konuşmak istemiyorum. Masum insanlara sebepsiz yere saldırıyor, onları kavgaya kışkırtıyorsun. Git buradan!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Selamlar, "+GetAddress_Form(NPChar)+". Buraya yeni mi geldiniz?";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+" - evet, öyleyim.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+", "+TimeGreeting()+" . Bir şey mi istiyorsun?";
				link.l1 = LinkRandPhrase("Bana anlatacak ilginç bir şeyin var mı?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatacak mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu görmek istedim. Hoşça kal.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Benim adım Lionell. Tanıştığımıza memnun oldum. Buraya nasıl geldin?";
			link.l1 = "Bir barkta... Burada bir kaçakçı koyu olduğunu duydum ve onu aramaya karar verdim... Eh, barkım battı ve işte buradayım.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "İnsanlar gerçekten adanın bir kaçakçı sığınağı olduğunu mu sanıyor?";
			link.l1 = "Resmi olarak değil. Çoğu insan senin varlığına bile inanmıyor.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Ve neden yapsınlar ki? Biz hiçbir haritada yokuz. Bu yerden ayrılamazsın. Buradakiler eskiden adanın Küba'yla ticaret yaptığını söyler, ama ben hatırlamıyorum ve neredeyse sekiz yıldır burada yaşıyorum.";
			link.l1 = "Anladım. Seninle konuşmak güzeldi. Hoşça kal.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Bana anlatacak ilginç bir şeyin var mı?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Dinliyorum.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Ana karaya dönmek ve buradan ayrılmak ister misin?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Burada, adada insanlar ne yapar?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Burada nereden alışveriş yapıyorsunuz? Yiyecek, giysi, içecek?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorular yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "That is an odd story. This island is the only place I've known in the Caribbean. I had a run of hard luck in England so I booked passage on a merchantman to the New World. I was going to find a job in Belize - maybe as a clerk for the harbourmaster. But we never made it to Belize.\nI'm no sailor, so I don't know the details, but a storm cropped up and wrecked us on the reefs. I'll never forget that terrible blow... the screaming...\nSomeone shouted, 'She's holed!' and people started jumping overboard. Me... I can't swim, so I stayed. Ironically, that saved my life: the ship survived and the storm broke at dawn.\nBefore I left the ship I took some food, built a raft, and paddled over a tranquil sea to the outer ring. That's how I survived; the only one out of the whole crew.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "İlk iki yılım boyunca buradan kaçmayı hayal ettim, ama şimdi... Ada gerçekten başka bir yerden daha mı kötü? Burada ne yeşil tarlalar var, ne de ağaçlar, ama muhteşem bir deniz ve yıldızlarla dolu bir gece gökyüzü var. Karnım tok, üstüm başım düzgün - İngiltere'de yaşarken alabileceğimden daha iyi. Bir sürü dostum var... Hayır efendim, buradan ayrılmak istemiyorum. Dışarıda beni ne bekliyor ki? Huysuz bir patronun yanında haftada üç yüz peso için masa başı bir iş mi? Asla! Aradığım her şeyi burada buldum ben. Başka hiçbir şeye ihtiyacım yok.";
			link.l1 = "Anladım. Senin adına sevindim!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Ne isterlerse onu yaparlar. Narvaller ve Rivados savaşır. Korsanlar erzak satar. Axel Yost enkaz alıp satar. Sancho Carpentero içki sunar ve insanları eğlendirir. Kardeş Julian dua eder, ayin yapar ve ilaç satar. Lauderdale ve Solderra birbirine karşı entrika çevirir. Abbot güneşte salına salına dolaşmayı sever. Jillian ve Tanneke gerçek aşkı hayal eder...";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Enkazlardan, dostum, enkazlardan. Dış halkadaki batık gemileri yağmalamak, adalıların en sevdiği uğraşlardan biridir. Orada her şeyi bulabilirsin: silahlar, ilaçlar, baharatlar ve rom. Birçok enkaz hâlâ keşfedilmedi – akıntılar sürekli yeni kurbanlar getiriyor...";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Eşyalarımdan elini çek, hırsız!","Bir dakikalığına arkamı döndüm, hemen beni soymaya mı kalkışıyorsun?! Sana göstereceğim!","Sandıklarımı mı talan ediyorsun?! Bunun hesabını vereceksin!");
			link.l1 = "Kes sesini!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "İznim olmadan eşyalarıma nasıl dokunursun! Biri yardım etsin! Hırsız!";
			link.l1 = "Kapa çeneni!";
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
			dialog.text = LinkRandPhrase("Silahını indir dostum. Bu beni tedirgin ediyor.","Biliyor musun, burada elinde bıçakla dolaşmana izin verilmez. Onu yerine koy.","Bak, şövalyecilik oynama, elinde kılıçla oradan oraya koşturma. Sana yakışmıyor, bırak onu...");
			link.l1 = LinkRandPhrase("Pekala.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu adanın bir sakiniyim ve senden kılıcını indirmeni rica ediyorum.","Bakın, ben bu adanın bir sakiniyim ve sizden kılıcınızı indirmenizi rica ediyorum.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol, dostum. Eline silah alıp ortalıkta dolaşman... beni tedirgin ediyor.","Silahını elinde tutarak dolaşan adamlardan hoşlanmam. Bu beni korkutuyor.");
				link.l1 = RandPhraseSimple("Üzgünüm.","Bunu kaldırıyorum.");
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
