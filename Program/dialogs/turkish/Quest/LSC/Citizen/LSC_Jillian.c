// Джиллиан Стайнер - просто девушка
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
				dialog.text = "Benden uzak dur! Sokakta kavga çıkaran adamlarla konuşmam.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah... merhaba! Beni korkuttunuz. Geldiğinizi duymadım... Size nasıl yardımcı olabilirim?";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+" .   Ben bu adanın yenisiyim. Buradaki insanları tanımaya çalışıyorum ve böyle güzel bir hanımefendiyle tanışmadan edemedim. İsminiz nedir?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Yardımcı olabilir miyim?";
				link.l1 = LinkRandPhrase("Jillian! Nasılsın? Ne var ne yok?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunuzu görmek istemiştim, madam. Hoşça kalın!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Beni utandırıyorsunuz efendim, ama bu benim için bir zevk. İlginiz için teşekkür ederim. Benim adım Jillian, Jillian Steiner.";
			link.l1 = "Gerçekten bir zevk, Jillian.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Buraya yeni mi geldin diyorsun? Söylesene, buraya nasıl ulaştın? Bir gemi kazasından sağ mı çıktın?";
			link.l1 = "Pekâlâ... öyle denebilir. Bir barçayla buraya geldim ve neredeyse resifleri geçiyordum, ama ne yazık ki dış halkaya çarptım ve gemim battı. Mürettebatımdan yalnızca ben buraya yüzerek ulaşabildim.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Ah! Demek adayı arayıp buldun? İnanılmaz!";
			link.l1 = "Evet, biraz deliydim. Efsanevi Adalet Adası'nı bulmaya karar verdim ve sonunda başardım. Ama... şimdi buradan nasıl çıkacağımı bilmiyorum.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "You are either very brave or very reckless. To sail here voluntarily... now you're stuck here with us; nobody has managed to leave this place in years.";
			link.l1 = "Hâlâ umudum var. Peki Jillian, teşekkür ederim, seni daha fazla tutmayayım. Şimdilik hoşça kal, madam!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Evet, tabii, "+pchar.name+". Dinliyorum.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Adadan ayrılmak mı istiyorsun?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Peki günlerini nasıl geçiriyorsun?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Evli olmadığını söylüyorsun... Böyle güzel bir kızın hiç hayranı yok mu?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorular yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Anne ve babamla birlikte İngiltere'den yelken açtık. Fakirdik ve Yeni Dünya'da yeni bir hayat kurmak istiyorduk, ama... fırtına gemimizi yakalayınca annemle babam öldü. Ben zar zor kurtuldum. Dış halkadaki bir enkaza ulaştım ve biri beni bulana kadar orada bir gün baygın yattım.\nYeni bir hayata başladım, ama belki de annemle babamın hayal ettiği gibi değil.";
			link.l1 = "Üzgünüm...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ve nereye gideceğim? Kim beni yanına alır ki? Ne bir evim var, ne kocam, ne de param. Londra'nın kenar mahallelerinden ve bu adadan başka bir yer bilmedim hiç... Eğer burada yaşamak kaderimse, olsun - bir kızın başına gelebilecek en kötü şey bu değil.";
			link.l1 = "Sanırım, yeterince adil.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I mostly help Brother Julian in the church. I also do some odd jobs in Axel's shop - that's how I make coin; I can't clamber around the shipwrecks at the outer ring.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Kıkır... hayranlarım var, evet, ama hiçbiri beş para etmez. Hiçbirini sevmiyorum ve hoşlanmadığım bir adamla yaşamak istemem. Hoşlandıklarım ise bana hiç aldırış etmiyor. Ben sadece sıradan, yoksul bir kızım...";
			link.l1 = "Eminim birini bulacaksın, önünde de koca bir hayat var...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ah, hırsız!","Kirli ellerini ondan çek, o benim!","Sandığımı açmana izin vermedim!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ellerini göğsümden çek, hırsız!";
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
			dialog.text = LinkRandPhrase("Beyefendi, lütfen silahınızı indirin. Beni korkutuyorsunuz.","Bu adada insanlar elinde kılıçla dolaşmandan pek hoşlanmaz.","Kılıçlarla etrafta koşuşturan adamlar beni etkilemiyor. Onu yerine koy.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bu adada insanlar elinde kılıçla dolaşmandan pek hoşlanmaz.","Lütfen kılıcınızı yerine koyun, efendim. Silahlı adamların etrafta dolaşması bizi tedirgin ediyor.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Affedersiniz...","Üzgünüm, madam...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyefendi, lütfen silahınızı indirin. Beni korkutuyorsunuz.","Kılıçlarla etrafta koşuşturan adamlar beni etkilemiyor. Onu yerine koy.");
				link.l1 = RandPhraseSimple("Üzgünüm...","Bunu kaldırıyorum.");
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
