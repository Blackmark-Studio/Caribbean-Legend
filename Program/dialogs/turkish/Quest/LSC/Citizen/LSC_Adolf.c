// Адольф Барбье - авантюрист
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
				dialog.text = "Seninle hiçbir işim olmaz. Masum sivillere sebepsiz yere saldırıyor ve onları kavgaya kışkırtıyorsun. Defol git!";
				link.l1 = "Şey...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Merhaba, merhaba... Sizi daha önce görmemiştim. Yeni misiniz?";
				link.l1 = "Adada yeni misin demek istiyorsun? Evet, doğru. Benim adım "+GetFullName(pchar)+", denizci ve maceraperest.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şeye mi ihtiyacın var?";
				link.l1 = LinkRandPhrase("Bana anlatacak ilginç bir şeyin var mı?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu görmek istemiştim. Hoşça kal!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha, tıpkı benim gibi. Denizci değilim ama macera tutkusu beni de buraya getirdi. Şimdi diğerleri gibi bu gemi mezarlığında çürüyüp gideceğim. Bu arada, adım Adolf Barbier.";
			link.l1 = "Seni tanımak güzeldi, Adolf. Hoşça kal.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Bana anlatacak ilginç bir şeyin var mı?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "Neden lanet olsun, izinsiz evime girdin?!";
			link.l1 = "Misafirine karşı pek misafirperver davranmıyorsun, Adolf. Seninle konuşmam gereken bir işim var.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "Tanımadığım insanlarla iş yapmam! Defol git!";
			link.l1 = "Öyle mi yani? Narvallarla iş yapacaksın ama benimle yapmayacaksın? Yazık...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "Ne diyorsun, soytarı? Narvallerle ne işin var? Seni dışarı atmadan önce gitmek için son şansın bu!";
			link.l1 = "Cesaretin yok... Şimdi beni iyi dinle! Amirali vurmak için kullanacağın stutzen nerede? Bunu bana kendi isteğinle mi söyleyeceksin, yoksa seni ikna etmek için daha ileri mi gitmem gerekecek?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "What? Are you mad, pal? I sold my stutzen - I don't have it anymore! And it's not your business whom I sold it to; I don't give a fuck what they do with it. And I'm not going to shoot anyone - admirals, generals, no one!. Do you understand me, fucker?";
			link.l1 = "Anladım ki sen bir yalancı ve katilsin, Adolf. Onu satmadığını, aslında kurtardığını biliyorum. Ayrıca borçlarını ödemek ve bu kulübeyi almak için yüklü bir para aldığını da biliyorum--";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "Bu para benim! Bunu ben kazandım! Ve stutzenimi sattım!";
			link.l1 = "Yalan söylüyorsun, Adolf. Narvaller seni Amirali vurman için tuttular. Stutzen'ini geri almak için sana para verdiler. Bu yeri de onlar finanse etti. Bu kapının arkasındaki baş bodoslama, Adalet Adası'nda Köpekbalığı'nın konutunun arka balkonunu vurabileceğin tek yer olduğunu benden daha iyi biliyorsun.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "Sen delirmişsin, dostum! Seni tımarhaneye kapatmak lazım! Sessile'in bu kulübeyi terk etmesini yarım yıldır bekliyorum--";
			link.l1 = "Yeter! Seni ve kamarayı arayacağım, stutzen'i bulacağım – ve başka kanıtlar da! – bundan eminim. Sonra birlikte Shark'ın yanına gideceğiz. O, gözlerinin içine bakıp gerçeği görecek.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "Ah, seni pislik herif! Eşyalarıma o deli pisliğin dokunmasına izin vermektense ölürüm daha iyi!";
			link.l1 = "Pekâlâ, o zaman. Eğer öldüysen, iznine ihtiyacım olmayacak.";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "Pekala, konuşalım. Ne bilmek istiyorsun?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Bana buradaki yerel klanlar hakkında ne anlatabilirsin?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Gemi halkasının dış kısmını keşfettin mi?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Adanın Küba ya da Anakarayla bir bağlantısı var mı?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Bir İspanyol denizcisi olan Ignacio Alvarado'nun güncesini buldum. Adayı büyük bir ayrıntıyla anlatmış, özellikle birkaç gemiden bahsetmiş: San Augustine, San Geronimo ve Tartarus. Hepsi de Betancourt'un filosuna aitti ve elli yıldan fazla bir süre önce ortadan kaybolmuşlardı.  Seferi araştırdım. Meğerse filoda bir de St. Anna adında dördüncü bir gemi varmış ve bu gemi filonun hazinesini taşıyormuş: bir yığın doblon! Dahası, gemilerin ambarlarında altın cevheri de varmış. Adayı bulmaya karar verdim.  Tanıdığım bir kaptanla anlaştım ve onun şilebiyle yelken açtık. Hikayenin nasıl bittiğini tahmin edersin: adayı bulduk, de Betancourt'un gemilerini, hatta torununu bile: Antonio de Betancourt. O günden beri buradayım.  Şilep kayalıklarda parçalandı, yol arkadaşım öldü, ben ve hayatta kalan birkaç kişi yüzerek buraya ulaşabildik. En kötüsü ise, aradığımı asla bulamadım – ne St. Anna'nın hazinesini, ne de altın cevherini.";
			link.l1 = "İlginç bir hikaye. Ben de Alvarado'nun kroniğini okudum.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "The Rivados are damned pagan scum. They're the offspring of negro slaves, brought here by de Betancourt from Africa. Even though they've learned how to use blades and muskets from us white folk, they're still savages.\nThe Narwhals are good people; smart, and decent fighters. They have outstanding craftsmen among them. I know a lot of them. Perhaps one day I'll join their clan.\nThe pirates are a pain in the arse - damn them! When they arrived, they captured our supplies and now dare to sell us our own food! Bastards, eh? Pity we don't have the numbers or skill to drive them away; we're stuck with the bloody lot of them.";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sure. A man has to make coin. Damn pirates demand gold, pesos or other valuables for the food. They sell it more cheaply to locals like me than to the clans, but it's no charity. Thank God there are plenty of ships on the outer ring to loot; a lot of them still remain untapped since their wreckage.\nAn interesting activity, but dangerous; you may fall into a flooded hold, break bones, get tangled in ropes, smashed by wooden beams or eaten by giant crabs - they often roam the wrecks out there.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ne yazık ki, öyle değil. Eskiden Küba'dan korsanlar ve kaçakçılar buraya sık sık gelir, erzak karşılığında altın ve ganimet takas eder, Narvaller de bazen kolonilere gitmek için ayrılırlarmış. Ama artık hepsi geçmişte kaldı. Şimdi kimse, dış halkadan geçip küçük ve dayanıksız teknelerle denize açılmaya cesaret edemiyor – fırtınalar onları paramparça eder, burada da daha iyi teknelerimiz yok.";
			link.l1 = "Ne yazık...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Orada ne yapıyorsun, ha? Hırsız!","Şuna bak! Daha arkamı döner dönmez, sandığımı yağmalamaya kalkıyorsun!","Sandıklarımı yağmalamaya mı karar verdin, ha? Bunu yanına bırakmam!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandıklarımı mı yağmalamaya karar verdin? Bunu yanına bırakmam!";
			link.l1 = "Lanet olası kız!";
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
			dialog.text = LinkRandPhrase("Dinle, silahını yerine koysan iyi olur. Beni tedirgin ediyor.","Biliyor musun, burada elinde bıçakla dolaşmak hoş karşılanmaz. Onu yerine koy.","Bak, şövalye gibi kılıçla dolaşmayı bırak, sana yakışmıyor. Onu yerine koy...");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.","Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni istiyorum.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekala.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol dostum, elinde öyle bir silahla dolaşmak beni tedirgin ediyor...","Yüzüme silah sallayan adamlardan hoşlanmam. Korkarım...");
				link.l1 = RandPhraseSimple("Anladım.","Onu kaldırıyorum.");
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
