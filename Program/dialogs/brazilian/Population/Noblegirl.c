//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Hm. Você está navegando sob a bandeira de "+NationNameGenitive(sti(pchar.nation))+", capitão. Não tenho vontade de falar com o inimigo do meu país. Hmph!";
					link.l1 = "Ah, sim. Um verdadeiro patriota...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("O que você quer de mim, "+GetAddress_Form(NPChar)+"? Não é adequado que um simples marinheiro converse com uma dama nobre, mas estou ouvindo você.","Ah, e o que um capitão tão corajoso quer de mim?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Não vou tomar muito do seu tempo, só queria perguntar...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("Preciso saber o que está acontecendo na sua colônia.","Preciso de algumas informações.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("A cidade inteira está em alerta – dom Fernando de Alamida, o inspetor real, chegou. Olha, já vi muita coisa por aqui, mas isso... Não é o luto que muda as pessoas, e sim como elas lidam com ele. Dizem que ele se transformou depois da morte do pai. Agora, não há servidor da Coroa mais incorruptível e... implacável em todo o Arquipélago.","Olhe só para o 'Santa Misericórdia'! Dizem que o próprio rei mandou construí-lo seguindo projetos especiais. E repare – não tem um arranhão sequer. Como se a própria Virgem Maria o protegesse. Mas ouvi uns boatos... talvez nem seja a Virgem, afinal.","Você sabe quantas vezes já tentaram matar Dom Fernando? Doze ataques em mar aberto – e isso só no último ano! Mas, com uma tripulação tão leal e bem treinada, e sob a proteção do Senhor – ele vai sobreviver ao décimo terceiro também!"),LinkRandPhrase("Você ficou sabendo? Don Fernando de Alamida chegou à nossa cidade, e dizem que ele está pelas ruas neste momento. Eu adoraria vê-lo com meus próprios olhos...","Um homem complicado, esse dom Fernando. Alguns dizem que ele é um salvador, limpando a Pátria da sujeira. Outros sussurram que algo se quebrou nele depois da morte do pai e que logo todos estaremos chorando. Mas vou te dizer uma coisa: não tema ele. Tema aqueles que o fizeram ser quem é.","Que homem bonito, esse dom Fernando! Mas sabe o que é estranho? Parece que ele não repara em ninguém. Só pensa em dever e serviço. Ouvi dizer que havia uma moça... mas depois de conversar com um padre, ele largou de vez os prazeres do mundo. Como se tivesse feito um voto."),RandPhraseSimple(RandPhraseSimple("Maldito inspetor! Enquanto ele está aqui – a cidade está morta. Sem comércio, sem diversão. Até respirar, parece, tem que ser mais devagar. E sabe o que é mais assustador? É assim em todo porto. Sempre igual. Sua Majestade Real não poderia ter inventado tortura pior pra todos nós!","Dom Fernando visitou o orfanato novamente. Faz doações generosas, reza por horas. Um homem tão digno deveria servir de exemplo para aqueles malditos ladrões de dinheiro!"),RandPhraseSimple("Ha! O 'santo' Fernando fechou todos os bordéis de novo. Mas deixa pra lá, logo ele vai embora e eles vão abrir de novo.","O insp... inspetor chegou, isso sim! Dom Fernando de Almeyda, ou, como é mesmo, Alamida! Tão importante que até o governador anda nas pontas dos pés perto dele. Dizem que ele olha nos seus olhos e enxerga todos os seus pecados de uma vez. Assustador!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Preciso repetir? Não quero que pensem que sou amigo de "+NationNameAblative(sti(pchar.nation))+"! Saia daqui ou vou chamar os guardas! Eles ficariam felizes em ter uma conversa com você.";
					link.l1 = "Tá bom, tá bom, calma. Eu já estou indo.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("O quê? Você de novo? Vá procurar outra pessoa pra conversar. Tem um monte de plebeus perambulando por aí, eles combinam mais com você. Agora preciso ir, hoje tem um banquete na residência do governador e meu penteado ainda não está pronto!","Não, agora você está sendo realmente irritante! Não entendeu ainda? Ou é lerdo mesmo?","Senhor, começo a suspeitar que o senhor não é só um idiota, mas também um canalha e um grosseirão. Aviso que vou chamar meu marido se não parar de me importunar com essas perguntas estúpidas!","Mais uma palavra e eu mando o comandante cuidar de você!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Entendi. Adeus.","Sim, sim, eu lembro, só esqueci de perguntar...","Você está me entendendo errado...","Calma, senhora, já estou indo embora...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("Certo, vamos ouvir.","Ah, tá bom. O que você quer?","Perguntas? Tudo bem, marinheiro, estou ouvindo.");
			link.l1 = LinkRandPhrase("Pode me contar as últimas fofocas desta cidade?","Aconteceu algo interessante por aqui ultimamente?","Alguma novidade do Caribe, minha senhora?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Você está maluco?! Você me assusta! Guarde sua arma ou vou avisar o comandante para mandar enforcá-lo no forte!","Você está louco?! Você me assusta! Guarde sua arma ou vou avisar o comandante para mandar enforcá-lo no forte!");
			link.l1 = LinkRandPhrase("Certo.","Como quiser.","Certo.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
