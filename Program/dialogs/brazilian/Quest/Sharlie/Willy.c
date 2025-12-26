// Вильям Патерсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Tem alguma coisa que você quer?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "Olá, Monsieur. Maldição, então é você quem causou toda essa confusão militar por aqui?!";
			link.l1 = TimeGreeting()+", senhor. Sim, foi o meu navio que fez o desembarque. Mas qual é o problema afinal? Quem é você? Um inglês, imagino?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "Um escocês, Monsieur. Capitão da Marinha Inglesa, William Paterson, e este é meu imediato e braço direito, Archibald Calhoun. O fato é que há um forte espanhol na selva. Minha missão é expulsar aqueles desgraçados do forte, que eles construíram perigosamente perto do território inglês.\nRecentemente, tentamos tomá-lo de assalto, mas os malditos conseguiram resistir apesar das baixas. Saí em busca de reforços e...";
			link.l1 = "No need for that now. I've completed your unfinished business; the jungle fort is empty. The Spanish commander, Diego de Montoya, is dead, and his squadron has been wiped out as well.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "Que tipo de vigilantismo é esse? Qual é a sua motivação para provocar uma ação militar dessas em território inglês?";
			link.l1 = "Permita-me lembrar, Capitão Paterson, que isto aqui não é Belize. Que posse inglesa? Toda essa confusão começou por causa de Dom Diego de Montoya e sua decisão irresponsável de me atacar, junto com meus navios.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "É... e por que motivo Dom Diego resolveu te atacar, hein, capitão?";
			link.l1 = "Ele e eu temos uma rixa antiga... Desde o dia em que o esquadrão que ele comandava atacou St. Pierre e, pouco depois, foi eliminado com a minha participação direta.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "Maldição! Eu precisava daquele venerável caballero vivo! Eu ia interrogá-lo para descobrir por que ele montou uma base militar na selva. Não podia ter sido à toa...";
			link.l1 = "Desculpe, mas ele não pode te contar nada agora. De qualquer forma, pode ser que haja soldados feridos da guarnição no forte. Será que algum deles pode conversar?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "Soldados... Ah, de que adianta esses cabeças-duras de baioneta!... Cadê o corpo do Don Diego? Ele podia estar com documentos importantes!";
			link.l1 = "Deixei Dom Diego no terreno do forte da armaria. Se você precisa tanto dele, pode encontrá-lo lá. Duvido que ele consiga fugir.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "Ah... e quem te pediu pra se meter nos assuntos dos outros... Você já me deu dor de cabeça demais...";
			link.l1 = "Capitão, não entendo por que está me repreendendo. Cumpri sua tarefa, coloquei meus próprios homens em combate, arrisquei minha vida, e mesmo assim você está insatisfeito. Agora só precisa informar Port Royal sobre o sucesso da missão e resolver seus assuntos. Garanto que não vou reivindicar nenhum mérito pela sua glória.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "Querer os méritos? O que você quer dizer com glória?! Você realmente não entende... Ah, chega. Adeus, senhor.";
			link.l1 = "Tudo de bom pra você também!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\English\sharlie\Willie Paterson.wav");
			dialog.text = "Rapaz, as fofocas não mentiram quando disseram que você tem nove vidas como um gato! "+TimeGreeting()+", Monsieur de Maure. Você não parece muito bem...";
			link.l1 = TimeGreeting()+", Sr. Paterson. Preciso admitir, você e seu amigo Archibald interpretaram seus papéis e me enganaram direitinho. Malditos sejam! Eu nem percebi o que estava acontecendo...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "Hey, don't swear before the gates of the Holy Land. You didn't see it coming? I am flattered: I have fooled one of the most famous intriguers of the archipelago. The diary idea was brilliant, don't you think?\nI had to lure you to some obscure place; killing you in the open would be a scandal, you are a close friend of Philippe de Poincy, am I correct? Now you are going to disappear without a trace and no one will ever know how.";
			link.l1 = "Então, tudo o que o Calhoun me contou... era mentira?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "Not at all. I really did find poor Archibald at this place. He didn't write any memoirs, though; the diary you found in his room was written at my request, especially for you, Monsieur de Maure.\nI have been keeping an eye on you since we met at Cape Catoche. It was you who took the map of Two Appearances from Don Diego's corpse, wasn't it? Don't deny it, I know it was you.";
			link.l1 = "Você também sabe sobre o Guardião da Verdade?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "Que pergunta idiota. É claro que tenho. E sei que você também está com a Garra do Chefe. Em breve, você vai devolver esses itens, que não te pertencem.";
			link.l1 = "Fico feliz que você não vacile como Dom Diego. Eu valorizo honestidade e franqueza. Pelo que entendi, você está com a bússola, a Flecha do Caminho?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "Hahaha! Bem, vamos ser sinceros até o fim... O senhor realmente acredita, meu caro, que eu sou tão tolo quanto você e Dom Diego, a ponto de carregar um objeto tão valioso comigo? A bússola está na Jamaica, e nem sequer em Port Royal, mas em um lugar onde ninguém jamais pensaria em procurar, e trancada a sete chaves. Mas essa informação não vai lhe servir de nada.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "Pelo que entendi, o senhor já me deu como morto, Sr. Paterson? Pois saiba que ainda me resta uma vida!… Onde estão meus oficiais?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "Pelo que entendi, o senhor já me enterrou, Sr. Paterson? Pois saiba que ainda resta uma vida a este gato!..";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "Preocupado com sua amiga, capitão? Sua mulher está ali nos arbustos, com um buraco na testa. Ela abriu caminho pra você, e logo logo você vai se juntar a ela. Tenho que admitir, ela era bem bonita! Espero que tenha aproveitado com ela mais de uma vez?";
				link.l1 = "C'est um filho da puta! Você vai pagar por isso, seu desgraçado?!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "Seus oficiais abriram caminho para você, Monsieur de Maure. Eles estão caídos ali nos arbustos. Logo você vai se juntar a eles.";
				link.l1 = "Veremos sobre isso!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "Vamos garantir que seja mesmo o seu último.";
			link.l1 = "Vamos ver isso!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "Você me faz rir. Um contra um batalhão inteiro! Chega de conversa... Apontem os mosquetes! Fogo!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
